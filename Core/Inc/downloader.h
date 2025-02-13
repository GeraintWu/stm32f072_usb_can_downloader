/*
 * downloader.h
 *
 *  Created on: 2019年12月12日
 *      Author: Jingtai_Wu
 */

#ifndef INC_DOWNLOADER_H_
#define INC_DOWNLOADER_H_

// ID (command) used for app update
#define CMD_UPDATE    (0x100)
#define CMD_ERASE     (0x200)
#define CMD_ADDR      (0x300)
#define CMD_DATA      (0x400)
#define CMD_END       (0x500)
//#define CMD_MASK_ANY  (0)

typedef enum
{
	rx_flash_update = CMD_UPDATE,
	rx_flash_erase = CMD_ERASE,
	rx_flash_data = CMD_DATA,
	rx_flash_end  = CMD_END,
	rx_flash_addr = CMD_ADDR

}rx_cmd_status_t;

typedef enum
{
	tx_flash_update_ack = CMD_UPDATE+1,
	tx_flash_erase_ack = CMD_ERASE+1,
	tx_flash_addr_ack = CMD_ADDR+1,
	tx_flash_data_ack = CMD_DATA+1,
	tx_flash_end_ack = CMD_END+1

}tx_cmd_status_t;


void download_app(void);




#endif /* INC_DOWNLOADER_H_ */
