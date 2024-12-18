/**
  * @file    main.c
  * @author  LuckkMaker
  * @brief   Main program body
  * @attention
  *
  * Copyright (c) 2024 LuckkMaker
  * All rights reserved.
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *     http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
#include <omni.h>

#define LED_PIN GET_PIN(E, 5)

#define AT24C01_SIZE     128
#define AT24C02_SIZE     256
#define AT24C04_SIZE     512
#define AT24C08_SIZE     1024
#define AT24C16_SIZE     2048
#define AT24C32_SIZE     4096
#define AT24C64_SIZE     8192
#define AT24C128_SIZE    16384
#define AT24C256_SIZE    32768

#define EEPROM_ADDR 0x50
#define EEPROM_TOTAL_SIZE AT24C256_SIZE
/** Page size of EEPROM
 *  AT24C01 has 8-byte page size
 *  AT24C02 has 8-byte page size
 *  AT24C04 has 16-byte page size
 *  AT24C08 has 16-byte page size
 *  AT24C16 has 16-byte page size
 *  AT24C32 has 32-byte page size
 *  AT24C64 has 32-byte page size
 *  AT24C128 has 64-byte page size
 *  AT24C256 has 64-byte page size
*/
#define EEPROM_PAGE_SIZE 64
#define EEPROM_PAGE_COUNT (EEPROM_TOTAL_SIZE / EEPROM_PAGE_SIZE)

#define EEPROM_TEST_DATA_SIZE 256

#define I2C_EEPROM_MAX_TRIALS       300

uint8_t eeprom_tx_data[EEPROM_TEST_DATA_SIZE];
uint8_t eeprom_rx_data[EEPROM_TEST_DATA_SIZE];

static volatile uint32_t i2c1_event;

static void i2c1_event_callback(uint32_t event);

void eeprom_init(void);
int eeprom_write_byte(uint16_t addr, uint8_t data);
int eeprom_write_page(uint16_t addr, uint8_t *data, uint16_t len);
int eeprom_read_random(uint16_t addr, uint8_t *data);
int eeprom_read_sequential(uint16_t addr, uint8_t *data, uint32_t len);

/** 
 * @brief The application entry point.
 * 
 * @return int 
 */
int main(void) {
    setup();

    eeprom_init();

    timer_driver.delay_ms(100);

    // Fill the data
    for (uint16_t i = 0; i < EEPROM_TEST_DATA_SIZE; i++) {
        eeprom_tx_data[i] = (uint16_t)i;
        eeprom_rx_data[i] = 0;
    }

    // Write byte to EEPROM
    eeprom_write_byte(10, 0x55);

    // Delay a write cycle
    timer_driver.delay_ms(5);

    // Read byte from EEPROM
    eeprom_read_random(10, eeprom_rx_data);

    // Write page to EEPROM
    eeprom_write_page(0, eeprom_tx_data, EEPROM_TEST_DATA_SIZE);

    // Sequential read from EEPROM
    eeprom_read_sequential(0, eeprom_rx_data, EEPROM_TEST_DATA_SIZE);

    for (uint16_t i = 0; i < EEPROM_TEST_DATA_SIZE; i++) {
        if (eeprom_tx_data[i] != eeprom_rx_data[i]) {
            // Error
            while (1) {
            }
        }
    }

    while (1) {
        // Do something
        gpio_driver.toggle(LED_PIN);
        timer_driver.delay_ms(500);
    }
}

/**
 * @brief Setup the application
 */
void setup(void) {
    gpio_driver_config_t gpio1_config = {
        .mode = GPIO_MODE_PP_OUTPUT,
        .pull = GPIO_PULL_NONE,
        .speed = GPIO_SPEED_LEVEL_HIGH,
        .level = GPIO_LEVEL_LOW,
    };

    gpio_driver.init(LED_PIN, &gpio1_config);
}

/**
 * @brief Initialize the EEPROM
 */
void eeprom_init(void) {
    i2c_driver_config_t i2c1_config = {
        .mode = I2C_MODE_I2C,
        .bus_speed = I2C_BUS_SPEED_STANDARD,
        .own_addr_bits = I2C_ADDR_BITS_7,
        .own_addr = 0x00,
        .event_cb = i2c1_event_callback,
    };

    i2c_driver.init(I2C_NUM_1, &i2c1_config);
}

/**
 * @brief Write a byte to EEPROM
 *
 * @param addr The data address
 * @param data The data
 * @return The status of the operation
 */
