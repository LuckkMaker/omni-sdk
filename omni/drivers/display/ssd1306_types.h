/**
  * @file    ssd1306_types.h
  * @author  LuckkMaker
  * @brief   SSD1306 driver types
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OMNI_DRIVER_SSD1306_TYPES_H
#define OMNI_DRIVER_SSD1306_TYPES_H

/* Includes ------------------------------------------------------------------*/
#include "include/device.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SSD1306_DEV_ADDR        0x3C    /**< SSD1306 device address */

#define SSD1306_CMD_BYTE        0x80    /**< Command byte Co=1 D/C=0 */
#define SSD1306_CMD_STREAM      0x00    /**< Command stream Co=0 D/C=0 */
#define SSD1306_DATA_BYTE       0xC0    /**< Data byte Co=1 D/C=1 */
#define SSD1306_DATA_STREAM     0x40    /**< Data stream Co=0 D/C=1 */

/**
 * @brief SSD1306 fundamental command
 */
#define SSD1306_SET_CONTRAST_CONTROL                0x81    /**< Set contrast control (double byte command) */
#define SSD1306_ENTIRE_DISPLAY_RESUME               0xA4    /**< Entire display resume */
#define SSD1306_ENTIRE_DISPLAY_ON                   0xA5    /**< Entire display on */
#define SSD1306_SET_NORMAL_DISPLAY                  0xA6    /**< Set normal display */
#define SSD1306_SET_INVERSE_DISPLAY                 0xA7    /**< Set inverse display */
#define SSD1306_SET_DISPLAY_OFF                     0xAE    /**< Set display off */
#define SSD1306_SET_DISPLAY_ON                      0xAF    /**< Set display on */

/**
 * @brief SSD1306 addressing setting command
 */
#define SSD1306_SET_LOWER_COL_START_ADDR            0x00    /**< Set lower column start address for page addressing mode */
#define SSD1306_SET_LOWER_COL_START_ADDR_MASK       0x0F

#define SSD1306_SET_HIGHER_COL_START_ADDR           0x10    /**< Set higher column start address for page addressing mode */
#define SSD1306_SET_HIGHER_COL_START_ADDR_MASK      0x0F

#define SSD1306_SET_MEMORY_ADDR_MODE                0x20    /**< Set memory addressing mode (double byte command) */
#define SSD1306_SET_MEMORY_ADDR_HORIZ               0x00    /**< Horizontal addressing mode */
#define SSD1306_SET_MEMORY_ADDR_VERT                0x01    /**< Vertical addressing mode */
#define SSD1306_SET_MEMORY_ADDR_PAGE                0x02    /**< Page addressing mode */

#define SSD1306_SET_COLUMN_ADDR                     0x21    /**< Set column address (double byte command) */
#define SSD1306_SET_PAGE_ADDR                       0x22    /**< Set page address (double byte command) */

#define SSD1306_SET_PAGE_START_ADDR                 0xB0    /**< Set page start address for page addressing mode */
#define SSD1306_SET_PAGE_START_ADDR_MASK            0x07

/**
 * @brief SSD1306 hardware configuration command
 */
#define SSD1306_SET_DISPLAY_START_LINE              0x40    /**< Set display start line */
#define SSD1306_SET_DISPLAY_START_LINE_MASK         0x3F

#define SSD1306_SET_SEGMENT_MAP_NORMAL              0xA0    /**< Set segment re-map (column address 0 is mapped to SEG0) */
#define SSD1306_SET_SEGMENT_MAP_REMAP               0xA1    /**< Set segment re-map (column address 127 is mapped to SEG0) */

#define SSD1306_SET_MULTIPLEX_RATIO                 0xA8    /**< Set multiplex ratio (double byte command) */

#define SSD1306_SET_COM_OUTPUT_SCAN_DIR_NORMAL      0xC0    /**< Set COM output scan direction (normal) */
#define SSD1306_SET_COM_OUTPUT_SCAN_DIR_FLIP        0xC8    /**< Set COM output scan direction (flip) */

#define SSD1306_SET_DISPLAY_OFFSET                  0xD3    /**< Set display offset (double byte command) */

#define SSD1306_SET_COM_PINS_HW_CONFIG              0xDA    /**< Set COM pins hardware configuration (double byte command) */
#define SSD1306_SET_COM_PINS_HW_CONFIG_SEQ          0x02    /**< Sequential COM pin configuration */
#define SSD1306_SET_COM_PINS_HW_CONFIG_ALT          0x12    /**< Alternative COM pin configuration */

/**
 * @brief SSD1306 controller
 */
typedef enum {
#if (CONFIG_SSD1306_NUM_1 == 1)
    SSD1306_NUM_1 = 0x01,
#endif /* (CONFIG_SSD1306_NUM_1 == 1) */
#if (CONFIG_SSD1306_NUM_2 == 1)
    SSD1306_NUM_2 = 0x02,
#endif /* (CONFIG_SSD1306_NUM_2 == 1) */
#if (CONFIG_SSD1306_NUM_3 == 1)
    SSD1306_NUM_3 = 0x03,
#endif /* (CONFIG_SSD1306_NUM_3 == 1) */
    SSD1306_NUM_MAX,
} ssd1306_num_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_DRIVER_SSD1306_TYPES_H */
