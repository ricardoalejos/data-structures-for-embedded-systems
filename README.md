# Introduction

This repository contains a code-base that I find useful for isolating the embedded applications I write from the characteristics that vary between hardware systems and microcontroller architectures. 

Each module is coded using *dependency-injection*, which allows compiling, testing, and integrating each module independently; making it more portable and modular. The idea is basically to write the modules by programming towards a generic interface whose concrete implementation can vary from one application (or running environment) to another.

The code-base includes modules that are common to embedded applications such as *general-purpose-IO*, *counters*, *queues*, etc. 

Please feel free to comment, ask questions, or give me advice on how to improve the code. 

# How to build

To build the project in a Linux system:

1. Clone the repository.
2. Run `cmake .` to generate the makefiles.
3. Run `make`.

If the latest command runs successfully, it should create the `lib` and `bin` directories. Inside the `lib` directory, you can find the archive files containing the functions of each module. The `bin` directory contains the executable tests, which require Linux environment to run (they use utilities such as *signals*, *threads*, *process-control tools*, and etcetera). 

If you want to build using a cross-compiler, then you have to set up the toolchain (compiler, archiver, linker, and etcetera) in the `CMakeLists.txt` file. 

