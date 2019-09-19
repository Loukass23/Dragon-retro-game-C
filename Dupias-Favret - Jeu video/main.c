
#include "global.h"
#include "structs.h"
#include "timer.h"



int main()
{
	SDL_Surface *screen;
	SDL_Surface *icone;
	icone = SDL_LoadBMP("icone.bmp");

    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return 0;
	}	
	
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,SDL_DOUBLEBUF);
	while(1)
	{
	 SDL_WM_SetCaption( "Escape the Dragon by Payots", NULL );
	 SDL_WM_SetIcon( icone, NULL );
	menu (screen);
	jeu(screen);
	
	}
	SDL_Quit();
	return 0;
}

	 
    
