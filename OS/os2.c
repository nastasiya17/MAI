#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

const int min_capacity = 2;
const double k = 3.0 / 2.0;

typedef struct{
	int *array;
    	int length;
    	int capacity;
}TVector;

TVector * Create_Vector(){
    	TVector * v = (TVector*)malloc(sizeof(TVector));
    	v->array = (int*)malloc(sizeof (int) * min_capacity);
    	v->length = 0;
    	v->capacity = min_capacity;
    	return v;
}

int Get_Vector(TVector * v, int index){
    	if (index < v->length && index >= 0)
        	return v->array[index];
    	else
        	return 0;
}

void Resize_Vector(TVector * v, int new_capacity){
    	v->array = (int*)realloc(v->array, sizeof(int) * new_capacity);
    	v->capacity = new_capacity;
}

void Push_back_Vector(TVector * v, int value){
    	if (v->length == v->capacity){
        	Resize_Vector(v, v->capacity * k);
    	}
    	v->array[v->length] = value;
    	v->length++;
}

void Remove_Vector(TVector * v){
    	v->length--;
    	if (v->length <= v->capacity / 2){
        	Resize_Vector(v, v->capacity / k);
    	}
}

void Destroy_Vector(TVector * v){
    	free(v);
}

void Print_Vector(TVector * v){
        for (int i = 0; i < v->length; i++) {
                printf("%d ",v->array[i]);
        }
        printf("\n");
}

int main() {

	TVector * str=Create_Vector();
	TVector * exmp=Create_Vector();
	char c;
	char found[1]="n";
	char found1[1]="n";
	pid_t p;
	int status;
	int fd[2];

	printf("Введите строку \n");
	c=getchar();
	while (c!='\n') {
		Push_back_Vector(str,c);
		c=getchar();
	}

	printf("Введите образец \n");
	c=getchar();
	while (c!='\n') {
		Push_back_Vector(exmp,c);
		c=getchar();
	}

	if (pipe(fd)<0) {
		printf("Невозможно создать pipe \n");
		exit(1);
	}

	for (int i=0; i<str->length; i++) {
		write(fd[1], &str[i], sizeof(int));
	}

	for (int i=0; i<exmp->length; i++) {
		write(fd[1], &exmp[i], sizeof(int));
	}

	p=fork();
	if (p<0) {
		printf("Невозможно создать дочерний процесс \n");
		exit(1);
	}
	
	else if (p==0) {
		int i=0;
		int j=0;
		int k=0;
		for (int i=0; i<str->length; i++) {
			read(fd[0], &str[i], sizeof(int));
		}
		for (int i=0; i<exmp->length; i++) {
			read(fd[0], &exmp[i], sizeof(int));
		}
		close(fd[0]);
		while ((i<str->length)&&(j<exmp->length)){
			if (Get_Vector(str,i)==Get_Vector(exmp,j)) {
				j++;
				i++;
			}
			else {
				j=0;
				k++;
				i=k;
			}
		}

		if (j==exmp->length) found[0]='y';
		write(fd[1],found,1);
		close(fd[1]);
		printf("Выход из дочернего процесса \n");
		exit(0);
	}

	else {
		wait(&status);
		close(fd[1]);
		read(fd[0],found1,1);
		printf("%s \n",found1);
		close(fd[0]);
		Destroy_Vector(str);
		Destroy_Vector(exmp);
		printf("Выход из родительского процесса \n");
	}
}
