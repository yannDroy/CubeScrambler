/* Author : YANN DROY */
/******** 2015 ********/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "scramble.h"
#include "const.h"

void init_cube (int cube[][9]){
  int i, j;

  for(i = 0; i < 6; i++){
    for(j = 0; j < 9; j++)
      cube[i][j] = i;
  }
}

char** init_scramble (int lines, int columns){
  char **tab = (char **) malloc(sizeof(char*) * lines);
  char *tab2 = (char *) malloc(sizeof(char) * columns * lines);
  int i;

  for(i = 0; i < lines; i++)
    tab[i] = &tab2[i * columns];

  if(tab == NULL){
    fprintf(stderr, "Scramble allocation failure\n");
    exit(EXIT_FAILURE);
  }

  return tab;
}
 
void free_scramble (char** scramble){
  free(scramble[0]);
  free(scramble);
}

void generate_scramble (int cube[][9], char** scramble, int nb_moves, int gen2){
  char moves[6] = {'R', 'L', 'U', 'D', 'F', 'B'};
  int i, x, previous1, previous2;

  srand(time(NULL));

  if(!gen2){
    x = rand() % 6;
    scramble[0][0] = moves[x];
    previous2 = x;
    do{
      x = rand() % 6;
    }while(x == previous2);
    scramble[0][1] = moves[x];
    previous1 = x;

    for(i = 2; i < nb_moves; i++){
      if((previous1 == previous2 - 1) || (previous1 == previous2 + 1)){
	do{
	  x = rand() % 6;
	}while(x == previous1 || x == previous2);
      }else{
	do{
	  x = rand() % 6;
	}while(x == previous1);
      }
      scramble[0][i] = moves[x];
      previous2 = previous1;
      previous1 = x;
    }
  }else{
    previous1 = -1; 
    for(i = 0; i < nb_moves; i++){
      do{
	x = rand() % 2;
      }while(x == previous1);
      if(x == 1)
	scramble[0][i] = 'R';
      else
	scramble[0][i] = 'U';
      previous1 = x;
    }
  }

  for(i = 0; i < nb_moves; i++){
    x = rand() % 3;

    switch(x){
    case 0:
      scramble[1][i] = ' ';
      break;
    case 1:
      scramble[1][i] = '2';
      break;
    case 2:
      scramble[1][i] = '\'';
      break;
    }
  }

  scramble_cube(cube, scramble, nb_moves);
}

void scramble_cube (int cube[][9], char** scramble, int nb_moves){
  int i;
  int n;

  for(i = 0; i < nb_moves; i++){

    if(scramble[1][i] == ' ')
      n = 1;
    else if(scramble[1][i] == '2')
      n = 2;
    else if(scramble[1][i] == '\'')
      n = 3;

    switch(scramble[0][i]){
    case 'R':
	turn_R_face(cube, n);
      break;
    case 'L':
	turn_L_face(cube, n);
      break;
    case 'U':
	turn_U_face(cube, n);
      break;
    case 'D':
	turn_D_face(cube, n);
      break;
    case 'F':
	turn_F_face(cube, n);
      break;
    case 'B':
	turn_B_face(cube, n);
      break;
    }
  }
}

void turn_R_face (int cube[][9], int n){
  int i;
  int tmp;

  for(i = 0; i < n; i++){
    tmp = cube[WHITE][2]; cube[WHITE][2] = cube[GREEN][2]; cube[GREEN][2] = cube[YELLOW][2]; cube[YELLOW][2] = cube[BLUE][2]; cube[BLUE][2] = tmp;
    tmp = cube[WHITE][5]; cube[WHITE][5] = cube[GREEN][5]; cube[GREEN][5] = cube[YELLOW][5]; cube[YELLOW][5] = cube[BLUE][5]; cube[BLUE][5] = tmp;
    tmp = cube[WHITE][8]; cube[WHITE][8] = cube[GREEN][8]; cube[GREEN][8] = cube[YELLOW][8]; cube[YELLOW][8] = cube[BLUE][8]; cube[BLUE][8] = tmp;

    tmp = cube[RED][0]; cube[RED][0] = cube[RED][6]; cube[RED][6] = cube[RED][8]; cube[RED][8] = cube[RED][2]; cube[RED][2] = tmp;
    tmp = cube[RED][1]; cube[RED][1] = cube[RED][3]; cube[RED][3] = cube[RED][7]; cube[RED][7] = cube[RED][5]; cube[RED][5] = tmp;
  }
}

void turn_L_face (int cube[][9], int n){
  int i;
  int tmp;

  for(i = 0; i < n; i++){
    tmp = cube[WHITE][0]; cube[WHITE][0] = cube[BLUE][0]; cube[BLUE][0] = cube[YELLOW][0]; cube[YELLOW][0] = cube[GREEN][0]; cube[GREEN][0] = tmp;
    tmp = cube[WHITE][3]; cube[WHITE][3] = cube[BLUE][3]; cube[BLUE][3] = cube[YELLOW][3]; cube[YELLOW][3] = cube[GREEN][3]; cube[GREEN][3] = tmp;
    tmp = cube[WHITE][6]; cube[WHITE][6] = cube[BLUE][6]; cube[BLUE][6] = cube[YELLOW][6]; cube[YELLOW][6] = cube[GREEN][6]; cube[GREEN][6] = tmp;

    tmp = cube[ORANGE][0]; cube[ORANGE][0] = cube[ORANGE][6]; cube[ORANGE][6] = cube[ORANGE][8]; cube[ORANGE][8] = cube[ORANGE][2]; cube[ORANGE][2] = tmp;
    tmp = cube[ORANGE][1]; cube[ORANGE][1] = cube[ORANGE][3]; cube[ORANGE][3] = cube[ORANGE][7]; cube[ORANGE][7] = cube[ORANGE][5]; cube[ORANGE][5] = tmp;
  }
}

