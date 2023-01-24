#ifndef ZMQ_STRUCT
#define ZMQ_STRUCT

typedef struct
{
    int key;
    int id;
    long long size;
} message_zmq;

enum Status{
    CHECK,
    PING,
    CREATE,
    REMOVE,
    EXEC,
    SUCCESS,
    FAIL,
    FAIL_PING,
    FAIL_CREATE
};

int ping_send(void * socket, message_zmq * msg);
message_zmq * ping_receive(void * socket);
int create_conn(int id, void * socket, void * context);
void send_string(void *socket, const char *string);
char * recv_string (void *socket, long long size);
#endif