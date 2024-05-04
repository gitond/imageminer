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
 * -1: reached the end of the function without reaching other return statement (EOF)
 * -2: ERROR: incorrect usage, unspecified file
 * -3: ERROR: Failed at creating quirc object
 * -4: ERROR: Failed to load image
 */
int imageQrCount(int argc, char **argv);


char * imageContents(int argc, char **argv);

#endif
