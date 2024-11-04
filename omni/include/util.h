/**
  * @file    util.h
  * @author  LuckkMaker
  * @brief   Useful utilities for omni
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
#ifndef OMNI_INC_UTIL_H
#define OMNI_INC_UTIL_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(UNUSED)
#define UNUSED(X) (void)X
#endif /* UNUSED */

#if !defined(ARRAY_SIZE)
/**
 * @brief Get the number of elements in an array
 *
 * @param array Array to get the number of elements
 * @return Number of elements in the array
 */
#define ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))
#endif /* ARRAY_SIZE */

#if !defined(MAX)
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif /* MAX */

#if !defined(MIN)
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif /* MIN */

#if !defined(LO_BYTE)
#define LO_BYTE(x) ((uint8_t)(x & 0x00FF))
#endif /* LO_BYTE */

#if !defined(HI_BYTE)
#define HI_BYTE(x) ((uint8_t)((x & 0xFF00) >> 8))
#endif /* HI_BYTE */

#if !defined(MB)
#define MB(size) ((size) * 1024 * 1024)
#endif /* MB */

#if !defined(KB)
#define KB(size) ((size) * 1024)
#endif /* KB */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_INC_UTIL_H */
