/*
 * usb_user_if.h
 *
 *  Created on: 2019年12月11日
 *      Author: Jingtai_Wu
 */

#ifndef INC_DRIVER_USER_IF_H_
#define INC_DRIVER_USER_IF_H_

#include <stdbool.h>

#define COMM_TIMEOUT (1000)

typedef enum
{
  COMM_OK = 0x00U,
  COMM_FAIL = 0x01U
} comm_status;


typedef struct {
    uint32_t cmd ;              /*!< command of the message */
    uint32_t length;            /*!< Length of payload in bytes */
#if 1
	uint8_t payload[8];
	uint8_t dummy[48];
	uint8_t *pdata;
#else
	uint8_t data[56];           /*!< Data bytes of the CAN message*/
#endif
} usb_msg;


typedef union {
	usb_msg msg;
	uint8_t packet[64];
} usb_message_t;


typedef struct {
	uint32_t cs;       /*!< Code and Status*/
    uint32_t id;       /*!< ID of the message */
    //uint8_t data[64];  /*!< Data bytes of the CAN message*/
    uint8_t *pdata;
    uint8_t length;    /*!< Length of payload in bytes */
} can_message_t;


void message_buffer_init(void);
uint8_t USB_Send(usb_message_t *message);
void USB_Receive_Callback(uint8_t event_idx, uint8_t state);
void CAN_Filter_Init(void);
uint8_t CAN_Send(can_message_t *message);


extern usb_message_t usb_tx_buf;
extern usb_message_t usb_rx_buf;
extern can_message_t can_tx_buf;
extern can_message_t can_rx_buf;
extern volatile bool g_usb_rx_complete;

#endif /* INC_DRIVER_USER_IF_H_ */
