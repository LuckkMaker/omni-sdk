/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Includes ------------------------------------------------------------------*/
#include "cdc_acm_hid.h"

/* Private includes ----------------------------------------------------------*/
#include "usbd_cdc.h"
#include "usbd_hid.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define USBD_VID           0x0483
#define USBD_PID           0xF001
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

/*!< endpoint address */
#define CDC_IN_EP               0x81
#define CDC_OUT_EP              0x01
#define CDC_INT_EP              0x83

#define HID_IN_EP               0x82
#ifdef CONFIG_USB_HS
#define HID_IN_EP_SIZE          1024
#define HID_IN_EP_INTERVAL      4
#else
#define HID_IN_EP_SIZE          64
#define HID_IN_EP_INTERVAL      10
#endif  // CONFIG_USB_HS

#define HID_OUT_EP              0x02
#ifdef CONFIG_USB_HS
#define HID_OUT_EP_SIZE         1024
#define HID_OUT_EP_INTERVAL     4
#else
#define HID_OUT_EP_SIZE         64
#define HID_OUT_EP_INTERVAL     10
#endif  // CONFIG_USB_HS

#ifdef CONFIG_USB_HS
#define CDC_MAX_MPS 512
#else
#define CDC_MAX_MPS 64
#endif

/*!< config descriptor size */
#define USB_CONFIG_SIZE (9 + CDC_ACM_DESCRIPTOR_LEN + USB_HID_CONFIG_DESC_SIZ)

#define USB_HID_CONFIG_DESC_SIZ (9 + 9 + 7 + 7)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/*!< global descriptor */
const uint8_t cdc_acm_hid_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0xEF, 0x02, 0x01, USBD_VID, USBD_PID, 0x0100, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x03, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    CDC_ACM_DESCRIPTOR_INIT(0x00, CDC_INT_EP, CDC_OUT_EP, CDC_IN_EP, CDC_MAX_MPS, 0x02),
    ///////////////////////////////////////
    /// Custom HID descriptor
    ///////////////////////////////////////
    /************** Descriptor of Custom interface *****************/
    0x09,                          /* bLength: Interface Descriptor size */
    USB_DESCRIPTOR_TYPE_INTERFACE, /* bDescriptorType: Interface descriptor type */
    0x02,                          /* bInterfaceNumber: Number of Interface */
    0x00,                          /* bAlternateSetting: Alternate setting */
    0x02,                          /* bNumEndpoints */
    0x03,                          /* bInterfaceClass: HID */
    0x01,                          /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    0x00,                          /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,                             /* iInterface: Index of string descriptor */
    /******************** Descriptor of Custom HID ********************/
    0x09,                          /* bLength: HID Descriptor size */
    HID_DESCRIPTOR_TYPE_HID,       /* bDescriptorType: HID */
    0x11,                          /* bcdHID: HID Class Spec release number */
    0x01,
    0x00,                          /* bCountryCode: Hardware target country */
    0x01,                          /* bNumDescriptors: Number of HID class descriptors to follow */
    0x22,                          /* bDescriptorType */
    HID_CUSTOM_REPORT_DESC_SIZE,   /* wItemLength: Total length of Report descriptor */
    0x00,
    /******************** Descriptor of Custom in endpoint ********************/
    0x07,                          /* bLength: Endpoint Descriptor size */
    USB_DESCRIPTOR_TYPE_ENDPOINT,  /* bDescriptorType: */
    HID_IN_EP,                     /* bEndpointAddress: Endpoint Address (IN) */
    0x03,                          /* bmAttributes: Interrupt endpoint */
    WBVAL(HID_IN_EP_SIZE),         /* wMaxPacketSize: 4 Byte max */
    HID_IN_EP_INTERVAL,            /* bInterval: Polling Interval */
    /******************** Descriptor of Custom out endpoint ********************/
    0x07,                          /* bLength: Endpoint Descriptor size */
    USB_DESCRIPTOR_TYPE_ENDPOINT,  /* bDescriptorType: */
    HID_OUT_EP,                    /* bEndpointAddress: Endpoint Address (OUT) */
    0x03,                          /* bmAttributes: Interrupt endpoint */
    WBVAL(HID_OUT_EP_SIZE),        /* wMaxPacketSize: 4 Byte max */
    HID_OUT_EP_INTERVAL,           /* bInterval: Polling Interval */
    ///////////////////////////////////////
    /// string0 descriptor
    ///////////////////////////////////////
    USB_LANGID_INIT(USBD_LANGID_STRING),
    ///////////////////////////////////////
    /// string1 descriptor
    ///////////////////////////////////////
    0x14,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'C', 0x00,                  /* wcChar0 */
    'h', 0x00,                  /* wcChar1 */
    'e', 0x00,                  /* wcChar2 */
    'r', 0x00,                  /* wcChar3 */
    'r', 0x00,                  /* wcChar4 */
    'y', 0x00,                  /* wcChar5 */
    'U', 0x00,                  /* wcChar6 */
    'S', 0x00,                  /* wcChar7 */
    'B', 0x00,                  /* wcChar8 */
    ///////////////////////////////////////
    /// string2 descriptor
    ///////////////////////////////////////
    0x26,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'C', 0x00,                  /* wcChar0 */
    'h', 0x00,                  /* wcChar1 */
    'e', 0x00,                  /* wcChar2 */
    'r', 0x00,                  /* wcChar3 */
    'r', 0x00,                  /* wcChar4 */
    'y', 0x00,                  /* wcChar5 */
    'U', 0x00,                  /* wcChar6 */
    'S', 0x00,                  /* wcChar7 */
    'B', 0x00,                  /* wcChar8 */
    ' ', 0x00,                  /* wcChar9 */
    'C', 0x00,                  /* wcChar10 */
    'D', 0x00,                  /* wcChar11 */
    'C', 0x00,                  /* wcChar12 */
    ' ', 0x00,                  /* wcChar13 */
    'D', 0x00,                  /* wcChar14 */
    'E', 0x00,                  /* wcChar15 */
    'M', 0x00,                  /* wcChar16 */
    'O', 0x00,                  /* wcChar17 */
    ///////////////////////////////////////
    /// string3 descriptor
    ///////////////////////////////////////
    0x16,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    '2', 0x00,                  /* wcChar0 */
    '0', 0x00,                  /* wcChar1 */
    '2', 0x00,                  /* wcChar2 */
    '2', 0x00,                  /* wcChar3 */
    '1', 0x00,                  /* wcChar4 */
    '2', 0x00,                  /* wcChar5 */
    '3', 0x00,                  /* wcChar6 */
    '4', 0x00,                  /* wcChar7 */
    '5', 0x00,                  /* wcChar8 */
    '6', 0x00,                  /* wcChar9 */
