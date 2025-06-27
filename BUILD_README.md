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

If you need to change the cross-compiler settings, edit `toolchain-aarch64.cmake`:
- Compiler path
- Sysroot location  
- CPU flags
- Optimization level

Then run `./build-arm.sh` to reconfigure and rebuild.