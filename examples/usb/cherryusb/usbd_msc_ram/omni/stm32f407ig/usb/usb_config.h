/**
  * @file    usb_config.h
  * @author  LuckkMaker
  * @brief   CherryUSB configuration file
  * @version 1.0.0
  * @date    15-Oct-2024
  * @attention
  *
  * Copyright (c) 2024 LuckkMaker
  * Copyright (c) 2022 sakumisu
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
#ifndef CHERRYUSB_CONFIG_H
#define CHERRYUSB_CONFIG_H

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------
#define CHERRYUSB_VERSION                           0x010300
#define CHERRYUSB_VERSION_STR                       "v1.3.0"

// <h> USB Common Configuration
#define CONFIG_USB_PRINTF(...)                      printf(__VA_ARGS__)

#define usb_malloc(size)                            malloc(size)
#define usb_free(ptr)                               free(ptr)

//      Attribute Data into no Cache RAM
#define USB_NOCACHE_RAM_SECTION                     __attribute__((section(".noncacheable")))

//  <o> USB Debug Level <0=>Error <1=>Warning <2=>Info <3=>Log
#define CONFIG_USB_DBG_LEVEL                        2
//  <q> USB Color Log
#define CONFIG_USB_COLOR_LOG                        1
#if (CONFIG_USB_COLOR_LOG == 1)
#define CONFIG_USB_PRINTF_COLOR_ENABLE
#endif /* CONFIG_USB_COLOR_LOG */
//  <o> Data alignment <4=>4
#define CONFIG_USB_ALIGN_SIZE                       4
// </h>

// <h> USB Device Port Configuration
//  <o> Max Bus Number <1=>1
#define CONFIG_USBDEV_MAX_BUS                       1
//  <o> Endpoint Number <1-15>
#define CONFIG_USBDEV_EP_NUM                        4

//  <h> FSDEV Configuration
//      <o> PMA Access <1=>1 <2=>2
#define CONFIG_USBDEV_FSDEV_PMA_ACCESS              2
//  </h>

//  <h> DWC2 Configuration
//  <i> FIFO sizes in bytes (total available memory for FIFOs is 1.25 kB) in FS mode
//  <i> FIFO sizes in bytes (total available memory for FIFOs is 4 kB) in HS mode
//      <o> RX FIFO Size <16-1024>
#define CONFIG_USB_DWC2_RXALL_FIFO_SIZE             160
//      <o> TX0 FIFO Size <16-1024>
#define CONFIG_USB_DWC2_TX0_FIFO_SIZE               40
//      <o> TX1 FIFO Size <16-1024>
#define CONFIG_USB_DWC2_TX1_FIFO_SIZE               40
//      <o> TX2 FIFO Size <16-1024>
#define CONFIG_USB_DWC2_TX2_FIFO_SIZE               40
//      <o> TX3 FIFO Size <16-1024>
#define CONFIG_USB_DWC2_TX3_FIFO_SIZE               40
//      <o> TX4 FIFO Size <16-1024>
#define CONFIG_USB_DWC2_TX4_FIFO_SIZE               128
//      <o> TX5 FIFO Size <16-1024>
#define CONFIG_USB_DWC2_TX5_FIFO_SIZE               128
//  </h>
// </h>

// <h> USB Host Port Configuration
//  <o> Max Bus Number <1=>1
#define CONFIG_USBHOST_MAX_BUS                      1
//  <o> Pipe Number <1-15>
#define CONFIG_USBHOST_PIPE_NUM                     10
// </h>

// <h> USB Device Stack Configuration
//  <o> EP0 IN and OUT transfer buffer size <512=>512
#define CONFIG_USBDEV_REQUEST_BUFFER_LEN            512
//  <c> Setup Packet Log for Debug
//#define CONFIG_USBDEV_SETUP_LOG_PRINT
//  </c>
//  <c> Send EP0 IN Data from User Buffer Instead of Copying into EP0 reqdata
//#define CONFIG_USBDEV_EP0_INDATA_NO_COPY
//  </c>
//  <c> Check If the Input Descriptor is Correct
//#define CONFIG_USBDEV_DESC_CHECK
//  </c>
//  <c> Enable test mode
//#define CONFIG_USBDEV_TEST_MODE
//  </c>

