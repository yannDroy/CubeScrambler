/* Author : YANN DROY */
/******** 2015 ********/

#ifndef __DISPLAY__
#define __DISPLAY__

void init_sdl ();

void init_window (SDL_Surface** window);

void sdl_kill();

void display_cube (int cube[][9], SDL_Surface* window, int border, Uint32* colors);

void display_blue (int cube[][9], SDL_Surface* window, Uint32* colors, SDL_Surface* sticker);

void display_orange (int cube[][9], SDL_Surface* window, Uint32* colors, SDL_Surface* sticker);

void display_white (int cube[][9], SDL_Surface* window, Uint32* colors, SDL_Surface* sticker);

void display_red (int cube[][9], SDL_Surface* window, Uint32* colors, SDL_Surface* sticker);

void display_yellow (int cube[][9], SDL_Surface* window, Uint32* colors, SDL_Surface* sticker);

void display_green (int cube[][9], SDL_Surface* window, Uint32* colors, SDL_Surface* sticker);

void display_scramble (char** scramble, int nb_moves, SDL_Surface* window, Uint32* colors);

void set_background (SDL_Surface** window, Uint32* colors);

void display_text (SDL_Surface** window, SDL_Rect* position, char* string);

void display_shade (SDL_Surface** window, SDL_Surface* shade[256], SDL_Rect* position, Uint32* colors, int currentcolor, int r, float v, int b);

#endif
