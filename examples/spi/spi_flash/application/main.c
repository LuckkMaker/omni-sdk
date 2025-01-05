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

// STM32H750VB PA10
// STM32H743II PB1
// STM32F411CE PC13
// STM32F407IG PE5
#define LED_PIN GET_PIN(E, 5)

#define SPI_CS_PIN GET_PIN(F, 5)
#define FLASH_SPI_NUM SPI_NUM_1

/**
 * @brief W25QXX device ID
 */
#define W25Q16_DEVICE_ID                        0xEF14U
#define W25Q32_DEVICE_ID                        0xEF15U
#define W25Q64_DEVICE_ID                        0xEF16U
#define W25Q128_DEVICE_ID                       0xEF17U
#define W25Q256_DEVICE_ID                       0xEF18U

/**
 * @brief W25QXX status register 1
 */
#define W25QXX_SR1_BUSY                         0x01U
#define W25QXX_SR1_WEL                          0x02U
#define W25QXX_SR1_BP0                          0x04U
#define W25QXX_SR1_BP1                          0x08U
#define W25QXX_SR1_BP2                          0x10U
#define W25QXX_SR1_TB                           0x20U
#define W25QXX_SR1_SEC                          0x40U
#define W25QXX_SR1_SRP0                         0x80U

/**
 * @brief W25QXX status register 2
 */
#define W25QXX_SR2_SRL                          0x01U
#define W25QXX_SR2_QE                           0x02U
#define W25QXX_SR2_LB1                          0x08U
#define W25QXX_SR2_LB2                          0x10U
#define W25QXX_SR2_LB3                          0x20U
#define W25QXX_SR2_CMP                          0x40U
#define W25QXX_SR2_SUS                          0x80U

/**
 * @brief W25QXX instructions table 1
 */
#define W25QXX_INS_WRITE_ENABLE                 0x06U
#define W25QXX_INS_WRITE_DISABLE                0x04U
#define W25QXX_INS_READ_STATUS_REG1             0x05U
#define W25QXX_INS_READ_STATUS_REG2             0x35U
#define W25QXX_INS_READ_STATUS_REG3             0x15U
#define W25QXX_INS_WRITE_STATUS_REG1            0x01U
#define W25QXX_INS_WRITE_STATUS_REG2            0x31U
#define W25QXX_INS_WRITE_STATUS_REG3            0x11U
#define W25QXX_INS_READ_DATA                    0x03U
#define W25QXX_INS_FAST_READ_DATA               0x0BU
#define W25QXX_INS_PAGE_PROGRAM                 0x02U
#define W25QXX_INS_BLOCK_ERASE                  0xD8U
#define W25QXX_INS_SECTOR_ERASE                 0x20U
#define W25QXX_INS_CHIP_ERASE                   0xC7U
#define W25QXX_INS_POWER_DOWN                   0xB9U
#define W25QXX_INS_RELEASE_POWER_DOWN           0xABU
#define W25QXX_INS_DEVICE_ID                    0xABU
#define W25QXX_INS_MANUFACTURE_ID               0x90U
#define W25QXX_INS_JEDEC_ID                     0x9FU
#define W25QXX_INS_UNIQUE_ID                    0x4BU
#define W25QXX_INS_READ_SFDP_REG                0x5AU
#define W25QXX_INS_ERASE_SECURITY_REG           0x44U
#define W25QXX_INS_PROGRAM_SECURITY_REG         0x42U
#define W25QXX_INS_READ_SECURITY_REG            0x48U
#define W25QXX_INS_GLOBAL_BLOCK_LOCK            0x7EU
#define W25QXX_INS_GLOBAL_BLOCK_UNLOCK          0x98U
#define W25QXX_INS_READ_BLOCK_LOCK              0x3DU
#define W25QXX_INS_INDIVIDUAL_BLOCK_LOCK        0x36U
#define W25QXX_INS_INDIVIDUAL_BLOCK_UNLOCK      0x39U
#define W25QXX_INS_ERASE_PROGRAM_SUSPEND        0x75U
#define W25QXX_INS_ERASE_PROGRAM_RESUME         0x7AU
#define W25QXX_INS_ENABLE_RESET                 0x66U
#define W25QXX_INS_RESET_DEVICE                 0x99U

/**
 * @brief W25QXX instructions table 2
 */
#define W25QXX_INS_FAST_READ_DUAL               0x3BU
#define W25QXX_INS_FAST_READ_DUAL_IO            0xBBU
#define W25QXX_INS_FAST_READ_QUAD               0x6BU
#define W25QXX_INS_FAST_READ_QUAD_IO            0xEBU
#define W25QXX_INS_MANUFACTURE_ID_DUAL          0x92U
#define W25QXX_INS_MANUFACTURE_ID_QUAD          0x94U
#define W25QXX_INS_PAGE_PROGRAM_QUAD            0x32U

/**
 * @brief Flash information
 */
typedef struct {
    uint32_t device_id;     /**< Device ID */
    uint32_t capacity;      /**< Capacity */
    uint32_t sector_size;   /**< Sector size */
} flash_info_t;

static volatile uint32_t spi1_event;

flash_info_t flash_info;

static void spi1_event_callback(uint32_t event);

int flash_init(flash_info_t *flash);
void flash_read_device_id(flash_info_t *flash);
void flash_chip_select(void);
void flash_chip_deselect(void);
int flash_write_enable(void);
int flash_wait_for_write_complete(void);

