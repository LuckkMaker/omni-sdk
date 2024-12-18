## Example Description
This example is a i2c eeprom read/write example.

## Overview
The example demonstrates how to read and write data to an I2C EEPROM. The example uses the I2C driver to communicate with the EEPROM. The example reads and writes data to the EEPROM and verifies the data read from the EEPROM. Include the following functions in the example:

- `eeprom_init()`: Initializes the I2C driver and the EEPROM.
- `eeprom_write_byte()`: Writes a byte to the EEPROM.
- `eeprom_write_page()`: Writes a page of data to the EEPROM.
- `eeprom_read_random()`: Reads a byte from the EEPROM at a random address.
- `eeprom_read_sequential()`: Reads a length of data from the EEPROM sequentially.

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
