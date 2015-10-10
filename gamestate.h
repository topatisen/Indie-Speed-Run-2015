//Player Header
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class cGameState
{
	public:
	/* Gamestates
	 * 0 = intro
	 * 1 = main menu
	 * 2 = playing
	 * 3 = about
	 * 4 = exit
	*/
	int state;
	int playerOnePoints;
	int playerTwoPoints;
	int menuPosition;
	
	void create()
	{
		// Initialize variables
		playerOnePoints = 0;
		playerTwoPoints = 0;
		menuPosition = 0;
		// First state is intro
		state = 0;
	}

	// Handles events
	int run(SDL_Event event)
	{
		//KEYPRESSTEST
		while (SDL_PollEvent(&event)) {
			//Kepresses, works like a charm! <3<3<3<3<3
			switch(event.type){
				case SDL_KEYUP:
					if(event.key.keysym.sym==SDLK_ESCAPE)
					{
						if(state != 1)
						{
							state = 1;
						} 
						else if(state == 1)
						{
							state = 2;
						}
						break;
					}
				}
		}
		if(state == 1) {
			switch(event.type) {
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_UP)
				{
					menuPosition--;
					if (menuPosition < 0)
					{
						menuPosition = 4;
					}
					else if (menuPosition > 4)
					{
						menuPosition = 0;
					}
				}
				if (event.key.keysym.sym == SDLK_DOWN)
				{
					menuPosition++;
					if (menuPosition < 0)
					{
						menuPosition = 4;
					}
					else if (menuPosition > 4)
					{
						menuPosition = 0;
					}
				}
				if(event.key.keysym.sym == SDLK_RETURN)
				{
					if(menuPosition == 4)
					{
						SDL_Quit();
						return 0;
					}
				}
			}
		}
	}

	// Draws to renderer
	int draw(SDL_Renderer *ren, SDL_Texture *sMenuOverlay, SDL_Texture *sMenuSelector)
	{
		//Draw Code
		// Draw the intro thingie
		if (state == 0)
		{
			// Draw intro here
			// Currently, skip directly to menu
		}
		
		// Draw menu if we're in the pause/menu state
		if(state == 1)
		{
			renderTexture(sMenuOverlay, ren, 0, 0);
			renderTexture(sMenuSelector, ren, 0, menuPosition*100);
			//Draw menu here
		}

		if(state == 2)
		{
			// Draw points and overlay here
		}

		if (state == 3)
		{
			// Destroy stuff, exit
			SDL_DestroyRenderer(ren);
			SDL_Quit();
			return 0;
		}

	}
};

#endif
