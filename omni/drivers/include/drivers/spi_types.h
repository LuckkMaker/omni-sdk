/**
  * @file    spi_types.h
  * @author  LuckkMaker
  * @brief   SPI driver types
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
#ifndef OMNI_DRIVER_SPI_TYPES_H
#define OMNI_DRIVER_SPI_TYPES_H

/* Includes ------------------------------------------------------------------*/
#include "include/device.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief SPI mode
 */
#define SPI_OP_MODE_POS         0U                                  /**< Mode position */
#define SPI_OP_MODE_MASK        (0x01U << SPI_OP_MODE_POS)          /**< Mode mask */
#define SPI_OP_MODE_MASTER      (0x00U << SPI_OP_MODE_POS)          /**< Master mode */
#define SPI_OP_MODE_SLAVE       (0x01U << SPI_OP_MODE_POS)          /**< Slave mode */
#define SPI_OP_MODE_GET(_opt_)  ((_opt_) & SPI_OP_MODE_MASK)        /**< Get mode */

/**
 * @brief SPI direction
 */
#define SPI_OP_DIR_POS              1U                                /**< Direction position */
#define SPI_OP_DIR_MASK             (0x03U << SPI_OP_DIR_POS)         /**< Direction mask */
#define SPI_OP_DIR_LINES_SINGLE     (0x00U << SPI_OP_DIR_POS)         /**< Single lines */
#define SPI_OP_DIR_LINES_DUAL       (0x01U << SPI_OP_DIR_POS)         /**< Dual lines */
#define SPI_OP_DIR_LINES_GET(opt)   ((opt) & SPI_OP_DIR_MASK)         /**< Get direction */

/**
 * @brief SPI clock polarity
 */
#define SPI_OP_CPOL_POS         3U                                  /**< Clock polarity position */
#define SPI_OP_CPOL_MASK        (0x01U << SPI_OP_CPOL_POS)          /**< Clock polarity mask */
#define SPI_OP_CPOL_LOW         (0x00U << SPI_OP_CPOL_POS)          /**< Clock polarity low */
#define SPI_OP_CPOL_HIGH        (0x01U << SPI_OP_CPOL_POS)          /**< Clock polarity high */
#define SPI_OP_CPOL_GET(opt)    ((opt) & SPI_OP_CPOL_MASK)          /**< Get clock polarity */

/**
 * @brief SPI clock phase
 */
#define SPI_OP_CPHA_POS         4U                                  /**< Clock phase position */
#define SPI_OP_CPHA_MASK        (0x01U << SPI_OP_CPHA_POS)          /**< Clock phase mask */
#define SPI_OP_CPHA_1EDGE       (0x00U << SPI_OP_CPHA_POS)          /**< Clock phase 1 edge */
#define SPI_OP_CPHA_2EDGE       (0x01U << SPI_OP_CPHA_POS)          /**< Clock phase 2 edge */
#define SPI_OP_CPHA_GET(opt)    ((opt) & SPI_OP_CPHA_MASK)          /**< Get clock phase */

/**
 * @brief SPI data size
 */
#define SPI_OP_DATA_SIZE_POS        5U                                  /**< Data size position */
#define SPI_OP_DATA_SIZE_MASK       (0x3FU << SPI_OP_DATA_SIZE_POS)     /**< Data size mask */
#define SPI_OP_DATA_SIZE_GET(opt)   ((opt) & SPI_OP_DATA_SIZE_MASK)     /**< Get data size */

/**
 * @brief SPI bit order
 */
#define SPI_OP_BIT_ORDER_POS        11U                                 /**< Bit order position */
#define SPI_OP_BIT_ORDER_MASK       (0x01U << SPI_OP_BIT_ORDER_POS)     /**< Bit order mask */
#define SPI_OP_BIT_ORDER_MSB        (0x00U << SPI_OP_BIT_ORDER_POS)     /**< MSB first */
#define SPI_OP_BIT_ORDER_LSB        (0x01U << SPI_OP_BIT_ORDER_POS)     /**< LSB first */
#define SPI_OP_BIT_ORDER_GET(opt)   ((opt) & SPI_OP_BIT_ORDER_MASK)     /**< Get bit order */

