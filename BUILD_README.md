# Build Scripts Guide

This project includes several build scripts to make compilation easier:

## Scripts Overview

### `./build.sh`
Builds the project for your native platform (macOS/Linux).
- Cleans the build directory
- Configures CMake with Release mode
- Builds all targets (library, tests, and demo)
- Generates compile_commands.json for IDE support

### `./build-arm.sh`
Cross-compiles the project for ARM64 (aarch64) Linux.
- Requires IMX_SYSROOT environment variable to be set
- Cleans the build-arm directory
- Configures CMake with the ARM toolchain
- Builds only the ckks_demo executable
- Creates a stripped version for smaller size
- Shows the copy command for deployment

### `./quick-build-arm.sh`
Quickly rebuilds ARM binary without reconfiguring.
- Use this when you've only changed source files
- Much faster than full rebuild
- Automatically falls back to full build if needed

### `./clean.sh`
Removes all build artifacts from both native and ARM builds.

## Usage Examples

### Full native build:
```bash
./build.sh
./build/tests           # Run tests
./build/ckks_demo      # Run demo
```

### Full ARM build:
```bash
# First set the sysroot path
export IMX_SYSROOT=/path/to/imx-sysroot

./build-arm.sh
# Copy to board:
scp build-arm/ckks_demo user@board-ip:/path/
```

### After changing source code only:
```bash
./quick-build-arm.sh   # Fast rebuild for ARM
```

### After changing CMakeLists.txt:
```bash
./build-arm.sh         # Full rebuild needed
```

### Clean everything:
```bash
./clean.sh
```

## Customizing the ARM Build

### Setting the Sysroot

First, you need to create a sysroot from your target board:

1. **Create sysroot on the board**:
   ```bash
   ssh root@your-board-ip
   tar czf /tmp/imx-sysroot.tar.gz /usr/include /usr/lib /lib
   ```

2. **Copy to development machine**:
   ```bash
   scp root@your-board-ip:/tmp/imx-sysroot.tar.gz .
   mkdir -p ~/imx-sysroot
   tar xzf imx-sysroot.tar.gz -C ~/imx-sysroot
   ```

3. **Configure the build** - two options:

   a. **Environment variable** (recommended):
   ```bash
   export IMX_SYSROOT=~/imx-sysroot
   ./build-arm.sh
   ```

   b. **CMake parameter**:
   ```bash
   cmake -B build-arm -S . -DIMX_SYSROOT=~/imx-sysroot -DCMAKE_TOOLCHAIN_FILE=toolchain-aarch64.cmake
   make -C build-arm ckks_demo
   ```

### Other Customizations
If you need to change the cross-compiler settings, edit `toolchain-aarch64.cmake`:
- Compiler path
- CPU flags
- Optimization level

Then run `./build-arm.sh` to reconfigure and rebuild.