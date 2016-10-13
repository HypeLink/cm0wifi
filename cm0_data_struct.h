typedef bool (*Usart1_CMD)(void);
typedef bool unsigned char;

bool empty_queue(QUEUE *pQ);
bool check_queue(QUEUE *pQ);
bool del_queue(QUEUE *pQ);

