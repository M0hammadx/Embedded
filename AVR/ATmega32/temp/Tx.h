///*
// * com.h
// *
// *  Created on: Aug 4, 2018
// *      Author: Sahar Elnagar
// */
//
//#ifndef COM_H_
//#define COM_H_
//#include "../../HAL/common.h"
//
//
//
//
//
//typedef enum
//{
//	COM_NO_ERRORS,
//	COM_INVALID_ARGUMENT,
//	COM_UNINITIALIZED,
//	COM_BUSY,
//}enumComErrors;
//
//typedef enum
//{
//	FINISHED_SENDING_FRAME,
//	FINISHED_RECEIVING_FRAME,
//    TRANSMITTING_TIMEOUT,
//	RECEIVING_TIMEOUT,
//}enumComNotification;
//
//typedef enum
//{
//  BLA,
//}enumComCmd;
//
//typedef struct
//{
//	void (*TxNotification)	(enumComNotification TxNotificationValue);
//	void (*RxNotification)	(enumComNotification RxNotificationValue);
//
//}strComNotification;
//
//                          /*Functions_Prototaypes*/
//
//enumComErrors Com_Init(uint8 UART_BASE,strComNotification *com_notification);
//
//enumComErrors Com_Send(uint8*Data,uint16 Size,enumComCmd  CMD);
//
//void Com_Dispatch(void);
//
//
//#endif /* COM_H_ */
