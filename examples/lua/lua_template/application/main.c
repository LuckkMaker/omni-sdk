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
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "SEGGER_RTT.h"

// STM32H750VB PA10
// STM32H743II PB1
// STM32F411CE PC13
// STM32F407IG PE5
#define LED_PIN GET_PIN(E, 6)

lua_State *lua_state;

/**
 * @brief The application entry point.
 * 
 * @return int 
 */
int main(void) {
    setup();

    while (1) {
        // Do something
        gpio_driver.toggle(LED_PIN);
        timer_driver.delay_ms(500);
        luaL_dostring(lua_state, "print('Hello, World!')");
    }
}

/**
 * @brief Setup the application
 */
void setup(void) {
    SEGGER_RTT_Init();

    lua_state = luaL_newstate();
    luaL_openlibs(lua_state);

    gpio_driver_config_t gpio1_config = {
        .mode = GPIO_MODE_PP_OUTPUT,
        .pull = GPIO_PULL_NONE,
        .speed = GPIO_SPEED_LEVEL_HIGH,
        .level = GPIO_LEVEL_LOW,
    };

    gpio_driver.init(LED_PIN, &gpio1_config);
}

/**
 * @brief GCC I/O library putchar function
 * 
 * @param ch 
 * @return int 
 */
int __io_putchar(int ch) {
    SEGGER_RTT_PutChar(0, ch);

    return ch;
}

int _gettimeofday(struct timeval *tv, void *tzvp) {
    return 0;
}
