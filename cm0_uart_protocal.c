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

void Usart1_Recv_Pro(void);



typedef enum
{
	false,
	true
}bool;

#define  dl_cmd_total   50				//队列容量

typedef struct
{
	char* CMD_DATA;						//队列数据
	struct DL_CMD*  DL_NEXT;					//指向下一个节点
}DL_CMD;

DL_CMD*  DL_HEAD = NULL;						//队列头指针
DL_CMD*  DL_TAIL = NULL;						//队列尾指针	


typedef enum
{
	AT_CMD_A1,
	AT_CMD_A2,
	AT_CMD_B1,
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

#define   RX_BUFFER_LENGTH   100
#define   TX_BUFFER_LENGTH   100
static unsigned char    GucUartRxBuffer[RX_BUFFER_LENGTH] = {0};                /* 接收缓冲区                   */
static unsigned char    GucUartTxBuffer[TX_BUFFER_LENGTH] = {0};                /* 发送缓冲区                   */

unsigned char  Out_waiting_index_G = 0;                                        /* 待发送数据索引值              */
unsigned char  In_saved_index_G    = 0;                                        /* 已接收数据索引值              */
unsigned char  In_waiting_index_G  = 0;                                        /* 待接收数据索引值              */


const char CMD_A1[]="AT+SOCKB\r";
const char CMD_A2[]="AT+SOCKB\r";
const char CMD_B1[]="AT+SOCKB\r";
const char CMD_B2[]="AT+SOCKB\r";
const char CMD_B3[]="AT+SOCKB\r";
const char CMD_B4[]="AT+SOCKB\r";
const char CMD_C1[]="AT+SOCKB\r";
const char CMD_C2[]="AT+SOCKB\r";
const char CMD_C3[]="AT+SOCKB\r";
const char CMD_C4[]="AT+SOCKB\r";
const char CMD_D1[]="AT+SOCKB\r";
const char CMD_D2[]="AT+SOCKB\r";
const char CMD_E1[]="AT+SOCKB\r";
const char CMD_E2[]="AT+SOCKB\r";

 
const char * at_cmds_list[] = 
{		
		&CMD_A1,
		&CMD_A2,
		&CMD_B1,
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


void DL_init()
{
	DL_HEAD = (DL_CMD *)malloc(sizeof(DL_CMD));			//分配队列空间
	DL_HEAD->CMD_DATA = NULL;
	DL_HEAD->DL_NEXT = NULL;
	DL_TAIL = DL_HEAD.DL_NEXT;
}

void  PUSH_DL(char * CMD)
{
	if(DL_HEAD->CMD_DATA == NULL)
	{
		DL_HEAD->CMD_DATA = CMD;								//入队
		DL_TAIL->DL_NEXT = (DL_CMD *)malloc(sizeof(DL_CMD));	
	}
	else
	{
		while(DL_TAIL != NULL)
			DL_TAIL = DL_TAIL->DL_NEXT;

		DL_TAIL = (DL_CMD *)malloc(sizeof(DL_CMD));	
		DL_TAIL->DL_NEXT = NULL;
		DL_TAIL->DL_DATA = CMD;							//入队
		DL_TAIL = DL_TAIL->DL_NEXT;		
	}
}								

void RELESE_DL()
{
	DL_CMD * p = DL_HEAD;
	DL_HEAD = DL_HEAD->DL_NEXT;
	free(p);
}


bool Usart1_CMD_A2(void)
{
	memset(GucUartTxBuffer,'\0',TX_BUFFER_LENGTH);
	strcpy(GucUartTxBuffer,at_cmds_list[AT_CMD_A2]);
	Out_waiting_index_G = strlen(GucUartTxBuffer);
	USART1_SEND();

	if(1)
		return true;
	else
		return false;
}

bool Usart1_CMD_B1(void)
{
	bool B1_1 = false, B1_2 = false;
	
	B1_1 = Usart1_CMD_B1_1();

	//等待时间
	if(B1_1) 
		B1_2 = Usart1_CMD_B1_2();
	
	if(B1_2)
		Usart1_CMD_B1_3();
}

bool Usart1_CMD_B1_1(void)
{
	memset(GucUartTxBuffer,'\0',TX_BUFFER_LENGTH);
	strcpy(GucUartTxBuffer,at_cmds_list[AT_CMD_B1]);
	Out_waiting_index_G = strlen(GucUartTxBuffer);
	USART1_SEND();

	if(1)
		return true;
	else
		return false;

}

bool Usart1_CMD_B1_2(void)
{
		memset(GucUartTxBuffer,'\0',TX_BUFFER_LENGTH);
		strcpy(GucUartTxBuffer,at_cmds_list[AT_CMD_B1]);
		Out_waiting_index_G = strlen(GucUartTxBuffer);
		USART1_SEND();

		if(1)
			return true;
		else
			return false;
}

bool Usart1_CMD_B1_3(void)
{
	memset(GucUartTxBuffer,'\0',TX_BUFFER_LENGTH);
	strcpy(GucUartTxBuffer,at_cmds_list[AT_CMD_B1]);
	Out_waiting_index_G = strlen(GucUartTxBuffer);
	USART1_SEND();

	if(1)
		return true;
	else
		return false;
}

bool Usart1_CMD_B2(void)
{
	memset(GucUartTxBuffer,'\0',TX_BUFFER_LENGTH);
	strcpy(GucUartTxBuffer,at_cmds_list[AT_CMD_B2]);
	Out_waiting_index_G = strlen(GucUartTxBuffer);
	USART1_SEND();

	if(1)
		return true;
	else
		return false;
}

bool Usart1_CMD_B3(void)
{
	memset(GucUartTxBuffer,'\0',TX_BUFFER_LENGTH);
	strcpy(GucUartTxBuffer,at_cmds_list[AT_CMD_B3]);
	Out_waiting_index_G = strlen(GucUartTxBuffer);
	USART1_SEND();

	if(1)
		return true;
	else
		return false;
}

bool Usart1_CMD_B4(void)
{
	memset(GucUartTxBuffer,'\0',TX_BUFFER_LENGTH);
	strcpy(GucUartTxBuffer,at_cmds_list[AT_CMD_B4]);
	Out_waiting_index_G = strlen(GucUartTxBuffer);
	USART1_SEND();

	if(1)
		return true;
	else
		return false;
}


bool (*uart1_cmd_list[UART1_CMD_TOTAL])(void) = {
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

