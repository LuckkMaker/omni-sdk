## Example Description
This example is shows how to use RAM as storage for USB MSC.

## Overview
The USB MSC RAM example provides a USB MSC device that uses RAM as storage.

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
