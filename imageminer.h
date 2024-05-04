/*
 * This header file should include all the descriptions of the functions to
 * be used in the imageminer backend. The idea is to compile these functions
 * on mobile hardware and integrate them into a react native app.
 */

#ifndef IMAGEMINER
#define IMAGEMINER

/*
 * A function that calculates the amount of QR-codes in an image.
 *
 * Possible returns:
 * numbers 0->:	amount of QR-codes in input image
 * -1:		reached the end of the function without reaching other return statement (EOF)
 * -2: 		ERROR: incorrect usage, unspecified file
 * -3: 		ERROR: Failed at creating quirc object
 * -4: 		ERROR: Failed to load image
 */
int imageQrCount(int argc, char **argv);

/*
 * A function that reads the QR-code payloads into the buffer and returns all readable payloads as char*.
 * Compatible with multiple QR-codes in the image
 *
 * Possible returns:
 * On succesful payload extraction:
 * n*'<payload id="x">s</payload>'
 * 	where:
 *		n is 	the amount of payloads extracted (1->)
 *		x is	an integer (1->)
 *		s is	an extracted payload
 *
 * On unsuccesful payload extraction (no readable QR-code in image or unexplained EOF error):
 * "imageContents EOF, no readable QR-codes found"
 *
 * On other, explainable error:
 * "ERROR: "s
 *	where:
 *		s is	an error message (char*)
 */
char * imageContents(int argc, char **argv);

#endif
