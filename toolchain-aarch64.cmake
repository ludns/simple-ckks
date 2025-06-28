# Toolchain file for cross-compiling to aarch64 (ARM64) Linux
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Specify the cross compiler
set(CMAKE_C_COMPILER aarch64-unknown-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-unknown-linux-gnu-g++)

# Set the sysroot
set(CMAKE_SYSROOT $ENV{HOME}/dev/gp/imx-sysroot)

# Set compiler flags
set(CMAKE_C_FLAGS "-mcpu=cortex-a35 -O2 -Wall" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "-mcpu=cortex-a35 -O2 -Wall -std=c++17" CACHE STRING "" FORCE)

# Search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# Search for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
