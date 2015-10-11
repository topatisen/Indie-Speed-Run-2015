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
	int menuPosition;
	int overLayPosition;
	
	void create()
	{
		// Initialize variables
		menuPosition = 1;
		overLayPosition = 240;
		// First state is playing
		state = 2;
	}

	// Handles events
	int run(const Uint8 *keyboardstate)
	{
		if(keyboardstate[SDL_SCANCODE_ESCAPE])
		{
			if(state != 1&&state != 0)
			{
				state = 1;
			}
			else if(state == 1)
			{
				state = 2;
			}
			else if(state == 3)
			{
				state == 1;
			}
			SDL_Delay(130);
		}
		// If we're in the menu
		if(state == 1)
		{
			if(keyboardstate[SDL_SCANCODE_UP])
			{
				overLayPosition -= 100;
				if(overLayPosition > 440)
					overLayPosition = 240;
				if(overLayPosition < 240)
					overLayPosition = 440;
				menuPosition--;
				if (menuPosition < 1)
				{
					menuPosition = 3;
					overLayPosition = 440;
				}
				else if (menuPosition > 3)
				{
					menuPosition = 1;
					overLayPosition = 240;
				}
				SDL_Delay(130);
			}
			if(keyboardstate[SDL_SCANCODE_DOWN])
			{
				menuPosition++;
				overLayPosition += 100;
				if(overLayPosition > 440)
					overLayPosition = 240;
				if(overLayPosition < 240)
					overLayPosition = 440;
				if (menuPosition > 3)
				{
					overLayPosition = 240;
					menuPosition = 1;
				}
				else if (menuPosition < 1)
				{
					menuPosition = 3;
					overLayPosition = 440;
				}
				SDL_Delay(130);
			}
			if(keyboardstate[SDL_SCANCODE_RETURN])
			{
				if(menuPosition == 1)
				{
					state = 2;
				}
				else if(menuPosition == 2)
				{
					state = 3;
				}
				else if(menuPosition == 3)
				{
					state = 4;
				}
			}
		}
	}
	// Draws to renderer
	int draw(SDL_Renderer *ren, SDL_Texture *sMenuOverlay, SDL_Texture *sMenuSelector, SDL_Texture *sAboutOverlay)
	{
		//Draw Code
		// Draw the intro thingie
		if (state == 0)
		{
			// Draw intro here
			// Currently, skip directly to menu
			state = 1;
		}
		
		// Draw menu if we're in the pause/menu state
		if(state == 1)
		{
			renderTexture(sMenuOverlay, ren, 0, 0);
			renderTexture(sMenuSelector, ren, 200, overLayPosition);
			//Draw menu here
		}

		if(state == 2)
		{
			// Draw points and overlay here
		}

		if(state == 3)
		{
			renderTexture(sAboutOverlay, ren, 0, 0);
		}

	}
};

#endif
