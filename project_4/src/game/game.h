/**
 * @file game.h
 * @brief Header file containing function prototypes for the game logic.
 *
 * @date 29.03.2025
 * @author Aleksandr Pavlov (s2400691)
*/

#ifndef _GAME_H
#define _GAME_H

#include <stdbool.h>

/* ======= Constants ======= */

#define CHESTS_NUMBER 3

/* ======= Pointers ======= */

extern void (*on_game_begun)();

extern void (*on_chest_opened)(int chest_index, bool treasured);

extern void (*on_game_over)(bool win);

/* ======= Function Prototypes ======= */

void start_game(void);

void select_chest(unsigned int chest_index);

unsigned int get_wins(void);

unsigned int get_losses(void);

#endif // _GAME_H
