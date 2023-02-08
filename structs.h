#pragma once
#include <cmath>
extern "C"
{
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH	900
#define SCREEN_HEIGHT	600
#define LEVEL_WIDTH  1280
#define LEVEL_HEIGHT  1280

#define NUMBER_OF_SHOTS 8

#define NUMBER_OF_PURPLEBALLS 30

struct Player
{
	static const int PLAYER_WIDTH = 50;
	static const int PLAYER_HEIGHT = 50;

	static const int PLAYER_VEL = 1;

	Player();

	void handleEvent(SDL_Event& event);

	void move();

	int getPosX();
	int getPosY();

	int PosX, PosY;

	int minionVelX, minionVelY;

	int minionHP;

	double score;

	double multiplier;

	SDL_Rect minionHitbox;
};

Player::Player()
{
	PosX = 50;
	PosY = 400;

	minionVelX = 0;
	minionVelY = 0;

	minionHitbox.w = PLAYER_WIDTH;
	minionHitbox.h = PLAYER_HEIGHT;
	minionHitbox.x = PosX - PLAYER_WIDTH / 2;
	minionHitbox.h = PosX - PLAYER_HEIGHT / 2;

	minionHP = 100;

	score = 0;

	multiplier = 1;
}

void Player::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP: minionVelY -= PLAYER_VEL; break;
		case SDLK_DOWN: minionVelY += PLAYER_VEL; break;
		case SDLK_LEFT: minionVelX -= PLAYER_VEL; break;
		case SDLK_RIGHT: minionVelX += PLAYER_VEL; break;
		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP: minionVelY += PLAYER_VEL; break;
		case SDLK_DOWN: minionVelY -= PLAYER_VEL; break;
		case SDLK_LEFT: minionVelX += PLAYER_VEL; break;
		case SDLK_RIGHT: minionVelX -= PLAYER_VEL; break;
		}
	}
}

void Player::move()
{
	PosX += minionVelX;
	minionHitbox.x = PosX - PLAYER_WIDTH / 2;

	if ((PosX - PLAYER_WIDTH / 2 < 0) || (PosX + PLAYER_WIDTH / 2 > LEVEL_WIDTH))
	{
		PosX -= minionVelX;
		minionHitbox.x = PosX;
	}

	PosY += minionVelY;
	minionHitbox.y = PosY;

	if ((PosY - PLAYER_HEIGHT / 2 < 0) || (PosY + PLAYER_HEIGHT / 2 > LEVEL_HEIGHT))
	{
		PosY -= minionVelY;
		minionHitbox.y = PosY - PLAYER_HEIGHT / 2;
	}
}

int Player::getPosX()
{
	return PosX;
}

int Player::getPosY()
{
	return PosY;
}



struct Enemy
{
	static const int WIDTH = 40;
	static const int HEIGHT = 80;

	Enemy();

	void move();

	int PosX, PosY;

	int VelX, VelY;

	int HP;

	int DMG;

	SDL_Rect Hitbox;
};

Enemy::Enemy()
{
	PosX = LEVEL_WIDTH / 2;
	PosY = LEVEL_HEIGHT / 2;

	VelX = 1;
	VelY = 0;
	Hitbox.w = WIDTH;
	Hitbox.h = HEIGHT;
	Hitbox.x = PosX - WIDTH / 2;
	Hitbox.y = PosY - HEIGHT / 2;

	HP = 50;

	DMG = 5;
}

void Enemy::move()
{
    PosX -= VelX;

	if (PosX - WIDTH / 2 < 0)
	{
		VelX = -1;
	}

	if (PosX - WIDTH / 2 > LEVEL_WIDTH)
	{
		VelX = 1;
	}

	Hitbox.x = PosX;
}

struct Fireball
{
	static const int FIREBALL_WIDTH = 30;
	static const int FIREBALL_HEIGHT = 40;

	static const int FIREBALL_VEL = 1;

	Fireball();

	void move(int fireballPosX, int fireballPosY, int PosX, int PosY);

	void Fireball::movePurple(double fireballPosX, double fireballPosY);

	double fireballPosX, fireballPosY;

	int fireballVelX, fireballVelY;

	SDL_Rect fireballHitbox;

	int alive;
};

Fireball::Fireball()
{
	fireballPosX = LEVEL_WIDTH / 2;
	fireballPosY = LEVEL_HEIGHT / 2;

	fireballVelX = 0;
	fireballVelY = 0;

	fireballHitbox.w = FIREBALL_WIDTH;
	fireballHitbox.h = FIREBALL_HEIGHT;
	fireballHitbox.x = fireballPosX - FIREBALL_WIDTH / 2;
	fireballHitbox.y = fireballPosY- FIREBALL_HEIGHT / 2;

	alive = 0;
}

void Fireball::move(int fireballVelX, int fireballVelY, int PosX, int PosY)
{
	fireballPosX += fireballVelX;
	fireballHitbox.x = fireballPosX;

	if ((fireballPosX - FIREBALL_WIDTH / 2 < 0) || (fireballPosX + FIREBALL_WIDTH / 2 > LEVEL_WIDTH))
	{
		fireballPosX = PosX;
	}

	fireballPosY += fireballVelY;
	fireballHitbox.y = fireballPosY;

	if ((fireballPosY - FIREBALL_HEIGHT / 2 < 0) || (fireballPosY + FIREBALL_HEIGHT / 2 > LEVEL_HEIGHT))
	{
		fireballPosY = PosY;
	}
}

