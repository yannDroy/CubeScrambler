/* Author : YANN DROY */
/******** 2015 ********/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "timer.h"
#include "file_rw.h"
#include "const.h"

void timer (SDL_Surface* window){
  SDL_Surface* clear = NULL;
  SDL_Surface* text = NULL;
  SDL_Surface* time_text = NULL;
  SDL_Rect position;
  SDL_Color timer_color = {230, 230, 230};
  SDL_Color text_color = {160, 160, 160};
  SDL_Color color_sign = {25, 255, 10};
  SDL_Color color = {40, 40, 40};
  SDL_Event event;
  TTF_Font* font = NULL;
  TTF_Font* littlefont = NULL;
  TTF_Font* signfont = NULL;
  char time_string[9] = {0};
  int time[3] = {0};
  int begin, actual, previous = 0, wait = 1, penalty;

  clear = SDL_CreateRGBSurface(SDL_HWSURFACE, WIDTH, HEIGTH, 32, 0, 0, 0, 0);
  SDL_FillRect(clear, NULL, (SDL_MapRGB(window->format, 40, 40, 40)));

  font = TTF_OpenFont("font.ttf", (HEIGTH / 3));
  littlefont = TTF_OpenFont("font.ttf", (STICKER / 2));
  signfont = TTF_OpenFont("font.ttf", (STICKER / 3));

  begin = SDL_GetTicks();

  while(wait){
    SDL_PollEvent(&event);

    actual = SDL_GetTicks();

    if(actual - previous > 25){
      position.x = 0;
      position.y = 0;
      SDL_BlitSurface(clear, NULL, window, &position);

      if((actual - begin) >= 600000){
	time[0] = -1;
	time[1] = -1;
	time[2] = -1;
      }else{
	time[0] = (actual - begin) / 60000;
	time[1] = ((actual - begin) - 60000 * time[0]) / 1000;
	time[2] = ((actual - begin) - 60000 * time[0] - 1000 * time[1]) / 10;
      }

      if(time[0] == -1)
	sprintf(time_string, "DNF");
      else if(time[0] == 0)
	sprintf(time_string, "%d.%02d", time[1], time[2]);
      else
	sprintf(time_string, "%d:%02d.%02d", time[0], time[1], time[2]);

      SDL_FreeSurface(time_text);
      time_text = TTF_RenderText_Shaded(font, time_string, timer_color, color);
      position.x = WIDTH / 2 - time_text->w / 2;
      position.y = HEIGTH / 2 - time_text->h / 2;    
      SDL_BlitSurface(time_text, NULL, window, &position);

      SDL_FreeSurface(text);
      text = TTF_RenderText_Shaded(littlefont, "Press any key to stop", text_color, color);
      position.x = WIDTH / 2 - text->w / 2;
      position.y = STICKER / 4;
      SDL_BlitSurface(text, NULL, window, &position);

      SDL_FreeSurface(text);
      text = TTF_RenderText_Shaded(signfont, "Dayan42", color_sign, color);
      position.x = WIDTH - text->w - STICKER / 8;
      position.y = HEIGTH - text->h - STICKER / 8;
      SDL_BlitSurface(text, NULL, window, &position);

      SDL_Flip(window);

      previous = actual;

      if(event.type == SDL_KEYDOWN)
	wait = 0;

    }else
      SDL_Delay(25 - (actual - previous));
  }
  
  penalty = solve_penalty(window);
  switch(penalty){
  case 0:
    break;
  case 1:
    if(time[0] != -1){
      if(time[0] == 9 && time[1] >= 58){
	time[0] = -1;
	time[1] = -1;
	time[2] = -1;
      }
      if(time[1] < 58)
	time[1] += 2;
      else{
	time[1] += 2 - 60;
	time[0] += 1;
      }
    }
    break;
  case 2:
    time[0] = -1;
    time[1] = -1;
    time[2] = -1;
    break;
  }

  if(penalty != 3)
    save_time(time[0], time[1], time[2]);
  
  if(time[0] == -1)
    sprintf(time_string, "DNF");
  else if(time[0] == 0)
    sprintf(time_string, "%d.%02d", time[1], time[2]);
  else
    sprintf(time_string, "%d:%02d.%02d", time[0], time[1], time[2]);
  
  position.x = 0;
  position.y = 0;
  SDL_BlitSurface(clear, NULL, window, &position);
  
  SDL_FreeSurface(time_text);
  time_text = TTF_RenderText_Shaded(font, time_string, timer_color, color);
  position.x = WIDTH / 2 - time_text->w / 2;
  position.y = HEIGTH / 2 - time_text->h / 2;
  SDL_BlitSurface(time_text, NULL, window, &position);
  
  SDL_FreeSurface(text);
  text = TTF_RenderText_Shaded(littlefont, "Backspace to return", text_color, color);
  position.x = WIDTH / 2 - text->w / 2;
  position.y = STICKER / 4;
  SDL_BlitSurface(text, NULL, window, &position);
  
  position.y += text->h * 1.5;
  SDL_FreeSurface(text);
  text = TTF_RenderText_Shaded(littlefont, "Enter to display a new scramble", text_color, color);
  position.x = WIDTH / 2 - text->w / 2;
  SDL_BlitSurface(text, NULL, window, &position);
  
  SDL_FreeSurface(text);
  text = TTF_RenderText_Shaded(signfont, "Dayan42", color_sign, color);
  position.x = WIDTH - text->w - STICKER / 8;
  position.y = HEIGTH - text->h - STICKER / 8;
  SDL_BlitSurface(text, NULL, window, &position);
  
  SDL_Flip(window);

  SDL_FreeSurface(clear);
  SDL_FreeSurface(text);
  SDL_FreeSurface(time_text);
  TTF_CloseFont(font);
  TTF_CloseFont(littlefont);
  TTF_CloseFont(signfont);

  load_time(window);
}

