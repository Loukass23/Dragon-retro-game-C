#include "global.h"

#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"



int check_collision(SDL_Rect A, SDL_Rect B)
{
    //cotés des rectangles A et B
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calcul cotes A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calcul cotes B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //verifier collisions
    if ((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) {
        return 0;
    } else {
        return 1;
    }
}

void appliquer_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}

int load_files(SDL_Surface **image_perso, SDL_Surface **image_background, SDL_Surface **image_dragon, SDL_Surface **tileSheet)
{
    //charger lesimage
    *image_perso = load_image( "perso.bmp" );
    *image_background = load_image( "bg.bmp" );
	*image_dragon = load_image( "dragon.bmp" );

    if((*image_perso == NULL) || (*image_background == NULL) || (*image_dragon == NULL)) {
        return 0;
    }
	//charger fueille de tiles
    *tileSheet = load_image( "tiles.bmp" );
    if( *tileSheet == NULL )
    {
        return 0;
    }
    return 1;
}

SDL_Surface *load_image(char *filename) {
	//Surface tampon qui nous servira pour charger l'image
	SDL_Surface* loadedImage = NULL;
	//L'image optimisée qu'on va utiliser
	SDL_Surface* optimizedImage = NULL;
	//Chargement de l'image
	loadedImage = SDL_LoadBMP(filename);
	//Si le chargement se passe bien
	if(loadedImage != NULL) {
		//Création de l'image optimisée
		optimizedImage = SDL_DisplayFormat(loadedImage);
		//Libération de l'ancienne image
		SDL_FreeSurface(loadedImage);
	}

	//On retourne l'image optimisée
	return optimizedImage;
}

int init(SDL_Rect *camera)
{
    camera->x = 0;
    camera->y = 0;
    camera->w = SCREEN_WIDTH;
    camera->h = SCREEN_HEIGHT;
    return 1;
}

void nettoyer()
{
    SDL_Quit();
}

void jeu (SDL_Surface *screen)
	{
    int quit = 0;

	SDL_Rect camera;
	SDL_Surface *tileSheet;
    SDL_Surface *image_perso;
    SDL_Surface *image_background;
    SDL_Surface *image_dragon;
    

	Map* map;

	Perso monPerso;
    Dragon monDragon;
	

	Timer fps;

    SDL_ShowCursor(SDL_DISABLE);
	
	if(!init(&camera))
	{
    }
    if (!load_files(&image_perso, &image_background, &image_dragon, &tileSheet)) 
	{
    }
	map = ChargerMap("level.txt");
	AfficherMap(map,image_background);
	init_perso(&monPerso, 0, 600, image_perso);
	init_dragon(&monDragon, 1280, 0, image_dragon);

	init_timer(&fps);

    while(!quit)
    {
		SDL_Event event;
        start_timer(&fps);
       
        while( SDL_PollEvent( &event ) )
        {
            gestion_clavier(&monPerso, &event);
            if( event.type == SDL_QUIT ) {
                exit(1);
            }
        }
        move_perso(&monPerso, &monDragon, map,screen);
		chasse(&monPerso, &monDragon,map);
		set_camera(&monPerso, &camera);
		appliquer_surface(0, 0, image_background, screen, &camera);
        afficher_perso(&monPerso, screen, camera);
        afficher_dragon(&monDragon, image_background);
         SDL_Flip( screen );
		 SDL_Flip( image_background );
       // LibererMap(m);
        if( get_ticks(&fps) < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - get_ticks(&fps) );
        }
    }  
}

void pause()
{
	int continuer =1;
	int positionhorizontale,positionverticale;
	SDL_Event event;

	while (continuer)
{
SDL_WaitEvent(&event);
switch(event.type)
{
    case SDL_QUIT:
        exit(1);
        break;
	
    case  SDL_MOUSEBUTTONUP:
    positionhorizontale=event.button.x;
    positionverticale=event.button.y;

    if (event.button.button == SDL_BUTTON_LEFT)
    {
       if (positionhorizontale>40 && positionhorizontale<200 && positionverticale>220 && positionverticale<250)
           exit(1);}
    
       if (positionhorizontale>40 && positionhorizontale<200 && positionverticale>50 && positionverticale<130)
       continuer = 0;
     }   
    } 
}

void menu(SDL_Surface *ecran)

{
    
    SDL_Surface *imageDeFond = NULL;
    SDL_Rect positionFond;
 
    positionFond.x = 0;
    positionFond.y = 0;

    imageDeFond = SDL_LoadBMP("menu.bmp");
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    SDL_Flip(ecran);
    pause(ecran);
    SDL_FreeSurface(imageDeFond);
  
}
