///*
// * com.c
// *
// *  Created on: Aug 4, 2018
// *      Author: Sahar Elnagar
// */
//
//
//#include"com.h"
//
//#define MAX_SIZE          1000
//#define HEADER_SIZE       3
//#define PING_REQUEST_TIME 3
//#define PING_REQUEST      0x55
//#define TIMEOUT_REQUEST   5
//#define  BITS0_7          0xFF
//#define  FIVE             5
//#define  ZERO             0
//#define  ONE              1
//                          /*enums&structs*/
//typedef enum
//{
// TX_IDLE=0,
// SENDING_FRAME,
// SENDING_BYTE,
// SENDING_BYTE_DONE,              /*important to send new data*/
// TRANSMIT_PING_REQUEST,
// TRANSMIT_TIME_OUT,
// RX_IDLE,
// RECEIVING_HEADER,
// RECEIVING_FRAME,
// RECEIVE_COMPLETE,
// RECEIVE_PING_REQUEST,
// RECEIVE_TIME_OUT
//
//}eunmComStates;
//                            /*Global*/
//static uint8    Current_State=TX_IDLE ;
//static uint8    Last_State=RX_IDLE ;
//static uint16   Tx_counter=ZERO;
//static uint8    Tx_pend_counter=ZERO;
//static uint8    Rx_pend_counter=ZERO;
//static uint16   RX_counter=ZERO;
//static uint8    Receiving_frame_flag=ZERO;
//typedef struct
//{
//	uint8  cmd;
//	uint16 size;
//	uint8* data;
//	int16   cs;
//}strDataFrame;
//
//uint8 ComReceiveBuffer[MAX_SIZE];
//strDataFrame* global_ptr_data_frame;
//strComNotification* global_com_notification ;
//                              /*Static_Functions*/
// /*
//  * send UART
//  * transmit Ok
//  * ISR
//  * ComUart_Cb
//  * */
//
//static void ComUartTxCb(void)
//{
//	Tx_pend_counter--;    /*Reset Tx_pend_counter*/
//	if (Last_State==TRANSMIT_PING_REQUEST)
//	{
//		Tx_counter--;
//		Last_State=SENDING_BYTE;
//	}
//	else
//
//   Current_State=SENDING_BYTE_DONE ;
//   Tx_counter++;
//
//}
//
//
//static void ComUartRxCb(void)
//{
//  Rx_pend_counter--;    /*Reset Rx_pend_counter*/
//  if(Receiving_frame_flag==ZERO)
//  {
//    Receiving_frame_flag=ONE ;                /*New Frame*/
//  }
//
//
//}
//
//
//static void ComTimerCb(void)
//{
// Tx_pend_counter++;
// Rx_pend_counter++;
// if(Rx_pend_counter==PING_REQUEST_TIME)
// {
//	 Last_State=TRANSMIT_PING_REQUEST;
//	 Current_State=SENDING_BYTE;
//	 //UART_Send(PING_REQUEST);
//
// }
// if (Rx_pend_counter==TIMEOUT_REQUEST)
// {
//	 Current_State=RECEIVE_TIME_OUT;
// }
//  if (Tx_pend_counter==TIMEOUT_REQUEST)
//  {
//	  Current_State=TRANSMIT_TIME_OUT;
//  }
//
//}
//
//
//
//
//                            /*Functions_Implementaion*/
//enumComErrors Com_Init(uint8 UART_BASE,strComNotification *com_notification)
//{
//
//	enumComErrors rtn_val=COM_NO_ERRORS;
//	/*Call UART_HAL */
//	/*Init Timer*/
//    global_com_notification=com_notification;
//	return rtn_val;
//}
//
//
//enumComErrors Com_Send(uint8*Data,uint16 Size,enumComCmd  CMD)
//{
//	enumComErrors rtn_val=COM_NO_ERRORS;
//
//	if(Data!=NULL&&Size<=MAX_SIZE)
//	{
//	   if(Current_State==TX_IDLE)
//	   {
//		global_ptr_data_frame->data=Data;
//		global_ptr_data_frame->size=Size;
//
//		Current_State=SENDING_FRAME;
//	   }
//	   else
//	   {
//		   rtn_val=COM_BUSY;
//	   }
//
//	}
//	else
//	{
//		rtn_val=COM_INVALID_ARGUMENT;
//	}
//
//	return rtn_val;
//}
//
//void Com_Dispatch(void)
//{
//
//	switch (Current_State)
//	{
//	case TX_IDLE:
//
//	break;
//	case SENDING_FRAME:
//
//		// UART_Send(global_ptr_data_frame->cmd);
//		Current_State=SENDING_BYTE ;
//	break;
//	case SENDING_BYTE:
//
//	break;
//	case SENDING_BYTE_DONE:
//       if(Tx_counter<HEADER_SIZE)
//       {
//
//        // UART_Send(global_ptr_data_frame->size&(BITS0_7<<((Tx_counter-1)*8))));
//
//
//       }
//       else
//       {
//
//    	   if(Tx_counter>(global_ptr_data_frame->size)+HEADER_SIZE)
//    	   {
//    		 //  UART_Send((global_ptr_data_frame->cs)&(BITS0_7<<((((counter-(global_ptr_data_frame->size)+HEADER_SIZE))*8))));
//    	   }
//		   else
//		   {
//			    (global_ptr_data_frame->cs)+=global_ptr_data_frame->data[Tx_counter]	; /*Calculate_CS*/
//			   //  UART_Send(global_ptr_data_frame->data[Tx_counter]);
//
//		   }
//
//
//       }
//       Current_State=SENDING_BYTE ;
//	   if(Tx_counter==(global_ptr_data_frame->size)+FIVE)
//	   {
//		 global_com_notification->TxNotification(FINISHED_SENDING_FRAME);
//		Current_State=TX_IDLE ;
//	   }
//	break;
//
//	case TRANSMIT_PING_REQUEST:
//
//
//	break;
//
//	case TRANSMIT_TIME_OUT:
//	     global_com_notification->TxNotification(TRANSMITTING_TIMEOUT);
//	break;
//
//
//
//	}
//
//}
