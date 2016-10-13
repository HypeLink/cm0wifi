/****************************************Copyright (c)****************************************************
**                               Zhejiang Hulong Motor Co., LTD.
**
**                                 http://www.hmcmotor.com.cn
**
**      
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               xxx_data_struct.c
** Last modified date:      2016-09-30
** Last version:            V1.0
** Description:             1.产品协议内需使用的数据结构定义及其实现函数调用接口
** 							2.协议方新增数据结构定义及实现函数调用接口
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
#include "cm0_uart_protocal.h"

typedef bool (*Usart1_CMD)(void);

typedef struct Queue2  
{  
    Usart1_CMD *pBase;	//pBase指向数组名（通常静态队列都使用循环队列）  
	#define QUEUE_SIZE	21
    unsigned char front;			//数组下标，这里规定从零开始  
    unsigned char rear;  
}QUEUE;//QUEUE代表了struct Queue

static Usart1_CMD cmdqueue[QUEUE_SIZE] = {
	Usart1_CMD_C1,
	Usart1_CMD_C2,
	Usart1_CMD_C3,
	Usart1_CMD_C4,
	0,
};

QUEUE Q;
Usart1_CMD_PARAM cmd2null = {0,};
u8 cmd3_delay_cnt = 0;

/**
 * initQ 
 * 初始化发送命令循环队列 
 * 
 * @author yuk (2016-10-12)
 * 
 * @param pQ 
 */
void initQ(QUEUE *pQ)
{
	pQ->pBase = cmdqueue;
	pQ->front=0;  
    pQ->rear=3;
}
/**
 * full_queue 
 * 队列是否已满判断函数 
 * 
 * @author yuk (2016-10-12)
 * 
 * @param pQ 队列指针
 * 
 * @return bool 队列满 返回 1 未满 返回0
 */
bool full_queue(QUEUE *pQ)
{
	if((pQ->rear+1)%QUEUE_SIZE == pQ->front)  
        return true;  
    else  
        return false;
}

/**
 * empty_queue 
 * 队列是否为空判断函数 
 * 
 * @author yuk (2016-10-12)
 * 
 * @param pQ 队列指针
 * 
 * @return bool 队列空 返回 1 不为空 返回0
 */
bool empty_queue(QUEUE *pQ)
{
	if(pQ->rear==pQ->front)//因为队列不为空时，rear和front肯定不相等  
        return true;  
    else  
        return false;  
}

/**
 * en_queue 
 * 发送命令入队列操作函数 
 * 
 * @author yuk (2016-10-12)
 * 
 * @param pQ   队列指针
 * @param cmdn 命令n
 * 
 * @return bool 
 */
bool en_queue(QUEUE *pQ,Usart1_CMD cmdn)
{
	u8 i = pQ->front;

	if(full_queue(pQ) && i == pQ->rear)  
    {  
        //printf("队列已满，入队失败！\n");  
        return false;  
    } 

    pQ->pBase[pQ->rear] = cmdn;  
    pQ->rear=(pQ->rear+1)%QUEUE_SIZE;//队尾加1  
    return true;  
}
/**
 * del_queue 
 * 发送命令出队列操作函数 
 * 
 * @author yuk (2016-10-12)
 * 
 * @param pQ   队列指针 
 * 
 * @return Usart1_CMD_PARAM 命令n
 */
bool del_queue(QUEUE *pQ)
{
	if(empty_queue(pQ))  
        return 0;

    pQ->front = (pQ->front+1) % QUEUE_SIZE;  
    return 1;  
}

/**
 * check_queue 
 * 检查当且列表 头指针指向函数是否执行完成 
 * 
 * @author yuk (2016-10-13)
 * 
 * @param pQ 
 * 
 * @return bool 
 */
bool check_queue(QUEUE *pQ)
{
	bool i;

	i = pQ->pBase[pQ->front]();
	return i;
}



