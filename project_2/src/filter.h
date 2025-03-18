/**
 * @file filter.h
 * @brief Header file containing image processing function prototypes.
 *
 * @author Pavlov Aleksandr (s2400691)
 * @date 24.03.2025
*/

#ifndef _FILTER_H
#define _FILTER_H

#include "pnm.h"

/* ======= Constants ======= */

#define FILTER_SUCCESS 0
#define FILTER_WRONG_IMAGE_FORMAT -1
#define FILTER_INVALID_PARAMETER -2

/* ======= Function Prototypes ======= */

/**
 * @brief Rotates the image by 180 degrees.
 *
 * @param image Pointer to the PNM image structure.
 *
 * @pre image != NULL
 *
 * @return
 *     0: Success
 *    -1: Image is NULL
 */
int turnaround(PNM *image);

/**
 * @brief Converts the image to monochrome based on a specific color channel.
 *
 * @param image Pointer to the PNM image structure.
 * @param parameter A string indicating the color channel ("r", "v", "b").
 *
 * @pre image != NULL, parameter != NULL
 *
 * @return
 *     0: Success
 *    -1: Image is NULL
 *    -2: Image is not in PPM format
 *    -3: Invalid parameter
 */
int monochrome(PNM *image, const char *parameter);

/**
 * @brief Inverts the colors of the image.
 *
 * Creates a negative of the image by subtracting each pixel's value from the
 * maximum value of the image.
 *
 * @param image Pointer to the PNM image structure.
 *
 * @pre image != NULL
 *
 * @return
 *     0: Success
 *    -1: Image is NULL
 *    -2: Image is not in PPM format
 */
int negative(PNM *image);

/**
 * @brief Converts the image to grayscale.
 *
 * Converts a PPM image to grayscale using one of two methods:
 * - Method 1: Averages the red, green, and blue channels.
 * - Method 2: Uses a weighted average (0.299 * R + 0.587 * G + 0.114 * B).
 *
 * @param image Pointer to the PNM image structure.
 * @param parameter A string indicating the method ("1" or "2").
 *
 * @pre image != NULL, parameter != NULL
 *
 * @return
 *     0: Success
 *    -1: Memory allocation failure
 *    -2: Image is not in PPM format
 *    -3: Invalid parameter
 */
int fifty_shades_of_grey(PNM *image, const char *parameter);

/**
 * @brief Converts the image to black and white.
 *
 * Thresholds the image to create a black-and-white (binary) image. Pixels with
 * a value above the threshold are set to white, and those below are set to
 * black.
 *
 * @param image Pointer to the PNM image structure.
 * @param parameter A string representing the threshold value (0 to 255).
 *
 * @pre image != NULL, parameter != NULL
 *
 * @return
 *     0: Success
 *    -1: Invalid parameter
 *    -2: Image is not in PPM format
 *    -3: Invalid parameter
 */
int black_and_white(PNM *image, const char *parameter);

#endif // _FILTER_H
