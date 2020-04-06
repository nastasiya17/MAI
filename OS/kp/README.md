Компиляция: 

gcc -std=c99 -pthread -Wall -D_POSIX_SOURCE=600 -D_XOPEN_SOURCE=600 client.c -o client -L/usr/local/lib -lzmq

gcc -std=c99 -pthread -Wall -D_POSIX_SOURCE=600 -D_XOPEN_SOURCE=600 vector.c server.c -o server -L/usr/local/lib -lzmq
