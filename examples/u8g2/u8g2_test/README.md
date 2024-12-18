## Example Description
This example is a u8g2 test example. It demonstrates how to use the u8g2 library to display text and graphics on an OLED display.

## Overview
The u8g2 test example provides a simple starting point for creating new examples. It includes:

- A basic directory structure
- A CMakeLists.txt file
- prj.conf file for configuration in Kconfig
- svd file and vscode launch.json for debugging

## How to use example
### Kconfig configuration
If using the 'ninja' generator, you can use the following command to configure the project:
```bash
ninja -C build menuconfig
```

If using the 'MinGW Makefiles' generator, you can use the following command to configure the project:
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
