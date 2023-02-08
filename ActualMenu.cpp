#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include"Header1.h"
#include "structs.h"


extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
#include "main.h"
}
SDL_Surface* levelChoice;

void WorkingMenu(int& quit, SDL_Event& event, SDL_Surface* screen, SDL_Surface*& charset, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Surface*& menuIMG)
{
	int level = 0;
	LoadGraphicsMenu(charset, menuIMG, levelChoice);
	DrawSurface(screen, menuIMG, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	while (!quit)
	{
		RendererActions(scrtex, screen, renderer);
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = 1;
				break;
			case SDLK_n:
				level = 1;
				SDL_FreeSurface(menuIMG);
				Game(screen, charset, scrtex, renderer, event, level);
				break;
			case SDLK_p:
				SDL_FreeSurface(menuIMG);
				LevelChoice(screen, quit, scrtex, renderer, event, charset);
			}
		}
	}
}

void LevelChoice(SDL_Surface* screen, int& quit, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Event& event, SDL_Surface*& charset)
{
	SDL_Surface* minion, * gru, * fireball, * banana, * background, * minionShield, * bananaEast, * bananaWest, * bananaNorth, * bananaSouth, * grave, * gruDancing, * minionDancing, * heart, * sun, * evilMinion, * purpleFireball, * angryMinionR, * angryMinionL, * iceEnemy, * iceBall, * smalliceBall, * mars;
	int level;
	DrawSurface(screen, levelChoice, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	while (!quit)
	{
		RendererActions(scrtex, screen, renderer);
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_1:
				SDL_FreeSurface(levelChoice);
				level = 1;
				Game(screen, charset, scrtex, renderer, event, level);
				break;
			case SDLK_2:
				SDL_FreeSurface(levelChoice);
				level = 2;
				Game(screen, charset, scrtex, renderer, event, level);
				break;
			case SDLK_3:
				SDL_FreeSurface(levelChoice);
				level = 3;
				Game(screen, charset, scrtex, renderer, event, level);
			case SDLK_ESCAPE:
				quit = 1;
				break;
			}
			break;
		}

	}
}
