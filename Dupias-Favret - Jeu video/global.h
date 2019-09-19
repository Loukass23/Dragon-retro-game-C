#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "SDL.h"
#include "structs.h"
#include "timer.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32
#define LEVEL_WIDTH 1280
#define LEVEL_HEIGHT 960
#define FRAMES_PER_SECOND 20

//Camera





int check_collision(SDL_Rect A, SDL_Rect B);

void appliquer_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

int load_files(SDL_Surface **image_perso, SDL_Surface **image_background, SDL_Surface **image_dragon, SDL_Surface **tileSheet);

SDL_Surface *load_image(char *filename);

int init(SDL_Rect *camera);

void nettoyer();

void menu(SDL_Surface *ecran);

void pause();

void jeu (SDL_Surface *screen);


#endif // __GLOBAL_H__
