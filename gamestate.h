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
		overLayPosition = 190;
		// First state is playing
		state = 0;
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
				overLayPosition -= 80;
				if(overLayPosition > 350)
					overLayPosition = 190;
				if(overLayPosition < 190)
					overLayPosition = 350;
				menuPosition--;
				if (menuPosition < 1)
				{
					menuPosition = 3;
					overLayPosition = 350;
				}
				else if (menuPosition > 3)
				{
					menuPosition = 1;
					overLayPosition = 190;
				}
				SDL_Delay(130);
			}
			if(keyboardstate[SDL_SCANCODE_DOWN])
			{
				menuPosition++;
				overLayPosition += 80;
				if(overLayPosition > 350)
					overLayPosition = 190;
				if(overLayPosition < 190)
					overLayPosition = 350;
				if (menuPosition > 3)
				{
					overLayPosition = 190;
					menuPosition = 1;
				}
				else if (menuPosition < 1)
				{
					menuPosition = 3;
					overLayPosition = 350;
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
	int draw(SDL_Renderer *ren, SDL_Texture *sMenuOverlay, SDL_Texture *sMenuSelector, SDL_Texture *sAboutOverlay, SDL_Texture *sIntroscreen, SDL_Texture *sControlscreen)
	{
		//Draw Code
		// Draw the intro thingie
		if (state == 0)
		{
			// Draw intro here
			renderTexture(sIntroscreen, ren, 0, 0);
			SDL_Delay(5000);
			renderTexture(sControlscreen, ren, 0, 0);
			SDL_Delay(5000);
			// Jump to menu when we're done
			state = 1;
		}
		
		// Draw menu if we're in the pause/menu state
		if(state == 1)
		{
			//Draw menu here
			renderTexture(sMenuOverlay, ren, 0, 0);
			renderTexture(sMenuSelector, ren, 140, overLayPosition);
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
