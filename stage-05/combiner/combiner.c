#include "signal.h"
#include <fcntl.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include "time.h"

void stop() {
    kill(son_pids->pid1, SIGINT);
    kill(son_pids->pid2, SIGINT);
    exit(0);
}

struct pids
{
    int pid1;
    int pid2;
};
struct pids* son_pids;

FILE* res;

const char *get_time(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    static char str[30];
    sprintf(str, "%d-%02d-%02d %02d:%02d:%02d",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return str;
}

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
    close(fifo_fd);
}

char true_pass[5]  = "1337";

void handle_keypad() {
    int fifo_fd;
    char readed_pass[5];
    fifo_fd = open("keypad_data", O_RDWR); // O_RDWR
    while (1) {
        if (read(fifo_fd, readed_pass, sizeof(readed_pass)) > 0) {
            if (strcmp(true_pass, readed_pass) == 0){
                res = fopen("result.txt", "a");
				fprintf(res, "%s %s\n", "True Pass", get_time());
				fclose(res);
            }
        }
    }
    close(fifo_fd);
}

void menu() {
    int state;
    int f = 1;
    while (f) {
        printf("Select option:\n 1. Change password\n 2. Stop program\n 3. Quit menu\nEnter option: ");
        scanf("%d", &state);
        switch (state)
        {
            case 1:
                printf("Enter new password in Foramt XXXX:");
                scanf("%s", true_pass);
                res = fopen("result.txt", "a");
				fprintf(res, "%s %s\n", "Added new password", get_time());
				fclose(res);
                break;
            case 2:
                stop();
                break;
            case 3:
                f = 0;
                system("clear");
                break;
            default:
                f = 0;
                system("clear");
                break;
        }
    }
}

int main(int argc, char *argv[]) {
    int pid1 = atoi(argv[1]);
    int pid2 = atoi(argv[2]);
    struct pids temp = {pid1, pid2};
    son_pids = &temp;
    // apply handler to sigint
    // читаем два канала и выводим инфу в файл отсюда
    handle_rfid();
    handle_keypad();
    // добавить сохранение и удаление паролся
    menu();
    return 0;
}