int eeprom_write_byte(uint16_t addr, uint8_t data) {
    // Clear the event
    i2c1_event = 0;

#if (EEPROM_TOTAL_SIZE > AT24C16_SIZE)
    i2c_driver.write(I2C_NUM_1, EEPROM_ADDR, addr, I2C_MEM_ADDR_SIZE_16, &data, 1);
#else
    i2c_driver.write(I2C_NUM_1, EEPROM_ADDR, addr, I2C_MEM_ADDR_SIZE_8, &data, 1);
#endif /* (EEPROM_TOTAL_SIZE > AT24C16_SIZE) */

    while (!(i2c1_event & I2C_EVENT_TRANSFER_COMPLETE)) {
        // Do something
    }
    if ((i2c1_event & I2C_EVENT_TRANSFER_INCOMPLETE) != 0U) {
        // Transfer incomplete
        return -1;
    }

    return 0;
}

/**
 * @brief Write a page to EEPROM
 *
 * @param addr The data address
 * @param data The data buffer
 * @param len The data length
 * @return The status of the operation
 */
int eeprom_write_page(uint16_t addr, uint8_t *data, uint16_t len) {
    uint16_t mem_addr = addr;
    uint16_t num = len;
    uint8_t *p_data = data;
    uint16_t page_offset;
    uint16_t page_remain;

    page_offset = mem_addr % EEPROM_PAGE_SIZE;

    while (num > 0) {
        page_remain = EEPROM_PAGE_SIZE - page_offset;
        page_remain = MIN(num, page_remain);

        // Write the current page
        i2c1_event = 0;
#if (EEPROM_TOTAL_SIZE > AT24C16_SIZE)
        i2c_driver.write(I2C_NUM_1, EEPROM_ADDR, mem_addr, I2C_MEM_ADDR_SIZE_16, p_data, page_remain);
#else
        i2c_driver.write(I2C_NUM_1, EEPROM_ADDR, mem_addr, I2C_MEM_ADDR_SIZE_8, p_data, page_remain);
#endif /* (EEPROM_TOTAL_SIZE > AT24C16_SIZE) */

        while (!(i2c1_event & I2C_EVENT_TRANSFER_COMPLETE)) {
            // Do something
        }
        if ((i2c1_event & I2C_EVENT_TRANSFER_INCOMPLETE) != 0U) {
            // Transfer incomplete
            return -1;
        }

        while (i2c_driver.is_device_ready(I2C_NUM_1, EEPROM_ADDR, I2C_EEPROM_MAX_TRIALS) != OMNI_OK) {
            // Do something
        }

        mem_addr += page_remain;
        p_data += page_remain;
        num -= page_remain;
    }

    return 0;
}

/**
 * @brief Read data from EEPROM by random mode
 *
 * @param addr The data address
 * @return The data
 */
int eeprom_read_random(uint16_t addr, uint8_t *data) {
    // Clear the event
    i2c1_event = 0;
#if (EEPROM_TOTAL_SIZE > AT24C16_SIZE)
    i2c_driver.read(I2C_NUM_1, EEPROM_ADDR, addr, I2C_MEM_ADDR_SIZE_16, data, 1U);
#else
    i2c_driver.read(I2C_NUM_1, EEPROM_ADDR, addr, I2C_MEM_ADDR_SIZE_8, data, 1U);
#endif /* (EEPROM_TOTAL_SIZE > AT24C16_SIZE) */

    while (!(i2c1_event & I2C_EVENT_TRANSFER_COMPLETE)) {
        // Do something
    }
    if ((i2c1_event & I2C_EVENT_TRANSFER_INCOMPLETE) != 0U) {
        // Transfer incomplete
        return -1;
    }

    return 0;
}

/**
 * @brief Read data from EEPROM by sequential mode
 *
 * @param addr The data address
 * @param data The data buffer
 * @param len The data length
 * @return The status of the operation
 */
int eeprom_read_sequential(uint16_t addr, uint8_t *data, uint32_t len) {
    // Clear the event
    i2c1_event = 0;
#if (EEPROM_TOTAL_SIZE > AT24C16_SIZE)
    i2c_driver.read(I2C_NUM_1, EEPROM_ADDR, addr, I2C_MEM_ADDR_SIZE_16, data, len);
#else
    i2c_driver.read(I2C_NUM_1, EEPROM_ADDR, addr, I2C_MEM_ADDR_SIZE_8, data, len);
#endif /* (EEPROM_TOTAL_SIZE > AT24C16_SIZE) */

    while (!(i2c1_event & I2C_EVENT_TRANSFER_COMPLETE)) {
        // Do something
    }
    if ((i2c1_event & I2C_EVENT_TRANSFER_INCOMPLETE) != 0U) {
        // Transfer incomplete
        return -1;
    }

    return 0;
}

/**
 * @brief I2C1 event callback
 * 
 * @param event 
 */
static void i2c1_event_callback(uint32_t event) {
    i2c1_event |= event;

    if (event & I2C_EVENT_TRANSFER_COMPLETE) {
        // Do something
    }
}
