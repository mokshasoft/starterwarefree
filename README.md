# starterwarefree
Unofficial repo of TI StarterWare

Improvements over official repo:
- More than 30x faster rebuild. For instance, rebuilding the BeagleBone gpio app;
makefile (3.4 s), CMake with Ninja generator (0.01 s)
- 5x times faster clean builds. BeagleBone gpio app;
makefile (3.4 s), CMake with Ninja generator (0.72 s)
- Builds are incremental
- At least 5x easier build files. Subjective, but check:
```
git diff a2422cf:build/armv7a/gcc/am335x/beaglebone/gpio/makefile 4a75983:examples/beaglebone/gpio/CMakeLists.txt
```

## Building

Run the following commands to build the BeagleBone gpio example app:
```
mkdir my_build
cd my_build
cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=../build/CMake/gcc.cmake ..
ninja gpio
```
Build all BeagleBone example apps:
```
ninja beaglebone
```
## Forked
Since I have no SourceForge account and want to experiment. Forked from https://sourceforge.net/projects/starterwarefree/

## Experiments
- bare-metal apps and unikernel experiments using Idris, https://www.idris-lang.org/
