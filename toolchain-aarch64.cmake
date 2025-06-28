# Toolchain file for cross-compiling to aarch64 (ARM64) Linux
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Specify the cross compiler
set(CMAKE_C_COMPILER aarch64-unknown-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-unknown-linux-gnu-g++)

# Set the sysroot
# You can set this via environment variable: export IMX_SYSROOT=/path/to/imx-sysroot
# Or pass it to cmake: -DIMX_SYSROOT=/path/to/imx-sysroot
if(DEFINED IMX_SYSROOT)
    set(CMAKE_SYSROOT ${IMX_SYSROOT})
elseif(DEFINED ENV{IMX_SYSROOT})
    set(CMAKE_SYSROOT $ENV{IMX_SYSROOT})
else()
    message(FATAL_ERROR "IMX_SYSROOT not set. Please set IMX_SYSROOT environment variable or pass -DIMX_SYSROOT=/path/to/sysroot to cmake")
endif()

# Set compiler flags
set(CMAKE_C_FLAGS "-mcpu=cortex-a35 -O2 -Wall" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "-mcpu=cortex-a35 -O2 -Wall -std=c++17" CACHE STRING "" FORCE)

# Search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# Search for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
