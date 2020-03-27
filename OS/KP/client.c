#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <pthread.h>

#include "zmq.h"
#include "message.h"
#include <string.h>

void menu(){
    printf("1) Send message\n");
    printf("2) Get message\n");
    printf("3) Look chat\n");
    printf("4) Exit\n");
}

void saveMes() {
    printf("1) Save messages\n");
    printf("2) Don't save messages\n");
}

void *SendRecv(void *arg){
    MsgData *md = (MsgData *) arg;
    zmq_msg_t message;
    zmq_msg_init_size(&message, sizeof(MsgData));
    memcpy(zmq_msg_data(&message), md, sizeof(MsgData));
    zmq_msg_send(&message, md->requester, 0);
    zmq_msg_close(&message);

    zmq_msg_init(&message);
    zmq_msg_recv(&message, md->requester, 0);
    md = (MsgData *) zmq_msg_data(&message);
    printf("%s\n", md->message);
    zmq_msg_close(&message);
    pthread_exit(NULL);
    return 0;
}

void *SendRecv2(void *arg){
    MsgData *md = (MsgData *) arg;
    zmq_msg_t message;
    zmq_msg_init_size(&message, sizeof(MsgData));
    memcpy(zmq_msg_data(&message), md, sizeof(MsgData));
    zmq_msg_send(&message, md->requester, 0);
    zmq_msg_close(&message);

    zmq_msg_init(&message);
    zmq_msg_recv(&message, md->requester, 0);
    md = (MsgData *) zmq_msg_data(&message);
    for (int i=0; i<50; i++) {
        printf("=");
    }
    printf("\n");
    printf("%s", md->str);
    for (int i=0; i<50; i++) {
        printf("=");
    }
    printf("\n");
    zmq_msg_close(&message);
    pthread_exit(NULL);
    return 0;
}

int main(int argc, char **argv){
    void * context = zmq_ctx_new();

    ID client, client2;

    printf("Enter client's login: ");
    scanf("%d", &client);

    char adress[25];
    sprintf(adress, "%s%d", "tcp://localhost:", 40000);

    void *sendSocket = zmq_socket(context, ZMQ_REQ);
    zmq_connect(sendSocket, adress);

    printf("Enter receiver's login: ");
    scanf("%d", &client2);
    
    int act = 0;
    int save = 0;
    saveMes();
    scanf("%d", &save);
    menu();

    do {
        scanf("%d", &act);
        MsgData md;

        md.action = act;
        md.client = client;
        md.client2 = client2;
        md.save = save;
        int i=0;

        switch (act) {
            case 1: {

                for(int j=0; j<STR_SIZE; j++) {
                    md.message[j]='\0';
                }                

                char c = getchar();
                c = getchar();
                while (c!='\n') {
                    md.message[i]=c;
                    c=getchar();
                    i++;
                }

                pthread_t th;
                md.requester = sendSocket;
                pthread_create(&th, NULL, SendRecv, &md);
                pthread_detach(th);
                break;
            }

            case 2: {
                pthread_t th;
                md.requester = sendSocket;
                pthread_create(&th, NULL, SendRecv, &md);
                pthread_detach(th);
                break;
            }

            case 3: {
                pthread_t th;
                md.requester = sendSocket;
                pthread_create(&th, NULL, SendRecv2, &md);
                pthread_detach(th);
                break;
            }

            case 4:
                break;
                
            default: {
                printf("Incorrect command\n");
                break;
            }
        }

    } while (act != 4);

    zmq_close(sendSocket);
    zmq_ctx_destroy(context);

    return 0;
}
