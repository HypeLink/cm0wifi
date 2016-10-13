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

typedef struct {
	u8 xxx1;
	u8 xxx2;
	u8 xxx3;
} Usart1_CMD_PARAM;

static Usart1_CMD_PARAM cmdqueue[QUEUE_SIZE];
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
void initQ(QUEUE *pQ);

/**
 * full_queue 
 * 队列是否已满判断函数 
 * 
 * @author yuk (2016-10-12)
 * 
 * @param pQ 队列指针
 * 
 * @return u8 队列满 返回 1 未满 返回0
 */
u8 full_queue(QUEUE *pQ);

/**
 * empty_queue 
 * 队列是否为空判断函数 
 * 
 * @author yuk (2016-10-12)
 * 
 * @param pQ 队列指针
 * 
 * @return u8 队列空 返回 1 不为空 返回0
 */
u8 empty_queue(QUEUE *pQ);

/**
 * en_queue 
 * 发送命令入队列操作函数 
 * 
 * @author yuk (2016-10-12)
 * 
 * @param pQ   队列指针
 * @param cmdn 命令n
 * 
 * @return u8 
 */
u8 en_queue(QUEUE *pQ,Usart1_CMD_PARAM cmdn);

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
Usart1_CMD_PARAM del_queue(QUEUE *pQ);