#ifdef CONFIG_USB_HS
    ///////////////////////////////////////
    /// device qualifier descriptor
    ///////////////////////////////////////
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x02,
    0x02,
    0x01,
    0x40,
    0x01,
    0x00,
#endif
    0x00
};

/*!< custom hid report descriptor */
const uint8_t hid_custom_report_desc[HID_CUSTOM_REPORT_DESC_SIZE] = {
#ifdef CONFIG_USB_HS
    /* USER CODE BEGIN 0 */
    0x06, 0x00, 0xff, /* USAGE_PAGE (Vendor Defined Page 1) */
    0x09, 0x01,       /* USAGE (Vendor Usage 1) */
    0xa1, 0x01,       /* COLLECTION (Application) */
    0x85, 0x02,       /*   REPORT ID (0x02) */
    0x09, 0x02,       /*   USAGE (Vendor Usage 1) */
    0x15, 0x00,       /*   LOGICAL_MINIMUM (0) */
    0x25, 0xff,       /*LOGICAL_MAXIMUM (255) */
    0x75, 0x08,        /*   REPORT_SIZE (8) */
    0x96, 0xff, 0x03, /*   REPORT_COUNT (63) */
    0x81, 0x02,       /*   INPUT (Data,Var,Abs) */
    /* <___________________________________________________> */
    0x85, 0x01,       /*   REPORT ID (0x01) */
    0x09, 0x03,       /*   USAGE (Vendor Usage 1) */
    0x15, 0x00,       /*   LOGICAL_MINIMUM (0) */
    0x25, 0xff, /*   LOGICAL_MAXIMUM (255) */
    0x75, 0x08,       /*   REPORT_SIZE (8) */
    0x96, 0xff, 0x03,   /*   REPORT_COUNT (63) */
    0x91, 0x02,       /*   OUTPUT (Data,Var,Abs) */
    /* USER CODE END 0 */
    0xC0 /*     END_COLLECTION	             */
#else
    /* USER CODE BEGIN 0 */
    0x06, 0x00, 0xff, /* USAGE_PAGE (Vendor Defined Page 1) */
    0x09, 0x01,       /* USAGE (Vendor Usage 1) */
    0xa1, 0x01,       /* COLLECTION (Application) */
    0x85, 0x02,       /*   REPORT ID (0x02) */
    0x09, 0x01,       /*   USAGE (Vendor Usage 1) */
    0x15, 0x00,       /*   LOGICAL_MINIMUM (0) */
    0x26, 0xff, 0x00, /*   LOGICAL_MAXIMUM (255) */
    0x95, 0x40 - 1,   /*   REPORT_COUNT (63) */
    0x75, 0x08,       /*   REPORT_SIZE (8) */
    0x81, 0x02,       /*   INPUT (Data,Var,Abs) */
    /* <___________________________________________________> */
    0x85, 0x01,       /*   REPORT ID (0x01) */
    0x09, 0x01,       /*   USAGE (Vendor Usage 1) */
    0x15, 0x00,       /*   LOGICAL_MINIMUM (0) */
    0x26, 0xff, 0x00, /*   LOGICAL_MAXIMUM (255) */
    0x95, 0x40 - 1,   /*   REPORT_COUNT (63) */
    0x75, 0x08,       /*   REPORT_SIZE (8) */
    0x91, 0x02,       /*   OUTPUT (Data,Var,Abs) */
    /* USER CODE END 0 */
    0xC0 /*     END_COLLECTION	             */
#endif
};

