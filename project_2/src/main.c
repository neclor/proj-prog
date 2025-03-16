/**
 * @file main.c
 * @author: Pavlov Aleksandr s2400691
 * @date: 24.03.2025
 * @brief Main file
*/

#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "filter.h"
#include "pnm/pnm.h"


#define PROGRAM_NAME "./filtre"
#define VERSION "0.1.0"
#define AUTHORS "Pavlov Aleksandr (s2400691)"


enum {
   GETOPT_HELP_CHAR = (CHAR_MIN - 2),
   GETOPT_VERSION_CHAR = (CHAR_MIN - 3),
};

static struct option const longopts[] = {
   {"input", required_argument, NULL, 'i'},
   {"output", required_argument, NULL, 'o'},
   {"filtre", required_argument, NULL, 'f'},
   {"parametres", required_argument, NULL, 'p'},
   {"help", no_argument, NULL, GETOPT_HELP_CHAR},
   {"version", no_argument, NULL, GETOPT_VERSION_CHAR},
   {NULL, no_argument, NULL, 0},
};

const char *program_name;


// ======= Prototypes =======


/**
 * @brief Displays help about using the command and exits the program.
 *
 * @param status
 */
static void usage(int status);


// ======= Code =======


/**
 * @brief Main function.
 *
 * @param argc
 * @param argv
 *
 * @return
 */
int main(int argc, char **argv) {
   program_name = argv[0];

   const char *input_filename = NULL;
   const char *output_filename = NULL;
   const char *filter_string = NULL;
   const char *parameter_string = NULL;

   int optc;
   while ((optc = getopt_long(argc, argv, "i:o:f:p:", longopts, NULL)) != -1) {
      switch (optc) {
         case 'i':
            input_filename = optarg;
            break;
         case 'o':
            output_filename = optarg;
            break;
         case 'f':
            filter_string = optarg;
            break;
         case 'p':
            parameter_string = optarg;
            break;
         case GETOPT_HELP_CHAR:
            usage(EXIT_SUCCESS);
            break;
         case GETOPT_VERSION_CHAR:
            fprintf(stdout, "%s %s\n\nWritten by %s.\n",
               PROGRAM_NAME, VERSION, AUTHORS);
            exit(EXIT_SUCCESS);
            break;
         default:
            usage(EXIT_FAILURE);
      }
   }

   if (input_filename == NULL) {
      fprintf(stderr, "%s: missing '-i' argument\n", program_name);
      usage(EXIT_FAILURE);
   }
   if (output_filename == NULL) {
      fprintf(stderr, "%s: missing '-o' argument\n", program_name);
      usage(EXIT_FAILURE);
   }
   if (filter_string == NULL) {
      fprintf(stderr, "%s: missing '-f' argument\n", program_name);
      usage(EXIT_FAILURE);
   }

   PNM *image = NULL;

   switch (load_pnm(&image, input_filename)) {
      case PNM_LOAD_SUCCESS:
         break;
      case PNM_LOAD_MEMORY_ERROR:
         fprintf(stderr, "%s: ", program_name);
         perror("");
         return EXIT_FAILURE;
      case PNM_LOAD_INVALID_FILENAME:
         fprintf(stderr, "%s: invalid filename '%s': ",
            program_name, input_filename);
         perror("");
         return EXIT_FAILURE;
      case PNM_LOAD_DECODE_ERROR:
         fprintf(stderr, "%s: '%s': decode error\n",
            program_name, input_filename);
         return EXIT_FAILURE;
      default:
         perror("");
         return EXIT_FAILURE;
   }

   int ok = 1;
   if (!strcasecmp(filter_string, "retournement")) {
      switch (turnaround(image)) {
         case 0:
            break;
         case 1:
            int ok = 0;
            fprintf(stderr, "%s: filter error", program_name);
            break;
         default:
            int ok = 0;
            perror("");
            break;
      }
   } else if (!strcasecmp(filter_string, "monochrome")) {
      switch (monochrome(image, parameter_string)) {
         case 0:
            break;
         case 1:
            int ok = 0;
            break;
         default:
            int ok = 0;
            break;
      }
   } else if (!strcasecmp(filter_string, "negatif")) {
      switch (negatif(image)) {
         case 0:
            break;
         case 1:
            int ok = 0;
            break;
         default:
            int ok = 0;
            break;
      }
   } else if (!strcasecmp(filter_string, "gris")) {

   } else if (!strcasecmp(filter_string, "NB")) {

   } else {
      fprintf(stderr, "%s: '%s': invalid filter\n",
         program_name, filter_string);
   }


   free_pnm(&image);


   retournement

   monochrome r   v b
   negatif
   gris       1 2
   NB 0 до 255









   switch (write_pnm(image, output_filename)) {
      case PNM_WRITE_SUCCESS:
         break;
      case PNM_WRITE_INVALID_FILENAME:
         ok = 0;
         fprintf(stderr, "%s: invalid filename '%s': ",
            program_name, output_filename);
         perror("");
         break;
      case PNM_WRITE_FILE_MANIPULATION_ERROR:
         ok = 0;
         fprintf(stderr, "%s: '%s': file manipulation error: ",
            program_name, output_filename);
         perror("");
         break;
      default:
         ok = 0;
         perror("");
   }

   free_pnm(&image);

   return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}

static void usage(int status) {
   if (status != EXIT_SUCCESS) {
      fprintf(stderr, "Try '%s --help' for more information.\n",
         program_name);
   } else {
      printf("Usage: %s [-f FORMAT] -i SOURCE -o DEST\n", program_name);
      fputs("\
Manipulates PNM format files.\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
  -f, --format=FORMAT          specify format FORMAT={PBM,PGM,PPM}\n\
  -i, --input=FILE             specify input file {.ppm,.pbm,.pgm}\n\
  -o, --output=FILE            specify output file {.ppm,.pbm,.pgm}\n\
      --help        display this help and exit\n\
      --version     output version information and exit\n\
", stdout);
   }
   exit(status);
}

