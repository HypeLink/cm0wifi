typedef bool (*Usart1_CMD)(void);
typedef bool (*Usart1_RCV)(void);
typedef bool  unsigned char;
typedef Uint8 unsigned char;

bool empty_queue(QUEUE *pQ);
bool check_queue(QUEUE *pQ);
bool del_queue(QUEUE *pQ);
CMD_TYPE get_queue_0(QUEUE *pQ);

