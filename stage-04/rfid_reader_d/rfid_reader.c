/*******************************************************************************
 * Copyright (c) 2022 Sergey Balabaev (sergei.a.balabaev@gmail.com)                     *
 *                                                                             *
 * The MIT License (MIT):                                                      *
 * Permission is hereby granted, free of charge, to any person obtaining a     *
 * copy of this software and associated documentation files (the "Software"),  *
 * to deal in the Software without restriction, including without limitation   *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell   *
 * copies of the Software, and to permit persons to whom the Software is       *
 * furnished to do so, subject to the following conditions:                    *
 * The above copyright notice and this permission notice shall be included     *
 * in all copies or substantial portions of the Software.                      *
 *                                                                             *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,             *
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR       *
 * OTHER DEALINGS IN THE SOFTWARE.                                             *
 ******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include "MFRC522.h"
#include "time.h"

int debug = 0;

void help()
{
	printf("    Use this application for reading from rfid reader\n");
	printf("    execute format: ./rfid_reader [-h][-q] \n");
	printf("    return: Card ID\n");
	printf("    -h - help\n");
	printf("    -q - quiet\n");
}

const char *get_time(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    static char str[30];
    sprintf(str, "%d-%02d-%02d %02d:%02d:%02d",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return str;
}


int main(int argc, char *argv[])
{
	int quiet = 0;
	int fifo_fd;
	if (argc > 1) {
		if ((strcmp(argv[1], "-h") == 0)) {
			help();
			return 0;
		} else {
			if ((strcmp(argv[1], "-q") == 0)) {
				quiet = 1;
			}

			if (argv[2] != "") {
				fifo_fd = open(argv[2], 2); // O_RDWR
			}
		}
	}

	uint8_t mode, bits;
	int status;
	unsigned char backBits;
	unsigned char *uid;
	unsigned char blockno;
	char *next;

	char true_uid[12];
	char readed_uid[12];

	FILE *res;

	MFRC522_Init(0);
	while (1) {
		while ((status = MFRC522_Request(PICC_REQIDL, &backBits)) !=
		       MI_OK)
			usleep(500);

		if (status == MI_OK)
			if (!quiet)
				printf("Card detected\n");

		status = MFRC522_Anticoll(&uid);

		if (status == MI_OK) {
			// print UID
			//if (!quiet) {
			//	printf("%02x %02x %02x %02x\n", uid[0], uid[1],
			//	       uid[2], uid[3]);
			//	fflush(stdout);
			//	break;
			//}

			sprintf(readed_uid, "%02x %02x %02x %02x", uid[0], uid[1], uid[2], uid[3]);
			if (strcmp(readed_uid, "<write here>") == 0){
				res = fopen("result.txt", "a");
				fprintf(res, "%s %s\n", "True RFID key", get_time());
				fclose(res);
			}
			
			fflush(stdout);
			sleep(1);
		}
	}
	close(fifo_fd);
	
}
