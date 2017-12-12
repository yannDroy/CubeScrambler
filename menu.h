/* Author : YANN DROY */
/******** 2015 ********/

#ifndef __MENU__
#define __MENU__

void freeze (int* run, int* pass, int* nb_moves, int* border, int* gen2, Uint32* colors, SDL_Surface* window, int cube[][9], char** scramble);

void init_colors (Uint32* colors, SDL_Surface* window);

void affect_color (SDL_Surface* window, Uint32* colors, int x, int y, int* coord_ok);

#endif
