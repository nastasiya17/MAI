#include "vector.h"
#include <string.h>

Vector VectorCreate(void){
    Vector v = (Vector) malloc(sizeof(*v));
    if (!v) {
        fprintf(stderr, "ERROR: no memory\n");
        exit(NOT_MEMORY);
    }
    v->clients = (Client) malloc(sizeof(*(v->clients)));
    v->size = 0;
    v->freespace = 1;
    return v;
}

void VectorResize(Vector v){
    v->clients = realloc(v->clients, 2 * v->size * sizeof(*(v->clients)));
    if (!v->clients) {
        fprintf(stderr, "ERROR: no memory\n");
        exit(NOT_MEMORY);
    }
    v->freespace = v->size;
}

void ClientAdd(Vector v, ID client){
    if (!v->freespace) {
        VectorResize(v);
    }

    v->clients[v->size].client = client;
    v->size++;
    v->freespace--;
}

void VectorPrint(Vector v, int index){
    if (v) {
            printf("ID sender: %d\t", v->clients[v->size-1].client);
            printf("ID receiver: %d\t\t", v->clients[v->size-1].client2);
            printf("MESSAGE: ");
            int l=strlen(v->clients[index].message);
            for (int j=0; j<l; j++) 
                printf("%c", v->clients[index].message[j]);
            printf("\n\n");
    }
}

Client ClientFind(Vector v, int clientint){
    if (v) {
        for (int i = v->size-1; i >=0; i--) {
            if (v->clients[i].client == clientint) {
                return &(v->clients[i]);
            }
        }
    }
    return NULL;
}

Client GetByIndex(Vector v, int index){
    if ((index>=0)&&(index<v->size))
        return &(v->clients[index]);
    else return NULL;
}

int IndexFind(Vector v, ID client2){
    if (v) {
        for (int i = v->size-1; i >=0; i--) {
            if ((v->clients[i].client == client2)&&(v->size-1==i)) {
                return i;
            }
        }
    }
    return -1;
}

void VectorDestroy(Vector *v){
    free((*v)->clients);
    (*v)->clients = NULL;
    free(*v);
    *v = NULL;
}

void SendMessage(ID client, ID client2, char message[], Vector v, int save){        
    ClientAdd(v, client);
    Client cl = ClientFind(v, client);
    int i;
    cl->save=save;
    cl->client2=client2;
    int l=strlen(message);
    for (i=0; i<l; i++)
        cl->message[i]=message[i];
    cl->message[i]='\0';
}

char GetMessage(Client cl, int i) {
    char mes;
    mes=cl->message[i];
    if (cl->save==2)
        cl->message[i]='*';
    return mes;
}

int GetMessageSize(Client cl) {
    return strlen(cl->message);
}

int Size(Vector v) {
    return v->size;
}

char GetMessageByIndex(Vector v, int index, int j) {
    return v->clients[index].message[j];
}

int GetMessageSizeByIndex(Vector v, ID client, ID client2, int index) {
    if(((v->clients[index].client==client)&&(v->clients[index].client2==client2)) ||
        ((v->clients[index].client==client2)&&(v->clients[index].client2==client)))
        return strlen(v->clients[index].message);
    return 0;
}
