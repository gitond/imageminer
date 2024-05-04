// C standard headers
#include <stdio.h>	// For print debugging, remove later
#include <string.h>
#include <stdlib.h>

// quirc library
#include "quirc.h"			// For main library functionality
#include "quirc/tests/dbgutil.h"	// For jpeg png related functionality

// Own headers
#include "imageminer.h"

int imageQrCount(int argc, char **argv){
	struct quirc *q; // Data location to hold qr-decoder

	if (argc < 2){
		return -2; // ERROR: incorrect usage. Specify file to test with.
	}

	q = quirc_new();
	if(!q){
		return -3; // ERROR: Failed at creating quirc object
	}

	int imgLoadStatus = -1;
	// We check if included file is readable jpeg or png. If not, exiting with error
	// This runs quirc_begin() internally
	if (check_if_png(argv[1])) {
		imgLoadStatus = load_png(q, argv[1]);
	} else {
		imgLoadStatus = load_jpeg(q, argv[1]);
	}
	if (imgLoadStatus < 0) {
		quirc_destroy(q);
		return -4; // ERROR: Failed to load image
	}

	quirc_end(q); // Necessary, because above code runs quirc_begin()

	int count = quirc_count(q); // How many QR-codes in image?
	quirc_destroy(q);
	return count;

	// By all logic this should be unreachable
	quirc_destroy(q);
	return -1; // imageQRCount EOF
}

char * imageContents(int argc, char **argv){
	struct quirc *q; // Data location to hold qr-decoder
	const int BUFFER_LENGTH = 2048;
	char mainBuffer[BUFFER_LENGTH];
	char tmpBuffer[BUFFER_LENGTH];
	int processedLength = 0;
	int totalLength = 0;

/*
	char* one = "quick";
	char* two = "brown";
	char* three = "fox";

	processedLength = snprintf(mainBuffer, BUFFER_LENGTH,
		"%s %s %s %s",
		tmpBuffer, one, two, three
	);

	strncpy(tmpBuffer, mainBuffer, BUFFER_LENGTH);

	processedLength = snprintf(mainBuffer, BUFFER_LENGTH,
		"%s %s %s %s",
		tmpBuffer, two, two, three
	);

	strncpy(tmpBuffer, mainBuffer, BUFFER_LENGTH);

	if (processedLength >= BUFFER_LENGTH){
		return "ERROR: amount of data in qr-codes exceeded 2048 byte buffer";
	}

	printf("Buffer: %s \n", mainBuffer);
*/

	if (argc < 2){
		return "ERROR: incorrect usage. Specify file to test with.";
	}

	q = quirc_new();
	if(!q){
		return "ERROR: Failed at creating quirc object";
	}

	int imgLoadStatus = -1;
	// We check if included file is readable jpeg or png. If not, exiting with error
	// This runs quirc_begin() internally
	if (check_if_png(argv[1])) {
		imgLoadStatus = load_png(q, argv[1]);
	} else {
		imgLoadStatus = load_jpeg(q, argv[1]);
	}
	if (imgLoadStatus < 0) {
		quirc_destroy(q);
		return "ERROR: Failed to load image";
	}

	quirc_end(q); // Necessary, because above code runs quirc_begin()

	int count = quirc_count(q); // How many QR-codes in image?

	for (int i = 0; i < count; i++){
		struct quirc_code code;
		struct quirc_data data;
		quirc_decode_error_t err;

		quirc_extract(q, i, &code); // should extract i:th code of image to memory address of code
		err = quirc_decode(&code, &data); // should read the data from the qr-code at &code and save it to the memory adress of data. Any generated errors get saved to err.
		if (err == QUIRC_ERROR_DATA_ECC) {
			// Trying to flip and reread data on unsuccessful read
			quirc_flip(&code); // QR-code mirrorind function as declared in quirc.h
			err = quirc_decode(&code, &data);
		}

		// For debugging (On cleanup remove stdio)
		if (data.payload_len > 0){

			processedLength = snprintf(mainBuffer, BUFFER_LENGTH, "%s<payload id=\"%d\">%s</payload>",tmpBuffer,i+1,data.payload);
			totalLength += processedLength;
			if (totalLength >= BUFFER_LENGTH){
				return "ERROR: amount of data in qr-codes exceeded 2048 byte buffer";
			}
			strncpy(tmpBuffer, mainBuffer, BUFFER_LENGTH);
/*
			printf("\n");
			printf("Payload %d : %s \n", i+1, data.payload);
			printf("Buffer: %s \n", mainBuffer);
*/
//			printf("No %d : %s \n", i+1, buffer);
//			printf("First char of payload %d : %c \n", i+1, data.payload[0]);
//			printf("Length of payload %d : %d \n", i+1, data.payload_len);

			//return &data.payload[0];
		}
	}

	if (totalLength > 0){
		char *returnable = malloc((totalLength * sizeof(char)));
		if (returnable) {
			strncpy(returnable, mainBuffer, totalLength);

			quirc_destroy(q);
	//		return &mainBuffer[0];
			return (returnable);
		}
		free(returnable);
	}

	quirc_destroy(q);
	return "imageContents EOF";
}
