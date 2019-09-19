#define _CRT_SECURE_NO_DEPRECATE   // pour visual C++ qui met des warning pour fopen et fscanf : aucun effet negatif pour les autres compilos.
#include <string.h>
#include "structs.h"
#include "global.h"
#define CACHE_SIZE 5000


SDL_Surface* LoadImage32(const char* fichier_image)
{
	SDL_Surface* image_result;
	SDL_Surface* image_ram = SDL_LoadBMP(fichier_image);	// charge l'image dans image_ram en RAM
	if (image_ram==NULL)
	{
		printf("Image %s introuvable !! \n",fichier_image);
		SDL_Quit();
		system("pause");
		exit(-1);
	}
	image_result = SDL_DisplayFormat(image_ram);
	SDL_FreeSurface(image_ram);
	return image_result;
}

void ChargerMap_tileset(FILE* F,Map* m)
{
	int numtile,i,j;
	char buf[CACHE_SIZE];  // un buffer, petite mémoire cache
	char buf2[CACHE_SIZE];  // un buffer, petite mémoire cache
	fscanf(F,"%s",buf); // #tileset
	fscanf(F,"%s",buf); // nom du fichier
	m->tileset = LoadImage32(buf);
	fscanf(F,"%d %d",&m->nbtilesX,&m->nbtilesY);
	m->LARGEUR_TILE = m->tileset->w/m->nbtilesX;
	m->HAUTEUR_TILE = m->tileset->h/m->nbtilesY;
	m->props = malloc(m->nbtilesX*m->nbtilesY*sizeof(TileProp));
	for(j=0,numtile=1;j<m->nbtilesY;j++)
	{
		for(i=1;i<m->nbtilesX;i++,numtile++)
		{
			m->props[numtile].R.w = m->LARGEUR_TILE;
			m->props[numtile].R.h = m->HAUTEUR_TILE;
			m->props[numtile].R.x = i*m->LARGEUR_TILE;
			m->props[numtile].R.y = j*m->HAUTEUR_TILE;
			
		}
	}
}

void ChargerMap_level(FILE* F,Map* m)
{
	int i,j;
	char buf[CACHE_SIZE];  // un buffer, petite mémoire cache
	fscanf(F,"%s",buf); // #level
	fscanf(F,"%d %d",&m->nbtiles_largeur_monde,&m->nbtiles_hauteur_monde);
	m->schema = malloc(m->nbtiles_largeur_monde*sizeof(Uint32*));
	for(i=0;i<m->nbtiles_largeur_monde;i++)
		m->schema[i] = malloc(m->nbtiles_hauteur_monde*sizeof(Uint32));
	for(j=0;j<m->nbtiles_hauteur_monde;j++)
	{
		for(i=0;i<m->nbtiles_largeur_monde;i++)
		{
			int tmp;
			fscanf(F,"%d",&tmp);
			if (tmp>=m->nbtilesX*m->nbtilesY)
			{
				printf("level tile hors limite\n");
				SDL_Quit();
				system("pause");
				exit(-1);
			}
			m->schema[i][j] = tmp;
		}
	}
}

Map* ChargerMap(const char* level)
{
	FILE* F;
	Map* m;
	F = fopen(level,"r");
	if (!F)
	{
		printf(" pas de fichier %s  \n",level);
		SDL_Quit();
		system("pause");
		exit(-1);
	}
	m = malloc(sizeof(Map));

	ChargerMap_tileset(F,m);
	ChargerMap_level(F,m);
	fclose(F);
	return m;
}

int AfficherMap(Map* map,SDL_Surface* screen)
{
	int i,j;
	int numero_tile;
	for(i=0;i<map->nbtiles_largeur_monde;i++)
	{
		for(j=0;j<map->nbtiles_hauteur_monde;j++)
		{ 
			map->bounding_box.x = i*map->LARGEUR_TILE;
			map->bounding_box.y = j*map->HAUTEUR_TILE;
			numero_tile = map->schema[i][j];
			SDL_BlitSurface(map->tileset,&(map->props[numero_tile].R),screen,&map->bounding_box);
			map->tableau [i][j] = map->bounding_box;
		}
	}
	return 0;
}

int CollisionDecor(Map* map,SDL_Rect perso)
	{
	int i,j;
	int numero_tile;
	SDL_Rect test;

	for(i=0;i<map->nbtiles_largeur_monde;i++)
	{
		for(j=0;j<map->nbtiles_hauteur_monde;j++)
		{ 
			test = map->tableau [i][j];
			if (check_collision (test,perso))
				return 1;

		}
	}
	return 0;
}

/*int LibererMap(Map* m)
{
	int i;
	SDL_FreeSurface(m->tileset);
	for(i=0;i<m->nbtiles_hauteur_monde;i++)
		free(m->schema[i]);
	free(m->schema);
	free(m->props);
	free(m);
	return 0;
}


*/