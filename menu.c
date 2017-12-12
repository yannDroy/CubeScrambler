/* Author : YANN DROY */
/******** 2015 ********/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"
#include "file_rw.h"
#include "display.h"
#include "timer.h"
#include "const.h"

void freeze (int* run, int* pass, int* nb_moves, int* border, int* gen2, Uint32* colors, SDL_Surface* window, int cube[][9], char** scramble){
  int wait = 1;
  SDL_Event event;
  int click = 0;
  int coord_ok = 1;
  int load = 0;
  int time = 0;

  while(wait){
    SDL_WaitEvent(&event);

    if(time){
      switch(event.type){
      case SDL_QUIT:
	  wait = 0;
	  (*run) = 0;
	  break;
      case SDL_KEYDOWN:
	switch(event.key.keysym.sym){
	case SDLK_ESCAPE:
	  wait = 0;
	  (*run) = 0;
	  break;
	case SDLK_q:
	  wait = 0;
	  (*run) = 0;
	  break;
	case SDLK_BACKSPACE:
	  wait = 0;
	  time = 0;
	  (*pass) = 1;
	  break;
	case SDLK_RETURN:
	  wait = 0;
	  time = 0;
	  (*pass) = 0;
	  break;
	case SDLK_KP_ENTER:
	  wait = 0;
	  time = 0;
	  (*pass) = 0;
	  break;
	case SDLK_d:
	  wait = 0;
	  time = 0;
	  (*pass) = 1;
	  delete_times();
	  break;
	default:
	  break;
	}
	break;
      default:
	break;
      }
    }else if(load){
      switch(event.type){
      case SDL_QUIT:
	  wait = 0;
	  (*run) = 0;
	  break;
      case SDL_KEYDOWN:
	switch(event.key.keysym.sym){
	case SDLK_ESCAPE:
	  wait = 0;
	  (*run) = 0;
	  break;
	case SDLK_q:
	  wait = 0;
	  (*run) = 0;
	  break;
	case SDLK_BACKSPACE:
	  wait = 0;
	  load = 0;
	  (*pass) = 1;
	  break;
	case SDLK_l:
	  wait = 0;
	  load = 0;
	  (*pass) = 1;
	  break;
	case SDLK_d:
	  wait = 0;
	  load = 0;
	  (*pass) = 1;
	  delete_scrambles();
	  break;
	default:
	  break;
	}
	break;
      default:
	break;
      }
    }else{
      switch(event.type){
      case SDL_QUIT:
	wait = 0;
	(*run) = 0;
	break;
      case SDL_KEYDOWN:
	switch(event.key.keysym.sym){
	case SDLK_ESCAPE:
	  wait = 0;
	  (*run) = 0;
	  break;
	case SDLK_RETURN:
	  wait = 0;
	  (*pass) = 0;
	  break;
	case SDLK_KP_ENTER:
	  wait = 0;
	  (*pass) = 0;
	  break;
	case SDLK_SPACE:
	  timer(window);
	  time = 1;
	  break;
	case SDLK_q:
	  wait = 0;
	  (*run) = 0;
	  break;
	case SDLK_b:
	  wait = 0;
	  (*border) = 4;
	  (*pass) = 1;
	  break;
	case SDLK_m:
	  wait = 0;
	  if((*nb_moves) != 21){
	    (*nb_moves) = 21;
	    (*pass) = 0;
	  }else
	    (*pass) = 1;
	  break;
	case SDLK_s:
	  wait = 0;
	  save_scramble(scramble, (*nb_moves));
	  (*pass) = 1;
	  break;
	case SDLK_l:
	  load_scramble(window);
	  load = 1;
	  break;
	case SDLK_r:
	  wait = 0;
	  init_colors(colors, window);
	  (*pass) = 1;
	  break;
	case SDLK_g:
	  wait = 0;
	  if((*gen2) == 0)
	    (*gen2) = 1;
	  else
	    (*gen2) = 0;
	  (*pass) = 0;
	  break;
	case SDLK_KP_PLUS:
	  wait = 0;
	  if((*nb_moves) < 30){
	    (*nb_moves)++;
	    (*pass) = 0;
	  }else
	    (*pass) = 1;
	  break;
	case SDLK_KP_MINUS:
	  wait = 0;
	  if((*nb_moves) > 1){
	    (*nb_moves)--;
	    (*pass) = 0;
	  }else
	    (*pass) = 1;
	  break;
	case SDLK_UP:
	  wait = 0;
	  if((*border) < (STICKER / 2) - 1)
	    (*border)++;
	  (*pass) = 1;
	  break;
	case SDLK_DOWN:
	  wait = 0;
	  if((*border) > 0)
	    (*border)--;
	  (*pass) = 1;
	  break;
	default:
	  break;
	}
	break;
      case SDL_MOUSEBUTTONUP:
	switch(event.button.button){
	case SDL_BUTTON_LEFT:
	  click = 0;
	  wait = 0;
	  if(coord_ok){
	    affect_color(window, colors, event.button.x, event.button.y, &coord_ok);
	    display_scramble(scramble, (*nb_moves), window, colors);
	    display_cube(cube, window, (*border), colors);
	  }
	  (*pass) = 1;
	  break;
	default:
	  break;
	}
	break;
      case SDL_MOUSEBUTTONDOWN:
	switch(event.button.button){
	case SDL_BUTTON_LEFT:
	  click = 1;
	  coord_ok = 1;
	  break;
	default:
	  break;
	}
	break;
      case SDL_MOUSEMOTION:
	if(click){
	  if(coord_ok){
	    affect_color(window, colors, event.motion.x, event.motion.y, &coord_ok);
	    display_scramble(scramble, (*nb_moves), window, colors);
	    display_cube(cube, window, (*border), colors);
	  }
	}
	break;
      default:
	break;
      }
    }
  }
}

