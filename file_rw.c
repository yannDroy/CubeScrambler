/* Author : YANN DROY */
/******** 2015 ********/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "file_rw.h"
#include "timer.h"
#include "const.h"

void save_scramble (char **scramble, int nb_moves){
  FILE* file = NULL;
  int i;

  file = fopen("saved_scrambles.txt", "a");

  if(file == NULL){
    fprintf(stderr, "File opening failure\n");
    exit(EXIT_FAILURE);
  }else{
    putc('\n', file);
    for(i = 0; i < nb_moves; i++){
      putc(scramble[0][i], file);
      putc(scramble[1][i], file);
      if(scramble[1][i] != ' ' && i < (nb_moves - 1))
	putc(' ', file);
    }
    fclose(file);
  }
}

void load_scramble (SDL_Surface* window){
  SDL_Surface* text = NULL;
  SDL_Surface* clear = NULL;
  SDL_Rect position;
  SDL_Color text_color = {160, 160, 160};
  SDL_Color scr_color[6] = {{0, 255, 0},{255, 255, 255},{255, 255, 0},{255, 127, 0},{0, 0, 255},{255, 0, 0}};
  SDL_Color color_sign = {25, 255, 10};
  SDL_Color color = {40, 40, 40};
  TTF_Font* font = NULL;
  FILE* file = NULL;
  char scramble[90];
  char number_string[20];
  int number = 0;
  char c;
  int i;

  file = fopen("saved_scrambles.txt", "r");

  if(file == NULL){
    fprintf(stderr, "File opening failure\n");
    exit(EXIT_FAILURE);
  }else{
    font = TTF_OpenFont("font.ttf", (STICKER / 3));
    
    clear = SDL_CreateRGBSurface(SDL_HWSURFACE, WIDTH, HEIGTH, 32, 0, 0, 0, 0);
    SDL_FillRect(clear, NULL, (SDL_MapRGB(window->format, 40, 40, 40)));
    position.x = 0;
    position.y = 0;
    SDL_BlitSurface(clear, NULL, window, &position);

    while((c = fgetc(file)) != EOF){
      if(c == '\n')
	number++;
    }
    if(number < 0)
      number = 0;

    rewind(file);

    text = TTF_RenderText_Shaded(font, "L / Backspace : return", text_color, color);
    position.x = WIDTH - STICKER / 4 - text->w;
    position.y = STICKER / 4;
    SDL_BlitSurface(text, NULL, window, &position);

    position.y += text->h * 2;
    SDL_FreeSurface(text);
    text = TTF_RenderText_Shaded(font, "D : delete all saved scrambles", text_color, color);
    position.x = WIDTH - STICKER / 4 - text->w;
    SDL_BlitSurface(text, NULL, window, &position);

    if(number == 0)
      sprintf(number_string, "no scramble saved");
    else if(number == 1)
      sprintf(number_string, "%d scramble saved", number);
    else
      sprintf(number_string, "%d scrambles saved", number);

    position.y += text->h * 2;
    text = TTF_RenderText_Shaded(font, number_string, text_color, color);
    position.x = WIDTH - STICKER / 4 - text->w;
    SDL_BlitSurface(text, NULL, window, &position);

    if(number > 13){
      for(i = 0; i < number - 12; i++){
	fgets(scramble, 100, file);
      }
    }else
      fgets(scramble, 100, file);

    position.x = STICKER / 4;
    position.y = STICKER / 4;
    SDL_FreeSurface(text);
    text = TTF_RenderText_Shaded(font, "13 last scrambles saved :", text_color, color);
    SDL_BlitSurface(text, NULL, window, &position);

    position.y += text->h * 2;
    i = 0;
    while ((fgets(scramble, 100, file) != NULL)){
      scramble[strlen(scramble) - 1] = '\0';
      SDL_FreeSurface(text);
      text = TTF_RenderText_Shaded(font, scramble, scr_color[i], color);
      SDL_BlitSurface(text, NULL, window, &position);
      position.y += text->h * 2;
      if(i == 5)
	i = 0;
      else
	i++;
    }

    SDL_FreeSurface(text);
    text = TTF_RenderText_Shaded(font, "Dayan42", color_sign, color);
    position.x = WIDTH - text->w - STICKER / 8;
    position.y = HEIGTH - text->h - STICKER / 8;
    SDL_BlitSurface(text, NULL, window, &position);

    SDL_Flip(window);

    SDL_FreeSurface(text);
    SDL_FreeSurface(clear);
    TTF_CloseFont(font);
    fclose(file);
  }
}