/* 2048 is only for test speed , please use CDC_MAX_MPS for common*/
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t cdc_read_buffer[CDC_MAX_MPS];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t cdc_write_buffer[CDC_MAX_MPS];

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t hid_read_buffer[HID_OUT_EP_SIZE];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t hid_send_buffer[HID_IN_EP_SIZE];

#define HID_STATE_IDLE 0
#define HID_STATE_BUSY 1

/*!< hid state ! Data can be sent only when state is idle  */
static volatile uint8_t custom_state;

volatile bool ep_tx_busy_flag = false;

/* Private function prototypes -----------------------------------------------*/

void usbd_event_handler(uint8_t busid, uint8_t event) {
    switch (event) {
        case USBD_EVENT_RESET:
            break;
        case USBD_EVENT_CONNECTED:
            break;
        case USBD_EVENT_DISCONNECTED:
            break;
        case USBD_EVENT_RESUME:
            break;
        case USBD_EVENT_SUSPEND:
            break;
        case USBD_EVENT_CONFIGURED:
            ep_tx_busy_flag = false;
            /* setup first out ep read transfer */
            usbd_ep_start_read(busid, CDC_OUT_EP, cdc_read_buffer, CDC_MAX_MPS);
            usbd_ep_start_read(busid, HID_OUT_EP, hid_read_buffer, HID_OUT_EP_SIZE);
            break;
        case USBD_EVENT_SET_REMOTE_WAKEUP:
            break;
        case USBD_EVENT_CLR_REMOTE_WAKEUP:
            break;

        default:
            break;
    }
}

/* External functions --------------------------------------------------------*/

__WEAK void usbd_cdc_get_out_data(uint8_t busid, uint8_t *data, uint32_t len) {
    ARG_UNUSED(busid);
    ARG_UNUSED(data);
    ARG_UNUSED(len);
}

void usbd_cdc_acm_bulk_out(uint8_t busid, uint8_t ep, uint32_t nbytes) {
//    USB_LOG_RAW("actual out len:%d\r\n", nbytes);
//    for (int i = 0; i < nbytes; i++) {
//        printf("%02x ", cdc_read_buffer[i]);
//    }
//    printf("\r\n");
    usbd_cdc_get_out_data(busid, cdc_read_buffer, nbytes);

    /* setup next out ep read transfer */
    usbd_ep_start_read(busid, CDC_OUT_EP, cdc_read_buffer, sizeof(cdc_read_buffer));
}

void usbd_cdc_acm_bulk_in(uint8_t busid, uint8_t ep, uint32_t nbytes) {
    // USB_LOG_RAW("actual in len:%d\r\n", nbytes);

    if ((nbytes % usbd_get_ep_mps(busid, ep)) == 0 && nbytes) {
        /* send zlp */
        usbd_ep_start_write(busid, CDC_IN_EP, NULL, 0);
    } else {
        ep_tx_busy_flag = false;
    }
}

static void usbd_hid_custom_in_callback(uint8_t busid, uint8_t ep, uint32_t nbytes) {
    (void)busid;
    (void)ep;
    USB_LOG_RAW("actual in len:%d\r\n", nbytes);
    custom_state = HID_STATE_IDLE;
}