void init_colors (Uint32* colors, SDL_Surface* window){
  colors[WHITE] = SDL_MapRGB(window->format, 220, 220, 220);
  colors[YELLOW] = SDL_MapRGB(window->format, 254, 254, 0);
  colors[GREEN] = SDL_MapRGB(window->format, 0, 240, 0);
  colors[BLUE] = SDL_MapRGB(window->format, 0, 0, 180);
  colors[RED] = SDL_MapRGB(window->format, 190, 0, 0);
  colors[ORANGE] = SDL_MapRGB(window->format, 254, 127, 0);
}

void affect_color (SDL_Surface* window, Uint32* colors, int x, int y, int* coord_ok){
  int x0 = WIDTH - STICKER / 8 - 255;
  int y0 = 11 * 30 + STICKER / 8 + 10;

  if(x >= x0 && x <= (WIDTH - STICKER / 8)){
    if(y >= y0 && y <= y0 + STICKER / 3)
      colors[WHITE] = SDL_MapRGB(window->format, (x - x0), (x - x0), (x - x0));
    else if(y >= (y0 + 35) && y <= (y0 + 35 + STICKER / 3))
      colors[YELLOW] = SDL_MapRGB(window->format, (x - x0), (x - x0), 0);
    else if(y >= (y0 + 2 * 35) && y <= (y0 + 2 * 35 + STICKER / 3))
      colors[RED] = SDL_MapRGB(window->format, (x - x0), 0, 0);
    else if(y >= (y0 + 3 * 35) && y <= (y0 + 3 * 35 + STICKER / 3))
      colors[ORANGE] = SDL_MapRGB(window->format, (x - x0), ((x - x0) / 2), 0);
    else if(y >= (y0 + 4 * 35) && y <= (y0 + 4 * 35 + STICKER / 3))
      colors[GREEN] = SDL_MapRGB(window->format, 0, (x - x0), 0);
    else if(y >= (y0 + 5 * 35) && y <= (y0 + 5 * 35 + STICKER / 3))
      colors[BLUE] = SDL_MapRGB(window->format, 0, 0, (x - x0));
    else
      (*coord_ok) = 0;
  }
}
