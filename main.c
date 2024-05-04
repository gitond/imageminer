// Driver for imageminer.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "imageminer.h"

int main(int argc, char **argv)
{
	// Test code for imageQrCount
	int iqrcOutp = imageQrCount(argc, argv);
	switch (iqrcOutp) {
		case -1:
			printf("imageQrCount EOF \n");
			break;
		case -2:
			printf("imageQrCount ERROR %d : incorrect usage, unspecified file \n", iqrcOutp);
			break;
		case -3:
			printf("imageQrCount ERROR %d : Failed at creating quirc object \n", iqrcOutp);
			break;
		case -4:
			printf("imageQrCount ERROR %d : Failed to load image \n", iqrcOutp);
			break;
		default:
			printf("Counted %d QR-codes in file \n", iqrcOutp);
	}

	// Test code for imageContenrs
	char *icOutp = imageContents(argc, argv);

	printf("%s \n", icOutp);

	// Buffer to char* conversion of payload uses malloc, free command is needed for memory management.
	if(strstr(icOutp, "</payload>")){
		free( icOutp );
	}

	return 0;
}
