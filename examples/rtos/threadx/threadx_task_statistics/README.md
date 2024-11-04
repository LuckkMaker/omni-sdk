## Example Description
This example is a ThreadX template for omni drivers.

## Overview
The threadx example provides a simple starting point for creating new examples. It includes:

- A basic directory structure
- A CMakeLists.txt file
- prj.conf file for configuration in Kconfig
- svd file and vscode launch.json for debugging
- Threadx configuration
- Threadx tasks

## How to use example
### Kconfig configuration
```bash
cd build
make menuconfig
```

### Build and Flash
```bash
mkdir build
cmake -G "MinGW Makefiles" -B build -DCMAKE_BUILD_TYPE=Debug
make -C build -j 10
```

## Contributing

Contributions are welcome! Please submit a pull request or open an issue on the [omni-sdk](https://github.com/LuckkMaker/omni-sdk).
