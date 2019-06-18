# Introduction

This repository contains a code-base that I find useful for isolating the embedded applications I write from the characteristics that vary between hardware systems and microcontroller architectures. 

Each module is coded using *dependency-injection*, which allows compiling, testing, and integrating each module independently; making it more portable and modular. The idea is basically to write the modules by programming towards a generic interface whose concrete implementation can vary from one application (or running environment) to another.

Most modules implement a base data-structure that carries with the information of the module dependencies and its attributes. For example, the module `MyModule` defines the data structure `MyModule_t`. Also, inside `MyModule_t`, the user must specify a concrete implementation of the "dependency `Z`" for the module to be integrated into an application. In this way, the user can separate the dependency implementation, the module itself, and the application so that they can be maintained/changed independently. 

In each module, the header `MyMoudule.h` contains the public declarations, while the behavioral implementation is inside the correspondent source file `MyModule.c`. Often, the source file contains only standard-C-library functions and calls to the dependencies (using the generic interfaces available in the module data-structure definition).

**@ MyModule/MyModule.h**
```C
/*...*/

typedef enum MyModule_eRetVal
{
    MY_MODULE__C_SUCCESS,
    MY_MODULE__C_FAIL
} MyModule_tRetVal;

struct MyModule_s;

typedef uint32_t (* MyModule_tCallback)(struct MyModule_s * iMyModuleInstance);

typedef struct Mod_sInterfaceToDependencyZ
{
    Mod_tCallback fActionA;
    Mod_tCallback fActionB;
} Mod_tInterfaceToDependencyZ;

typedef struct MyModule_s
{
    uint32_t vAttributeX;
    uint32_t vAttributeY;
    const Mod_tInterfaceToDependencyZ * vInterfaceToDependencyZ;
} MyModule_t;

/* Application interface */
MyModule_tRetVal MyModule_fBehaviorM(MyModule_t * iMyModuleInstance);
MyModule_tRetVal MyModule_fBehaviorN(MyModule_t * iMyModuleInstance);

/* To be called in the dependency module when the action C happens. */
MyModule_tRetVal MyModule_fNotifyAboutActionC(MyModule_t * iMyModuleInstance);

/*...*/
```

**@ MyModule/MyModule.c**
```C
/*...*/

MyModule_tRetVal MyModule_fBehaviorM(MyModule_t * iMyModuleInstance)
{
    /* Here, action A from Dependency Z is invoked */
    if(iMyModuleInstance->vInterfaceToDependencyZ->fActionA(iMyModuleInstance))
        return MY_MODULE__C_FAIL;

    /* ... do stuff ...*/

    return MY_MODULE__C_SUCCESS;
}

/*...*/
```

**@ ConcreteZ.c**
```C
#include "MyModule/MyModule.h"

uint32_t ConcreteZ_fActionA(MyModule_t * iMyModuleInstance);
uint32_t ConcreteZ_fActionB(MyModule_t * iMyModuleInstance);

const Mod_tInterfaceToDependencyZ ConcreteZInterface = {
    .fActionA = ConcreteZ_fActionA;
    .fActionB = ConcreteZ_fActionB;
};

/* ... Concrete definitions of ConcreteZ_fActionA and ConcreteZ_fActionB ...*/
```

**@ ConcreteZ.h**
```C
#include "MyModule/MyModule.h"

extern const Mod_tInterfaceToDependencyZ ConcreteZInterface;
```

**@ Application.c**
```C
#include "MyModule/MyModule.h"
#include "ConcreteZ.h"

int main()
{
    MyModule_t vMyModuleInstance = {
        .vAttributeX = 0,
        .vAttributeY = 0,
        .vInterfaceToDependencyZ = &ConcreteZInterface;
    };

    if (MyModule_fBehaviorM(&vMyModuleInstance) == MY_MODULE__C_SUCCESS)
        return 0;
    else
        return 1;
}

```

Since this code is oriented towards embedded applications, I recommend to initialize the module data-structures statically (avoiding dynamic memory allocation). 

The code-base includes modules that are common to embedded applications such as *general-purpose-IO*, *counters*, *queues*, etc. 

Please feel free to comment, ask questions, or give me advice on how to improve the code. 

# How to build

To build the project in a Linux system:

1. Clone the repository.
2. Run `cmake .` to generate the makefiles.
3. Run `make`.

If the latest command runs successfully, it should create the `lib` and `bin` directories. Inside the `lib` directory, you can find the archive files containing the functions of each module. The `bin` directory contains the executable tests, which require Linux environment to run (they use utilities such as *signals*, *threads*, *process-control tools*, and etcetera). 

If you want to build using a cross-compiler, then you have to set up the toolchain (compiler, archiver, linker, and etcetera) in the `CMakeLists.txt` file. 

# How to clean the working directory

Run the `./clean.sh` script. It deletes all CMake-generated files, together with the `bin`, `out`, and `include` directories that are created during the building process.
