#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <strings.h>

#include "filter.h"


#define PBM_MAX_VALUE 1
#define PGM_MAX_VALUE 255


// ---------------------------------     just for testing
struct PNM_t {
   FormatPNM format;
   unsigned int width;
   unsigned int height;
   uint16_t max_value;

   size_t data_count;
   uint16_t *data;
};
typedef struct PNM_t PNM;
// ---------------------------------


// ======= Prototypes =======




// ======= Code =======


int turnaround(PNM *image) {
   if (image == NULL) return 1;

   FormatPNM format = image->format;
   unsigned int width = image->width;
   unsigned int height = image->height;
   uint16_t *data = image->data;

   size_t size = width * height;

   for (size_t i = 0; i < size / 2; ++i) {
      size_t j = size - 1 - i;
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
   if (image == NULL) return 1;
   if (image->format != FORMAT_PPM) return 2;

   unsigned int p;
   if (!strcasecmp(parameter, "r")) {
      p = 0;
   } else if (!strcasecmp(parameter, "v")) {
      p = 1;
   } else if (!strcasecmp(parameter, "b")) {
      p = 2;
   } else {
      return 3;
   }

   unsigned int width = image->width;
   unsigned int height = image->height;
   uint16_t *data = image->data;

   size_t size = width * height;

   for (size_t i = 0; i < size; ++i) {
      uint16_t temp = data[3 * i + p];
      data[3 * i] = 0;
      data[3 * i + 1] = 0;
      data[3 * i + 2] = 0;
      data[3 * i + p] = temp;
   }

   return 0;
}

int negative(PNM *image) {
   if (image == NULL) return 1;
   if (image->format != FORMAT_PPM) return 2;

   uint16_t max_value = image->max_value;
   size_t data_count = image->data_count;
   uint16_t *data = image->data;

   for (size_t i = 0; i < data_count; ++i) {
      data[i] = max_value - data[i];
   }
   return 0;
}

int fifty_shades_of_grey(PNM *image, const char *parameter) {
   if (image == NULL) return 1;
   if (image->format != FORMAT_PPM) return 2;

   int mode;
   if (sscanf(parameter, "%d", &mode) != 1) return 3;

   unsigned int width = image->width;
   unsigned int height = image->height;
   uint16_t max_value = image->max_value;
   uint16_t *data = image->data;

   size_t size = width * height;

   uint16_t *new_data = malloc(size * sizeof(uint16_t));
   if (new_data == NULL) return 1;

   switch (mode) {
      case 1:
         for (size_t i = 0; i < size; ++i) {
            int r = data[3 * i], g = data[3 * i + 1], b = data[3 * i + 2];
            new_data[i] = (uint16_t)round((r + g + b) / 3);
            new_data[i] = new_data[i] / max_value * PGM_MAX_VALUE;
         }
         break;
      case 2:
         for (size_t i = 0; i < size; ++i) {
            int r = data[3 * i], g = data[3 * i + 1], b = data[3 * i + 2];
            new_data[i] = (uint16_t)round(0.299 * r + 0.587 * g + 0.114 * b);
            new_data[i] = new_data[i] / max_value * PGM_MAX_VALUE;
         }
         break;
      default:
         free(new_data);
         return 3;
   }

   image->format = FORMAT_PGM;
   image->max_value = PGM_MAX_VALUE;
   image->data_count = size;
   image->data = new_data;

   free(data);

   return 0;
}

int black_and_white(PNM *image, const char *parameter) {
   if (image == NULL) return 1;
   if (image->format == FORMAT_PBM) return 2;

   int threshold;
   if (sscanf(parameter, "%d", &threshold) != 1) return 3;
   if (threshold < 0 || 255 < threshold) return 3;

   if (image->format == FORMAT_PPM) {
      if (fifty_shades_of_grey(image, "2") != 0) return 1;
   }

   unsigned int width = image->width;
   unsigned int height = image->height;
   uint16_t *data = image->data;

   size_t size = width * height;

   for (size_t i = 0; i < size; ++i) {
      data[i] = (data[i] >= threshold) ? PBM_MAX_VALUE : 0;
   }

   image->format = FORMAT_PBM;
   image->max_value = PBM_MAX_VALUE;

   return 0;
}
