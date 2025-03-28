/**
 * @file
 * @brief
 *
 * @date 27.03.2025
 * @author Aleksandr Pavlov (s2400691)
*/

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

/* ======= Pointers ======= */

void (*on_game_begun)() = NULL;
void (*on_chest_opened)(int chest_index, bool treasured) = NULL;
void (*on_game_over)(bool win) = NULL;

/* ======= Constants ======= */

typedef enum States_t {
   FIRST_CHOICE,
   SECOND_CHOICE,
   END,
} States;

/* ======= Variables ======= */

static States state = FIRST_CHOICE;

static unsigned int wins = 0;
static unsigned int losses = 0;

static int treasure_chest_index = 0;
static int selected_chest_index;
static int opened_chest_index;

/* ======= Internal Function Prototypes ======= */

static void first_select_chest(unsigned int i);
static void open_empty_chest();
static void second_select_chest(unsigned int i);

/* ======= External Functions ======= */

void start_game() {
   srand(time(NULL));
   state = FIRST_CHOICE;
   treasure_chest_index = rand() % CHESTS_NUMBER;

   if (on_game_begun!= NULL) on_game_begun();
}

void select_chest(unsigned int i) {
   if (i < 0 || 2 < i) return;

   switch (state) {
      case FIRST_CHOICE:
         first_select_chest(i);
         break;

      case SECOND_CHOICE:
         second_select_chest(i);
         break;

      default:
         break;
   }
}

unsigned int get_wins() {
   return wins;
}

unsigned int get_losses() {
   return losses;
}

/* ======= Internal Functions ======= */

static void first_select_chest(unsigned int chest_index) {
   selected_chest_index = chest_index;
   open_empty_chest();
}

static void open_empty_chest() {
   do {
      opened_chest_index = rand() % CHESTS_NUMBER;
   } while (
      opened_chest_index == selected_chest_index ||
      opened_chest_index == treasure_chest_index
   );

   state = SECOND_CHOICE;

   if (on_chest_opened != NULL) on_chest_opened(opened_chest_index, false);
}

static void second_select_chest(unsigned int i) {
   if (i == opened_chest_index) return;

   bool win = (i == treasure_chest_index) ? true : false;
   if (win) {
      wins++;
   } else {
      losses++;
   }

   state = END;

   if (on_chest_opened != NULL) on_chest_opened(i, win);
   if (on_game_over != NULL) on_game_over(win);
}
