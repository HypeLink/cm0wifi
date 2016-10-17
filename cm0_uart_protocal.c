/****************************************Copyright (c)****************************************************
**                               Zhejiang Hulong Motor Co., LTD.
**
**                                 http://www.hmcmotor.com.cn
**
**      
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               xxx_uart_protocal.c
** Last modified date:      2016-09-30
** Last version:            V1.0
** Description:             协议实现函数及接口数据定义
** 							
**
**--------------------------------------------------------------------------------------------------------
** Created by:              yuk
** Created date:            2016-09-30
** Version:                 V1.0
** Descriptions:            The original version 初始版本
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
**********************************************************************************************************/

/*********************************************************************************************************
  Private Function Defines
*********************************************************************************************************/
#include<malloc.h>
#include "cm0_data_struct.h"

/*********************************************************************************************************
  Private Function Defines
*********************************************************************************************************/

bool Usart1_CMD_A1(void);
bool Usart1_CMD_A2(void);
bool Usart1_CMD_B1(void);
bool Usart1_CMD_B2(void);
bool Usart1_CMD_B3(void);
bool Usart1_CMD_B4(void);
bool Usart1_CMD_C1(void);
bool Usart1_CMD_C2(void);
bool Usart1_CMD_C3(void);
bool Usart1_CMD_C4(void);
bool Usart1_CMD_D1(void);
bool Usart1_CMD_D2(void);
bool Usart1_CMD_E1(void);
bool Usart1_CMD_E2(void);

bool Usart1_IRQ_Recv_Check(void);
bool Usart1_CMD_Data_Check(void);
bool Usart1_CMD_Done_Check(void);
bool Usart1_RECV_Data_Deal(void);

#define USART_RECV_DOHE		usart_states.uart_Flag0

typedef struct {
	Uint8	uart_Flag0:1;
	Uint8	uart_Flag1:1;
	Uint8	uart_Flag2:1;
	Uint8	uart_Flag3:1;

	Uint8	uart_Flag4:1;
	Uint8	uart_Flag5:1;
	Uint8	uart_Flag6:1;
	Uint8	uart_Flag7:1;

	Uint8	word_0;
	Uint8	word_1;
	Uint8	word_2;
	Uint8	word_3;
} CMD_State;

CMD_State usart_states = {0,};

typedef struct {
    Usart1_CMD cmdstep[3];
} CMD_Queue;

const CMD_Queue uart1_cmd_list[UART1_CMD_TOTAL] = {
	{ Usart1_CMD_A1, 		func_null, 		  func_null},		/*-0---A1---*/
	{ Usart1_CMD_A2, 		func_null, 		  func_null},		/*-1---A2---*/
	{ Usart1_CMD_B1_1, Usart1_CMD_B1_2, Usart1_CMD_B1_3},		/*-2---B1---*/
	{ Usart1_CMD_B2, 		func_null, 		  func_null},		/*-3---B2---*/
	{ Usart1_CMD_B3, 		func_null, 		  func_null},		/*-4---B3---*/
	{ Usart1_CMD_B4, 		func_null, 		  func_null},		/*-5---B4---*/
	{ Usart1_CMD_C1, 		func_null, 		  func_null},		/*-6---C1---*/
	{ Usart1_CMD_C2, 		func_null, 		  func_null},		/*-7---C2---*/
	{ Usart1_CMD_C3, 		func_null, 		  func_null},		/*-8---C3---*/
	{ Usart1_CMD_C4, 		func_null, 		  func_null},		/*-9---C4---*/
	{ Usart1_CMD_D1, 		func_null, 		  func_null},		/*-10--D1---*/
	{ Usart1_CMD_D2, 		func_null, 		  func_null},		/*-11--D2---*/
	{ Usart1_CMD_E1,	Send_CMD_Data, 		  func_null},		/*-12--E1---*/
	{ Usart1_CMD_E2, 	Send_CMD_Data, 		  func_null},		/*-13--E2---*/
};

Usart1_RCV uart1_rcv_list[UART1_RCV_TOTAL] = {
	Usart1_IRQ_Recv_Check,	/*-0---A----*/ 
	Usart1_CMD_Data_Check,  /*-1---B----*/ 
	Usart1_CMD_Done_Check,  /*-2---C----*/ 
	Usart1_RECV_Data_Deal,  /*-3---D----*/ 
};


#define		RX_BUFFER_LENGTH   100
#define		TX_BUFFER_LENGTH   100
#define		AT_BUFFER_LENGTH   50

static Uint8    GucUartRxBuffer[RX_BUFFER_LENGTH] = {0};                /* 接收缓冲区                   */
static Uint8    GucUartTxBuffer[TX_BUFFER_LENGTH] = {0};                /* 发送缓冲区                   */

Uint8  Out_waiting_index_G = 0;                                        /* 待发送数据索引值              */
Uint8  In_saved_index_G    = 0;                                        /* 已接收数据索引值              */
Uint8  In_waiting_index_G  = 0;                                        /* 待接收数据索引值              */

