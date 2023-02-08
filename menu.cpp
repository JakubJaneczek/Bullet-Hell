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



int menu()
{
	int rc, quit;
	quit = 0;
	SDL_Event event;
	SDL_Surface* screen, * charset, *menuIMG;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
	printf("eloooo\n");


	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	CreateWindow(rc, window, renderer);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH * 4, SCREEN_HEIGHT * 4);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetWindowTitle(window, "Projekt 2");
	SDL_ShowCursor(SDL_DISABLE);

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	char text[128];

	WorkingMenu(quit, event, screen, charset, scrtex, renderer, menuIMG);
	ClearAll(charset, screen, scrtex, renderer, window);


	return {};
}


