/**
  * @file    u8g2_gui.c
  * @author  LuckkMaker
  * @brief   U8G2 GUI program body
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
#include "u8g2_gui.h"
#include "u8g2.h"

/* Private defines -----------------------------------------------------------*/
#include <omni.h>

#define SSD1306_DEVICE_ADDR 0x3C

static u8g2_t u8g2;
static volatile uint32_t i2c1_event;

static void i2c1_event_callback(uint32_t event);
static uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
static uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

/**
 * @brief u8g2 init
 */
void u8g2_init(void) {
    u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_hw_i2c, u8x8_gpio_and_delay);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);
    u8g2_ClearBuffer(&u8g2);
    u8g2_SetFont(&u8g2, u8g2_font_ncenB14_tr);
    u8g2_DrawStr(&u8g2, 0, 20, "Hello, World!");
    u8g2_DrawCircle(&u8g2, 64, 40, 10, U8G2_DRAW_ALL);
    u8g2_SendBuffer(&u8g2);
}

/**
 * @brief U8X8 GPIO and delay callback
 */
static uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    switch (msg) {
        case U8X8_MSG_DELAY_100NANO: // delay arg_int * 100 nano seconds
            __NOP();
            break;
        case U8X8_MSG_DELAY_10MICRO: // delay arg_int * 10 micro seconds
            for (uint16_t n = 0; n < 320; n++)
                __NOP();
            break;
        case U8X8_MSG_DELAY_MILLI:   // delay arg_int * 1 milli second
            timer_driver.delay_ms(arg_int);
            break;
        case U8X8_MSG_DELAY_I2C:     // arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
            timer_driver.delay_us(5);
            break;                    // arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
        case U8X8_MSG_GPIO_I2C_CLOCK: // arg_int=0: Output low at I2C clock pin
            break;                    // arg_int=1: Input dir with pullup high for I2C clock pin
        case U8X8_MSG_GPIO_I2C_DATA:  // arg_int=0: Output low at I2C data pin
            break;                    // arg_int=1: Input dir with pullup high for I2C data pin
        case U8X8_MSG_GPIO_MENU_SELECT:
            u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
            break;
        case U8X8_MSG_GPIO_MENU_NEXT:
            u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
            break;
        case U8X8_MSG_GPIO_MENU_PREV:
            u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
            break;
        case U8X8_MSG_GPIO_MENU_HOME:
            u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
            break;
        default:
            u8x8_SetGPIOResult(u8x8, 1); // default return value
            break;
    }
    return 1;
}

/**
 * @brief U8X8 byte hardware I2C callback
 */
static uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    static uint8_t buffer[32];  // u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER
    static uint8_t buf_idx;
    uint8_t *data;

    switch (msg) {
        case U8X8_MSG_BYTE_INIT:
            /* add your custom code to init i2c subsystem */
            i2c_driver_config_t i2c1_config = {
                .mode = I2C_MODE_I2C,
                .bus_speed = I2C_BUS_SPEED_FAST,
                .own_addr_bits = I2C_ADDR_BITS_7,
                .own_addr = 0x00,
                .event_cb = i2c1_event_callback,
            };

            i2c_driver.open(I2C_NUM_1, &i2c1_config);
            break;
        case U8X8_MSG_BYTE_SEND:
            data = (uint8_t *)arg_ptr;
            while ( arg_int > 0 ) {
                buffer[buf_idx++] = *data;
                data++;
                arg_int--;
            }
            break;
        case U8X8_MSG_BYTE_SET_DC:
            /* ignored for i2c */
            break;
        case U8X8_MSG_BYTE_START_TRANSFER:
            buf_idx = 0;
            break;
        case U8X8_MSG_BYTE_END_TRANSFER:
            i2c1_event = 0;
            i2c_driver.master_transmit(I2C_NUM_1, SSD1306_DEVICE_ADDR, buffer, buf_idx, 1);
            while (!(i2c1_event & I2C_EVENT_TRANSFER_COMPLETE)) {
                // Do something
            }
            if ((i2c1_event & I2C_EVENT_TRANSFER_INCOMPLETE) != 0U) {
                // Transfer incomplete
                return 0;
            }
            break;
        default:
            return 0;
    }
    return 1;
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
