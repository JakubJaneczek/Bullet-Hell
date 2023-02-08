#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include"Header1.h"
#include "structs.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}


SDL_Renderer* Renderer;

void Game(SDL_Surface* screen, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Event& event, int level)
{
	struct Player player;
	struct Enemy gruberto;
	struct Enemy badMinion;
	struct Enemy frozenEnemy;
	struct Fireball ball[16];
	struct Banana banan[NUMBER_OF_SHOTS];
	struct Heart HPboost;


	int t1, t2, quit, frames, rc, shot = 0;
	double delta, worldTime, fpsTimer, fps, t3, t4;

	int bananaNumber = 0;
	t1 = SDL_GetTicks();
	t3 = 0;
	t4 = 0;

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	worldTime = 0;

	char text[128];
	int white = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
	int green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);

	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	

	while (!quit)
	{
		if (level == 1)
		{
			LoadGraphicsLvl1(minion, gru, fireball, banana, background, minionShield, bananaEast, bananaWest, bananaNorth, bananaSouth, grave, gruDancing, minionDancing, heart);
			Level1(bananaNumber, event, quit, player, banan, shot, t2, delta, t1, worldTime, fpsTimer, fps, frames, screen, red, black, text, charset, scrtex, renderer, camera, gruberto, t3, ball, white, HPboost, level);
		}
		if (level == 2)
		{
			LoadGraphicsLvl2(minion, minionShield, banana, bananaEast, bananaWest, bananaNorth, heart, minionDancing, bananaSouth, grave, purpleFireball, sun, evilMinion, angryMinionR, angryMinionL);
			Level2(badMinion, quit, bananaNumber, event, player, banan, shot, t2, delta, t1, worldTime, fpsTimer, fps, frames, screen, red, black, text, charset, scrtex, renderer, camera, t3,  white, HPboost);
		}
		/*if (level == 3)
		{
			loadGraphicsLvl3(minion, minionShield, banana, bananaEast, bananaWest, bananaNorth, heart, minionDancing, bananaSouth, grave, mars, iceEnemy, iceBall, smalliceBall);
			struct Fireball iceball[NUMBER_OF_ICEBALLS];
			struct Megaball bigiceball[NUMBER_OF_BIGICEBALLS];
			player.PosX = 50;
			player.PosY = 400;
			int level = 2;
			double t4 = 0;
			int j = 0;
			int bulletNumber = 0;
			while (level == 2 && !quit)
			{
				StaticInLevels(bananaNumber, event, quit, player, banan, shot, t2, delta, t1, worldTime, fpsTimer, fps, frames, screen, red, black, text, charset, scrtex, renderer, camera);
				ScoreDisplay(screen, camera, red, black, text, player, charset, mars);

				if (player.minionHP > 0 && frozenEnemy.HP > 0)
				{
					if (j > 3)
					{
						j = 0;
					}
					if (bulletNumber > NUMBER_OF_ICEBALLS) 
					{
						bulletNumber = 0;
					}
					player.move();
					CameraMove(camera, player);
					DrawSurface(screen, minion, player.PosX - camera.x, player.PosY - camera.y);
					PlayerInvincibleImage(worldTime, t3, screen, player, camera);
					DrawSurface(screen, iceEnemy, frozenEnemy.PosX - camera.x, frozenEnemy.PosY - camera.y);
					if (("% .1lf", worldTime) - ("% .1lf", t4) > 1)
					{
						for (int i = 0; i < 16; i++)
						{
							DrawSurface(screen, smalliceBall, iceball[i].fireballPosX - camera.x, iceball[i].fireballPosY - camera.y);
							ShootingPattern1(i, iceball, 1, 0, 0);
							if (i > 7)
							{
								break;
							}
						}
					}
					PlayerShooting(screen, banan, camera, player, frozenEnemy, charset);
					RenderHPPlayer(screen, red, white, player.minionHP, camera, player);
					RenderHPEnemy(screen, red, white, frozenEnemy.HP, camera, frozenEnemy);
					RandomHPBoosts(HPboost, player, screen, camera);
				}
				else if (player.minionHP <= 0)
				{
					EnemyWin(screen, player, camera, frozenEnemy, red, black, text, charset, evilMinion);

					AfterGameChoice(event, quit, screen, charset, scrtex, renderer);
				}
				else if (frozenEnemy.HP <= 0)
				{
					PlayerWin(screen, frozenEnemy, camera, player, red, black, text, charset, event, quit, scrtex, renderer);

					while (SDL_PollEvent(&event) != 0)
					{
						switch (event.key.keysym.sym)
						{
						case SDLK_ESCAPE:
							quit = 1;
							break;
						case SDLK_n:
							ClearAllLvl3();
							level = 1;
							break;
						}
					}
				}
				frames++;
			}
		}*/
	}
}

