/**
  * @file    irq_hal.c
  * @author  LuckkMaker
  * @brief   IRQ HAL for STM32
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
#include "hal/irq_hal.h"
#include "ll/irq_ll.h"

// NVIC priority grouping
#define NVIC_PRIORITY_GROUPING_0     0x00000007U
#define NVIC_PRIORITY_GROUPING_1     0x00000006U
#define NVIC_PRIORITY_GROUPING_2     0x00000005U
#define NVIC_PRIORITY_GROUPING_3     0x00000004U
#define NVIC_PRIORITY_GROUPING_4     0x00000003U

typedef void(*irq_vector_table_t)(void);

#define IRQ_VECTOR_NUM  (CONFIG_IRQ_RES_NUM + CONFIG_IRQ_DEV_NUM)

static __attribute__((section(".vtable"))) \
irq_vector_table_t irq_ram_vector_table[IRQ_VECTOR_NUM] __attribute__((aligned(256)));


/**
 * @brief Register an interrupt handler
 * 
 * @param irq Interrupt number
 * @param handler Pointer to the interrupt handler
 */
void irq_hal_register_handler(int irq, void (*handler)(void)) {
    void (**base_addr)(void);
    uint32_t i;

    // Check if the RAM vector table is initialized
    if (SCB->VTOR != (uint32_t)irq_ram_vector_table) {
        base_addr = (void (**)(void))SCB->VTOR;
        // Copy the vector table to RAM
        for (i = 0; i < IRQ_VECTOR_NUM; i++) {
            irq_ram_vector_table[i] = base_addr[i];
        }

        // Set the vector table to RAM
        SCB->VTOR = (uint32_t)irq_ram_vector_table;
    }

    // Register the interrupt handler
    irq_ram_vector_table[irq + CONFIG_IRQ_RES_NUM] = handler;
}

/**
 * @brief Unregister an interrupt handler
 * 
 * @param irq Interrupt number
 */
void irq_hal_unregister_handler(int irq) {
    // Unregister the interrupt handler
    irq_ram_vector_table[irq + CONFIG_IRQ_RES_NUM] = Default_Handler;
}

/**
 * @brief Set interrupt vector
 * 
 * @param irq Interrupt number
 * @param vector Address of interrupt handler function
 */
void irq_hal_set_vector(int irq, uint32_t vector) {
    NVIC_SetVector(irq, vector);
}

/**
 * @brief Get interrupt vector
 * 
 * @param irq Interrupt number
 * @return Address of interrupt handler function
 */
uint32_t irq_hal_get_vector(int irq) {
    return NVIC_GetVector(irq);
}

/**
 * @brief Set interrupt priority grouping
 * 
 * @param priority_grouping Priority grouping
 */
void irq_hal_set_priority_grouping(irq_priority_grouping_t priority_grouping) {
    uint32_t temp;

    switch (priority_grouping) {
        case IRQ_PRIORITY_GROUP_0:
            temp = NVIC_PRIORITY_GROUPING_0;
            break;
        case IRQ_PRIORITY_GROUP_1:
            temp = NVIC_PRIORITY_GROUPING_1;
            break;
        case IRQ_PRIORITY_GROUP_2:
            temp = NVIC_PRIORITY_GROUPING_2;
            break;
        case IRQ_PRIORITY_GROUP_3:
            temp = NVIC_PRIORITY_GROUPING_3;
            break;
        case IRQ_PRIORITY_GROUP_4:
            temp = NVIC_PRIORITY_GROUPING_4;
            break;
        default:
            temp = NVIC_PRIORITY_GROUPING_4;
            break;
    }

    // Set priority grouping
    NVIC_SetPriorityGrouping(temp);
}

/**
 * @brief Get interrupt priority grouping
 * 
 * @return Priority grouping
 */
uint32_t irq_hal_get_priority_grouping(void) {
    return NVIC_GetPriorityGrouping();
}

/**
 * @brief Enable interrupt
 * 
 * @param irq Interrupt number
 */
void irq_hal_enable(int irq) {
    NVIC_EnableIRQ(irq);
}

/**
 * @brief Get interrupt enable status
 * 
 * @param irq Interrupt number
 * @return Enable status
 */
uint32_t irq_hal_get_enable(int irq) {
    return NVIC_GetEnableIRQ(irq);
}

/**
 * @brief Disable interrupt
 * 
 * @param irq Interrupt number
 */
void irq_hal_disable(int irq) {
    NVIC_DisableIRQ(irq);
}

/**
 * @brief Set interrupt pending
 * 
 * @param irq Interrupt number
 */
void irq_hal_set_pending(int irq) {
    NVIC_SetPendingIRQ(irq);
}

/**
 * @brief Get interrupt pending status
 * 
 * @param irq Interrupt number
 * @return Pending status
 */
uint32_t irq_hal_get_pending(int irq) {
    return NVIC_GetPendingIRQ(irq);
}

/**
 * @brief Clear interrupt pending
 * 
 * @param irq Interrupt number
 */
void irq_hal_clear_pending(int irq) {
    NVIC_ClearPendingIRQ(irq);
}

/**
 * @brief Set interrupt priority
 * 
 * @param irq Interrupt number
 * @param preemption_priority Preemption priority
 * @param sub_priority Sub priority
 */
void irq_hal_set_priority(int irq, uint32_t preemption_priority, uint32_t sub_priority) {
    NVIC_SetPriority(irq, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), preemption_priority, sub_priority));
}

/**
 * @brief Get interrupt priority
 * 
 * @param irq Interrupt number
 * @param preemption_priority Preemption priority
 * @param sub_priority Sub priority
 */
void irq_hal_get_priority(int irq, uint32_t *preemption_priority, uint32_t *sub_priority) {
    NVIC_DecodePriority(NVIC_GetPriority(irq), NVIC_GetPriorityGrouping(), preemption_priority, sub_priority);
}

/**
 * @brief Get active interrupt
 * 
 * @param irq Interrupt number
 * @return Active interrupt
 */
uint32_t irq_hal_get_active(int irq) {
    return NVIC_GetActive(irq);
}

/**
 * @brief System reset
 */
void irq_hal_system_reset(void) {
    NVIC_SystemReset();
}
