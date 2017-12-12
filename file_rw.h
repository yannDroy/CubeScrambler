/* Author : YANN DROY */
/******** 2015 ********/

#ifndef __FILE_RW__
#define __FILE_RW__

void save_scramble (char **scramble, int nb_moves);

void load_scramble (SDL_Surface* window);

void delete_scrambles ();

void test_file ();

void delete_times ();

void save_time (int m, int s, int cs);

void load_time (SDL_Surface* window);

#endif
