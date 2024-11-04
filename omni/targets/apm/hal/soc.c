/**
  * @file    soc.c
  * @author  LuckkMaker
  * @brief   System on Chip (SoC) initialization for STM32
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
#include "drivers/init.h"
#include "hal/dwt_hal.h"

/**
 * @brief Initialize device
 */
void device_init(void) {
    DAL_Init();
}

/**
 * @brief Initialize power
 */
void power_init(void) {
    // TODO: Add power initialization
}

/**
 * @brief Initialize watchdog
 */
void watchdog_init(void) {
    // TODO: Add watchdog initialization
}

/**
  * @brief This function configures the source of the time base.
  *        The time source is configured  to have 1ms time base with a dedicated 
  *        Tick interrupt priority.
  * @param TickPriority Tick interrupt priority.
  * @retval HAL status
  */
DAL_StatusTypeDef DAL_InitTick(uint32_t TickPriority) {
    dwt_hal_init();

    return DAL_OK;
}

/**
  * @brief This function is called to increment  a global variable "uwTick"
  *        used as application time base.
  */
void DAL_IncTick(void) {
}

/**
  * @brief Provides a tick value in millisecond.
  * @retval tick value
  */
uint32_t DAL_GetTick(void) {
    return dwt_hal_get_tick(1000);
}

/**
  * @brief This function provides minimum delay (in milliseconds) based 
  *        on variable incremented.
  * @param Delay specifies the delay time length, in milliseconds.
  * @retval None
  */
void DAL_Delay(uint32_t Delay) {
    dwt_hal_delay_ms(Delay);
}

/**
  * @brief Suspend Tick increment.
  * @retval None
  */
void DAL_SuspendTick(void) {
}

/**
  * @brief Resume Tick increment.
  * @retval None
  */
void DAL_ResumeTick(void) {
}
