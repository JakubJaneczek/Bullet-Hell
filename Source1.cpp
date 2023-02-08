#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include"Header1.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH	900
#define SCREEN_HEIGHT	600
#define LEVEL_WIDTH 1280
#define LEVEL_HEIGHT 1280

#define NUMBER_OF_PURPLEBALLS 30

// narysowanie napisu txt na powierzchni screen, zaczynajπc od punktu (x, y)
// charset to bitmapa 128x128 zawierajπca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt úrodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};

// rysowanie pojedynczego pixela
// draw a single pixel
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};

// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1) 
// bπdü poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

// rysowanie prostokπta o d≥ugoúci bokÛw l i k
// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

void ClearAll(SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Window* window)
{
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
};

int LoadGraphicsMenu(SDL_Surface*& charset, SDL_Surface*& MenuIMG, SDL_Surface*& levelChoice)
{
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		return 1;
	};

	MenuIMG = SDL_LoadBMP("./menu.bmp");
	if (MenuIMG == NULL) {
		printf("SDL_LoadBMP(menu.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(MenuIMG);
		return 1;
	};

	levelChoice = SDL_LoadBMP("./levelchoice.bmp");
	if (levelChoice == NULL) {
		printf("SDL_LoadBMP(levelchoice.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(levelChoice);
		return 1;
	};
	SDL_SetColorKey(charset, true, 0x000000);
}

void ClearAllLvl1()
{
	SDL_FreeSurface(minion);
	SDL_FreeSurface(gru);
	SDL_FreeSurface(fireball);
	SDL_FreeSurface(banana);
	SDL_FreeSurface(background);
	SDL_FreeSurface(minionShield);
	SDL_FreeSurface(bananaEast);
	SDL_FreeSurface(bananaNorth);
	SDL_FreeSurface(bananaSouth);
	SDL_FreeSurface(bananaWest);
	SDL_FreeSurface(grave);
	SDL_FreeSurface(gruDancing);
	SDL_FreeSurface(minionDancing);
	SDL_FreeSurface(heart);
}

void ClearAllLvl2()
{
	SDL_FreeSurface(minion);
	SDL_FreeSurface(evilMinion);
	SDL_FreeSurface(purpleFireball);
	SDL_FreeSurface(banana);
	SDL_FreeSurface(sun);
	SDL_FreeSurface(minionShield);
	SDL_FreeSurface(bananaEast);
	SDL_FreeSurface(bananaNorth);
	SDL_FreeSurface(bananaSouth);
	SDL_FreeSurface(grave);
	SDL_FreeSurface(minionDancing);
	SDL_FreeSurface(heart);
	SDL_FreeSurface(bananaWest);
}

void ClearAllLvl3()
{
	SDL_FreeSurface(minion);
	SDL_FreeSurface(iceEnemy);
	SDL_FreeSurface(smalliceBall);
	SDL_FreeSurface(banana);
	SDL_FreeSurface(mars);
	SDL_FreeSurface(minionShield);
	SDL_FreeSurface(bananaEast);
	SDL_FreeSurface(bananaNorth);
	SDL_FreeSurface(bananaSouth);
	SDL_FreeSurface(grave);
	SDL_FreeSurface(minionDancing);
	SDL_FreeSurface(heart);
	SDL_FreeSurface(bananaWest);
	SDL_FreeSurface(iceBall);
}

int LoadGraphicsLvl1(SDL_Surface*& minion, SDL_Surface*& gru, SDL_Surface*& fireball, SDL_Surface*& banana, SDL_Surface*& background, SDL_Surface*& minionShield, SDL_Surface*& bananaEast, SDL_Surface*& bananaWest, SDL_Surface*& bananaNorth, SDL_Surface*& bananaSouth, SDL_Surface*& grave, SDL_Surface*& gruDancing, SDL_Surface*& minionDancing, SDL_Surface*& heart)
{
	LoadStaticGraphics(minion, minionShield, banana, bananaEast, bananaWest, bananaNorth, heart, minionDancing, bananaSouth, grave);
	gru = SDL_LoadBMP("./gru.bmp");
	if (gru == NULL) {
		printf("SDL_LoadBMP(gru.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(gru);
		return 1;
	};

	fireball = SDL_LoadBMP("./Fireball.bmp");
	if (fireball == NULL) {
		printf("SDL_LoadBMP(Fireball.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(fireball);
		return 1;
	};


	background = SDL_LoadBMP("./moon.bmp");
	if (background == NULL) {
		printf("SDL_LoadBMP(moon.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(background);
		return 1;
	};


	gruDancing = SDL_LoadBMP("./gruDancing.bmp");
	if (gruDancing == NULL) {
		printf("SDL_LoadBMP(gruDancing.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(gruDancing);
		return 1;
	};


}

int LoadGraphicsLvl2(SDL_Surface*& minion, SDL_Surface*& minionShield, SDL_Surface*& banana, SDL_Surface*& bananaEast, SDL_Surface*& bananaWest, SDL_Surface*& bananaNorth, SDL_Surface*& heart, SDL_Surface*& minionDancing, SDL_Surface*& bananaSouth, SDL_Surface*& grave, SDL_Surface*& purpleFireball, SDL_Surface*& sun, SDL_Surface*& evilMinion, SDL_Surface*& angryMinionR, SDL_Surface*& angryMinionL)
{
	LoadStaticGraphics(minion, minionShield, banana, bananaEast, bananaWest, bananaNorth, heart, minionDancing, bananaSouth, grave);
	sun = SDL_LoadBMP("./sun.bmp");
	if (sun == NULL) {
		printf("SDL_LoadBMP(sun.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(sun);
		return 1;
	};
	evilMinion = SDL_LoadBMP("./evilMinion.bmp");
	if (evilMinion == NULL) {
		printf("SDL_LoadBMP(evilMinion.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(evilMinion);
		return 1;
	};
	angryMinionL = SDL_LoadBMP("./angryEvilMinionL.bmp");
	if (angryMinionL == NULL) {
		printf("SDL_LoadBMP(angryEvilMinionL.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(angryMinionL);
		return 1;
	};
	angryMinionR = SDL_LoadBMP("./angryEvilMinionR.bmp");
	if (angryMinionR == NULL) {
		printf("SDL_LoadBMP(angryEvilMinionR.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(angryMinionR);
		return 1;
	};
	purpleFireball = SDL_LoadBMP("./purpleFireball.bmp");
	if (purpleFireball == NULL) {
		printf("SDL_LoadBMP(purpleFireball.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(purpleFireball);
		return 1;
	};
}

int loadGraphicsLvl3(SDL_Surface*& minion, SDL_Surface*& minionShield, SDL_Surface*& banana, SDL_Surface*& bananaEast, SDL_Surface*& bananaWest, SDL_Surface*& bananaNorth, SDL_Surface*& heart, SDL_Surface*& minionDancing, SDL_Surface*& bananaSouth, SDL_Surface*& grave, SDL_Surface*& mars, SDL_Surface*& iceEnemy, SDL_Surface*& iceBall, SDL_Surface*& smalliceBall)
{
	LoadStaticGraphics(minion, minionShield, banana, bananaEast, bananaWest, bananaNorth, heart, minionDancing, bananaSouth, grave);

	iceBall = SDL_LoadBMP("./iceball.bmp");
	if (iceBall == NULL) {
		printf("SDL_LoadBMP(iceball.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(iceBall);
		return 1;
	};
	smalliceBall = SDL_LoadBMP("./smalliceBall.bmp");
	if (smalliceBall == NULL) {
		printf("SDL_LoadBMP(smalliceBall.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(smalliceBall);
		return 1;
	};
	iceEnemy = SDL_LoadBMP("./iceEnemy.bmp");
	if (iceEnemy == NULL) {
		printf("SDL_LoadBMP(iceEnemy.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(iceEnemy);
		return 1;
	};
	mars = SDL_LoadBMP("./mars.bmp");
	if (mars == NULL) {
		printf("SDL_LoadBMP(mars.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(mars);
		return 1;
	};
}
int LoadStaticGraphics(SDL_Surface*& minion, SDL_Surface*& minionShield, SDL_Surface*& banana, SDL_Surface*& bananaEast, SDL_Surface*& bananaWest, SDL_Surface*& bananaNorth, SDL_Surface*& heart, SDL_Surface*& minionDancing, SDL_Surface*& bananaSouth, SDL_Surface*& grave)
{
	minion = SDL_LoadBMP("./minion.bmp");
	if (minion == NULL) {
		printf("SDL_LoadBMP(minion.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(minion);
		return 1;
	};

	minionShield = SDL_LoadBMP("./MinionShield.bmp");
	if (minionShield == NULL) {
		printf("SDL_LoadBMP(minion.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(minionShield);
		return 1;
	};
	banana = SDL_LoadBMP("./banan.bmp");
	if (banana == NULL) {
		printf("SDL_LoadBMP(banan.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(banana);
		return 1;
	};
	bananaEast = SDL_LoadBMP("./bananEast.bmp");
	if (bananaEast == NULL) {
		printf("SDL_LoadBMP(bananEast.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(bananaEast);
		return 1;
	};

	bananaWest = SDL_LoadBMP("./bananWest.bmp");
	if (bananaWest == NULL) {
		printf("SDL_LoadBMP(bananWest.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(bananaWest);
		return 1;
	};

	bananaNorth = SDL_LoadBMP("./bananNorth.bmp");
	if (bananaNorth == NULL) {
		printf("SDL_LoadBMP(bananNorth.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(bananaNorth);
		return 1;
	};
	heart = SDL_LoadBMP("./heart.bmp");
	if (heart == NULL) {
		printf("SDL_LoadBMP(heart.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(heart);
		return 1;
	};

	minionDancing = SDL_LoadBMP("./minionDancing.bmp");
	if (minionDancing == NULL) {
		printf("SDL_LoadBMP(minionDancing.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(minionDancing);
		return 1;
	};
	bananaSouth = SDL_LoadBMP("./bananSouth.bmp");
	if (bananaSouth == NULL) {
		printf("SDL_LoadBMP(bananSouth.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(bananaSouth);
		return 1;
	};

	grave = SDL_LoadBMP("./grave.bmp");
	if (grave == NULL) {
		printf("SDL_LoadBMP(grave.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(grave);
		return 1;
	};
}

int CreateWindow(int& rc, SDL_Window*& window, SDL_Renderer*& renderer)
{
	// tryb pe≥noekranowy / fullscreen mode
	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
	//rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};
}

void RendererActions(SDL_Texture* scrtex, SDL_Surface* screen, SDL_Renderer* renderer)
{
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void EnemyWin(SDL_Surface* screen, Player& player, SDL_Rect& camera, Enemy& gruberto, int red, int black, char  text[128], SDL_Surface* charset, SDL_Surface* character)
{
	DrawSurface(screen, grave, player.PosX - camera.x, player.PosY - camera.y);
	DrawSurface(screen, character, gruberto.PosX - camera.x, gruberto.PosY - camera.y);

	DrawRectangle(screen, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 * 3, SCREEN_WIDTH / 2, 50, red, black);
	sprintf(text, "PRZEGRALES! \n Nowa gra: N \n Wyjscie: ESC");
	DrawString(screen, SCREEN_WIDTH / 4 + 50, SCREEN_HEIGHT / 4 * 3 + 20, text, charset);
}

void PlayerWin(SDL_Surface* screen, Enemy& gruberto, SDL_Rect& camera, Player& player, int red, int black, char  text[128], SDL_Surface* charset, SDL_Event& event, int& quit, SDL_Texture* scrtex, SDL_Renderer* renderer)
{
	DrawSurface(screen, grave, gruberto.PosX - camera.x, gruberto.PosY - camera.y);
	DrawSurface(screen, minionDancing, player.PosX - camera.x, player.PosY - camera.y);

	DrawRectangle(screen, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 * 3, SCREEN_WIDTH / 2, 50, red, black);
	sprintf(text, "WYGRALES! \n Nowa gra: N \n Wyjscie: ESC");
	DrawString(screen, SCREEN_WIDTH / 4 + 50, SCREEN_HEIGHT / 4 * 3 + 20, text, charset);

	AfterGameChoice(event, quit, screen, charset, scrtex, renderer);
}

void RandomHPBoosts(Heart& HPboost, Player& player, SDL_Surface* screen, SDL_Rect& camera)
{
	if (HPboost.alive == 0)
	{
		HPboost.PosX = rand() % 1280;
		HPboost.PosY = rand() % 1280;
		HPboost.UpdateHitbox();
		HPboost.alive = 1;
	}
	if (checkCollision(HPboost.heartHitbox, player.minionHitbox))
	{
		printf("%d  ", HPboost.PosX); printf("%d\n", HPboost.PosY);
		printf("%d  ", HPboost.heartHitbox.x); printf("%d  ", HPboost.heartHitbox.y);
		printf("%d  ", player.PosX); printf("%d\n", player.PosY);
		if (player.minionHP < 50)
		{
			player.minionHP += 5;
		}
		HPboost.alive = 0;
	}
	DrawSurface(screen, heart, HPboost.PosX - camera.x, HPboost.PosY - camera.y);
}

void ScoreDisplay(SDL_Surface* screen, SDL_Rect& camera, int red, int black, char  text[128], Player& player, SDL_Surface* charset, SDL_Surface* background)
{
	DrawSurface(screen, background, LEVEL_WIDTH / 2 - camera.x, LEVEL_HEIGHT / 2 - camera.y);
	DrawRectangle(screen, 780, 480, 100, 50, red, black);
	sprintf(text, "%2.1f", player.score);
	DrawString(screen, 800, 500, text, charset);
	DrawRectangle(screen, 80, 480, 100, 50, red, black);
	sprintf(text, "x %2.1f", player.multiplier);
	DrawString(screen, 100, 500, text, charset);
}

void AfterGameChoice(SDL_Event& event, int& quit, SDL_Surface* screen, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer)
{
	int level;
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			quit = 1;
			break;
		case SDLK_n:
			level = 1;
			Game(screen, charset, scrtex, renderer, event, level);
			break;
		}
	}
}

void ShotsLimiter(int& bananaNumber)
{
	if (bananaNumber > 7)
	{
		bananaNumber = 0;
	}
}

void PlayerInvincibleImage(double worldTime, double t3, SDL_Surface* screen, Player& player, SDL_Rect& camera)
{
	if (("% .1lf", worldTime) - ("% .1lf", t3) < 1 && t3 != 0)
	{
		DrawSurface(screen, minionShield, player.PosX - camera.x, player.PosY - camera.y);
	}
}

void KeyControl(SDL_Event& event, int& quit, Player& player, Banana banan[NUMBER_OF_SHOTS], int shot, int& bananaNumber)
{
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			quit = 1;
			break;
		case SDL_QUIT:
			quit = 1;
			break;
		}

		player.handleEvent(event);

		if (banan[bananaNumber].alive == 0)
		{
			banan[bananaNumber].handleEvent(event, player.getPosX(), player.getPosY(), bananaNumber);
		}
	}
}

void GruShooting(SDL_Surface* screen, Fireball  ball[16], SDL_Rect& camera, Player& player, Enemy& gruberto, SDL_Surface* charset, double& t3, double& worldTime)
{
	for (int i = 0; i < 16; i++)
	{
		if (i < 8)
		{
			int a = 1;
			DrawSurface(screen, fireball, ball[i].fireballPosX - camera.x, ball[i].fireballPosY - camera.y);
			ShootingPattern1(i, ball, a, gruberto.PosX, gruberto.PosY);
		}
		if (i > 7)
		{
			int a = 2;
			DrawSurface(screen, fireball, ball[i].fireballPosX - camera.x, ball[i].fireballPosY - camera.y);
			ShootingPattern1(i, ball, a, gruberto.PosX, gruberto.PosY);
		}

		PlayerInvincible(worldTime, t3, player, ball, i, gruberto);
	}
}

void EvilMinionShooting(double& worldTime, double& t4, int& j, Fireball  purpleball[30], Enemy& badMinion, SDL_Surface* screen, SDL_Rect& camera, double& t3, Player& player)
{
	if (("% .1lf", worldTime) - ("% .1lf", t4) > 0.4)
	{
		for (int a = j; a < NUMBER_OF_PURPLEBALLS; a++)
		{
			if (purpleball[a].alive == 0);
			{
				purpleball[a].fireballPosX = badMinion.PosX;
				purpleball[a].fireballPosY = badMinion.PosY;
				purpleball[a].alive = 1;
				j++;
				t4 = worldTime;

			}
			if (j % 4 == 0 && j != 0)
			{
				break;
			}
		}
	}
	{
		for (int i = 0; i < NUMBER_OF_PURPLEBALLS; i++)
		{
			int a = 2;
			DrawSurface(screen, purpleFireball, purpleball[i].fireballPosX - camera.x, purpleball[i].fireballPosY - camera.y);
			ShootingPattern2(i, purpleball, a);
			PlayerInvincible(worldTime, t3, player, purpleball, i, badMinion);
		}
	}
}

void PurpleBallLimiter(int& j)
{
	if (j > 29)
	{
		j = 0;
	}
}

void BadMinionMoveDirection(Enemy& badMinion, SDL_Surface* screen, SDL_Rect& camera)
{
	if (badMinion.VelX > 0)
	{
		DrawSurface(screen, angryMinionL, badMinion.PosX - camera.x, badMinion.PosY - camera.y);
	}
	else
	{
		DrawSurface(screen, angryMinionR, badMinion.PosX - camera.x, badMinion.PosY - camera.y);
	}
}

void PlayerShooting(SDL_Surface* screen, Banana  banan[8], SDL_Rect& camera, Player& player, Enemy& badMinion, SDL_Surface* charset)
{
	for (int i = 0; i < NUMBER_OF_SHOTS; i++)
	{
		if (banan[i].alive == 1)
		{
			switch (banan[i].direction)
			{
			case 'N':
				PrintBananas(screen, banan, i, camera, badMinion, bananaNorth, player);
				break;
			case 'W':
				PrintBananas(screen, banan, i, camera, badMinion, bananaWest, player);
				break;
			case 'S':
				PrintBananas(screen, banan, i, camera, badMinion, bananaSouth, player);
				break;
			case 'E':
				PrintBananas(screen, banan, i, camera, badMinion, bananaEast, player);
				break;
			}
		}
	}
}

void PrintBananas(SDL_Surface* screen, Banana  banan[8], int i, SDL_Rect& camera, Enemy& gruberto, SDL_Surface* banana, Player& player)
{
	DrawSurface(screen, banana, banan[i].bananaPosX - camera.x, banan[i].bananaPosY - camera.y);
	banan[i].move();
	if (checkCollision(banan[i].bananaHitbox, gruberto.Hitbox))
	{
		gruberto.HP--;
		banan[i].alive = 0;
		player.score += 1 * player.multiplier;
		player.multiplier += 0.1;
	}
}

void ShootingPattern1(int i, Fireball  ball[], int a, int PosX, int PosY)
{
	if (i % 8 == 0) { ball[i].move(-a * ball[i].FIREBALL_VEL, 0, PosX, PosY); }
	if (i % 8 == 1) { ball[i].move(0, a * ball[i].FIREBALL_VEL, PosX, PosY); }
	if (i % 8 == 2) { ball[i].move(a * ball[i].FIREBALL_VEL, 0, PosX, PosY); }
	if (i % 8 == 3) { ball[i].move(0, -a * ball[i].FIREBALL_VEL, PosX, PosY); }
	if (i % 8 == 4) { ball[i].move(a * ball[i].FIREBALL_VEL, -a * ball[i].FIREBALL_VEL, PosX, PosY); }
	if (i % 8 == 5) { ball[i].move(-a * ball[i].FIREBALL_VEL, -a * ball[i].FIREBALL_VEL, PosX, PosY); }
	if (i % 8 == 6) { ball[i].move(a * ball[i].FIREBALL_VEL, a * ball[i].FIREBALL_VEL, PosX, PosY); }
	if (i % 8 == 7) { ball[i].move(-a * ball[i].FIREBALL_VEL, a * ball[i].FIREBALL_VEL, PosX, PosY); }
}

void ShootingPattern2(int i, Fireball  purpleball[NUMBER_OF_PURPLEBALLS], int a)
{

	if (i % 4 == 0) { purpleball[i].movePurple(0,  -purpleball[i].FIREBALL_VEL); }
	if (i % 4 == 1) { purpleball[i].movePurple(0, purpleball[i].FIREBALL_VEL); }
	if (i % 4 == 2) { purpleball[i].movePurple(a * -purpleball[i].FIREBALL_VEL, 0); }
	if (i % 4 == 3) { purpleball[i].movePurple(a * purpleball[i].FIREBALL_VEL, 0); }

}

void ShootingPattern3(int i, Megaball  bigiceball[NUMBER_OF_BIGICEBALLS], int a)
{

	if (i % 4 == 0) { bigiceball[i].move(0, -bigiceball[i].VEL); }
	if (i % 4 == 1) { bigiceball[i].move(0, bigiceball[i].VEL); }
	if (i % 4 == 2) { bigiceball[i].move(a * -bigiceball[i].VEL, 0); }
	if (i % 4 == 3) { bigiceball[i].move(a * bigiceball[i].VEL, 0); }

}

void PlayerInvincible(double& worldTime, double& t3, Player& player, Fireball  ball[], int i, Enemy& badMinion)
{
	if (("% .1lf", worldTime) - ("% .1lf", t3) > 1)
	{
		if (checkCollision(player.minionHitbox, ball[i].fireballHitbox) || checkCollision(player.minionHitbox, badMinion.Hitbox))
		{
			player.minionHP -= badMinion.DMG;
			t3 = worldTime;
			player.multiplier = 1;
			player.score -= 50;
		}
	}
}

void GetTime(int& t2, double& delta, int& t1, double& worldTime, double& fpsTimer, double& fps, int& frames)
{
	t2 = SDL_GetTicks();

	delta = (t2 - t1) * 0.001;
	t1 = t2;

	worldTime += delta;

	fpsTimer += delta;
	if (fpsTimer > 0.5) {
		fps = frames * 2;
		frames = 0;
		fpsTimer -= 0.5;
	};
}

void GameInfo(SDL_Surface* screen, int red, int black, char  text[128], double worldTime, double fps, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer)
{
	DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, red, black);
	sprintf(text, "Jakub Janeczek, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
	sprintf(text, "Esc - wyjscie, \030 - gora, \031 - dol, \032 - lewo, \033 - prawo");
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);
	RendererActions(scrtex, screen, renderer);
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}

void CameraMove(SDL_Rect& camera, Player& player)
{
	camera.x = (player.getPosX() + Player::PLAYER_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (player.getPosY() + Player::PLAYER_HEIGHT / 2) - SCREEN_HEIGHT / 2;

	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void RenderHPPlayer(SDL_Surface* screen, int red, int white, int hp, SDL_Rect& camera, Player& object)
{
	SDL_Rect basePlayerHPBar{ object.PosX - 25 - camera.x, object.PosY - 30 - camera.y, 50, 5 };
	SDL_Rect currentPlayerHPBar{ object.PosX - 25 - camera.x, object.PosY - 30 - camera.y, 0.5 * hp, 5 };
	SDL_FillRect(screen, &basePlayerHPBar, white);
	SDL_FillRect(screen, &currentPlayerHPBar, red);
}

void RenderHPEnemy(SDL_Surface* screen, int red, int white, int hp, SDL_Rect& camera, Enemy& object)
{
	SDL_Rect basePlayerHPBar{ object.PosX - 25 - camera.x, object.PosY - 50 - camera.y, 50, 5 };
	SDL_Rect currentPlayerHPBar{ object.PosX - 25 - camera.x, object.PosY - 50 - camera.y, hp, 5 };
	SDL_FillRect(screen, &basePlayerHPBar, white);
	SDL_FillRect(screen, &currentPlayerHPBar, red);
}

