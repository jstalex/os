#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>


const char *get_time(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    static char str[30];
    sprintf(str, "%d-%02d-%02d %02d:%02d:%02d",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return str;
}


int main(int argc, char *argv[])
{
	FILE *res;
    res = fopen("result.txt", "A");

    char x = '\0';
    // char line[10];
    char pass[4] = { '\0' };
    char temp[2];
    int curr_ind = 0;

    while (1) { 
        //scanf("%s", &temp);
        //sprintf(temp, "%s", line);
        if (x) {
            sprintf(temp, "%c", x);
            // printf("index = %d, x = %s, temp = %s\n", curr_ind, temp, temp);
            if (curr_ind < 4) {
                strncat(pass, temp, 1);    
                curr_ind++;
            }
            else {
                curr_ind = 0;
            }
            printf("%s\n", pass);

            if (strcmp(pass, "1337") == 0){
                // printf("%s\n", "im here");
                fprintf(res, "%s\n", "True Pass");
                char pass[4] = { '\0' };
                curr_ind = 0;
            }

            if (curr_ind == 3) {
                if (strcmp(pass, "1337") == 0){
                    printf("%s\n", "im here");
                    char pass[4] = { '\0' };
                    fprintf(res, "%s\n", "True Pass");
                    curr_ind = 0;
                }
            }
        }
    }

    fclose(res);
    return 0;
}