void Level1(int& bananaNumber, SDL_Event& event, int& quit, Player& player, Banana  banan[8], int shot, int& t2, double& delta, int& t1, double& worldTime, double& fpsTimer, double& fps, int& frames, SDL_Surface* screen, int red, int black, char  text[128], SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Rect& camera, Enemy& gruberto, double& t3, Fireball  ball[16], int white, Heart& HPboost, int& level)
{
	while (level==1 && !quit)
	{
		StaticInLevels(bananaNumber, event, quit, player, banan, shot, t2, delta, t1, worldTime, fpsTimer, fps, frames, screen, red, black, text, charset, scrtex, renderer, camera);
		ScoreDisplay(screen, camera, red, black, text, player, charset, background);
		if (player.minionHP > 0 && gruberto.HP > 0)
		{
			player.move();
			CameraMove(camera, player);
			DrawSurface(screen, minion, player.PosX - camera.x, player.PosY - camera.y);
			PlayerInvincibleImage(worldTime, t3, screen, player, camera);
			DrawSurface(screen, gru, gruberto.PosX - camera.x, gruberto.PosY - camera.y);
			GruShooting(screen, ball, camera, player, gruberto, charset, t3, worldTime);
			PlayerShooting(screen, banan, camera, player, gruberto, charset);
			RenderHPPlayer(screen, red, white, player.minionHP, camera, player);
			RenderHPEnemy(screen, red, white, gruberto.HP, camera, gruberto);
			RandomHPBoosts(HPboost, player, screen, camera);
		}
		else if (player.minionHP <= 0)
		{
			EnemyWin(screen, player, camera, gruberto, red, black, text, charset, gruDancing);

			AfterGameChoice(event, quit, screen, charset, scrtex, renderer);
		}
		else if (gruberto.HP <= 0)
		{
			PlayerWin(screen, gruberto, camera, player, red, black, text, charset, event, quit, scrtex, renderer);

			while (SDL_PollEvent(&event) != 0)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = 1;
					break;
				case SDLK_n:
					level = 1;
					break;
				case SDLK_q:
					ClearAllLvl1();
					level = 2;
					break; 
				}
			}
			frames++;

		}
	}
}

void Level2(Enemy& badMinion, int& quit, int& bananaNumber, SDL_Event& event, Player& player, Banana  banan[8], int shot, int& t2, double& delta, int& t1, double& worldTime, double& fpsTimer, double& fps, int& frames, SDL_Surface* screen, int red, int black, char  text[128], SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Rect& camera, double& t3, int white, Heart& HPboost)
{	
	struct Fireball purpleball[NUMBER_OF_PURPLEBALLS];
	player.PosX = 50;
	player.PosY = 400;
	int level = 2;
	double t4 =0;
	int j = 0;
	while (level == 2 && !quit)
	{
		PurpleBallLimiter(j);
		StaticInLevels(bananaNumber, event, quit, player, banan, shot, t2, delta, t1, worldTime, fpsTimer, fps, frames, screen, red, black, text, charset, scrtex, renderer, camera);
		ScoreDisplay(screen, camera, red, black, text, player, charset, sun);

		if (player.minionHP > 0 && badMinion.HP > 0)
		{
			badMinion.move();
			player.move();
			CameraMove(camera, player);
			DrawSurface(screen, minion, player.PosX - camera.x, player.PosY - camera.y);
			PlayerInvincibleImage(worldTime, t3, screen, player, camera);
			BadMinionMoveDirection(badMinion, screen, camera);
			EvilMinionShooting(worldTime, t4, j, purpleball, badMinion, screen, camera, t3, player);			
			PlayerShooting(screen, banan, camera, player, badMinion, charset);
			RenderHPPlayer(screen, red, white, player.minionHP, camera, player);
			RenderHPEnemy(screen, red, white, badMinion.HP, camera, badMinion);
			RandomHPBoosts(HPboost, player, screen, camera);
		}
		else if (player.minionHP <= 0)
		{
			EnemyWin(screen, player, camera, badMinion, red, black, text, charset, evilMinion);

			AfterGameChoice(event, quit, screen, charset, scrtex, renderer);
		}
		else if (badMinion.HP <= 0)
		{
			PlayerWin(screen, badMinion, camera, player, red, black, text, charset, event, quit, scrtex, renderer);

			while (SDL_PollEvent(&event) != 0)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = 1;
					break;
				case SDLK_n:
					ClearAllLvl2();
					level = 1;
					break;
				case SDLK_q:
					ClearAllLvl2();
					level = 3;
					break;
				}
			}
		}
		frames++;
	}
}

void StaticInLevels(int& bananaNumber, SDL_Event& event, int& quit, Player& player, Banana  banan[8], int shot, int& t2, double& delta, int& t1, double& worldTime, double& fpsTimer, double& fps, int& frames, SDL_Surface* screen, int red, int black, char  text[128], SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Rect& camera)
{
	ShotsLimiter(bananaNumber);
	KeyControl(event, quit, player, banan, shot, *&bananaNumber);
	GetTime(t2, delta, t1, worldTime, fpsTimer, fps, frames);
	GameInfo(screen, red, black, text, worldTime, fps, charset, scrtex, renderer);
}





