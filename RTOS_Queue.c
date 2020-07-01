/*
* Created: 5/20/2020 10:17:22 AM
* Author : Khalid
*/
#if 1
/*include FreeRTOS files*/
#include "FreeRTOS.h"
#include "task.h"

#include "queue.h"
#include "semphr.h"
/*Include drivers*/
#include "board.h"
#include "uart.h"/* Prototype */void T_SEND(void* pvData);void T_Recieve(void* pvData);void system_init(void);/* OS Services Declaration */xQueueHandle     mqTermerminal ;int main(void){	/* Init Peripherals */	system_init();		/* OS Services Create and Init */		mqTermerminal = xQueueCreate(10,1);		/* Tasks Create */	xTaskCreate(T_SEND,"T_SEND",100,NULL,1,NULL);	xTaskCreate(T_Recieve,"T_Recieve",100,NULL,2,NULL);		/* Start OS or Scheduler */	vTaskStartScheduler();}void T_SEND(void* pvData){	INT8U Data = 0;		while(1){		if(Uart_ReceiveByte_Unblock(UART_0,&Data))		{			xQueueSend(mqTermerminal,&Data,portMAX_DELAY);		}	}}void T_Recieve(void* pvData){	INT8U RecevedData=0 ;	while(1){				if(xQueueReceive(mqTermerminal,&RecevedData,portMAX_DELAY))		{			/*ACT AS IF THERE IS SOME PROCESSING */			vTaskDelay(3000);			UART_SendByte(UART_0,RecevedData);		}			}}/*Send data to uart0 every second*/void system_init(void){	UART_Init(UART_0,9600);	Uart_SendStr(UART_0,"Started ...\r\n");}


#endif