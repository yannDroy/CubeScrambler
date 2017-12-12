/* Author : YANN DROY */
/******** 2015 ********/

#ifndef __TIMER__
#define __TIMER__

void timer (SDL_Surface* window);

int averageof5 (int a, int b, int c, int d, int e);

int averageof12 (int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l);

void calculate_avg(SDL_Surface* window, int* solves, int number);

void sort (int* tab, int n);

int solve_penalty (SDL_Surface* window);

#endif
