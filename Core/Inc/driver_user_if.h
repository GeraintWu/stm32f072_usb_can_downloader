/*
 * usb_user_if.h
 *
 *  Created on: 2019年12月11日
 *      Author: Jingtai_Wu
 */

#ifndef INC_DRIVER_USER_IF_H_
#define INC_DRIVER_USER_IF_H_

#define COMM_TIMEOUT (0xFFFF)

typedef struct {
    uint8_t cmd ;              /*!< command of the message */
    uint8_t length;    /*!< Length of payload in bytes */
    uint8_t data[62];  /*!< Data bytes of the CAN message*/
} usb_msg;

typedef union {
	usb_msg msg;
	uint8_t packet[64];
} usb_message_t;


typedef struct {
	uint32_t cs;       /*!< Code and Status*/
    uint32_t id;       /*!< ID of the message */
    uint8_t data[64];  /*!< Data bytes of the CAN message*/
    uint8_t length;    /*!< Length of payload in bytes */
} can_message_t;


uint8_t USB_Send(usb_message_t *message);
void USB_Receive_Callback(uint8_t event_idx, uint8_t state);
void CAN_Filter_Init(void);
uint8_t CAN_Send(can_message_t *message);

extern usb_message_t usb_tx_buf;
extern usb_message_t usb_rx_buf;

#endif /* INC_DRIVER_USER_IF_H_ */
