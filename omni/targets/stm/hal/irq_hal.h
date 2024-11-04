/**
  * @file    irq_hal.h
  * @author  LuckkMaker
  * @brief   Header for irq_hal.c file
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
#ifndef OMNI_HAL_IRQ_H
#define OMNI_HAL_IRQ_H

/* Includes ------------------------------------------------------------------*/
#include "include/device.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief IRQ pre-emption priority group
 */
typedef enum {
    IRQ_PRIORITY_GROUP_0 = 0x00,   /**< 0 bits for pre-emption priority, 4 bits for subpriority */
    IRQ_PRIORITY_GROUP_1 = 0x01,   /**< 1 bits for pre-emption priority, 3 bits for subpriority */
    IRQ_PRIORITY_GROUP_2 = 0x02,   /**< 2 bits for pre-emption priority, 2 bits for subpriority */
    IRQ_PRIORITY_GROUP_3 = 0x03,   /**< 3 bits for pre-emption priority, 1 bits for subpriority */
    IRQ_PRIORITY_GROUP_4 = 0x04,   /**< 4 bits for pre-emption priority, 0 bits for subpriority */
} irq_priority_grouping_t;

void irq_hal_register_handler(int irq, void (*handler)(void));
void irq_hal_unregister_handler(int irq);
void irq_hal_set_vector(int irq, uint32_t vector);
uint32_t irq_hal_get_vector(int irq);
void irq_hal_set_priority_grouping(irq_priority_grouping_t priority_grouping);
uint32_t irq_hal_get_priority_grouping(void);
void irq_hal_enable(int irq);
uint32_t irq_hal_get_enable(int irq);
void irq_hal_disable(int irq);
void irq_hal_set_pending(int irq);
uint32_t irq_hal_get_pending(int irq);
void irq_hal_clear_pending(int irq);
void irq_hal_set_priority(int irq, uint32_t preemption_priority, uint32_t sub_priority);
void irq_hal_get_priority(int irq, uint32_t *preemption_priority, uint32_t *sub_priority);
uint32_t irq_hal_get_active(int irq);
void irq_hal_system_reset(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_HAL_IRQ_H */
