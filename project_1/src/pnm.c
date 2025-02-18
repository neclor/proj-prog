/**
 * @author: Pavlov Aleksandr s2400691
 * @date: 12.02.2025
 * @projet: INFO0030 Projet 1
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <strings.h>

#include "pnm.h"

typedef union DataPNM_t {
   unsigned int *ui;
   unsigned char *uc;
} DataPNM;

struct PNM_t {
   FormatPNM format;
   unsigned int width;
   unsigned int height;
   unsigned int max_value;
   size_t data_count;
   DataPNM data;
};

int str_to_format(FormatPNM *format, const char *format_string) {
   if (strcasecmp(format_string, "pbm") == 0) {
      *format = FORMAT_PBM;
   } else if (strcasecmp(format_string, "pgm") == 0) {
      *format = FORMAT_PGM;
   } else if (strcasecmp(format_string, "ppm") == 0) {
      *format = FORMAT_PPM;
   } else {
      return 1;
   }
   return 0;
}

int file_extension_to_format(FormatPNM *format, const char *filename) {
   int filename_len = strlen(filename);
   if (filename_len < 4) return 1;
   if (filename[filename_len - 4] != '.') return 1;
   const char *extension_string = &(filename[filename_len - 3]);
   return str_to_format(format, extension_string);
}

int create_pnm(
   PNM **image,
   FormatPNM format,
   unsigned int width,
   unsigned int height,
   unsigned int max_value
   ) {
   *image = malloc(sizeof(PNM));
   PNM *image_pnm = *image;
   if (image_pnm == NULL) return 1;
   image_pnm->format = format;
   image_pnm->width = width;
   image_pnm->height = height;
   image_pnm->max_value = max_value;

   size_t data_count = width * height;;
   size_t data_size;
   if (format == FORMAT_PPM) {
      data_count *= 3;
      data_size = data_count * sizeof(unsigned int);
   } else {
      data_size = data_count * sizeof(unsigned char);
   }

   void *data = malloc(data_size);
   if (data == NULL) {
      free(image_pnm);
      *image = NULL;
      return 1;
   }
   image_pnm->data_count = data_count;
   image_pnm->data.ui = data;
   return 0;
}

void free_pnm(PNM **image) {
   free((*image)->data.ui);
   free(*image);
   *image = NULL;
}

void skip_comments(FILE *file) {
   char c;
   while ((c = fgetc(file)) != EOF) {
      if isspace(c) continue;
      if (c == '#') {
         while ((c = fgetc(file)) != EOF && c != '\n') {
         }
      } else {
         ungetc(c, file);
         break;
      }
   }
}

int magic_string_to_format(FormatPNM *format, const char *magic_string) {
   if (strcmp(magic_string, "P1")) {
      *format = FORMAT_PBM;
   } else if (strcmp(magic_string, "P2")) {
      *format = FORMAT_PGM;
   } else if (strcmp(magic_string, "P3")) {
      *format = FORMAT_PPM;
   } else {
      return 1;
   }
   return 0;
}

int read_header(
   FormatPNM *format,
   unsigned int *width,
   unsigned int *height,
   unsigned int *max_value,
   FILE *file
   ) {
   skip_comments(file);

   char magic_string[3];
   if (fscanf(file, "%2s", magic_string) != 1) return 1;
   if (magic_string_to_format(format, magic_string) != 0) return 1;

   skip_comments(file);

   if (fscanf(file, "%u", width) != 1) return 1;

   skip_comments(file);

   if (fscanf(file, "%u", height) != 1) return 1;

   skip_comments(file);

   if (*format == FORMAT_PBM) {
      *max_value = 1;
   } else {
      if (fscanf(file, "%u", max_value) != 1) return 1;
   }
   return 0;
}

int read_data(PNM *image, FILE *file) {
   FormatPNM format = image->format;
   unsigned int width = image->width;
   unsigned int height = image->height;
   unsigned int max_value = image->max_value;
   size_t data_count = image->data_count;
   DataPNM data = image->data;

   for (size_t i = 0; i < data_count; i++) {
      skip_comments(file);

      unsigned int value;
      if (fscanf(file, "%u", &value) != 1) return 1;
      if (max_value < value) {
         value = max_value;
      }

      if (format == FORMAT_PPM) {
         data.ui[i] = value;
      } else {
         data.uc[i] = value;
      }
   }

   return 0;
}

int load_pnm(PNM **image, const char *filename) {
   FormatPNM file_extension;
   if (read_file_extension(&file_extension, filename) != 0) {
      return PNM_LOAD_INVALID_FILENAME;
   }

   FILE *file = fopen(filename, "r");
   if (file == NULL) return PNM_LOAD_INVALID_FILENAME;

   FormatPNM format;
   unsigned int width;
   unsigned int height;
   unsigned int max_value;

   if (read_header(&format, &width, &height, &max_value, file) != 0) {
      fclose(file);
      return PNM_LOAD_DECODE_ERROR;
   }

   if (format != file_extension) {
      fclose(file);
      return PNM_LOAD_DECODE_ERROR;
   }

   if (create_pnm(image, format, width, height, max_value) != 0) {
      fclose(file);
      return PNM_LOAD_MEMORY_ERROR;
   }

   if (read_data(*image, file) != 0) {
      free_pnm(image);
      fclose(file);
      return PNM_LOAD_DECODE_ERROR;
   }

   fclose(file);
   return PNM_LOAD_SUCCESS;
}

int write_pnm(PNM *image, const char *filename) {
   /* Insérez le code ici */

   return 0;
}





/*

fscanf(FILE *stream, format, …)	Читает форматированные данные из файла.

fgets(char *str, int size, FILE *stream)	Читает строку, включая пробелы и \n.

fgetc(FILE *stream)	Читает один символ.

getc(FILE *stream)	Аналогично fgetc().

ungetc(int ch, FILE *stream)	"Возвращает" символ в поток.

fread(void *ptr, size_t size, size_t count, FILE *stream)




*/
