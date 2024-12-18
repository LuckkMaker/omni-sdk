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

static int clock_hal_init(void);

const struct clock_driver_api clock_driver = {
    .init = clock_hal_init,
};

/**
 * @brief Initialize clock driver
 * 
 * @return Operation status
 */
static int clock_hal_init(void) {
    uint32_t osc_type = 0;
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

#if defined(CONFIG_SOC_FAMILY_STM32F1XX)
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_BKP_CLK_ENABLE();
#endif /* CONFIG_SOC_FAMILY_STM32F1XX */

#if defined(CONFIG_SOC_FAMILY_STM32F4XX)
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(CONFIG_PWR_REG_VOLTAGE);
#endif /* CONFIG_SOC_FAMILY_STM32F4XX */

#if defined(CONFIG_SOC_FAMILY_STM32H7XX)
    HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(CONFIG_PWR_REG_VOLTAGE);

    while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
#endif /* CONFIG_SOC_FAMILY_STM32H7XX */

#if (CONFIG_HSE_STATE != 0)
    osc_type |= RCC_OSCILLATORTYPE_HSE;
#endif /* CONFIG_HSE_STATE */
#if (CONFIG_HSI_STATE != 0)
    osc_type |= RCC_OSCILLATORTYPE_HSI;
#endif /* CONFIG_HSI_STATE */
#if (CONFIG_HSI48_STATE != 0)
    osc_type |= RCC_OSCILLATORTYPE_HSI48;
#endif /* CONFIG_HSI48_STATE */
#if (CONFIG_LSE_STATE != 0)
    osc_type |= RCC_OSCILLATORTYPE_LSE;
#endif /* CONFIG_LSE_STATE */
#if (CONFIG_LSI_STATE != 0)
    osc_type |= RCC_OSCILLATORTYPE_LSI;
#endif /* CONFIG_LSI_STATE */
#if (CONFIG_CSI_STATE != 0)
    osc_type |= RCC_OSCILLATORTYPE_CSI;
#endif /* CONFIG_CSI_STATE */

    RCC_OscInitStruct.OscillatorType = osc_type;
#if (CONFIG_HSE_STATE == 1)
    RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
#elif (CONFIG_HSE_STATE == 2)
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
#endif /* CONFIG_HSE_STATE */

#if (CONFIG_HSI_STATE == 1)
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
#endif /* CONFIG_HSI_STATE */

#if (CONFIG_HSI48_STATE == 1)
    RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
#endif /* CONFIG_HSI48_STATE */

#if (CONFIG_LSE_STATE == 1)
    RCC_OscInitStruct.LSEState = RCC_LSE_BYPASS;
#elif (CONFIG_LSE_STATE == 2)
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
#endif /* CONFIG_LSE_STATE */

#if (CONFIG_LSI_STATE == 1)
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
#endif /* CONFIG_LSI_STATE */

#if (CONFIG_CSI_STATE == 1)
    RCC_OscInitStruct.CSIState = RCC_CSI_ON;
#endif /* CONFIG_CSI_STATE */

#if (CONFIG_PLL == 0)
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
#else
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = CONFIG_PLL_SRC;
#if defined(CONFIG_SOC_FAMILY_STM32F1XX)
    RCC_OscInitStruct.PLL.PLLMUL = CONFIG_PLL_MUL;
#endif /* CONFIG_SOC_FAMILY_STM32F1XX */

#if defined(CONFIG_SOC_FAMILY_STM32F4XX)
    RCC_OscInitStruct.PLL.PLLM = CONFIG_PLL_M;
    RCC_OscInitStruct.PLL.PLLN = CONFIG_PLL_N;
    RCC_OscInitStruct.PLL.PLLP = CONFIG_PLL_P;
    RCC_OscInitStruct.PLL.PLLQ = CONFIG_PLL_Q;
#endif /* CONFIG_SOC_FAMILY_STM32F4XX */

#if defined(CONFIG_SOC_FAMILY_STM32H7XX)
    RCC_OscInitStruct.PLL.PLLM = CONFIG_PLL_M;
    RCC_OscInitStruct.PLL.PLLN = CONFIG_PLL_N;
    RCC_OscInitStruct.PLL.PLLP = CONFIG_PLL_P;
    RCC_OscInitStruct.PLL.PLLQ = CONFIG_PLL_Q;
    RCC_OscInitStruct.PLL.PLLR = CONFIG_PLL_R;
    RCC_OscInitStruct.PLL.PLLRGE = CONFIG_PLL_RGE;
    RCC_OscInitStruct.PLL.PLLVCOSEL = CONFIG_PLL_VCOSEL;
    RCC_OscInitStruct.PLL.PLLFRACN = CONFIG_PLL_FRACN;
#endif /* CONFIG_SOC_FAMILY_STM32H7XX */
#endif /* CONFIG_PLL */

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        return OMNI_FAIL;
    }

#if defined(CONFIG_SOC_FAMILY_STM32H7XX)
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2
                                | RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = CONFIG_SYSCLK_SRC;
    RCC_ClkInitStruct.SYSCLKDivider = CONFIG_SYSCLK_PRESC;
    RCC_ClkInitStruct.AHBCLKDivider = CONFIG_AHB_PRESC;
    RCC_ClkInitStruct.APB1CLKDivider = CONFIG_APB1_PRESC;
    RCC_ClkInitStruct.APB2CLKDivider = CONFIG_APB2_PRESC;
    RCC_ClkInitStruct.APB3CLKDivider = CONFIG_APB3_PRESC;
    RCC_ClkInitStruct.APB4CLKDivider = CONFIG_APB4_PRESC;

#else
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = CONFIG_SYSCLK_SRC;
    RCC_ClkInitStruct.AHBCLKDivider = CONFIG_AHB_PRESC;
    RCC_ClkInitStruct.APB1CLKDivider = CONFIG_APB1_PRESC;
    RCC_ClkInitStruct.APB2CLKDivider = CONFIG_APB2_PRESC;
#endif /* CONFIG_SOC_FAMILY_STM32H7XX */

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, CONFIG_FLASH_LATENCY) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}
