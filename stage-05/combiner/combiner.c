#include "signal.h"
#include <fcntl.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>



void handler(int sig) {
    kill(son_pids->pid1, SIGINT);
    kill(son_pids->pid2, SIGINT);
}

struct pids
{
    int pid1;
    int pid2;
};
struct pids* son_pids;

FILE* res;

void handle_rfid() {
    int fifo_fd;
    char buffer[80];
    fifo_fd = open("rfid_data", O_RDWR); // O_RDWR
    while (1) {
        if (read(fifo_fd, buffer, sizeof(buffer)) > 0) {
            res = fopen("result.txt", "a");
		    fprintf(res, "%s\n", buffer);
		    fclose(res);
        }
    }
}

int main(int argc, char *argv[]) {
    int pid1 = atoi(argv[1]);
    int pid2 = atoi(argv[2]);
    struct pids temp = {pid1, pid2};
    son_pids = &temp;
    // apply handler to sigint
    signal(SIGINT, &handler);
    // читаем два канала и выводим инфу в файл отсюда
    // добавить сохранение и удаление паролся
   
    return 0;
}