#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define NOT_MEMORY -1
#define STR_SIZE 256

typedef int32_t ID;

typedef struct _client {
    ID client;
    ID client2;
    int save;
    char message[STR_SIZE];
} *Client;

typedef struct _Vector {
    Client clients;
    uint32_t size;
    uint32_t freespace;
} *Vector;

Vector VectorCreate(void);
void ClientAdd(Vector v, ID client);
void VectorPrint(Vector v, int index);
Client ClientFind(Vector v, int clientint);
Client GetByIndex(Vector v, int index);
int IndexFind(Vector v, ID client2);
void VectorDestroy(Vector *v);
void SendMessage(ID client, ID client2, char message[], Vector v, int save);
char GetMessage(Client cl, int i);
int GetMessageSize(Client cl);
int Size(Vector v);
char GetMessageByIndex(Vector v,int index, int j);
int GetMessageSizeByIndex(Vector v, ID client, ID client2, int index);

#endif