/**
 * @brief SPI slave select
 */
#define SPI_OP_SLAVE_SEL_POS          12U                                   /**< Slave select position */
#define SPI_OP_SLAVE_SEL_MASK         (0x03U << SPI_OP_SLAVE_SEL_POS)       /**< Slave select mask */
#define SPI_OP_SLAVE_SEL_NONE         (0x00U << SPI_OP_SLAVE_SEL_POS)       /**< No slave select */
#define SPI_OP_SLAVE_SEL_SOFT         (0x01U << SPI_OP_SLAVE_SEL_POS)       /**< Software slave select */
#define SPI_OP_SLAVE_SEL_HARD_INPUT   (0x02U << SPI_OP_SLAVE_SEL_POS)       /**< Hardware slave select input */
#define SPI_OP_SLAVE_SEL_HARD_OUTPUT  (0x03U << SPI_OP_SLAVE_SEL_POS)       /**< Hardware slave select output */
#define SPI_OP_SLAVE_SEL_GET(opt)     ((opt) & SPI_OP_SLAVE_SEL_MASK)       /**< Get slave select */

/**
 * @brief SPI control slave select
 */
#define SPI_OP_CTRL_SS_POS            14U                                   /**< Control slave select position */
#define SPI_OP_CTRL_SS_MASK           (0x01U << SPI_OP_CTRL_SS_POS)         /**< Control slave select mask */
#define SPI_OP_CTRL_SS_ENABLE         (0x00U << SPI_OP_CTRL_SS_POS)         /**< Enable control slave select */
#define SPI_OP_CTRL_SS_DISABLE        (0x01U << SPI_OP_CTRL_SS_POS)         /**< Disable control slave select */
#define SPI_OP_CTRL_SS_GET(opt)       ((opt) & SPI_OP_CTRL_SS_MASK)         /**< Get control slave select */

/**
 * @brief SPI protocol mode
 */
#define SPI_OP_PROTOCOL_POS           15U                                   /**< Protocol position */
#define SPI_OP_PROTOCOL_MASK          (0x01U << SPI_OP_PROTOCOL_POS)        /**< Protocol mask */
#define SPI_OP_PROTOCOL_MOTOROLA      (0x00U << SPI_OP_PROTOCOL_POS)        /**< Motorola protocol */
#define SPI_OP_PROTOCOL_TI            (0x01U << SPI_OP_PROTOCOL_POS)        /**< TI protocol */
#define SPI_OP_PROTOCOL_GET(opt)      ((opt) & SPI_OP_PROTOCOL_MASK)        /**< Get protocol */

typedef uint32_t spi_option_t;

/**
 * @brief SPI bus number
 */
typedef enum {
#if (CONFIG_SPI_NUM_1 == 1)
    SPI_NUM_1 = 0x01,
#endif /* CONFIG_SPI_NUM_1 */
#if (CONFIG_SPI_NUM_2 == 1)
    SPI_NUM_2 = 0x02,
#endif /* CONFIG_SPI_NUM_2 */
#if (CONFIG_SPI_NUM_3 == 1)
    SPI_NUM_3 = 0x03,
#endif /* CONFIG_SPI_NUM_3 */
#if (CONFIG_SPI_NUM_4 == 1)
    SPI_NUM_4 = 0x04,
#endif /* CONFIG_SPI_NUM_4 */
#if (CONFIG_SPI_NUM_5 == 1)
    SPI_NUM_5 = 0x05,
#endif /* CONFIG_SPI_NUM_5 */
#if (CONFIG_SPI_NUM_6 == 1)
    SPI_NUM_6 = 0x06,
#endif /* CONFIG_SPI_NUM_6 */
    SPI_NUM_MAX,
} spi_num_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_DRIVER_SPI_TYPES_H */
