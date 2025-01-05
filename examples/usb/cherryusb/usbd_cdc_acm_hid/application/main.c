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
#include "cdc_acm_hid.h"

#define LED_PIN GET_PIN(E, 5)

static void uart1_event_callback(uint32_t event);

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
        cdc_acm_data_send(0, (uint8_t *)"Hello, World!\r\n", 15);
    }
}

/**
 * @brief Setup the application
 */
void setup(void) {
    driver_init();

    gpio_driver_config_t gpio1_config = {
        .mode = GPIO_MODE_PP_OUTPUT,
        .pull = GPIO_PULL_NONE,
        .speed = GPIO_SPEED_LEVEL_HIGH,
        .level = GPIO_LEVEL_LOW,
    };

    gpio_driver.init(LED_PIN, &gpio1_config);

    usart_driver_config_t uart1_config = {
        .mode = USART_MODE_UART,
        .baudrate = 115200,
        .data_bits = USART_DATA_BITS_8,
        .stop_bits = USART_STOP_BITS_1,
        .parity = USART_PARITY_DISABLE,
        .flow_ctrl = USART_FLOW_CTRL_DISABLE,
        .event_cb = uart1_event_callback,
    };

    usart_driver.init(USART_NUM_1, &uart1_config);

    static struct usbd_itf cdc_itf0;
    cdc_itf0.type = USB_ITF_TYPE_CDC;
    cdc_itf0.interface = &cdc_intf0;
    cdc_itf0.ep_num_max = 0U;   // Ignore the CDC command endpoint

    static struct usbd_itf cdc_itf1;
    cdc_itf1.type = USB_ITF_TYPE_CDC;
    cdc_itf1.interface = &cdc_intf1;
    cdc_itf1.ep_num_max = 2U;   // CDC data endpoints
    cdc_itf1.ep[0] = &cdc_out_ep;
    cdc_itf1.ep[1] = &cdc_in_ep;

    static struct usbd_itf hid_itf;
    hid_itf.type = USB_ITF_TYPE_HID;
    hid_itf.interface = &hid_intf;
    hid_itf.ep_num_max = 2U;
    hid_itf.ep[0] = &custom_hid_in_ep;
    hid_itf.ep[1] = &custom_hid_out_ep;

    usbd_config_t usbd1_config = {
        .busid = 0,
        .descriptor = cdc_acm_hid_descriptor,
        .hid_report_desc = hid_custom_report_desc,
        .hid_report_desc_size = ARRAY_SIZE(hid_custom_report_desc),
        .itf[0] = &cdc_itf0,
        .itf[1] = &cdc_itf1,
        .itf[2] = &hid_itf,
        .usbd_event_callback = usbd_event_handler,
    };
    usb_device.init(USB_NUM_1, &usbd1_config);
}

/**
 * @brief UART event callback function
 * 
 * @param event 
 */
static void uart1_event_callback(uint32_t event) {
}

/**
 * @brief GCC I/O library putchar function
 * 
 * @param ch 
 * @return int 
 */
int __io_putchar(int ch) {
    /* send a byte of data to the serial port */
    usart_driver.poll_send(USART_NUM_1, (uint8_t*)&ch, 1, 1000);

    return ch;
}
