/**
  * @file    dma_hal.c
  * @author  LuckkMaker
  * @brief   DMA HAL driver
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
#include "hal/dma_hal.h"

/********************* HAL functions **********************/

/**
 * @brief Enable DMA clock
 * 
 * @param dev DMA device information
 */
void dma_hal_enable_clock(DMA_TypeDef *DMAx) {
#if defined(DMA1)
    if (DMAx== DMA1) {__DAL_RCM_DMA1_CLK_ENABLE();}
#endif /* DMA1 */
#if defined(DMA2)
    if (DMAx == DMA2) {__DAL_RCM_DMA2_CLK_ENABLE();}
#endif /* DMA2 */
}
