/**
 * @file main.c
 * @brief Treasure Hunt
 *
 * @date 00.00.2025
 * @version 1.0.0
 * @authors Aleksandr Pavlov (s2400691)
*/

#include <gtk/gtk.h>

#include "game.h"
#include "ui.h"

/* ======= Functions ======= */

int main(int argc, char **argv) {
   gtk_init(&argc, &argv);

   init_ui();
   start_game();

   gtk_main();
   return EXIT_SUCCESS;
}