/**
 * @brief The application entry point.
 * 
 * @return int 
 */
int main(void) {
    setup();

    flash_init(&flash_info);

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
    driver_init();

    gpio_driver_config_t gpio1_config = {
        .mode = GPIO_MODE_PP_OUTPUT,
        .pull = GPIO_PULL_NONE,
        .speed = GPIO_SPEED_LEVEL_HIGH,
        .level = GPIO_LEVEL_LOW,
    };
    gpio_driver.init(LED_PIN, &gpio1_config);

    gpio_driver_config_t spi_cs_gpio_config = {
        .mode = GPIO_MODE_PP_OUTPUT,
        .pull = GPIO_PULL_NONE,
        .speed = GPIO_SPEED_LEVEL_HIGH,
        .level = GPIO_LEVEL_HIGH,
    };
    gpio_driver.init(SPI_CS_PIN, &spi_cs_gpio_config);
}

/**
 * @brief Initialize the external flash
 *
 * @param flash Flash information
 * @return operation status
 */
int flash_init(flash_info_t *flash) {
    spi_driver_config_t spi1_config = {
        .option = SPI_OP_MODE_MASTER | \
                  SPI_OP_DIR_LINES_DUAL | \
                  SPI_OP_CPOL_HIGH | \
                  SPI_OP_CPHA_2EDGE | \
                  SPI_OP_DATA_SIZE_SET(8U) | \
                  SPI_OP_BIT_ORDER_MSB | \
                  SPI_OP_SLAVE_SEL_SOFT | \
                  SPI_OP_PROTOCOL_MOTOROLA,
        .frequency = 22000000,
        .event_cb = spi1_event_callback,
    };

    spi_driver.init(FLASH_SPI_NUM, &spi1_config);

    flash_read_device_id(flash);

    switch (flash->device_id) {
        case W25Q16_DEVICE_ID:
            flash->capacity = MB(2);
            flash->sector_size = KB(4);
            break;

        case W25Q32_DEVICE_ID:
            flash->capacity = MB(4);
            flash->sector_size = KB(4);
            break;

        case W25Q64_DEVICE_ID:
            flash->capacity = MB(8);
            flash->sector_size = KB(4);
            break;

        case W25Q128_DEVICE_ID:
            flash->capacity = MB(16);
            flash->sector_size = KB(4);
            break;

        case W25Q256_DEVICE_ID:
            flash->capacity = MB(32);
            flash->sector_size = KB(4);
            break;

        default:
            return -1;
    }

    return 0;
}

/**
 * @brief Read the device ID of the flash
 * 
 * @param flash Flash information
 */
void flash_read_device_id(flash_info_t *flash) {
    uint8_t tx_data[4] = {W25QXX_INS_JEDEC_ID, 0x00, 0x00, 0x00};
    uint8_t rx_data[4];

    flash_chip_select();

    spi_driver.transfer(FLASH_SPI_NUM, &tx_data, &rx_data, 4);

    while (!(spi1_event & SPI_EVENT_TRANSFER_COMPLETE)) {
        // Do something
    }

    flash_chip_deselect();

    flash->device_id = (rx_data[1] << 16) | (rx_data[2] << 8) | rx_data[3];
}

/**
 * @brief Select the flash chip
 */
void flash_chip_select(void) {
    gpio_driver.set_level(SPI_CS_PIN, GPIO_LEVEL_LOW);
}

/**
 * @brief Deselect the flash chip
 */
void flash_chip_deselect(void) {
    gpio_driver.set_level(SPI_CS_PIN, GPIO_LEVEL_HIGH);
}

/**
 * @brief Enable the flash write
 * 
 * @return operation status
 */
int flash_write_enable(void) {
    uint8_t tx_data = W25QXX_INS_WRITE_ENABLE;
    uint8_t rx_data;

    flash_chip_select();

    spi_driver.transfer(FLASH_SPI_NUM, &tx_data, &rx_data, 1);

    while (!(spi1_event & SPI_EVENT_TRANSFER_COMPLETE)) {
        // Do something
    }

    flash_chip_deselect();

    return 0;
}

/**
 * @brief Wait for the flash write complete
 * 
 * @return operation status
 */
int flash_wait_for_write_complete(void) {
    uint8_t tx_data = W25QXX_INS_READ_STATUS_REG1;
    uint8_t rx_data;

    flash_chip_select();

    spi_driver.transfer(FLASH_SPI_NUM, &tx_data, &rx_data, 1);

    while (!(spi1_event & SPI_EVENT_TRANSFER_COMPLETE)) {
        // Do something
    }

    flash_chip_deselect();

    while (rx_data & W25QXX_SR1_WEL) {
        flash_chip_select();

        spi_driver.transfer(FLASH_SPI_NUM, &tx_data, &rx_data, 1);

        while (!(spi1_event & SPI_EVENT_TRANSFER_COMPLETE)) {
            // Do something
        }

        flash_chip_deselect();
    }

    return 0;
}

/**
 * @brief SPI1 event callback
 * 
 * @param event 
 */
static void spi1_event_callback(uint32_t event) {
    spi1_event |= event;

    if (event & SPI_EVENT_TRANSFER_COMPLETE) {
        // Do something
    }
}
