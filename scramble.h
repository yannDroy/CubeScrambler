/* Author : YANN DROY */
/******** 2015 ********/

#ifndef __SCRAMBLE__
#define __SCRAMBLE__

void init_cube (int cube[][9]);

char** init_scramble (int lines, int columns);

void free_scramble (char** scramble);

void generate_scramble (int cube[][9], char** scramble, int nb_moves, int gen2);

void scramble_cube (int cube[][9], char** scramble, int nb_moves);

void turn_R_face (int cube[][9], int n);

void turn_L_face (int cube[][9], int n);

void turn_U_face (int cube[][9], int n);

void turn_D_face (int cube[][9], int n);

void turn_F_face (int cube[][9], int n);

void turn_B_face (int cube[][9], int n);

#endif
