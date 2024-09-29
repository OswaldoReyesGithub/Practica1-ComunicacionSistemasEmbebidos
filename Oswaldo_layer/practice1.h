#ifndef PRACTICE1_H_
#define PRACTICE1_H_

//libraries
#include "board.h"
#include "practice1_cfg.h"

#define CRC_OK				1
#define CRC_NOT_OK			0
#define STATUS_OK			1
#define STATUS_NOT_OK		0

typedef void receive_cb_function(uint8_t *data, uint32_t len);

void Ethernet_Configuration_Init(receive_cb_function callback_function); 	//Ethernet_CFG_Init
void Ethernet_Data_Transmit(uint8_t *data, uint32_t len);			        //Ehernet_To_Send_Frame
void cb_app(uint8_t *data, uint32_t len);									//Callback_App

#endif /* PRACTICE1_H_ */
