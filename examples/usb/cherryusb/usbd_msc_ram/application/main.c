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
#include "msc_ram.h"

#define LED_PIN GET_PIN(E, 5)

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
    }
}

/**
 * @brief Setup the application
 */
void setup(void) {
    driver_init();

    // Initialize GPIO
    gpio_driver_config_t gpio1_config = {
        .mode = GPIO_MODE_PP_OUTPUT,
        .pull = GPIO_PULL_NONE,
        .speed = GPIO_SPEED_LEVEL_HIGH,
        .level = GPIO_LEVEL_LOW,
    };

    gpio_driver.init(LED_PIN, &gpio1_config);

    // Initialize CherryUSB
    static struct usbd_itf msc_itf;
    msc_itf.type = USB_ITF_TYPE_MSC;
    msc_itf.interface = &msc_intf0;
    msc_itf.ep_num_max = 2U;
    msc_itf.ep[0] = &msc_out_ep;
    msc_itf.ep[1] = &msc_in_ep;

    usbd_config_t usbd1_config = {
        .busid = 0,
        .descriptor = msc_ram_descriptor,
        .itf[0] = &msc_itf,
        .usbd_event_callback = usbd_event_handler,
    };
    usb_device.init(USB_NUM_1, &usbd1_config);
}
