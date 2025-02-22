/**
 * @author: Pavlov Aleksandr s2400691
 * @date: 12.02.2025
 * @projet: INFO0030 Projet 1
*/


#ifndef _PNM_H
#define _PNM_H 1


#define PNM_LOAD_SUCCESS 0
#define PNM_LOAD_MEMORY_ERROR -1
#define PNM_LOAD_INVALID_FILENAME -2
#define PNM_LOAD_DECODE_ERROR -3

#define PNM_WRITE_SUCCESS 0
#define PNM_WRITE_INVALID_FILENAME -1
#define PNM_WRITE_FILE_MANIPULATION_ERROR -2


typedef enum FormatPNM_t {
    FORMAT_PBM,
    FORMAT_PGM,
    FORMAT_PPM
} FormatPNM;

typedef struct PNM_t PNM;


/**
 * Converts a string to the corresponding FormatPNM enum value.
 *
 * @param format (FormatPNM*): Pointer to store the resulting enum value.
 * @param format_string (const char*): String representation of the format.
 *
 * @return:
 *     0 Success
 *     1 If the string does not match any format
 */
int str_to_format(const char *format_string, FormatPNM *format);

/**
 * Determines the file format based on the filename extension and sets
 * the corresponding FormatPNM enum value.
 *
 * @param format (FormatPNM*): Pointer to store the resulting enum value.
 * @param filename (const char*): Name of the file to analyze.
 *
 * @return:
 *     0 Success
 *     1 If file extension does not match any format
 */
int file_extension_to_format(const char *filename, FormatPNM *format);

/**
 * @param image (PNM**):
 */
void free_pnm(PNM **image);

/**
 * Charge une image PNM depuis un fichier.
 *
 * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * @param filename le chemin vers le fichier contenant l'image.
 *
 * @pre: image != NULL, filename != NULL
 * @post: image pointe vers l'image chargée depuis le fichier.
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 */
int load_pnm(PNM **image, const char* filename);

/**
 * Sauvegarde une image PNM dans un fichier.
 *
 * @param image un pointeur sur PNM.
 * @param filename le chemin vers le fichier de destination.
 *
 * @pre: image != NULL, filename != NULL
 * @post: le fichier filename contient l'image PNM image.
 *
 * @return:
 *     0 Succès
 *    -1 Nom du fichier malformé
 *    -2 Erreur lors de la manipulation du fichier
 */
int write_pnm(PNM *image, const char* filename);

#endif // pnm.h
