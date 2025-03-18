/**
 * @file filter.h
 * @brief Header file containing image processing function prototypes.
 *
 * @author Pavlov Aleksandr
 * @date 24.03.2025
*/

#ifndef _FILTER_H
#define _FILTER_H

#include "pnm/pnm.h"

/* ======= Function Prototypes ======= */

/**
 * @brief Rotates the image by 180 degrees.
 *
 * Reverses the order of the pixels in the image, effectively rotating it by
 * 180 degrees.
 *
 * @param image Pointer to the PNM image structure.
 *
 * @pre image != NULL
 *
 * @return
 *     - 0: Success
 *     - 1: Error (e.g., image is NULL)
 */
int turnaround(PNM *image);

/**
 * @brief Converts the image to monochrome based on a specific color channel.
 *
 * Extracts one of the red, green, or blue channels from a PPM image and sets
 * the other channels to zero, creating a monochrome image based on the
 * selected channel.
 *
 * @param image Pointer to the PNM image structure.
 * @param parameter A string indicating the color channel ("r", "v", or "b").
 *
 * @pre image != NULL, parameter != NULL
 *
 * @return
 *     - 0: Success
 *     - 1: Error (e.g., invalid parameter)
 *     - 2: Error (e.g., image is not in PPM format)
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
 *     - 0: Success
 *     - 1: Error (e.g., image is NULL)
 *     - 2: Error (e.g., image is not in PPM format)
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
 *     - 0: Success
 *     - 1: Error (e.g., memory allocation failure)
 *     - 2: Error (e.g., image is not in PPM format)
 *     - 3: Error (e.g., invalid parameter)
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
 *     - 0: Success
 *     - 1: Error (e.g., invalid parameter)
 *     - 2: Error (e.g., image is not in PPM format)
 */
int black_and_white(PNM *image, const char *parameter);

#endif // _FILTER_H
