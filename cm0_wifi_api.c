/****************************************Copyright (c)****************************************************
**                               Zhejiang Hulong Motor Co., LTD.
**
**                                 http://www.hmcmotor.com.cn
**
**      
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               xxx_wifi_api.c
** Last modified date:      2016-09-30
** Last version:            V1.0
** Description:             wifi模块协议端指令的实现函数及接口定义
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
*********************************************************************************************************/
#include "cm0_data_struct.h"


/**
 * Usart1_CMD_A2 
 * CM0 发送命令 CMD_A2 处理函数 
 * 
 * @author yuk (2016-10-15)
 * 
 * @return bool 
 */
bool Usart1_CMD_A2(void)
{
	return Core_CMD_Send(AT_CMD_A2);
}

/**
 * Usart1_CMD_B1_1 
 * CM0 发送命令 CMD_B1_1 处理函数 
 * 
 * @author yuk (2016-10-14)
 * 
 * @return bool 完成 返回 1 否则 返回 0
 */
bool Usart1_CMD_B1_1(void)
{
	return Core_CMD_Send(AT_CMD_B1_1);
}

/**
 * Usart1_CMD_B1_2 
 * CM0 发送命令 CMD_B1_2 处理函数 
 * 
 * @author yuk (2016-10-15)
 * 
 * @return bool 
 */
bool Usart1_CMD_B1_2(void)
{
	return Core_CMD_Send(AT_CMD_B1_2);
}

/**
 * Usart1_CMD_B1_3 
 * CM0 发送命令 CMD_B1_3 处理函数 
 * 
 * @author yuk (2016-10-15)
 * 
 * @return bool 
 */
bool Usart1_CMD_B1_3(void)
{
	return Core_CMD_Send(AT_CMD_B1_3);
}

bool Usart1_CMD_B2(void)
{
	return Core_CMD_Send(AT_CMD_B2);
}

bool Usart1_CMD_B3(void)
{
	return Core_CMD_Send(AT_CMD_B3);
}

bool Usart1_CMD_B4(void)
{
	return Core_CMD_Send(AT_CMD_B4);
}

bool Usart1_CMD_C1(void)
{
	return Core_CMD_Send(AT_CMD_C1);
}

bool Usart1_CMD_C2(void)
{
	return Core_CMD_Send(AT_CMD_C2);
}

bool Usart1_CMD_C3(void)
{
	return Core_CMD_Send(AT_CMD_C3);
}

bool Usart1_CMD_C4(void)
{
	return Core_CMD_Send(AT_CMD_C4);
}

bool Usart1_CMD_D1(void)
{
	return Core_CMD_Send(AT_CMD_D1);
}

bool Usart1_CMD_D2(void)
{
	return Core_CMD_Send(AT_CMD_D2);
}

bool Usart1_CMD_E1(void)
{
	return Core_CMD_Send(AT_CMD_E1);
}


bool Send_CMD_Data(void)
{
	return Core_CMD_Send(AT_CMD_DATA);
}



bool Usart1_CMD_E2(void)
{
	return Core_CMD_Send(AT_CMD_E2);
}



