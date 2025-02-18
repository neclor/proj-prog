/**
 * @author: Pavlov Aleksandr s2400691
 * @date: 12.02.2025
 * @projet: INFO0030 Projet 1
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "pnm.h"

struct PNM_t {
   FormatPNM format;
   unsigned int width;
   unsigned int height;
   unsigned int max_value;
   void *data;
};

FormatPNM get_format(PNM *image) {
   return image->format;
}

int create_pnm(PNM **image,
   FormatPNM format,
   unsigned int width,
   unsigned int height,
   unsigned int max_value
   ) {
   *image = malloc(sizeof(PNM));
   if (*image == NULL) return 1;
   PNM *image_pnm = *image;
   image_pnm->format = format;
   image_pnm->width = width;
   image_pnm->height = height;
   image_pnm->max_value = max_value;

   size_t data_size;
   if (format == FORMAT_PPM) {
      data_size = 3 * width * height * sizeof(unsigned int);
   } else {
      data_size = width * height * sizeof(unsigned char);
   }

   void *data = malloc(data_size);
   if (data == NULL) {
      free(*image);
      *image = NULL;
      return 1;
   }
   image_pnm->data = data;
   return 0;
}

void free_pnm(PNM **image) {
   free((*image)->data);
   free(*image);
   *image = NULL;
}

int read_file_extension(FormatPNM *file_extension, const char *filename) {
   int filename_len = strlen(filename);
   if (filename_len < 4) return 1;

   const char *filename_end = &(filename[filename_len - 4]);
   if (strcmp(filename_end, ".pbm") == 0) {
      *file_extension = FORMAT_PBM;
   } else if (strcmp(filename_end, ".pgm") == 0) {
      *file_extension = FORMAT_PGM;
   } else if (strcmp(filename_end, ".ppm") == 0) {
      *file_extension = FORMAT_PPM;
   } else {
      return 1;
   }
   return 0;
}

void skip_comments(FILE *file) {
   char c;
   while ((c = fgetc(file)) != EOF) {
      if isspace(c) continue;
      if (c == '#') {
         while ((c = fgetc(file)) != EOF && c != '\n') {}
      } else {
         ungetc(c, file);
         break;
      }
   }
}

int read_header(
   FormatPNM *format,
   unsigned int *width,
   unsigned int *height,
   unsigned int *max_value,
   FILE *file
   ) {
   skip_comments(file);

   char format_string[3];
   if (fscanf(file, "%2s", format_string) != 1) return 1;

   if (strcmp(format_string, "P1")) {
      *format = FORMAT_PBM;
   } else if (strcmp(format_string, "P2")) {
      *format = FORMAT_PGM;
   } else if (strcmp(format_string, "P3")) {
      *format = FORMAT_PPM;
   } else {
      return 1;
   }

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
   void *data = image->data;
   size_t count = width * height * (format == FORMAT_PPM ? 3 : 1);

   for (size_t i = 0; i < count; i++) {
      skip_comments(file);

      unsigned int value;
      if (fscanf(file, "%u", &value) != 1) return 1;
      if (max_value < value) return 1;

      if (format == FORMAT_PPM) {
         ((unsigned int*)data)[i] = value;
      } else {
         ((unsigned char*)data)[i] = (unsigned char)value;
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
      return PNM_LOAD_INVALID_FILENAME;
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
