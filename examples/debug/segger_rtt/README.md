## Example Description
This example is a SEGGER RTT example that demonstrates how to use segger rtt for logging.

## Overview
The segger rtt example initializes the segger rtt module and logs messages to the terminal. It includes:

- SEGGER RTT initialization
- Logging messages to the terminal

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
