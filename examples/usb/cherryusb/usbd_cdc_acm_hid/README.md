## Example Description
This example is shows how to implement a USB composite device with HID and CDC ACM interfaces.

## Overview
The USB CDC ACM HID example provides a USB composite device with HID and CDC ACM. It includes:

- Initialization of USB hardware
- Functions for sending and receiving data

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
