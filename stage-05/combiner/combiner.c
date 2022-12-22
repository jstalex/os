#include "signal.h"



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