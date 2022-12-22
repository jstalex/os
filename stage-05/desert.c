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

const char *get_time();

char true_pass[5] = "1337";

int main(int argc, char *argv[]) {
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
                printf("%s\n", true_pass);
                break;
            case 2:
                //stop();
                exit(0);
                break;
            case 3:
                f = 0;
                system("clear");
                break;
            default:
                printf("imhere\n");
                f = 0;
                //system("clear");
                break;
        }
    }
}





const char *get_time(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    static char str[30];
    sprintf(str, "%d-%02d-%02d %02d:%02d:%02d",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return str;
}


// int main(int argc, char *argv[])
// {
// 	FILE *res;

//     char x = '\0';
//     char line[10];
//     char pass[4] = { '\0' };
//     char temp[2];
//     int curr_ind = 0;

//     while (1) { 
//         //scanf("%s", &temp);
//         //sprintf(temp, "%s", line);
        
//         fgets(line, 10, stdin);

//         if (1) {
//             // sprintf(temp, "%s", line);
//             // printf("index = %d, x = %s, temp = %s\n", curr_ind, temp, temp);
//             if (curr_ind < 4) {
//                 strncat(pass, line, 1);    
//                 curr_ind++;
//             }
//             // printf("%s\n", pass);
//             if (strcmp(pass, "1337") == 0){
//                 printf("%s\n", "im here");

//                 res = fopen("result.txt", "a");
//                 fprintf(res, "%s %s\n", "True Pass", get_time());
//                 fclose(res);

//                 strcpy(pass, "");
//                 curr_ind = 0;
//             }
//             if (line[0] == (char)'#'){
//                 printf("%s\n", "im here again");
//                 strcpy(pass, "");
//                 curr_ind = 0;
//             }
//         }
//     }
//     return 0;
// }



