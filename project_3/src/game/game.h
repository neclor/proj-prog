/**
 * @file game.h
 * @brief File contains functions for game logic
 *
 * @date 27.03.2025
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





void start_game();






void select_chest(unsigned int chest_index);





unsigned int get_wins();







unsigned int get_losses();

#endif // _GAME_H
