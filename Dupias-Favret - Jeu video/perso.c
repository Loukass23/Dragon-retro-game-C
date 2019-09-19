#include "structs.h"


void init_perso(Perso *perso, int x, int y, SDL_Surface *image)
{
    perso->bounding_box.x = x;
    perso->bounding_box.y = y;

    perso->bounding_box.w = SQUARE_WIDTH;
    perso->bounding_box.h = SQUARE_HEIGHT;

    perso->vx = 0;
	perso->vy = 0;

	perso->image= load_image( "perso.bmp" );
	
}
void init_dragon(Dragon *dragon, int x, int y, SDL_Surface *image)
{
    dragon->bounding_box.x = x;
    dragon->bounding_box.y = y;

    dragon->bounding_box.w = SQUARE_WIDTH;
    dragon->bounding_box.h = SQUARE_HEIGHT;

    dragon->vx = 0;
    dragon->vy = 0;

	dragon->image= load_image( "dragon.bmp" );
	
}
void move_perso(Perso *perso,Dragon *dragon, Map* map,SDL_Surface *screen)
{
	SDL_Surface *image_perdu = NULL;
	SDL_Surface *image_gagne = NULL;
	SDL_Rect dest;
		
	SDL_Rect victoire;
	dest.x = 0;
	dest.y = 0;

	victoire.x = 130;
	victoire.y = 150;
	victoire.h = 20;
	victoire.w = 10;
	image_perdu = SDL_LoadBMP("perdu.bmp");
	image_gagne = SDL_LoadBMP("gagne.bmp");
    //droite gauche
    perso->bounding_box.x += perso->vx;
	
    //si colision droite gauche
    if ( CollisionDecor(map, perso->bounding_box)||( perso->bounding_box.x < 0) || (perso->bounding_box.x + SQUARE_WIDTH > LEVEL_WIDTH))
    {
        //Reculer
        perso->bounding_box.x -= perso->vx;
		
    }

    // haut bas
    perso->bounding_box.y += perso->vy;
    //si collision haut bas
    if( CollisionDecor(map, perso->bounding_box)||( perso->bounding_box.y < 0) || (perso->bounding_box.y + SQUARE_HEIGHT > LEVEL_HEIGHT))
    {
        //Reculer
        perso->bounding_box.y -= perso->vy;
    }
	
	
	if (check_collision (perso->bounding_box, dragon->bounding_box))
	{
		SDL_BlitSurface(image_perdu, NULL, screen, &dest);
		SDL_Flip(screen);
		pause();
		SDL_FreeSurface(image_perdu);	
	}
	if (check_collision(perso->bounding_box, victoire))
	{
		SDL_BlitSurface(image_gagne, NULL, screen, &dest);
		SDL_Flip(screen);
		pause();
		SDL_FreeSurface(image_gagne);	
	}
}
int chasse(Perso *perso, Dragon *dragon, Map*map)
{
	 dragon->bounding_box.x += dragon->vx;
	
    //si colision droite gauche
    if ( CollisionDecor(map, dragon->bounding_box)||( dragon->bounding_box.x < 0) || (dragon->bounding_box.x + SQUARE_WIDTH > LEVEL_WIDTH))
    {
        //Reculer
        dragon->bounding_box.x -= dragon->vx;
		
    }
	 if( CollisionDecor(map, dragon->bounding_box)||( dragon->bounding_box.y < 0) || (dragon->bounding_box.y + SQUARE_HEIGHT > LEVEL_HEIGHT))
    {
        //Reculer
        dragon->bounding_box.y -= dragon->vy;
    }
if (check_collision (perso->bounding_box, dragon->bounding_box))
{
	return 0;
}
else

	{
	if ( perso->bounding_box.x != dragon->bounding_box.x)
		{
			if ( perso->bounding_box.x < dragon->bounding_box.x)
			{
				dragon->bounding_box.x -=2;
			}
			else 
			{
				dragon->bounding_box.x = dragon->bounding_box.x +2;
			}
		}
	
if ( perso->bounding_box.y != dragon->bounding_box.y)	
	{
	if (perso->bounding_box.y < dragon->bounding_box.y)
		{
			dragon->bounding_box.y = dragon->bounding_box.y -2;
		}
	else
		{
			dragon->bounding_box.y = dragon->bounding_box.y +2;
		}

	}
	return 1;
	}

}
void afficher_perso(Perso *perso, SDL_Surface *screen, SDL_Rect camera)
{
    
	appliquer_surface( perso->bounding_box.x - camera.x,perso->bounding_box.y - camera.y, perso->image, screen, NULL );
}
void afficher_dragon(Dragon *dragon, SDL_Surface *screen)
{
    
	appliquer_surface( dragon->bounding_box.x,dragon->bounding_box.y, dragon->image, screen, NULL );
}
void gestion_clavier(Perso *perso, SDL_Event *event)
{
    //Si une touche est pressee
    if(event->type == SDL_KEYDOWN) {
        switch( event->key.keysym.sym )
        {
            case SDLK_UP:  perso->vy -= SQUARE_HEIGHT / 2; break;
            case SDLK_DOWN: perso->vy += SQUARE_HEIGHT / 2; break;
            case SDLK_LEFT: perso->vx -= SQUARE_WIDTH / 2; break;
            case SDLK_RIGHT: perso->vx += SQUARE_WIDTH / 2; break;
            default: break;
        }
    }
   // Si une touche est relachee
    else if(event->type == SDL_KEYUP )
    {
        switch( event->key.keysym.sym )
        {
            case SDLK_UP:  perso->vy += SQUARE_HEIGHT / 2; break;
           case SDLK_DOWN: perso->vy -= SQUARE_HEIGHT / 2; break;
            case SDLK_LEFT: perso->vx += SQUARE_WIDTH / 2; break;
            case SDLK_RIGHT: perso->vx -= SQUARE_WIDTH / 2; break;
            default: break;
        }
    }
}
void set_camera(Perso *perso, SDL_Rect *camera)
{
    //Center camera sur perso
    camera->x = ( perso->bounding_box.x + SQUARE_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    camera->y = ( perso->bounding_box.y + SQUARE_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

    //garder la camera dans le niveau
    if( camera->x < 0 ) {
        camera->x = 0;
    }
    if( camera->y < 0 ) {
        camera->y = 0;
    }
    if( camera->x > LEVEL_WIDTH - camera->w ) {
        camera->x = LEVEL_WIDTH - camera->w;
    }
    if( camera->y > LEVEL_HEIGHT - camera->h ) {
        camera->y = LEVEL_HEIGHT - camera->h;
    }
}
