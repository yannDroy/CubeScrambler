/* Author : YANN DROY */
/******** 2015 ********/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "display.h"
#include "const.h"

void init_sdl (){
  if(SDL_Init(SDL_INIT_VIDEO) == -1){
    fprintf(stderr, "SDL loading failure : %s.\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  if(TTF_Init() == -1){
    fprintf(stderr, "TTF loading failure : %s.\n", TTF_GetError());
    exit(EXIT_FAILURE);
  }
}

void init_window (SDL_Surface** window){
  *window = SDL_SetVideoMode(WIDTH, HEIGTH, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

  if(window == NULL){
    fprintf(stderr, "Window opening failure : %s.\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }else{
    SDL_WM_SetCaption("CubeScrambler 5.4.7", NULL);
    SDL_WM_SetIcon(SDL_LoadBMP("icon.bmp"), NULL);
    SDL_Flip(*window);
  }
}

void sdl_kill (){
  TTF_Quit();
  SDL_Quit();
}

void display_cube (int cube[][9], SDL_Surface* window, int border, Uint32* colors){
  SDL_Surface* sticker;

  sticker = SDL_CreateRGBSurface(SDL_HWSURFACE, (STICKER - 2 * border), (STICKER - 2 * border), 32, 0, 0, 0, 0);

  display_blue(cube, window, colors, sticker);
  display_orange(cube, window, colors, sticker);
  display_white(cube, window, colors, sticker);
  display_red(cube, window, colors, sticker);
  display_yellow(cube, window, colors, sticker);
  display_green(cube, window, colors, sticker);

  SDL_Flip(window);
  SDL_FreeSurface(sticker);
}

void display_blue (int cube[][9], SDL_Surface* window, Uint32* colors, SDL_Surface* sticker){
  int i;
  SDL_Rect position;

  for(i = 0; i < 9; i++){
    switch(i){
    case 0:
      position.x = 4 * STICKER;
      position.y = STICKER;
      break;
    case 1:
      position.x = 5 * STICKER;
      position.y = STICKER;
      break;
    case 2:
      position.x = 6 * STICKER;
      position.y = STICKER;
      break;
    case 3:
      position.x = 4 * STICKER;
      position.y = 2 * STICKER;
      break;
    case 4:
      position.x = 5 * STICKER;
      position.y = 2 * STICKER;
      break;
    case 5:
      position.x = 6 * STICKER;
      position.y = 2 * STICKER;
      break;
    case 6:
      position.x = 4 * STICKER;
      position.y = 3 * STICKER;
      break;
    case 7:
      position.x = 5 * STICKER;
      position.y = 3 * STICKER;
      break;
    case 8:
      position.x = 6 * STICKER;
      position.y = 3 * STICKER;
      break;
      }

    switch(cube[BLUE][i]){
    case WHITE:
      SDL_FillRect(sticker, NULL, colors[WHITE]);
      break;
    case YELLOW:
      SDL_FillRect(sticker, NULL, colors[YELLOW]);
      break;
    case GREEN:
      SDL_FillRect(sticker, NULL, colors[GREEN]);
      break;
    case BLUE:
      SDL_FillRect(sticker, NULL, colors[BLUE]);
      break;
    case RED:
      SDL_FillRect(sticker, NULL, colors[RED]);
      break;
    case ORANGE:
      SDL_FillRect(sticker, NULL, colors[ORANGE]);
      break;
    }
    SDL_BlitSurface(sticker, NULL, window, &position);
  }
}

void display_orange (int cube[][9], SDL_Surface* window, Uint32* colors, SDL_Surface* sticker){
  int i;
  SDL_Rect position;

  for(i = 0; i < 9; i++){
    switch(i){
    case 0:
      position.x = 3 * STICKER;
      position.y = 4 * STICKER;
      break;
    case 1:
      position.x = 3 * STICKER;
      position.y = 5 * STICKER;
      break;
    case 2:
      position.x = 3 * STICKER;
      position.y = 6 * STICKER;
      break;
    case 3:
      position.x = 2 * STICKER;
      position.y = 4 * STICKER;
      break;
    case 4:
      position.x = 2 * STICKER;
      position.y = 5 * STICKER;
      break;
    case 5:
      position.x = 2 * STICKER;
      position.y = 6 * STICKER;
      break;
    case 6:
      position.x = STICKER;
      position.y = 4 * STICKER;
      break;
    case 7:
      position.x = STICKER;
      position.y = 5 * STICKER;
      break;
    case 8:
      position.x = STICKER;
      position.y = 6 * STICKER;
      break;
    }

    switch(cube[ORANGE][i]){
    case WHITE:
      SDL_FillRect(sticker, NULL, colors[WHITE]);
      break;
    case YELLOW:
      SDL_FillRect(sticker, NULL, colors[YELLOW]);
      break;
    case GREEN:
      SDL_FillRect(sticker, NULL, colors[GREEN]);
      break;
    case BLUE:
      SDL_FillRect(sticker, NULL, colors[BLUE]);
      break;
    case RED:
      SDL_FillRect(sticker, NULL, colors[RED]);
      break;
    case ORANGE:
      SDL_FillRect(sticker, NULL, colors[ORANGE]);
      break;
    }
    SDL_BlitSurface(sticker, NULL, window, &position);
  }
}

void display_white (int cube[][9], SDL_Surface* window, Uint32* colors, SDL_Surface* sticker){
  int i;
  SDL_Rect position;

  for(i = 0; i < 9; i++){
    switch(i){
    case 0:
      position.x = 4 * STICKER;
      position.y = 4 * STICKER;
      break;
    case 1:
      position.x = 5 * STICKER;
      position.y = 4 * STICKER;
      break;
    case 2:
      position.x = 6 * STICKER;
      position.y = 4 * STICKER;
      break;
    case 3:
      position.x = 4 * STICKER;
      position.y = 5 * STICKER;
      break;
    case 4:
      position.x = 5 * STICKER;
      position.y = 5 * STICKER;
      break;
    case 5:
      position.x = 6 * STICKER;
      position.y = 5 * STICKER;
      break;
    case 6:
      position.x = 4 * STICKER;
      position.y = 6 * STICKER;
      break;
    case 7:
      position.x = 5 * STICKER;
      position.y = 6 * STICKER;
      break;
    case 8:
      position.x = 6 * STICKER;
      position.y = 6 * STICKER;
      break;
    }

    switch(cube[WHITE][i]){
    case WHITE:
      SDL_FillRect(sticker, NULL, colors[WHITE]);
      break;
    case YELLOW:
      SDL_FillRect(sticker, NULL, colors[YELLOW]);
      break;
    case GREEN:
      SDL_FillRect(sticker, NULL, colors[GREEN]);
      break;
    case BLUE:
      SDL_FillRect(sticker, NULL, colors[BLUE]);
      break;
    case RED:
      SDL_FillRect(sticker, NULL, colors[RED]);
      break;
    case ORANGE:
      SDL_FillRect(sticker, NULL, colors[ORANGE]);
      break;
    }
    SDL_BlitSurface(sticker, NULL, window, &position);
  }
}

void display_red (int cube[][9], SDL_Surface* window, Uint32* colors, SDL_Surface* sticker){
  int i;
  SDL_Rect position;

  for(i = 0; i < 9; i++){
    switch(i){
    case 0:
      position.x = 7 * STICKER;
      position.y = 6 * STICKER;
      break;
    case 1:
      position.x = 7 * STICKER;
      position.y = 5 * STICKER;
      break;
    case 2:
      position.x = 7 * STICKER;
      position.y = 4 * STICKER;
      break;
    case 3:
      position.x = 8 * STICKER;
      position.y = 6 * STICKER;
      break;
    case 4:
      position.x = 8 * STICKER;
      position.y = 5 * STICKER;
      break;
    case 5:
      position.x = 8 * STICKER;
      position.y = 4 * STICKER;
      break;
    case 6:
      position.x = 9 * STICKER;
      position.y = 6 * STICKER;
      break;
    case 7:
      position.x = 9 * STICKER;
      position.y = 5 * STICKER;
      break;
    case 8:
      position.x = 9 * STICKER;
      position.y = 4 * STICKER;
      break;
    }

    switch(cube[RED][i]){
    case WHITE:
      SDL_FillRect(sticker, NULL, colors[WHITE]);
      break;
    case YELLOW:
      SDL_FillRect(sticker, NULL, colors[YELLOW]);
      break;
    case GREEN:
      SDL_FillRect(sticker, NULL, colors[GREEN]);
      break;
    case BLUE:
      SDL_FillRect(sticker, NULL, colors[BLUE]);
      break;
    case RED:
      SDL_FillRect(sticker, NULL, colors[RED]);
      break;
    case ORANGE:
      SDL_FillRect(sticker, NULL, colors[ORANGE]);
      break;
    }
    SDL_BlitSurface(sticker, NULL, window, &position);
  }
}

void display_yellow (int cube[][9], SDL_Surface* window, Uint32* colors, SDL_Surface* sticker){
  int i;
  SDL_Rect position;

  for(i = 0; i < 9; i++){
    switch(i){
    case 0:
      position.x = 12 * STICKER;
      position.y = 6 * STICKER;
      break;
    case 1:
      position.x = 11 * STICKER;
      position.y = 6 * STICKER;
      break;
    case 2:
      position.x = 10 * STICKER;
      position.y = 6 * STICKER;
      break;
    case 3:
      position.x = 12 * STICKER;
      position.y = 5 * STICKER;
      break;
    case 4:
      position.x = 11 * STICKER;
      position.y = 5 * STICKER;
      break;
    case 5:
      position.x = 10 * STICKER;
      position.y = 5 * STICKER;
      break;
    case 6:
      position.x = 12 * STICKER;
      position.y = 4 * STICKER;
      break;
    case 7:
      position.x = 11 * STICKER;
      position.y = 4 * STICKER;
      break;
    case 8:
      position.x = 10 * STICKER;
      position.y = 4 * STICKER;
      break;
    }

    switch(cube[YELLOW][i]){
    case WHITE:
      SDL_FillRect(sticker, NULL, colors[WHITE]);
      break;
    case YELLOW:
      SDL_FillRect(sticker, NULL, colors[YELLOW]);
      break;
    case GREEN:
      SDL_FillRect(sticker, NULL, colors[GREEN]);
      break;
    case BLUE:
      SDL_FillRect(sticker, NULL, colors[BLUE]);
      break;
    case RED:
      SDL_FillRect(sticker, NULL, colors[RED]);
      break;
    case ORANGE:
      SDL_FillRect(sticker, NULL, colors[ORANGE]);
      break;
    }
    SDL_BlitSurface(sticker, NULL, window, &position);
  }
}

void display_green (int cube[][9], SDL_Surface* window, Uint32* colors, SDL_Surface* sticker){
  int i;
  SDL_Rect position;

  for(i = 0; i < 9; i++){
    switch(i){
    case 0:
      position.x = 4 * STICKER;
      position.y = 7 * STICKER;
      break;
    case 1:
      position.x = 5 * STICKER;
      position.y = 7 * STICKER;
      break;
    case 2:
      position.x = 6 * STICKER;
      position.y = 7 * STICKER;
      break;
    case 3:
      position.x = 4 * STICKER;
      position.y = 8 * STICKER;
      break;
    case 4:
      position.x = 5 * STICKER;
      position.y = 8 * STICKER;
      break;
    case 5:
      position.x = 6 * STICKER;
      position.y = 8 * STICKER;
      break;
    case 6:
      position.x = 4 * STICKER;
      position.y = 9 * STICKER;
      break;
    case 7:
      position.x = 5 * STICKER;
      position.y = 9 * STICKER;
      break;
    case 8:
      position.x = 6 * STICKER;
      position.y = 9 * STICKER;
      break;
    }

    switch(cube[GREEN][i]){
    case WHITE:
      SDL_FillRect(sticker, NULL, colors[WHITE]);
      break;
    case YELLOW:
      SDL_FillRect(sticker, NULL, colors[YELLOW]);
      break;
    case GREEN:
      SDL_FillRect(sticker, NULL, colors[GREEN]);
      break;
    case BLUE:
      SDL_FillRect(sticker, NULL, colors[BLUE]);
      break;
    case RED:
      SDL_FillRect(sticker, NULL, colors[RED]);
      break;
    case ORANGE:
      SDL_FillRect(sticker, NULL, colors[ORANGE]);
      break;
    }
    SDL_BlitSurface(sticker, NULL, window, &position);
  }
}

void display_scramble (char** scramble, int nb_moves, SDL_Surface* window, Uint32* colors){
  TTF_Font* font = NULL;
  SDL_Surface* scr_text = NULL;
  SDL_Surface* moves_text = NULL;
  SDL_Rect position;
  SDL_Color scramble_color = {255, 255, 10};
  SDL_Color text_color = {160, 160, 160};
  SDL_Color color = {40, 40, 40};
  char* scr_string = NULL;
  char moves_string[11] = {0};
  int i;
  int j = 0;

  set_background(&window, colors);

  scr_string = malloc((nb_moves * 4 + 1) * sizeof(char));
  font = TTF_OpenFont("font.ttf", (STICKER / 3));

  for(i = 0; i < nb_moves; i++){
    scr_string[j] = scramble[0][i];
    scr_string[j + 1] = scramble[1][i];
    scr_string[j + 2] = ' ';
    scr_string[j + 3] = ' ';
    j += 4;
  }
  scr_string[nb_moves * 4] = '\0';

  scr_text = TTF_RenderText_Shaded(font, scr_string, scramble_color, color);
  sprintf(moves_string, "Moves : %d", nb_moves);
  moves_text = TTF_RenderText_Shaded(font, moves_string, text_color, color);

  position.x = STICKER / 8;
  position.y = HEIGTH - scr_text->h - STICKER / 17;
  SDL_BlitSurface(scr_text, NULL, window, &position);

  position.y = STICKER / 16;
  SDL_BlitSurface(moves_text, NULL, window, &position);

  SDL_FreeSurface(scr_text);
  SDL_FreeSurface(moves_text);
  TTF_CloseFont(font);
}

void set_background (SDL_Surface** window, Uint32* colors){
  SDL_Rect position;
  TTF_Font* font = NULL;
  SDL_Surface* sign = NULL;
  SDL_Surface* shade[256] = {NULL};
  SDL_Color color_sign = {25, 255, 10};
  SDL_Color color = {40, 40, 40};
  int i;

  SDL_FillRect(*window, NULL, (SDL_MapRGB((**window).format, 40, 40, 40)));

  font = TTF_OpenFont("font.ttf", (STICKER / 3));
  sign = TTF_RenderText_Shaded(font, "Dayan42", color_sign, color);
  position.x = WIDTH - sign->w - STICKER / 8;
  position.y = HEIGTH - sign->h - STICKER / 8;
  SDL_BlitSurface(sign, NULL, *window, &position);
  
  position.y = STICKER / 8;
  display_text(window, &position, "+ / - : change scramble length");
  display_text(window, &position, "Up / Down arrow : change border width");
  display_text(window, &position, "Enter : change scramble");
  display_text(window, &position, "Space : start the timer");
  display_text(window, &position, "S : save current scramble");
  display_text(window, &position, "L : display saved scrambles");
  display_text(window, &position, "G : 2-gen R U scramble");
  display_text(window, &position, "M : reset number of moves");
  display_text(window, &position, "R : reset color scheme");
  display_text(window, &position, "B : reset border width");
  display_text(window, &position, "Q / Escape : quit program");

  for(i = 0; i < 256; i++)
    shade[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, (STICKER / 3), 32, 0, 0, 0, 0);

  position.y += 10;
  display_shade(window, shade, &position, colors, WHITE, 1, 1.0, 1);
  display_shade(window, shade, &position, colors, YELLOW, 1, 1.0, 0);
  display_shade(window, shade, &position, colors, RED, 1, 0.0, 0);
  display_shade(window, shade, &position, colors, ORANGE, 1, 0.5, 0);
  display_shade(window, shade, &position, colors, GREEN, 0, 1.0, 0);
  display_shade(window, shade, &position, colors, BLUE, 0, 0.0, 1);

  for(i = 0; i < 256; i++)
    SDL_FreeSurface(shade[i]);

  SDL_FreeSurface(sign);
  TTF_CloseFont(font);
}

void display_text (SDL_Surface** window, SDL_Rect* position, char* string){
  SDL_Surface* text = NULL;
  TTF_Font* font = NULL;
  SDL_Color color1 = {160, 160, 160};
  SDL_Color color2 = {40, 40, 40};

  font = TTF_OpenFont("font.ttf", (STICKER / 3));

  text = TTF_RenderText_Shaded(font, string, color1, color2);
  position->x = WIDTH - text->w - STICKER / 8;
  SDL_BlitSurface(text, NULL, *window, position);
  position->y += 30;

  SDL_FreeSurface(text);
  TTF_CloseFont(font);
}

void display_shade (SDL_Surface** window, SDL_Surface* shade[256], SDL_Rect* position, Uint32* colors, int current_color, int r, float v, int b){
  SDL_Surface* cursor = NULL;
  SDL_Rect pos_cursor;
  Uint32 color;
  int i;

  cursor = SDL_CreateRGBSurface(SDL_HWSURFACE, 5, (STICKER / 3 + 6), 32, 0, 0, 0, 0);
  SDL_FillRect(cursor, NULL, (SDL_MapRGB((*window)->format, 200, 200, 200)));

  position->x = WIDTH - 256 - STICKER / 8;
  for(i = 0; i < 256; i++){
    color = SDL_MapRGB((*window)->format, r * i, (int)(v * i), b * i);
    SDL_FillRect(shade[i], NULL, color);
    SDL_BlitSurface(shade[i], NULL, *window, position);
    if(color == colors[current_color])
      pos_cursor.x = position->x - 3;
    position->x++;
  }
  pos_cursor.y = position->y - 3;
  position->y += 35;
  SDL_BlitSurface(cursor, NULL, *window, &pos_cursor);

  SDL_FreeSurface(cursor);
}