//  <h> USB Device MSC Class
//  <o> MSC Max LUN <1-15>
#define CONFIG_USBDEV_MSC_MAX_LUN                   1
//  <o> MSC Max Block Size <512-65536>
#define CONFIG_USBDEV_MSC_MAX_BUFSIZE               512
//  <s> MSC Manufacturer String
#define CONFIG_USBDEV_MSC_MANUFACTURER_STRING       "omni"
//  <s> MSC Product String
#define CONFIG_USBDEV_MSC_PRODUCT_STRING            "omni"
//  <s> MSC Serial Number String
#define CONFIG_USBDEV_MSC_VERSION_STRING            "0.0.1"
//  <c> Enable MSC Thread
//#define CONFIG_USBDEV_MSC_THREAD
//  </c>
//  <o> MSC Thread Priority <0-15>
#define CONFIG_USBDEV_MSC_PRIO                      4
//  <o> MSC Thread Stack Size <2048-65536>
#define CONFIG_USBDEV_MSC_STACKSIZE                 2048
//  </h>

//  <h> USB Device RNDIS Class
//  <o> RNDIS Response Buffer Size <156-512>
#define CONFIG_USBDEV_RNDIS_RESP_BUFFER_SIZE        156
//  <o> Ethernet maximum frame size
//  <i> RNDIS transfer buffer size, must be a multiple of (1536 + 44)
#define CONFIG_USBDEV_RNDIS_ETH_MAX_FRAME_SIZE      1580
//  <o> RNDIS Vendor ID
#define CONFIG_USBDEV_RNDIS_VENDOR_ID               0x0000FFFF
//  <s> RNDIS Vendor Description
#define CONFIG_USBDEV_RNDIS_VENDOR_DESC             "omni"
//  <c> Enable RNDIS LwIP
//#define CONFIG_USBDEV_RNDIS_USING_LWIP
//  </c>
//  </h>
// </h>

// <h> USB Host Stack Configuration
//  <o> EP0 transfer buffer size <512=>512 <1024=>1024 <2048=>2048
#define CONFIG_USBHOST_REQUEST_BUFFER_LEN           512
//  <o> Control Transfer Timeout <1-1000>
#define CONFIG_USBHOST_CONTROL_TRANSFER_TIMEOUT     500
//  <o> Max Root Hub Ports <1-15>
#define CONFIG_USBHOST_MAX_RHPORTS                  1
//  <o> Max External Hub Ports <1-15>
#define CONFIG_USBHOST_MAX_EXTHUBS                  1
//  <o> Max External Hub Ports <1-15>
#define CONFIG_USBHOST_MAX_EHPORTS                  4
//  <o> Max Interface Number <1-15>
#define CONFIG_USBHOST_MAX_INTERFACES               8
//  <o> Max Intf Alternate Setting Number <1-15>
#define CONFIG_USBHOST_MAX_INTF_ALTSETTINGS         8
//  <o> Max Endpoint Number <1-15>
#define CONFIG_USBHOST_MAX_ENDPOINTS                4
//  <o> Max CDC ACM Class Number <1-15>
#define CONFIG_USBHOST_MAX_CDC_ACM_CLASS            4
//  <o> Max HID Class Number <1-15>
#define CONFIG_USBHOST_MAX_HID_CLASS                4
//  <o> Max MSC Class Number <1-15>
#define CONFIG_USBHOST_MAX_MSC_CLASS                2
//  <o> Max Audio Class Number <1-15>
#define CONFIG_USBHOST_MAX_AUDIO_CLASS              1
//  <o> Max Video Class Number <1-15>
#define CONFIG_USBHOST_MAX_VIDEO_CLASS              1
//  <o> Max Device Name Length <16=>16
#define CONFIG_USBHOST_DEV_NAMELEN                  16
//  <o> Host PSC Priority <0-15>
//  <i> Priority of host plugging threads (0 is the highest)
#define CONFIG_USBHOST_PSC_PRIO                     0
//  <o> Host PSC Stack Size <2048-65536>
#define CONFIG_USBHOST_PSC_STACKSIZE                2048
//  <c> Enable Host Get String Descriptor
//#define CONFIG_USBHOST_GET_STRING_DESC
//  </c>
//  <h> USB Host WINUSB
//      <c> Enable Host MS OS Feature
//#define CONFIG_USBHOST_MSOS_ENABLE
//      </c>
//      <o> Host MS OS Vendor Code <0x00-0xFF>
#define CONFIG_USBHOST_MSOS_VENDOR_CODE             0x00
//  </h>

