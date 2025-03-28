/**
 * @file
 * @brief
 *
 * @date 27.03.2025
 * @author Aleksandr Pavlov (s2400691)
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
