#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main() {

	char c;
	pid_t p;
	int status;
	char* data_str;
	char* data_exmp;
	char* res;
	int count1=0;
	int count2=0;

	int fd = open("String", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if(fd < 0) {
		printf("Невозможно открыть файл \n");
  		exit(1);
	}

	printf("Введите строку \n");
	c=getchar();
	count1++;
	while (c!='\n') {
		if (write(fd, &c, 1)!= 1){
        	perror("Ошибка вызова функции write");
        	exit(1);
    	}
    	c=getchar();
    	count1++;
    }
    count1--;

    data_str = (char*)mmap(0, count1-1, PROT_WRITE, MAP_SHARED, fd, 0);
	if(data_str == MAP_FAILED) {
		printf("Ошибка вызова функции mmap \n");
  		exit(1);
	} 

	close(fd);

    int fd1 = open("Example", O_CREAT | O_RDWR | O_TRUNC , 0777);
	if(fd1 < 0) {
		printf("Невозможно открыть файл \n");
  		exit(1);
	}

    printf("Введите образец \n");
	c=getchar();
	count2++;
	while (c!='\n') {
		if (write(fd, &c, 1)!= 1){
        	perror("Ошибка вызова функции write");
        	exit(1);
    	}
    	c=getchar();
    	count2++;
    }
	count2--;

	data_exmp = (char*)mmap(0, count2-1, PROT_WRITE, MAP_SHARED, fd1, 0);
	if(data_exmp == MAP_FAILED) {
		printf("Ошибка вызова функции mmap \n");
  		exit(1);
	}

    close(fd1);


    int fd2 = open("Size1", O_CREAT | O_RDWR | O_TRUNC , 0777);
	if(fd2 < 0) {
		printf("Невозможно открыть файл \n");
  		exit(1);
	}

	if (write(fd2, &count1, 1)!= 1){
        perror("Ошибка вызова функции write");
        exit(1);
    } 

    char* size1 = (char*)mmap(0, 1, PROT_WRITE, MAP_SHARED, fd2, 0);
    if(size1 == MAP_FAILED) {
		printf("Ошибка вызова функции mmap \n");
  		exit(1);
	} 

    close(fd2);


	int fd3 = open("Size2", O_CREAT | O_RDWR | O_TRUNC , 0777);
	if(fd3 < 0) {
		printf("Невозможно открыть файл \n");
  		exit(1);
	}

	if (write(fd3, &count2, 1)!= 1){
        perror("Ошибка вызова функции write");
        exit(1);
    }

    char* size2 = (char*)mmap(0, 1, PROT_WRITE, MAP_SHARED, fd3, 0);
    if(size2 == MAP_FAILED) {
		printf("Ошибка вызова функции mmap \n");
  		exit(1);
	} 

    close(fd3);

	p=fork();
	if (p<0) {
		printf("Невозможно создать дочерний процесс \n");
		exit(1);
	}
	
	else if (p==0) {
		int i=0;
		int j=0;
		int k=0;

    	fd2 = open("Size1", O_RDWR , 0777);
		if(fd2 < 0) {
			printf("Невозможно открыть файл \n");
  			exit(1);
		}

		/*char* size1 = (char*)mmap(0, 1, PROT_READ, MAP_SHARED, fd2, 0);
		if(size1 == MAP_FAILED) {
			printf("Ошибка вызова функции mmap \n");
  			exit(1);
		} */

		char* size3 = (char*)malloc(sizeof (char)); 
		memcpy(size3, size1, 1);

		close(fd2);

		fd3 = open("Size2", O_RDWR , 0777);
		if(fd3 < 0) {
			printf("Невозможно открыть файл \n");
  			exit(1);
		}

    	/*char* size2 = (char*)mmap(0, 1, PROT_READ, MAP_SHARED, fd3, 0);
    	if(size2 == MAP_FAILED) {
			printf("Ошибка вызова функции mmap \n");
  			exit(1);
		} */

		char* size4 = (char*)malloc(sizeof (char)); 
		memcpy(size4, size2, 1);

    	close(fd3);

    	fd = open("String", O_RDWR , 0777);
		if(fd < 0) {
			printf("Невозможно открыть файл \n");
  			exit(1);
		}

		/*char* data_str = (char*)mmap(0, size3[0], PROT_READ, MAP_SHARED, fd, 0);
		if(data_str == MAP_FAILED) {
			printf("Ошибка вызова функции mmap \n");
  			exit(1);
		}*/

		char* data_str1 = (char*)malloc(sizeof (char) * size3[0]); 
		memcpy(data_str1, data_str, size3[0]);

		close(fd);

		fd1 = open("Example", O_RDWR , 0777);
		if(fd1 < 0) {
			printf("Невозможно открыть файл \n");
  			exit(1);
		}

		/*data_exmp = (char*)mmap(0, size4[0], PROT_READ, MAP_SHARED, fd1, 0);
		if(data_exmp == MAP_FAILED) {
			printf("Ошибка вызова функции mmap \n");
  			exit(1);
		}*/

		char* data_exmp1 = (char*)malloc(sizeof (char) * size4[0]); 
		memcpy(data_exmp1, data_exmp, size4[0]);

    	close(fd1);
			
		while ((i<size3[0])&&(j<size4[0])){
			if (data_str1[i]==data_exmp1[j]) {
				j++;
				i++;
			}
			else {
				j=0;
				k++;
				i=k;
			}
		} 

		int fd4 = open("Result", O_CREAT | O_RDWR | O_TRUNC , 0777);
		if(fd4 < 0) {
			printf("Невозможно открыть файл \n");
  			exit(1);
		}

		if (j==size4[0]) {
			if (write(fd4, "y", 1)!= 1) {
				perror("Ошибка вызова функции write");
        		exit(1);
			}
		}
		else {
			if (write(fd4, "n", 1)!= 1) {
				perror("Ошибка вызова функции write");
        		exit(1);
			}
		}

		res = (char*)mmap(0, 1, PROT_WRITE, MAP_SHARED, fd4, 0);
		if(res == MAP_FAILED) {
			printf("Ошибка вызова функции mmap \n");
  			exit(1);
		}

		char* res1 = (char*)malloc(sizeof (char)); 
		memcpy(res1, res, 1);

		close(fd4);

		printf("Выход из дочернего процесса \n");
		exit(0);
	} 

	else {

		int fd4 = open("Result", O_RDWR, 0777);
		if(fd4 < 0) {
			printf("Невозможно открыть файл \n");
  			exit(1);
		}

    	char* res1 = (char*)mmap(0, 1, PROT_READ, MAP_SHARED, fd4, 0);
    	if(res == MAP_FAILED) {
			printf("Ошибка вызова функции mmap \n");
  			exit(1);
  		}

		close(fd4);

		wait(&status);
		printf("%c\n", res1[0]);
		printf("Выход из родительского процесса \n"); 
	} 
}