//  <h> USB Host MSC
//      <o> MSC Class Transfer Timeout <1-5000>
#define CONFIG_USBHOST_MSC_TIMEOUT                  5000
//  </h>

//  <h> USB Host RNDIS
//      <o> RNDIS Ethernet maximum receive buffer size <2048-16384>
//      <i> This parameter affects usb performance, and depends on (TCP_WND)tcp eceive windows size,
//      <i> you can change to 2K ~ 16K and must be larger than TCP RX windows size in order to avoid being overflow.
#define CONFIG_USBHOST_RNDIS_ETH_MAX_RX_SIZE        2048
//      <o> RNDIS Ethernet maximum transmit buffer size <2048=>2048
//      <i> Because lwip do not support multi pbuf at a time, so increasing this variable has no performance improvement.
#define CONFIG_USBHOST_RNDIS_ETH_MAX_TX_SIZE        2048
//  </h>

//  <h> USB Host CDC NCM
//      <o> CDC NCM Ethernet maximum receive buffer size <2048-16384>
//      <i> This parameter affects usb performance, and depends on (TCP_WND)tcp eceive windows size,
//      <i> you can change to 2K ~ 16K and must be larger than TCP RX windows size in order to avoid being overflow.
#define CONFIG_USBHOST_CDC_NCM_ETH_MAX_RX_SIZE      2048
//      <o> CDC NCM Ethernet maximum transmit buffer size <2048=>2048
//      <i> Because lwip do not support multi pbuf at a time, so increasing this variable has no performance improvement.
#define CONFIG_USBHOST_CDC_NCM_ETH_MAX_TX_SIZE      2048
//  </h>

//  <h> USB Host RTL8152
//      <o> RTL8152 Ethernet maximum receive buffer size <2048-16384>
//      <i> This parameter affects usb performance, and depends on (TCP_WND)tcp eceive windows size,
//      <i> you can change to 2K ~ 16K and must be larger than TCP RX windows size in order to avoid being overflow.
#define CONFIG_USBHOST_RTL8152_ETH_MAX_RX_SIZE      2048
//      <o> RTL8152 Ethernet maximum transmit buffer size <2048=>2048
//      <i> Because lwip do not support multi pbuf at a time, so increasing this variable has no performance improvement.
#define CONFIG_USBHOST_RTL8152_ETH_MAX_TX_SIZE      2048
//  </h>

//  <h> USB Host Bluetooth
//      <c> Bluetooth HCI H4
//#define CONFIG_USBHOST_BLUETOOTH_HCI_H4
//      </c>
//      <c> Bluetooth HCI Log
//#define CONFIG_USBHOST_BLUETOOTH_HCI_LOG
//      </c>
//      <o> Bluetooth RX Buffer Size <2048-16384>
#define CONFIG_USBHOST_BLUETOOTH_RX_SIZE            2048
//      <o> Bluetooth TX Buffer Size <2048-16384>
#define CONFIG_USBHOST_BLUETOOTH_TX_SIZE            2048
//  </h>
// </h>

#endif /* CHERRYUSB_CONFIG_H */
