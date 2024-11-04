## Example Description
This example shows how to use implement a console using UART communication.

## Overview
The UART console example provides a simple interface for sending and receiving data over a serial connection. It includes:

- Initialization of UART hardware
- Functions for sending and receiving data
- A simple command-line interface for interacting with the system

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
