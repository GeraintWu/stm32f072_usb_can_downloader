/*
 * downloader.c
 *
 *  Created on: 2019年12月12日
 *      Author: Jingtai_Wu
 */
#include "main.h"

static void can_packet_tx_rx(void);

void download_app(void)
{
	//uint32_t i;

	while(1)
	{
		if(g_usb_rx_complete == true)
		{
			g_usb_rx_complete = false;

			can_packet_tx_rx();

		} // end of if(g_usb_rx_complete == true)

	} //end of while(1)
}

static void can_packet_tx_rx(void)
{

	can_tx_buf.id = usb_rx_buf.msg.cmd;
	can_tx_buf.length = (uint8_t) usb_rx_buf.msg.length;
	can_rx_buf.id = 0; //clear CAN rx_cmd

	CAN_Send(&can_tx_buf);

	while(can_rx_buf.id != (usb_rx_buf.msg.cmd+1)); // wait ACK from loader

	usb_tx_buf.msg.cmd = can_rx_buf.id;
	usb_tx_buf.msg.length = (uint32_t) can_rx_buf.length;
	USB_Send(&usb_tx_buf);

}

