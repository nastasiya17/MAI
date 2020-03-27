#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;

void* Experiment(void* Data) {
	int* data = (int*) Data;
	pthread_mutex_lock(&mutex);
	printf("%d\t%d\n", data[0], data[1]);
	int sum1=data[0];
	int sum2=data[1];
	int tyr=data[2];
	pthread_mutex_unlock(&mutex);
	for (int j=0; j<tyr; j++) {
		int t=rand()%6 +1;
		sum1=sum1+t;
		t=rand()%6+1;
		sum1=sum1+t;
		t=rand()%6 +1;
		sum2=sum2+t;
		t=rand()%6+1;
		sum2=sum2+t;
	}
	pthread_mutex_lock(&mutex);
	data[0]=sum1;
	data[1]=sum2;
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main() {
	int K,T,S1,S2,N;
	int pc;
	int pj;
	scanf("%d%d%d%d%d", &K, &T, &S1, &S2, &N);
	pthread_t pth[N];
	pthread_mutex_init(&mutex, NULL);
	int data[3];
	data[0]=0;
	data[1]=0;
	data[2]=K-T;

	for (int i=0; i<N; i++) {
		pc=pthread_create(&pth[i], NULL, Experiment, (void*) data);
		if (pc!=0) {
			printf("error: can't create thread \n");
			exit(1);
		}

		pj=pthread_join(pth[i], NULL);
		if (pj!=0) {
			printf("error: can't join thread \n");
			exit(2);
		}
	}

	pthread_mutex_destroy(&mutex);
	double chance1=(double) data[0]/N/(K-T)/12 + S1/T/12;
	double chance2=(double) data[1]/N/(K-T)/12 + S2/T/12;
	printf("chance1=%f\n", chance1);
	printf("chance2=%f\n", chance2);
}