void turn_U_face (int cube[][9], int n){
  int i;
  int tmp;

  for(i = 0; i < n; i++){
    tmp = cube[GREEN][0]; cube[GREEN][0] = cube[RED][0]; cube[RED][0] = cube[BLUE][8]; cube[BLUE][8] = cube[ORANGE][0]; cube[ORANGE][0] = tmp;
    tmp = cube[GREEN][2]; cube[GREEN][2] = cube[RED][2]; cube[RED][2] = cube[BLUE][6]; cube[BLUE][6] = cube[ORANGE][2]; cube[ORANGE][2] = tmp;
    tmp = cube[GREEN][1]; cube[GREEN][1] = cube[RED][1]; cube[RED][1] = cube[BLUE][7]; cube[BLUE][7] = cube[ORANGE][1]; cube[ORANGE][1] = tmp;

    tmp = cube[WHITE][0]; cube[WHITE][0] = cube[WHITE][6]; cube[WHITE][6] = cube[WHITE][8]; cube[WHITE][8] = cube[WHITE][2]; cube[WHITE][2] = tmp;
    tmp = cube[WHITE][1]; cube[WHITE][1] = cube[WHITE][3]; cube[WHITE][3] = cube[WHITE][7]; cube[WHITE][7] = cube[WHITE][5]; cube[WHITE][5] = tmp;
  }
}

void turn_D_face (int cube[][9], int n){
  int i;
  int tmp;

  for(i = 0; i < n; i++){
    tmp = cube[GREEN][6]; cube[GREEN][6] = cube[ORANGE][6]; cube[ORANGE][6] = cube[BLUE][2]; cube[BLUE][2] = cube[RED][6]; cube[RED][6] = tmp;
    tmp = cube[GREEN][8]; cube[GREEN][8] = cube[ORANGE][8]; cube[ORANGE][8] = cube[BLUE][0]; cube[BLUE][0] = cube[RED][8]; cube[RED][8] = tmp;
    tmp = cube[GREEN][7]; cube[GREEN][7] = cube[ORANGE][7]; cube[ORANGE][7] = cube[BLUE][1]; cube[BLUE][1] = cube[RED][7]; cube[RED][7] = tmp;

    tmp = cube[YELLOW][0]; cube[YELLOW][0] = cube[YELLOW][6]; cube[YELLOW][6] = cube[YELLOW][8]; cube[YELLOW][8] = cube[YELLOW][2]; cube[YELLOW][2] = tmp;
    tmp = cube[YELLOW][1]; cube[YELLOW][1] = cube[YELLOW][3]; cube[YELLOW][3] = cube[YELLOW][7]; cube[YELLOW][7] = cube[YELLOW][5]; cube[YELLOW][5] = tmp;
  }
}

void turn_F_face (int cube[][9], int n){
  int i;
  int tmp;

  for(i = 0; i < n; i++){
    tmp = cube[WHITE][6]; cube[WHITE][6] = cube[ORANGE][8]; cube[ORANGE][8] = cube[YELLOW][2]; cube[YELLOW][2] = cube[RED][0]; cube[RED][0] = tmp;
    tmp = cube[WHITE][8]; cube[WHITE][8] = cube[ORANGE][2]; cube[ORANGE][2] = cube[YELLOW][0]; cube[YELLOW][0] = cube[RED][6]; cube[RED][6] = tmp;
    tmp = cube[WHITE][7]; cube[WHITE][7] = cube[ORANGE][5]; cube[ORANGE][5] = cube[YELLOW][1]; cube[YELLOW][1] = cube[RED][3]; cube[RED][3] = tmp;

    tmp = cube[GREEN][0]; cube[GREEN][0] = cube[GREEN][6]; cube[GREEN][6] = cube[GREEN][8]; cube[GREEN][8] = cube[GREEN][2]; cube[GREEN][2] = tmp;
    tmp = cube[GREEN][1]; cube[GREEN][1] = cube[GREEN][3]; cube[GREEN][3] = cube[GREEN][7]; cube[GREEN][7] = cube[GREEN][5]; cube[GREEN][5] = tmp;
  }
}

void turn_B_face (int cube[][9], int n){
  int i;
  int tmp;

  for(i = 0; i < n; i++){
    tmp = cube[WHITE][0]; cube[WHITE][0] = cube[RED][2]; cube[RED][2] = cube[YELLOW][8]; cube[YELLOW][8] = cube[ORANGE][6]; cube[ORANGE][6] = tmp;
    tmp = cube[WHITE][2]; cube[WHITE][2] = cube[RED][8]; cube[RED][8] = cube[YELLOW][6]; cube[YELLOW][6] = cube[ORANGE][0]; cube[ORANGE][0] = tmp;
    tmp = cube[WHITE][1]; cube[WHITE][1] = cube[RED][5]; cube[RED][5] = cube[YELLOW][7]; cube[YELLOW][7] = cube[ORANGE][3]; cube[ORANGE][3] = tmp;

    tmp = cube[BLUE][0]; cube[BLUE][0] = cube[BLUE][6]; cube[BLUE][6] = cube[BLUE][8]; cube[BLUE][8] = cube[BLUE][2]; cube[BLUE][2] = tmp;
    tmp = cube[BLUE][1]; cube[BLUE][1] = cube[BLUE][3]; cube[BLUE][3] = cube[BLUE][7]; cube[BLUE][7] = cube[BLUE][5]; cube[BLUE][5] = tmp;
  }
}
