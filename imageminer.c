// C standard headers

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

	quirc_destroy(q);
	return "imageContents EOF";
}