const char WORD_CMD_A1[]="";
const char WORD_CMD_A2[]="AT+SOCKB\r";
const char WORD_CMD_B1_1[]="AT+WJAP=";
const char WORD_CMD_B1_2[]="AT+SOCKB=";
const char WORD_CMD_B1_3[]="AT+TCPDISB=on\r";
const char WORD_CMD_B2[]="AT+WSCAN\r";
const char WORD_CMD_B3[]="AT+WRMID=Hulong02\r";
const char WORD_CMD_B4[]="AT+WAKEY=WPA2PSK,AES,2016101312";
const char WORD_CMD_C1[]="+++a";
const char WORD_CMD_C2[]="AT+TMODE=cmd\r";
const char WORD_CMD_C3[]="AT+E=on\r";
const char WORD_CMD_C4[]="AT+WMODE=APSTA\r";
const char WORD_CMD_D1[]="AT+RECV=54,1\r";
const char WORD_CMD_D2[]="AT+RCVB=54,1\r";
const char WORD_CMD_E1[]="AT+SEND=54\r";
const char WORD_CMD_E2[]="AT+SNDB=54\r";

/**
 * 
 * 
 * @author Liuq (2016-10-17)
 */



/**
 * 
 * 
 * @author wup (2016-10-17)
 */



/**
 * 
 * 
 * @author yuk (2016-10-17)
 */



/***--------------------END-------------------------------------------------------------*/



char CMDPAR_B1_1[] = {0,};
char CMDPAR_B1_2[] = {0,};
char CMDPAR_B1_3[] = {0,};

Uint8 Send_Data_Buff[TX_BUFFER_LENGTH] = {0,};
Uint8 Recv_ATcm_Buff[AT_BUFFER_LENGTH] = {0,};
Uint8 Recv_Data_Buff[TX_BUFFER_LENGTH] = {0,};

typedef enum
{
	CMD_A1,
	CMD_A2,
	CMD_B1,
	CMD_B2,
	CMD_B3,
	CMD_B4,
	CMD_C1,
	CMD_C2,
	CMD_C3,
	CMD_C4,
	CMD_D1,
	CMD_D2,
	CMD_E1,
	CMD_E2,
	CMD_NULL,
} CMD_TYPE;

typedef enum
{
	AT_CMD_A1,
	AT_CMD_A2,
	AT_CMD_B1_1,
	AT_CMD_B1_2,
	AT_CMD_B1_3,
	AT_CMD_B2,
	AT_CMD_B3,
	AT_CMD_B4,
	AT_CMD_C1,
	AT_CMD_C2,
	AT_CMD_C3,
	AT_CMD_C4,
	AT_CMD_D1,
	AT_CMD_D2,
	AT_CMD_E1,
	AT_CMD_E2,
	AT_CMD_DATA,
} CMD_CORE_TYPE;
 
const Uint8 * at_cmds_list[] = 
{		
	&WORD_CMD_A1,
	&WORD_CMD_A2,
	&WORD_CMD_B1_1,
	&WORD_CMD_B1_2,
	&WORD_CMD_B1_3,
	&WORD_CMD_B2,
	&WORD_CMD_B3,
	&WORD_CMD_B4,
	&WORD_CMD_C1,
	&WORD_CMD_C2,
	&WORD_CMD_C3,
	&WORD_CMD_C4,
	&WORD_CMD_D1,
	&WORD_CMD_D2,
	&WORD_CMD_E1,
	&WORD_CMD_E2,
};

bool get_sub_total(CMD_TYPE n)
{
	Uint8 i = 0;

	for (i=0; i<3; i++)
	{
		if(func_null == uart1_cmd_list[n].cmdstep[i])
			return i;
	}

	return i;
}

bool Core_CMD_Send(CMD_CORE_TYPE n)
{
	static Uint8 status = 0;

	switch(status)
	{
		case 0:
			memset(GucUartTxBuffer,'\0',TX_BUFFER_LENGTH);
			if (AT_CMD_DATA == n)
			{
				strcpy(GucUartTxBuffer,Send_Data_Buff);
			}
			else
			{
				strcpy(GucUartTxBuffer,at_cmds_list[n]);
				if (AT_CMD_B1_1 == n || AT_CMD_B1_2 == n || AT_CMD_B1_3 == n )
				{
					;
				}
			}
			Out_waiting_index_G = strlen(GucUartTxBuffer);
			USART1_SEND();

			status = 1;
			return 0;

		case 1:
			if(Usart1_CMD_Done_Check())
			{
				status = 0;
				return 1;
			}
			else
				return 0;
		default:
			return 0;
	}
	
}

/**
 * Usart1_CMD_Send 
 * 通信CMD_SEND 类命令处理函数 
 * 
 * @author yuk (2016-10-13)
 * 
 * @return bool 处理结束 返回1 未结束 返回0
 */
bool Usart1_CMD_Send(CMD_TYPE N)
{
	static Uint8 status = 0;

	Uint8 Sub_step_ok = 0;
	Uint8 Sub_step_total = 0;

	Sub_step_total = get_sub_total(N);

	for (i=0; i<Sub_step_total ;)
	{
		Sub_step_ok = uart1_cmd_list[N].cmdstep[i]();

		i = (Sub_step_ok) ? i++ : return 0;

		if(i == Sub_step_total)
			return 1;
		else
			return 0;
	}
}

bool Usart1_IRQ_Recv_Check(void)
{

}

bool Usart1_CMD_Data_Check(void)
{

}

bool Usart1_CMD_Done_Check(void)
{

}

bool Usart1_RECV_Data_Deal(void)
{

}

void Usart1_Rcv_Pro(void)
{

}

void USART1_Process(void)
{
	CMD_TYPE cmd_n;

	if(empty_queue(&Q))
	{
		en_queue(&Q, CMD_D1);
	}
	else
	{
		if(check_queue(&Q))
		{
			del_queue(&Q);
		}
	}
}