void calculate_avg(SDL_Surface* window, int* solves, int number){
  SDL_Surface* text = NULL;
  TTF_Font* font = NULL;
  SDL_Rect position;
  SDL_Color text_color = {160, 160, 160};
  SDL_Color color = {40, 40, 40};
  int* avg5 = NULL;
  int* avg12 = NULL;
  char avg_string[25] = {0};
  int i, j, m, s, cs;

  font = TTF_OpenFont("font.ttf", (STICKER / 3));

  if(number >= 5){
    avg5 = malloc((number - 5 + 1) * sizeof(int));
    for(i = 0; i < (number - 5 + 1); i++){
      j = i;
      avg5[i] = averageof5(solves[j], solves[j + 1], solves[j + 2], solves[j + 3], solves[j + 4]);
    }

    if(avg5[number - 5] != -1){
      m = avg5[number - 5] / 6000;
      s = (avg5[number - 5] - 6000 * m) / 100;
      cs = avg5[number - 5] - 6000 * m - 100 * s;
    }else
      m = -1;

    if(m == -1)
      sprintf(avg_string, "Current avg5 : DNF");
    else if(m == 0)
      sprintf(avg_string, "Current avg5 : %d.%02d", s, cs);
    else
      sprintf(avg_string, "Current avg5 : %d:%02d.%02d", m, s, cs);

    text = TTF_RenderText_Shaded(font, avg_string, text_color, color);
    position.x = WIDTH - text->w -STICKER / 4;
    position.y = STICKER / 4;
    SDL_BlitSurface(text, NULL, window, &position);

    sort(avg5, (number - 5 + 1));
    if(avg5[0] != -1){
      m = avg5[0] / 6000;
      s = (avg5[0] - 6000 * m) / 100;
      cs = avg5[0] - 6000 * m - 100 * s;
    }else
      m = -1;

    if(m == -1)
      sprintf(avg_string, "Best avg5 : DNF");
    else if(m == 0)
      sprintf(avg_string, "Best avg5 : %d.%02d", s, cs);
    else
      sprintf(avg_string, "Best avg5 : %d:%02d.%02d", m, s, cs);

    SDL_FreeSurface(text);
    text = TTF_RenderText_Shaded(font, avg_string, text_color, color);
    position.x = WIDTH - text->w -STICKER / 4;
    position.y += 30;
    SDL_BlitSurface(text, NULL, window, &position);

    SDL_FreeSurface(text);
    free(avg5);
  }

  if(number >= 12){
    avg12 = malloc((number - 12 + 1) * sizeof(int));
    for(i = 0; i < (number - 12 + 1); i++){
      j = i;
      avg12[i] = averageof12(solves[j], solves[j + 1], solves[j + 2], solves[j + 3], solves[j + 4], solves[j + 5], solves[j + 6], solves[j + 7], solves[j + 8], solves[j + 9], solves[j + 10], solves[j + 11]);
    }

    if(avg12[number - 12] != -1){
      m = avg12[number - 12] / 6000;
      s = (avg12[number - 12] - 6000 * m) / 100;
      cs = avg12[number - 12] - 6000 * m - 100 * s;
    }else
      m = -1;

    if(m == -1)
      sprintf(avg_string, "Current avg12 : DNF");
    else if(m == 0)
      sprintf(avg_string, "Current avg12 : %d.%02d", s, cs);
    else
      sprintf(avg_string, "Current avg12 : %d:%02d.%02d", m, s, cs);

    text = TTF_RenderText_Shaded(font, avg_string, text_color, color);
    position.x = WIDTH - text->w -STICKER / 4;
    position.y = 90;
    SDL_BlitSurface(text, NULL, window, &position);

    sort(avg12, (number - 12 + 1));
    if(avg12[0] != -1){
      m = avg12[0] / 6000;
      s = (avg12[0] - 6000 * m) / 100;
      cs = avg12[0] - 6000 * m - 100 * s;
    }else
      m = -1;

    if(m == -1)
      sprintf(avg_string, "Best avg12 : DNF");
    else if(m == 0)
      sprintf(avg_string, "Best avg12 : %d.%02d", s, cs);
    else
      sprintf(avg_string, "Best avg12 : %d:%02d.%02d", m, s, cs);

    SDL_FreeSurface(text);
    text = TTF_RenderText_Shaded(font, avg_string, text_color, color);
    position.x = WIDTH - text->w -STICKER / 4;
    position.y += 30;
    SDL_BlitSurface(text, NULL, window, &position);

    SDL_FreeSurface(text);
    free(avg12);
  }

  SDL_Flip(window);

  TTF_CloseFont(font);
}

