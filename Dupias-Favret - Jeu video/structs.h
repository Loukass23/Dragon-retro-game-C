#ifndef __PERSO_H__
#define __PERSO_H__


#define SQUARE_WIDTH 10
#define SQUARE_HEIGHT 10
#define TOTAL_TILES 3348

#include "SDL.h"
#include "global.h"


typedef struct _perso
{
    int vx;
    int vy;
    SDL_Rect bounding_box;
    SDL_Surface *image;
} Perso;

typedef struct _dragon
{
    int vx;
    int vy;
    SDL_Rect bounding_box;
    SDL_Surface *image;
} Dragon;

typedef struct _tileprop
{
	SDL_Rect R;
	int mur;
	// tout ce que vous voulez...
} TileProp;

typedef struct _map
{
	SDL_Rect bounding_box;
	int LARGEUR_TILE,HAUTEUR_TILE;
	int nbtilesX,nbtilesY;
	SDL_Surface* tileset;
	TileProp* props;
	Uint32** schema;
	SDL_Rect tableau [54] [62];
	int nbtiles_largeur_monde,nbtiles_hauteur_monde;
	
	 
} Map;

int CollisionDecor(Map* map, SDL_Rect perso) ;

int AfficherMap(Map* m,SDL_Surface* screen);

int LibererMap(Map* m);

Map* ChargerMap(const char* fic);

void init_perso(Perso *perso, int x, int y, SDL_Surface *image);

void init_dragon(Dragon *dragon, int x, int y, SDL_Surface *image);

void move_perso(Perso *perso, Dragon *dragon, SDL_Surface *screen);

void afficher_perso(Perso *perso, SDL_Surface *screen, SDL_Rect camera);

void afficher_dragon(Dragon *dragon, SDL_Surface *background);

void gestion_clavier(Perso *perso, SDL_Event *event);

void set_camera(Perso *perso, SDL_Rect *camera);

int chasse(Perso *perso, Dragon *dragon,Map*map);



#endif // __PERSO_H__
