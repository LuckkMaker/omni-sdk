/**
  * @file    assert.h
  * @author  LuckkMaker
  * @brief   Assert functions for Omni
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
#ifndef OMNI_INC_ASSERT_H
#define OMNI_INC_ASSERT_H

/* Includes ------------------------------------------------------------------*/
#include "omni_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Assert function for OmniOS
 * @param expr: The expression to be evaluated
 * @param file: The file name where the assert function is called
 * @param line: The line number where the assert function is called
 */
static inline void omni_assert_base(const char *expr, const char *file, int line) {
    (void)expr;
    (void)file;
    (void)line;
    while (1) {
        /* Infinite loop */
    }
}

#if defined(CONFIG_OMNI_ASSERT)
#define omni_assert(expr) ((expr) ? (void)(expr) : omni_assert_base(#expr, __FILE__, __LINE__))
#else
#define omni_assert(expr) ((void)(expr))
#endif /* CONFIG_OMNI_ASSERT */

/**
 * @brief Asset that the condition is true
 * 
 * @param cond: The condition to check
 */
#define omni_assert_true(cond) omni_assert(cond)

/**
 * @brief Asset that the condition is false
 * 
 * @param cond: The condition to check
 */
#define omni_assert_false(cond) omni_assert(!(cond))

/**
 * @brief Asset that the value is NULL
 * 
 * @param ptr: The pointer to check
 */
#define omni_assert_is_null(ptr) omni_assert((ptr) == NULL)

/**
 * @brief Asset that the value is not NULL
 * 
 * @param ptr: The pointer to check
 */
#define omni_assert_not_null(ptr) omni_assert((ptr) != NULL)

/**
 * @brief Asset that the value is zero
 * 
 * @param cond: The value to check
 */
#define omni_assert_zero(cond) omni_assert(!(cond))

/**
 * @brief Asset that the value is non-zero
 * 
 * @param cond: The value to check
 */
#define omni_assert_non_zero(cond) omni_assert(!!(cond))

/**
 * @brief Asset that the value is equal to the expected value
 * 
 * @param actual: The actual value
 * @param expected: The expected value
 */
#define omni_assert_equal(actual, expected) omni_assert((actual) == (expected))

/**
 * @brief Asset that the value is not equal to the expected value
 * 
 * @param actual: The actual value
 * @param expected: The expected value
 */
#define omni_assert_not_equal(actual, expected) omni_assert((actual) != (expected))

/**
 * @brief Asset that the value is within the expected range
 * 
 * @param actual: The actual value
 * @param expected: The expected value
 * @param delta: The range
 */
#define omni_assert_within(actual, expected, delta) \
    omni_assert(((actual) >= ((expected) - (delta))) && ((actual) <= ((expected) + (delta))))

/**
 * @brief Asset that the value is out of the expected range
 * 
 * @param actual: The actual value
 * @param min: The minimum value
 * @param max: The maximum value
 */
#define omni_assert_in_range(actual, min, max) \
    omni_assert(((int)(actual) >= (int)(min)) && ((int)(actual) <= (int)(max)))

#ifdef __cplusplus
}
#endif

#endif /* OMNI_INC_ASSERT_H */