int solve_penalty (SDL_Surface* window){
  SDL_Surface* text = NULL;
  SDL_Surface* clear = NULL;
  SDL_Rect position;
  SDL_Event event;
  TTF_Font* font = NULL;
  SDL_Color color1 = {160, 160, 160};
  SDL_Color color2 = {40, 40, 40};
  int wait = 1;

  font = TTF_OpenFont("font.ttf", (STICKER / 2));

  clear = SDL_CreateRGBSurface(SDL_HWSURFACE, WIDTH, 50, 32, 0, 0, 0, 0);
  SDL_FillRect(clear, NULL, (SDL_MapRGB(window->format, 40, 40, 40)));
  position.x = 0;
  position.y = 0;
  SDL_BlitSurface(clear, NULL, window, &position);

  position.y = 450;
  text = TTF_RenderText_Shaded(font, "This time was :", color1, color2);
  position.x = WIDTH / 2 - text->w / 2;
  SDL_BlitSurface(text, NULL, window, &position);
  position.y += 50;

  SDL_FreeSurface(text);
  text = TTF_RenderText_Shaded(font, "Enter : no penalty   + : +2   F : DNF", color1, color2);
  position.x = WIDTH / 2 - text->w / 2;
  SDL_BlitSurface(text, NULL, window, &position);
  
  position.y += 50;
  SDL_FreeSurface(text);
  text = TTF_RenderText_Shaded(font, "D : don't save this time", color1, color2);
  position.x = WIDTH / 2 - text->w / 2;
  SDL_BlitSurface(text, NULL, window, &position);
  
  SDL_Flip(window);

  SDL_FreeSurface(text);
  SDL_FreeSurface(clear);
  TTF_CloseFont(font);

  while(wait){
    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_QUIT:
      exit(EXIT_SUCCESS);
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
      case SDLK_RETURN:
	wait = 0;
	return 0;
      case SDLK_KP_ENTER:
	wait = 0;
	return 0;
      case SDLK_KP_PLUS:
	wait = 0;
	return 1;
      case SDLK_f:
	wait = 0;
	return 2;
      case SDLK_d:
	wait = 0;
	return 3;
      case SDLK_q:
	exit(EXIT_SUCCESS);
      default:
	break;
      }
      break;
    default:
      break;
    }
  }
  return 0;
}

int averageof5 (int a, int b, int c, int d, int e){
  int times[5] = {0};

  times[0] = a; times[1] = b; times[2] = c; times[3] = d; times[4] = e;
  sort(times, 5);
  if(times[1] == -1 || times[2] == -1 || times[3] == -1)
    return -1;
  else
    return ((times[1] + times[2] + times[3]) / 3);
}

int averageof12 (int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l){
  int times[12] = {0};
  int x;
  int somme = 0;
  
  times[0] = a; times[1] = b; times[2] = c; times[3] = d; times[4] = e; times[5] = f;
  times[6] = g; times[7] = h; times[8] = i; times[9] = j; times[10] = k; times[11] = l;
  sort(times, 12);
  for(x = 1; x < 11; x++){
    if(times[x] == -1)
      return -1;
    else
      somme += times[x];
  }
  return (somme / 10);
}

void sort (int* tab, int n){
  int i, j, tmp;

  for(i = 1; i < n; i++){
    for(j = i; j > 0; j--){
      if(tab[j] < tab[j - 1]){
	tmp = tab[j];
	tab[j] = tab[j - 1];
	tab[j - 1] = tmp;
      }
    }
  }
  for(i = (n - 1); i >= 0 ; i--){
    for(j = i; j < (n - 1); j++){
      if(tab[j] == -1){
	tmp = tab[j];
	tab[j] = tab[j + 1];
	tab[j + 1] = tmp;
      }
    }
  }
}