static void usbd_hid_custom_out_callback(uint8_t busid, uint8_t ep, uint32_t nbytes) {
    USB_LOG_RAW("actual out len:%d\r\n", nbytes);
    usbd_ep_start_read(busid, ep, hid_read_buffer, HID_IN_EP_SIZE);
    hid_read_buffer[0] = 0x02; /* IN: report id */
    usbd_ep_start_write(busid, HID_IN_EP, hid_read_buffer, nbytes);
}

/*!< endpoint call back */
struct usbd_endpoint cdc_out_ep = {
    .ep_addr = CDC_OUT_EP,
    .ep_cb = usbd_cdc_acm_bulk_out
};

struct usbd_endpoint cdc_in_ep = {
    .ep_addr = CDC_IN_EP,
    .ep_cb = usbd_cdc_acm_bulk_in
};

struct usbd_endpoint custom_hid_in_ep = {
    .ep_cb = usbd_hid_custom_in_callback,
    .ep_addr = HID_IN_EP
};

struct usbd_endpoint custom_hid_out_ep = {
    .ep_cb = usbd_hid_custom_out_callback,
    .ep_addr = HID_OUT_EP
};

struct usbd_interface cdc_intf0;
struct usbd_interface cdc_intf1;
struct usbd_interface hid_intf;

int cdc_acm_hid_init(uint8_t busid, uint32_t reg_base) {
    int ret;

    const uint8_t data[10] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30 };

    memcpy(&cdc_write_buffer[0], data, 10);
    memset(&cdc_write_buffer[10], 'a', CDC_MAX_MPS - 10);

    usbd_desc_register(busid, cdc_acm_hid_descriptor);
    usbd_add_interface(busid, usbd_cdc_acm_init_intf(busid, &cdc_intf0));
    usbd_add_interface(busid, usbd_cdc_acm_init_intf(busid, &cdc_intf1));
    usbd_add_endpoint(busid, &cdc_out_ep);
    usbd_add_endpoint(busid, &cdc_in_ep);

    usbd_add_interface(busid, usbd_hid_init_intf(busid, &hid_intf, hid_custom_report_desc, HID_CUSTOM_REPORT_DESC_SIZE));
    usbd_add_endpoint(busid, &custom_hid_in_ep);
    usbd_add_endpoint(busid, &custom_hid_out_ep);

    ret = usbd_initialize(busid, reg_base, usbd_event_handler);

    return ret;
}

/********************** CDC ACM **************************/

volatile uint8_t dtr_enable = 0;

void usbd_cdc_acm_get_line_coding(uint8_t busid, uint8_t intf, struct cdc_line_coding *line_coding) {
    line_coding->dwDTERate = 115200;    /* baudrate */
    line_coding->bDataBits = 8;         /* data bits */
    line_coding->bParityType = 0;       /* parity */
    line_coding->bCharFormat = 0;       /* stop bits */
}

void usbd_cdc_acm_set_line_coding(uint8_t busid, uint8_t intf, struct cdc_line_coding *line_coding) {
    ARG_UNUSED(busid);
    ARG_UNUSED(intf);
    ARG_UNUSED(line_coding);
}

void usbd_cdc_acm_set_dtr(uint8_t busid, uint8_t intf, bool dtr) {
    if (dtr) {
        dtr_enable = 1;
    } else {
        dtr_enable = 0;
    }
}

void usbd_cdc_acm_set_rts(uint8_t busid, uint8_t intf, bool rts) {
    ARG_UNUSED(busid);
    ARG_UNUSED(intf);
    ARG_UNUSED(rts);
}

void usbd_cdc_acm_send_break(uint8_t busid, uint8_t intf) {
    ARG_UNUSED(busid);
    ARG_UNUSED(intf);
}

void cdc_acm_data_send_with_dtr_test(uint8_t busid) {
    if (dtr_enable) {
        ep_tx_busy_flag = true;
        memset(&cdc_write_buffer[0], 'a', 10);
        usbd_ep_start_write(busid, CDC_IN_EP, cdc_write_buffer, 10);
        while (ep_tx_busy_flag) {
        }
    }
}

uint8_t cdc_acm_data_send(uint8_t busid, uint8_t *data, uint32_t len) {
    ep_tx_busy_flag = true;
    usbd_ep_start_write(busid, CDC_IN_EP, data, len);
    while (ep_tx_busy_flag) {
    }

    return 0;
}
