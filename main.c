/* Author : YANN DROY */
/******** 2015 ********/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "scramble.h"
#include "display.h"
#include "menu.h"
#include "file_rw.h"
#include "const.h"

int main (int argc, char* argv[]){

  char** scramble = NULL;
  int cube[6][9] = {{0}};
  int nb_moves = 21;
  int nb_moves_tmp;
  int run = 1;
  int pass = 0;
  int border = 4;
  int gen2 = 0;
  SDL_Surface* window = NULL;
  Uint32 colors[6] = {0};

  system("clear");

  test_file();
  init_sdl();
  init_window(&window);
  init_colors(colors, window);
  set_background(&window, colors);
  scramble = init_scramble(2, nb_moves);

  while(run){
    if(!pass){
      init_cube(cube);
      generate_scramble(cube, scramble, nb_moves, gen2);
    }

    display_scramble(scramble, nb_moves, window, colors);
    display_cube(cube, window, border, colors);
    nb_moves_tmp = nb_moves;
    freeze(&run, &pass, &nb_moves, &border, &gen2, colors, window, cube, scramble);

    if(nb_moves != nb_moves_tmp){
      free_scramble(scramble);
      scramble = init_scramble(2, nb_moves);
    }
  }

  free_scramble(scramble);
  sdl_kill();

  return EXIT_SUCCESS;
}
