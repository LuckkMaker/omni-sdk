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
#include "winusb2_cdc.h"

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
    // Initialize GPIO
    gpio_driver_config_t gpio1_config = {
        .mode = GPIO_MODE_PP_OUTPUT,
        .pull = GPIO_PULL_NONE,
        .speed = GPIO_SPEED_LEVEL_HIGH,
        .level = GPIO_LEVEL_LOW,
    };

    gpio_driver.init(LED_PIN, &gpio1_config);

    // Initialize CherryUSB
    static struct usbd_itf winusb_itf;
    winusb_itf.type = USB_ITF_TYPE_WINUSB;
    winusb_itf.interface = &winusb_intf;
    winusb_itf.ep_num_max = 2U;
    winusb_itf.ep[0] = &winusb_out_ep1;
    winusb_itf.ep[1] = &winusb_in_ep1;

    static struct usbd_itf cdc_itf1;
    cdc_itf1.type = USB_ITF_TYPE_CDC;
    cdc_itf1.interface = &cdc_intf1;
    cdc_itf1.ep_num_max = 0U;   // Ignore the CDC command endpoint

    static struct usbd_itf cdc_itf2;
    cdc_itf2.type = USB_ITF_TYPE_CDC;
    cdc_itf2.interface = &cdc_intf2;
    cdc_itf2.ep_num_max = 2U;
    cdc_itf2.ep[0] = &cdc_out_ep;
    cdc_itf2.ep[1] = &cdc_in_ep;

    usbd_config_t usbd1_config = {
        .busid = 0,
        .descriptor = winusbv2_descriptor,
        .bos = &bos_desc,
        .msosv2 = &msosv2_desc,
        .itf[0] = &winusb_itf,
        .itf[1] = &cdc_itf1,
        .itf[2] = &cdc_itf2,
        .usbd_event_callback = usbd_event_handler,
    };
    usb_device.init(USB_NUM_1, &usbd1_config);
}
