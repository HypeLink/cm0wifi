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

Usart1_CMD uart1_cmd_list[UART1_CMD_TOTAL] = {
	Usart1_CMD_A1,			/*-0---A1---*/
	Usart1_CMD_A2,			/*-1---A2---*/
	Usart1_CMD_B1,			/*-2---B1---*/
	Usart1_CMD_B2,			/*-3---B2---*/
	Usart1_CMD_B3,			/*-4---B3---*/
	Usart1_CMD_B4,			/*-5---B4---*/
	Usart1_CMD_C1,			/*-6---C1---*/
	Usart1_CMD_C2,			/*-7---C2---*/
	Usart1_CMD_C3,			/*-8---C3---*/
	Usart1_CMD_C4,			/*-9---C4---*/
	Usart1_CMD_D1,			/*-10--D1---*/
	Usart1_CMD_D2,			/*-11--D2---*/
	Usart1_CMD_E1,			/*-12--E1---*/
	Usart1_CMD_E2,			/*-13--E2---*/
};

#define   RX_BUFFER_LENGTH   100
#define   TX_BUFFER_LENGTH   100
static unsigned char    GucUartRxBuffer[RX_BUFFER_LENGTH] = {0};                /* 接收缓冲区                   */
static unsigned char    GucUartTxBuffer[TX_BUFFER_LENGTH] = {0};                /* 发送缓冲区                   */

unsigned char  Out_waiting_index_G = 0;                                        /* 待发送数据索引值              */
unsigned char  In_saved_index_G    = 0;                                        /* 已接收数据索引值              */
unsigned char  In_waiting_index_G  = 0;                                        /* 待接收数据索引值              */

const char CMD_A1[]="";
const char CMD_A2[]="AT+SOCKB\r";
const char CMD_B1_1[]="AT+WJAP=";
const char CMD_B1_2[]="AT+SOCKB=";
const char CMD_B1_3[]="AT+TCPDISB=";
const char CMD_B2[]="AT+WSCAN\r";
const char CMD_B3[]="AT+WRMID=Hulong02\r";
const char CMD_B4[]="AT+WAKEY=WPA2PSK,AES,2016101312";
const char CMD_C1[]="+++a";
const char CMD_C2[]="AT+TMODE=cmd\r";
const char CMD_C3[]="AT+E=on\r";
const char CMD_C4[]="AT+WMODE=APSTA\r";
const char CMD_D1[]="AT+SOCKB\r";
const char CMD_D2[]="AT+SOCKB\r";
const char CMD_E1[]="AT+SOCKB\r";
const char CMD_E2[]="AT+SOCKB\r";

char CMDPAR_B1_1[] = {0,};
char CMDPAR_B1_2[] = {0,};
char CMDPAR_B1_3[] = {0,};

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
	AT_CMD_E2
} CMD_TYPE;
 
const char * at_cmds_list[] = 
{		
	&CMD_A1,
	&CMD_A2,
	&CMD_B1_1,
	&CMD_B1_2,
	&CMD_B1_3,
	&CMD_B2,
	&CMD_B3,
	&CMD_B4,
	&CMD_C1,
	&CMD_C2,
	&CMD_C3,
	&CMD_C4,
	&CMD_D1,
	&CMD_D2,
	&CMD_E1,
	&CMD_E2
};

bool Usart1_CMD_Send(CMD_TYPE n);
{
	memset(GucUartTxBuffer,'\0',TX_BUFFER_LENGTH);
	strcpy(GucUartTxBuffer,at_cmds_list[n]);
	Out_waiting_index_G = strlen(GucUartTxBuffer);
	USART1_SEND();
}

bool Usart1_CMD_A2(void)
{
	Usart1_CMD_Send(AT_CMD_A2);

	if(1)
		return true;
	else
		return false;
}

bool Usart1_CMD_B1_1(void)
{
	Usart1_CMD_Send(AT_CMD_B1_1);

	if(1)
		return true;
	else
		return false;

}

bool Usart1_CMD_B1_2(void)
{
	Usart1_CMD_Send(AT_CMD_B1_2);

	if(1)
		return true;
	else
		return false;
}

bool Usart1_CMD_B1_3(void)
{
	Usart1_CMD_Send(AT_CMD_B1_3);

	if(1)
		return true;
	else
		return false;
}

/**
 * Usart1_CMD_B1 
 * 通信CMD_B1类命令处理函数 
 * 
 * @author yuk (2016-10-13)
 * 
 * @return bool 处理结束 返回1 未结束 返回0
 */
bool Usart1_CMD_B1(void)
{
	static unsigned char status = 0;

	bool B1_step_ok = 0;

	switch(status)
	{
		case 0:
			B1_step_ok = Usart1_CMD_B1_1();
			status = (B1_step_ok) ? 1:0;
			return 0;
		case 1:
			B1_step_ok = Usart1_CMD_B1_2();
			status = (B1_step_ok) ? 2:1;
			return 0;
		case 2:
			B1_step_ok = Usart1_CMD_B1_3();
			status = (B1_step_ok) ? 0:2;
			return B1_step_ok;
		default:
			break;
	}
}


bool Usart1_CMD_B2(void)
{
	Usart1_CMD_Send(AT_CMD_B2);

	if(1)
		return true;
	else
		return false;
}

bool Usart1_CMD_B3(void)
{
	Usart1_CMD_Send(AT_CMD_B3);

	if(1)
		return true;
	else
		return false;
}

bool Usart1_CMD_B4(void)
{
	Usart1_CMD_Send(AT_CMD_B4);

	if(1)
		return true;
	else
		return false;
}

                                 
void Usart1_Rcv_Pro(void)
{

}


void USART1_Process(void)
{
	if(empty_queue(&Q))
	{
		en_queue(&Q, uart1_cmd_list[AT_CMD_D1]);
	}
	else
	{
		if(check_queue(&Q))
		{
			del_queue(&Q);
		}
	}
}
