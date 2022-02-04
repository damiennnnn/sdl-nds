#include <SDL.h>


int main()
{
	SDL_Surface *text_screen;

	SDL_Init(SDL_INIT_VIDEO);


	text_screen=SDL_SetVideoMode(256,192,8,SDL_SWSURFACE|SDL_DOUBLEBUF);

	SDL_ShowCursor(SDL_DISABLE);

  
  SDL_Rect ra;
  ra.x=0;
  ra.y=0;
  ra.w=256;
  ra.h=192;
	SDL_FillRect(text_screen, &ra, 0x250);

		SDL_Flip(text_screen);
SDL_FillRect(text_screen, &ra, 0x250);
SDL_Flip(text_screen);
		SDL_Delay(2000); 	

	SDL_Delay(12000);


	return 0;

}
