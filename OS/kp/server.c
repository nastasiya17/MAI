#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stropts.h>
#include <signal.h>

#include "zmq.h"
#include "vector.h"
#include "message.h"

volatile sig_atomic_t flag = 0;

void block_func(int sig){
    if (!flag) {
        flag = 1;
    } else {
        exit(0);
    }
}

void unblock_func(int sig){
    flag = 0;
}

int main(){
    Vector clientBase = VectorCreate();
    void * context = zmq_ctx_new();
    void *responsSocket = zmq_socket(context, ZMQ_REP);

    char adress[25];

    sprintf(adress, "%s%d", "tcp://*:", 40000);

    zmq_bind(responsSocket, adress);

    int index=-1;

    while (1) {
        signal(SIGINT, block_func);
        signal(SIGTSTP, unblock_func);
        if (!flag) {

            zmq_msg_t message;

            zmq_msg_init(&message);
            zmq_msg_recv(&message, responsSocket, 0);
            MsgData *md = (MsgData *) zmq_msg_data(&message);
            zmq_msg_close(&message);

            char info[STR_SIZE];

            switch (md->action) {
                case 1: {

                    if (IndexFind(clientBase, md->client2)!=-1)
                        index=IndexFind(clientBase, md->client2);

                    SendMessage(md->client, md->client2, md->message, clientBase, md->save);
                    strcpy(info, "\0");

                    memcpy(md->message, info, strlen(info) + 1);
                    zmq_msg_init_size(&message, sizeof(MsgData));
                    memcpy(zmq_msg_data(&message), md, sizeof(MsgData));
                    zmq_msg_send(&message, responsSocket, 0);
                    zmq_msg_close(&message);
                    break;
                }

                case 2: {

                    index++;
                    Client cl=GetByIndex(clientBase, index);
                    Client client=ClientFind(clientBase, md->client2);
                 
                    if (client==NULL) {
                        strcpy(info, "No client2\0");
                        memcpy(md->message, info, strlen(info) + 1);
                    }
                    else if(cl==NULL) {
                        strcpy(info, "No messages from client2\0");
                        memcpy(md->message, info, strlen(info) + 1);
                    }
                    else {
                        int l=GetMessageSizeByIndex(clientBase, md->client, md->client2, index);
                        for (int i=0; i<l; i++) {
                            md->message[i]=GetMessage(cl, i); 
                        }
                        md->message[l]='\0';
                        VectorPrint(clientBase, index);
                    }
                    zmq_msg_init_size(&message, sizeof(MsgData));
                    memcpy(zmq_msg_data(&message), md, sizeof(MsgData));
                    zmq_msg_send(&message, responsSocket, 0);
                    zmq_msg_close(&message);
                
                    break;
                }

                case 3: {

                    int k=0;  
                    int t=0;                 
                    for (int i=0; i<Size(clientBase); i++) {
                        int l=GetMessageSizeByIndex(clientBase, md->client, md->client2, i);
                        if (l!=0) {
                            for (int j=0; j<l; j++) {
                                md->str[t+j+k]=GetMessageByIndex(clientBase, i, j); 
                            }
                            t+=l;
                            md->str[t+k]='\n';
                            k++;
                        }
                    }
                    md->str[t+k]='\0';

                    zmq_msg_init_size(&message, sizeof(MsgData));
                    memcpy(zmq_msg_data(&message), md, sizeof(MsgData));
                    zmq_msg_send(&message, responsSocket, 0);
                    zmq_msg_close(&message);
                }
            }
            zmq_msg_close(&message);
        }
    }
    zmq_close(responsSocket);
    zmq_ctx_destroy(context);

    VectorDestroy(&clientBase);
}
