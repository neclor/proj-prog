/**
 * main.c
 * 
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: Nom Prenom Matricule
 * @date: 
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include "pnm.h"



int main(int argc, char *argv[]) {
   char *optstring = "i:o:f:";
   int option;
   char *input_filename = NULL;
   char *output_filename = NULL;
   PNM *image = NULL;

   while ((option = getopt(argc, argv, optstring)) != -1) {
      switch (option) {
         case 'i':
            input_filename = optarg;
            break;
         case 'o':
            output_filename = optarg;
            break;
         default:
            fprintf(stderr, "Usage: %s -i input_file -o output_file\n", argv[0]);
            exit(EXIT_FAILURE);
      }
   }

   if (input_filename == NULL || output_filename == NULL) {
      fprintf(stderr, "Input and output files must be specified.\n");
      exit(EXIT_FAILURE);
   }

   if (load_pnm(&image, input_filename) != 0) {
      fprintf(stderr, "Failed to load PNM image from %s\n", input_filename);
      exit(EXIT_FAILURE);
   }

   if (write_pnm(image, output_filename) != 0) {
      fprintf(stderr, "Failed to write PNM image to %s\n", output_filename);
      exit(EXIT_FAILURE);
   }

   
   return 0;
}