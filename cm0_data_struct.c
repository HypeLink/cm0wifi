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
** Description:             1.��ƷЭ������ʹ�õ����ݽṹ���弰��ʵ�ֺ������ýӿ�
** 							2.Э�鷽�������ݽṹ���弰ʵ�ֺ������ýӿ�
**
**--------------------------------------------------------------------------------------------------------
** Created by:              yuk
** Created date:            2016-09-30
** Version:                 V1.0
** Descriptions:            The original version ��ʼ�汾
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#include "cm0_uart_protocal.h"

typedef struct Queue {  
    CMD_TYPE *pBase;			//pBaseָ����������ͨ����̬���ж�ʹ��ѭ�����У�  
	#define QUEUE_SIZE	11		//ѭ�����г���
    Uint8 front;		//�����±꣬����涨���㿪ʼ  
    Uint8 rear;  
} QUEUE;//QUEUE������struct Queue

/**
 * cmdqueue 
 * ��ʼ��ָ�˳��д����� 
 * 
 * @author yuk (2016-10-13)
 */
static CMD_TYPE cmdqueue[QUEUE_SIZE] = {
	CMD_C1,
    CMD_C2,
    CMD_C3,
    CMD_C4,
    0,0,0,0,0,
};

QUEUE Q;

Usart1_CMD cmd2null = {0,};


/**
 * initQ 
 * ��ʼ����������ѭ������ 
 * 
 * @author yuk (2016-10-12)
 * 
 * @param pQ 
 */
void initQ(QUEUE *pQ)
{
	pQ->pBase = cmdqueue;
	pQ->front = 0;  
    pQ->rear = 3;
}
/**
 * full_queue 
 * �����Ƿ������жϺ��� 
 * 
 * @author yuk (2016-10-12)
 * 
 * @param pQ ����ָ��
 * 
 * @return bool ������ ���� 1 δ�� ����0
 */
bool full_queue(QUEUE *pQ)
{
	if((pQ->rear+1)%QUEUE_SIZE == pQ->front)  
        return 1;  
    else  
        return 0;
}

/**
 * empty_queue 
 * �����Ƿ�Ϊ���жϺ��� 
 * 
 * @author yuk (2016-10-12)
 * 
 * @param pQ ����ָ��
 * 
 * @return bool ���п� ���� 1 ��Ϊ�� ����0
 */
bool empty_queue(QUEUE *pQ)
{
	//��Ϊ���в�Ϊ��ʱ��rear��front�϶������ 
	if(pQ->rear==pQ->front) 
        return 1;  
    else  
        return 0;  
}

/**
 * en_queue 
 * ������������в������� 
 * 
 * @author yuk (2016-10-12)
 * 
 * @param pQ   ����ָ��
 * @param cmdn ����n
 * 
 * @return bool 
 */
bool en_queue(QUEUE *pQ, CMD_TYPE cmdn)
{
	u8 i = pQ->front;

	if(full_queue(pQ) && i == pQ->rear)  
    {  
        //printf("�������������ʧ�ܣ�\n");  
        return 0;  
    } 

    pQ->pBase[pQ->rear] = cmdn;  
    pQ->rear=(pQ->rear+1)%QUEUE_SIZE;//��β��1  
    return 1;  
}

/**
 * del_queue 
 * ������������в������� 
 * 
 * @author yuk (2016-10-12)
 * 
 * @param pQ   ����ָ�� 
 * 
 * @return CMD_TYPE ����n
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
 * ��鵱���б� ͷָ��ָ�����Ƿ�ִ����� 
 * 
 * @author yuk (2016-10-13)
 * 
 * @param pQ 
 * 
 * @return bool 
 */
bool check_queue(QUEUE *pQ)
{
	CMD_TYPE cmd_i;

	cmd_i = pQ->pBase[pQ->front];
	
	return Usart1_CMD_Send(cmd_i);
}

/**
 * get_queue_0 
 * ��ȡ��ǰ����front������ִ�е����� 
 * 
 * @author yuk (2016-10-17)
 * 
 * @param pQ 
 * 
 * @return CMD_TYPE 
 */
CMD_TYPE get_queue_0(QUEUE *pQ)
{
	CMD_TYPE cmd_i;

	cmd_i = pQ->pBase[pQ->front];

	return cmd_i;
}

