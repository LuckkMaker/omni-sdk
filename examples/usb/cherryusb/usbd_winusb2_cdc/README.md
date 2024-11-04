## Example Description
This example is shows how to implement a USB composite device with WinUSB and CDC ACM interfaces.

## Overview
The USB WinUSB2 CDC example provides a USB composite device with WinUSB and CDC ACM. It includes:

- Initialization of USB hardware
- Functions for sending and receiving data

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
