/**
 * @file filter.c
 * @brief Implementation of filter functions for PNM images.
 *
 * @author Pavlov Aleksandr (s2400691)
 * @date 24.03.2025
*/

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings.h>

#include "pnm.h"

/* ======= External Functions ======= */

int turnaround(PNM *image) {
   if (image == NULL) return -1;

   FormatPNM format = get_format(image);
   unsigned int width = get_width(image);
   unsigned int height = get_height(image);
   uint16_t *data = get_data(image);

   size_t data_size = width * height;

   for (size_t i = 0; i < data_size / 2; ++i) {
      size_t j = data_size - 1 - i;
      if (format == FORMAT_PPM) {
         for (int a = 0; a < 3; ++a) {
            uint16_t temp = data[3 * i + a];
            data[3 * i + a] = data[3 * j + a];
            data[3 * j + a] = temp;
         }
      } else {
         uint16_t temp = data[i];
         data[i] = data[j];
         data[j] = temp;
      }
   }
   return 0;
}

int monochrome(PNM *image, const char *parameter) {
   if (image == NULL || parameter == NULL) return -1;
   if (get_format(image) != FORMAT_PPM) return -2;

   unsigned int p;
   if (!strcasecmp(parameter, "r")) {
      p = 0;
   } else if (!strcasecmp(parameter, "v")) {
      p = 1;
   } else if (!strcasecmp(parameter, "b")) {
      p = 2;
   } else {
      return -3;
   }

   unsigned int width = get_width(image);
   unsigned int height = get_height(image);
   uint16_t *data = get_data(image);

   size_t data_size = width * height;

   for (size_t i = 0; i < data_size; ++i) {
      uint16_t temp = data[3 * i + p];
      for (int a = 0; a < 3; ++a) data[3 * i + a] = 0;
      data[3 * i + p] = temp;
   }
   return 0;
}

int negative(PNM *image) {
   if (image == NULL) return -1;
   if (get_format(image) != FORMAT_PPM) return -2;

   uint16_t max_value = get_max_value(image);
   uint16_t *data = get_data(image);

   size_t data_count = get_width(image) * get_height(image) * 3;

   for (size_t i = 0; i < data_count; ++i) {
      data[i] = max_value - data[i];
   }
   return 0;
}

int fifty_shades_of_grey(PNM *image, const char *parameter) {
   if (image == NULL || parameter == NULL) return -1;
   if (get_format(image) != FORMAT_PPM) return -2;

   int mode;
   if (sscanf(parameter, "%d", &mode) != 1) return -3;
   if (mode != 1 && mode != 2) return -3;

   unsigned int width = get_width(image);
   unsigned int height = get_height(image);
   uint16_t max_value = get_max_value(image);
   uint16_t *data = get_data(image);

   size_t data_size = width * height;

   uint16_t *new_data = malloc(data_size * sizeof(uint16_t));
   if (new_data == NULL) return -4;

   for (size_t i = 0; i < data_size; ++i) {
      int r = data[3 * i];
      int g = data[3 * i + 1];
      int b = data[3 * i + 2];
      switch (mode) {
         case 1:
            new_data[i] = (uint16_t)round((r + g + b) / 3);
            break;
         case 2:
            new_data[i] = (uint16_t)round(0.299 * r + 0.587 * g + 0.114 * b);
            break;
      }
      new_data[i] *= PGM_MAX_VALUE / max_value;
   }

   set_pnm(image, FORMAT_PGM, width, height, PGM_MAX_VALUE, new_data);
   free(data);
   return 0;
}

int black_and_white(PNM *image, const char *parameter) {
   if (image == NULL || parameter == NULL) return -1;

   FormatPNM format = get_format(image);
   if (format == FORMAT_PBM ) return -2;

   int threshold;
   if (sscanf(parameter, "%d", &threshold) != 1) return -3;
   if (threshold < 0 || 255 < threshold) return -3;

   if (format == FORMAT_PPM) {
      if (fifty_shades_of_grey(image, "2") != 0) return -1;
   }

   unsigned int width = get_width(image);
   unsigned int height = get_height(image);
   uint16_t *data = get_data(image);

   size_t data_size = width * height;

   for (size_t i = 0; i < data_size; ++i) {
      data[i] = (data[i] >= threshold) ? PBM_MAX_VALUE : 0;
   }

   set_pnm(image, FORMAT_PBM, width, height, PBM_MAX_VALUE, data);
   return 0;
}