void delete_scrambles (){
  FILE* file = NULL;

  file = fopen("saved_scrambles.txt", "w+");

  if(file == NULL){
    fprintf(stderr, "File opening failure\n");
    exit(EXIT_FAILURE);
  }else{
    fprintf(file, "Saved scrambles :");
    fclose(file);
  }
}

void test_file (){
  FILE* file = NULL;

  file = fopen("saved_scrambles.txt", "r");

  if(file == NULL)
    delete_scrambles();
  else
    fclose(file);

  delete_times();
}

void delete_times (){
  FILE* file = NULL;

  file = fopen("saved_times.txt", "w+");

  if(file == NULL){
    fprintf(stderr, "File opening failure\n");
    exit(EXIT_FAILURE);
  }else{
    fprintf(file, "Saved times :");
    fclose(file);
  }
}

void save_time (int m, int s, int cs){
  FILE* file = NULL;

  file = fopen("saved_times.txt", "a");

  if(file == NULL){
    fprintf(stderr, "File opening failure\n");
    exit(EXIT_FAILURE);
  }else{
    putc('\n', file);
    fprintf(file, "%d %d %d", m, s, cs);
  }
  fclose(file);
}

void load_time (SDL_Surface* window){
  SDL_Surface* text = NULL;
  SDL_Rect position;
  SDL_Color timer_color = {230, 230, 230};
  SDL_Color text_color = {160, 160, 160};
  SDL_Color worst_color = {255, 25, 10};
  SDL_Color color_sign = {25, 255, 10};
  SDL_Color color = {40, 40, 40};
  TTF_Font* font = NULL;
  FILE* file = NULL;
  char c;
  char time_string[9] = {0};
  int* solves = NULL;
  int i, m, s, cs, number = 0;

  file = fopen("saved_times.txt", "r");

  if(file == NULL){
    fprintf(stderr, "File opening failure\n");
    exit(EXIT_FAILURE);
  }else{
    font = TTF_OpenFont("font.ttf", (STICKER / 3));

    while((c = fgetc(file)) != EOF){
      if(c == '\n')
	number++;
    }
    if(number < 0)
      number = 0;

    rewind(file);

    text = TTF_RenderText_Shaded(font, "D : delete all solves", text_color, color);
    position.x = WIDTH / 2 - text->w / 2;
    position.y = HEIGTH - STICKER / 4 - text->h;
    SDL_BlitSurface(text, NULL, window, &position);

    if(number > 0){
      solves = malloc(number * sizeof(int));

      fseek(file, 14, SEEK_SET);
      for(i = 0; i < number; i++){
	fscanf(file, "%d %d %d", &m, &s, &cs);
	if(m == -1)
	  solves[i] = -1;
	else
	  solves[i] = cs + 100 * s + 6000 * m;
      }
      calculate_avg(window, solves, number);
      sort(solves, number);

      position.x = STICKER / 8;
      position.y = STICKER / 8;

      rewind(file);
      if(number > 19){
	for(i = 0; i < number - 18; i++){
	  fgets(time_string, 9, file);
	}
      }else
	fseek(file, 14, SEEK_SET);
      
      position.x = STICKER / 8;
      position.y = STICKER / 8;

      SDL_FreeSurface(text);
      text = TTF_RenderText_Shaded(font, "20 last solves :", text_color, color);
      SDL_BlitSurface(text, NULL, window, &position);

      position.y += 30;
      while ((fscanf(file, "%d %d %d", &m, &s, &cs)) > 0){
      if(m == -1)
	sprintf(time_string, "DNF");
      else if(m == 0)
	sprintf(time_string, "%d.%02d", s, cs);
      else
	sprintf(time_string, "%d:%02d.%02d", m, s, cs);

	SDL_FreeSurface(text);
	if((cs + 100 * s + 6000 * m) <= solves[0] && m != -1)
	  text = TTF_RenderText_Shaded(font, time_string, color_sign, color);
	else if((cs + 100 * s + 6000 * m) >= solves[number - 1] && solves[number - 1] != -1)
	  text = TTF_RenderText_Shaded(font, time_string, worst_color, color);
	else if(m == -1)
	  text = TTF_RenderText_Shaded(font, time_string, worst_color, color);
	else
	  text = TTF_RenderText_Shaded(font, time_string, timer_color, color);

	SDL_BlitSurface(text, NULL, window, &position);
	position.y += 30;
      }
      free(solves);
    }

    SDL_FreeSurface(text);
    text = TTF_RenderText_Shaded(font, "Dayan42", color_sign, color);
    position.x = WIDTH - text->w - STICKER / 8;
    position.y = HEIGTH - text->h - STICKER / 8;
    SDL_BlitSurface(text, NULL, window, &position);

    SDL_Flip(window);

    SDL_FreeSurface(text);
    TTF_CloseFont(font);
    fclose(file);
  }
}
