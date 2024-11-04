/**
  * @file    clock_hal.c
  * @author  LuckkMaker
  * @brief   Clock HAL driver
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
#include "drivers/clock.h"

static int clock_open(void);

const struct clock_driver_api clock_driver = {
    .open = clock_open,
};

/**
 * @brief Open clock driver
 * 
 * @return Operation status
 */
static int clock_open(void) {
    RCM_OscInitTypeDef RCM_OscInitStruct = {0};
    RCM_ClkInitTypeDef RCM_ClkInitStruct = {0};

#if defined(CONFIG_SOC_FAMILY_APM32F4XX)
    __DAL_RCM_PMU_CLK_ENABLE();
    __DAL_PMU_VOLTAGESCALING_CONFIG(CONFIG_PWR_REG_VOLTAGE);
#endif /* CONFIG_SOC_FAMILY_APM32F4XX */

    RCM_OscInitStruct.OscillatorType = CONFIG_OSC_TYPE;
#if (CONFIG_HSE_STATE == 1)
    RCM_OscInitStruct.HSEState = RCM_HSE_BYPASS;
#elif (CONFIG_HSE_STATE == 2)
    RCM_OscInitStruct.HSEState = RCM_HSE_ON;
#endif /* CONFIG_HSE_STATE */

#if (CONFIG_HSI_STATE == 1)
    RCM_OscInitStruct.HSIState = RCM_HSI_ON;
#endif /* CONFIG_HSI_STATE */

#if (CONFIG_LSE_STATE == 1)
    RCM_OscInitStruct.LSEState = RCM_LSE_BYPASS;
#elif (CONFIG_LSE_STATE == 2)
    RCM_OscInitStruct.LSEState = RCM_LSE_ON;
#endif /* CONFIG_LSE_STATE */

#if (CONFIG_LSI_STATE == 1)
    RCM_OscInitStruct.LSIState = RCM_LSI_ON;
#endif /* CONFIG_LSI_STATE */

#if (CONFIG_PLL == 0)
    RCM_OscInitStruct.PLL.PLLState = RCM_PLL_NONE;
#else
    RCM_OscInitStruct.PLL.PLLState = RCM_PLL_ON;
    RCM_OscInitStruct.PLL.PLLSource = CONFIG_PLL_SRC;

#if defined(CONFIG_SOC_FAMILY_APM32F4XX)
    RCM_OscInitStruct.PLL.PLLB = CONFIG_PLL_B;
    RCM_OscInitStruct.PLL.PLL1A = CONFIG_PLL_A;
    RCM_OscInitStruct.PLL.PLL1C = CONFIG_PLL_C;
    RCM_OscInitStruct.PLL.PLLD = CONFIG_PLL_D;
#endif /* CONFIG_SOC_FAMILY_APM32F4XX */

#endif /* CONFIG_PLL */

    if (DAL_RCM_OscConfig(&RCM_OscInitStruct) != DAL_OK) {
        return OMNI_FAIL;
    }

    RCM_ClkInitStruct.ClockType = RCM_CLOCKTYPE_HCLK | RCM_CLOCKTYPE_SYSCLK
                                | RCM_CLOCKTYPE_PCLK1 | RCM_CLOCKTYPE_PCLK2;
    RCM_ClkInitStruct.SYSCLKSource = CONFIG_SYSCLK_SRC;
    RCM_ClkInitStruct.AHBCLKDivider = CONFIG_AHB_PRESC;
    RCM_ClkInitStruct.APB1CLKDivider = CONFIG_APB1_PRESC;
    RCM_ClkInitStruct.APB2CLKDivider = CONFIG_APB2_PRESC;
    if (DAL_RCM_ClockConfig(&RCM_ClkInitStruct, CONFIG_FLASH_LATENCY) != DAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}
