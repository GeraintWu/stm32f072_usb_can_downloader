/*
 * downloader.c
 *
 *  Created on: 2019年12月12日
 *      Author: Jingtai_Wu
 */
#include "main.h"

static uint8_t message_transport(void);
static void comm_error(void);

void download_app(void)
{
	uint32_t i;


	uint8_t ret;

	while(1)
	{
		if(g_usb_rx_complete == true)
		{
			g_usb_rx_complete = false;

			ret = message_transport();

#ifdef __DEBUG_PRINTF__
	       printf("ERROR CODE:%d\n", ret);
#endif

	       if(ret == COMM_FAIL)
	       {
	    	   comm_error();
	       }
		} // end of if(g_usb_rx_complete == true)

		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        for(i=0;i<1600000;i++)
        	if(g_usb_rx_complete == true) break;

	} //end of while(1)
}

static uint8_t message_transport(void)
{
	comm_status status;

    uint32_t tickstart = 0U;

	can_tx_buf.id = usb_rx_buf.msg.cmd;
	can_tx_buf.length = (uint8_t) usb_rx_buf.msg.length;
	can_rx_buf.id = 0; //clear CAN rx_cmd

	status = CAN_Send(&can_tx_buf);

	if(status != COMM_OK)
		return COMM_FAIL;

    tickstart = HAL_GetTick();

	while(can_rx_buf.id != (usb_rx_buf.msg.cmd+1)) // wait ACK from loader
	{
        if((HAL_GetTick()-tickstart) > COMM_TIMEOUT)
        {
            // non-acknowledge
            return COMM_FAIL;
        }
    }


	usb_tx_buf.msg.cmd = can_rx_buf.id;
	usb_tx_buf.msg.length = (uint32_t) can_rx_buf.length;
	status = USB_Send(&usb_tx_buf);

	if(status != COMM_OK)
		return COMM_FAIL;

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);

}

static void comm_error(void)
{
	memset(usb_tx_buf.packet, 0, sizeof(usb_tx_buf.packet));
	USB_Send(&usb_tx_buf);
}