void Fireball::movePurple(double fireballVelX, double fireballVelY )
{
	(double)fireballPosX;
	fireballPosX += fireballVelX;
	fireballHitbox.x = fireballPosX;

	if (fireballPosX - FIREBALL_WIDTH / 2 < 0)
	{
		alive = 0;
	}
	if (fireballPosX - FIREBALL_WIDTH / 2 > LEVEL_WIDTH)
	{
		alive = 0;
	}
	(double)fireballPosY;
	fireballPosY += fireballVelY;
	fireballHitbox.y = fireballPosY;

	if (fireballPosY - FIREBALL_HEIGHT / 2 < 0)
	{
		alive = 0;
	}
	if (fireballPosY - FIREBALL_HEIGHT / 2  > LEVEL_HEIGHT)
	{
		alive = 0;
	}
}



struct Banana
{
	static const int BANANA_WIDTH = 20;
	static const int BANANA_HEIGHT = 13;

	static const int BANANA_VEL = 1;

	Banana();

	void move();

	void handleEvent(SDL_Event& event, int PosX, int PosY, int &bananaNumber);

	void BananaChangeVars(int PosX, int PosY, char a, int velx, int vely, int &bananaNumber);

	char direction;

	int bananaPosX = 0, bananaPosY = 0;

	int bananaStartPosX = 0, bananaStartPosY = 0;

	int alive = 0;

	int bananaVelX, bananaVelY;

	SDL_Rect bananaHitbox;
};

Banana::Banana()
{
	bananaVelX = 0;
	bananaVelY = 0;

	bananaHitbox.w = BANANA_WIDTH;
	bananaHitbox.h = BANANA_HEIGHT;
	bananaHitbox.x = bananaPosX - BANANA_WIDTH / 2;
	bananaHitbox.y = bananaPosY - BANANA_HEIGHT / 2;
}

void Banana::handleEvent(SDL_Event& event, int PosX, int PosY, int &bananaNumber)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w: 
			BananaChangeVars(PosX, PosY, 'N', 0, BANANA_VEL, bananaNumber);
			break;
		case SDLK_s: 
			BananaChangeVars(PosX, PosY, 'S', 0, -BANANA_VEL, bananaNumber);
			break;
		case SDLK_a: 
			BananaChangeVars(PosX, PosY, 'W', -BANANA_VEL, 0, bananaNumber);
			break;
		case SDLK_d: 
			BananaChangeVars(PosX, PosY, 'E', BANANA_VEL, 0, bananaNumber);
			break;
		}
	}
}

void Banana::BananaChangeVars(int PosX, int PosY, char a, int velx, int vely, int &bananaNumber)
{
	bananaPosX = PosX;
	bananaPosY = PosY;
	direction = a;
	bananaVelX = velx;
	bananaVelY = -vely;
	bananaStartPosX = PosX;
	bananaStartPosY = PosY;
	alive = 1;
	bananaNumber++;
}

void Banana::move()
{
	bananaPosX += bananaVelX;
	bananaHitbox.x = bananaPosX;

	bananaPosY += bananaVelY;
	bananaHitbox.y = bananaPosY;

	if ((bananaPosX - BANANA_WIDTH / 2 < 0) || (bananaPosX + BANANA_WIDTH / 2 > LEVEL_WIDTH) || abs(bananaPosX - bananaStartPosX) > 500)
	{
		alive = 0;
	}
	if ((bananaPosY - BANANA_HEIGHT / 2 < 0) || (bananaPosY + BANANA_HEIGHT / 2 > LEVEL_HEIGHT) || abs(bananaPosY - bananaStartPosY) > 500)
	{	
		alive = 0;
	}
}


struct Heart
{
	static const int HEART_WIDTH = 20;
	static const int HEART_HEIGHT = 20;

	int PosX, PosY ;

	Heart();

	int alive = 0;

	void UpdateHitbox();
		
	SDL_Rect heartHitbox;
};

Heart::Heart()
{
	PosX = 0;
	PosY = 0;

	heartHitbox.w = HEART_WIDTH;
	heartHitbox.h = HEART_HEIGHT;
	heartHitbox.x = PosX - HEART_WIDTH / 2;
	heartHitbox.y = PosY - HEART_HEIGHT / 2;
}

void Heart::UpdateHitbox()
{
	heartHitbox.x = PosX - HEART_WIDTH / 2;
	heartHitbox.y = PosY - HEART_HEIGHT / 2;
}


struct Megaball
{

	static const int WIDTH = 100;
	static const int HEIGHT = 100;
	double VEL;

	void move(double VelX, double VelY);

	int PosX, PosY;

	int startPosX, startPosY;

	SDL_Rect hitbox;

	int alive;

	Megaball();

};

Megaball::Megaball()
{
	VEL = 1;

	PosX = LEVEL_WIDTH / 2;
	PosY = LEVEL_HEIGHT / 2;

	startPosX = LEVEL_WIDTH / 2;
	startPosY = LEVEL_HEIGHT / 2;

	alive = 0;
}

void Megaball::move(double VelX, double VelY)
{
	PosX += VelX;
	PosY += VelY;
}