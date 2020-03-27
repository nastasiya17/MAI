#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <inttypes.h>

#define STR_SIZE 256
#define MAX_SIZE 10000

typedef int32_t ID;

typedef struct _msg {
    ID client;
    ID client2;
    int action;
    int save; 
    void *requester;
    char message[STR_SIZE];
    char str[MAX_SIZE];
} MsgData;

#endif
