/*
 * usb_user_if.c
 *
 *  Created on: 2019年12月11日
 *      Author: Jingtai_Wu
 */

#include "main.h"
#include "usbd_customhid.h"



extern USBD_HandleTypeDef hUsbDeviceFS;
extern CAN_HandleTypeDef hcan;
extern uint8_t USBD_CUSTOM_HID_SendReport(USBD_HandleTypeDef *pdev,
                                   uint8_t *report,
                                   uint16_t len);

usb_message_t usb_tx_buf;
usb_message_t usb_rx_buf;
can_message_t can_tx_buf;
can_message_t can_rx_buf;

volatile static uint8_t can_tx_complete;
static CAN_FilterTypeDef sFilterConfig;
static CAN_TxHeaderTypeDef can_tx_hd;
static CAN_RxHeaderTypeDef can_rx_hd;
static uint32_t messagebox;



/*FUNCTION**********************************************************************
 *
 * Function Name : CAN_Filter_Init
 * Description   : Filter Init and start
 * Implements    :
 *END**************************************************************************/

void CAN_Filter_Init(void)
{
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;

    if(HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
    {
        /* Notification Error */
        Error_Handler();
    }

    HAL_CAN_Start(&hcan);

}

/*FUNCTION**********************************************************************
 *
 * Function Name : CAN_Send
 * Description   : CAN message send
 * Implements    :
 *END**************************************************************************/
uint8_t CAN_Send(can_message_t *message)
{

    uint32_t tickstart = 0U;

    //can_tx_hd.StdId = 0x321;
    can_tx_hd.ExtId = message->id;
    can_tx_hd.RTR = CAN_RTR_DATA;
    can_tx_hd.IDE = CAN_ID_EXT;
    can_tx_hd.DLC = message->length;
    can_tx_hd.TransmitGlobalTime = DISABLE;

    tickstart = HAL_GetTick();
    while( HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0)
    {
        if((HAL_GetTick()-tickstart) > 0xFFFF)
        {
            // fail to get mailbox
            return 1;
        }
    }

    can_tx_complete = 0;
    tickstart = HAL_GetTick();

    HAL_CAN_AddTxMessage(&hcan, &can_tx_hd, message->data, &messagebox);

    while(can_tx_complete == 0)
    {
        if((HAL_GetTick()-tickstart) > COMM_TIMEOUT)
        {
            //fail to complete send
            return 1;
        }
    }
    return 0;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : USB_Send
 * Description   : USB message send
 * Implements    :
 *END**************************************************************************/
uint8_t USB_Send(usb_message_t *message)
{
    uint32_t tickstart = 0U;

    tickstart = HAL_GetTick();

    while(USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t*)message, 64) != USBD_OK)
    {
        if((HAL_GetTick()-tickstart) > COMM_TIMEOUT)
        {
            //fail to send
            return 1;
        }
    }
    return 0;
}


/**************************INTERRUPT CALLBACK *********************************/
/*FUNCTION**********************************************************************
 *
 * Function Name :
 * Description   :
 * Implements    :
 *END**************************************************************************/

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
{
    can_tx_complete = 1;
}
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &can_rx_hd, can_rx_buf.data);
    can_rx_buf.id = can_rx_hd.ExtId;
}

void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
    Error_Handler();
}

void USB_Receive_Callback(uint8_t event_idx, uint8_t state)
{

	//USBD_CUSTOM_HID_HandleTypeDef *hhid = hUsbDeviceFS.pClassData;
	memcpy(usb_rx_buf.packet, hUsbDeviceFS.pClassData, 64);
#ifdef __DEBUG_PRINTF__
	printf("usb data received!\n");
#endif
}
