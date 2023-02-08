#pragma once

extern "C"
{
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#include "structs.h"

SDL_Surface* minion, * gru, * fireball, * banana, * background, * minionShield, * bananaEast, * bananaWest, * bananaNorth, * bananaSouth, * grave, * gruDancing, * minionDancing, * heart, *sun, *evilMinion, *purpleFireball, *angryMinionR, *angryMinionL, *iceEnemy, *iceBall, *smalliceBall, *mars;

#define SCREEN_WIDTH	900
#define SCREEN_HEIGHT	600
#define LEVEL_WIDTH  1280
#define LEVEL_HEIGHT  1280

#define NUMBER_OF_SHOTS 8

#define NUMBER_OF_PURPLEBALLS 30

#define NUMBER_OF_ICEBALLS 32
#define NUMBER_OF_BIGICEBALLS 4

void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);

void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);

void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);

void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);

void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

void ClearAll(SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Window* window);

int LoadGraphicsMenu(SDL_Surface*& charset, SDL_Surface*& MenuIMG, SDL_Surface*& levelChoice);

int LoadGraphicsLvl1(SDL_Surface*& minion, SDL_Surface*& gru, SDL_Surface*& fireball, SDL_Surface*& banana, SDL_Surface*& background, SDL_Surface*& minionShield, SDL_Surface*& bananaEast, SDL_Surface*& bananaWest, SDL_Surface*& bananaNorth, SDL_Surface*& bananaSouth, SDL_Surface*& grave, SDL_Surface*& gruDancing, SDL_Surface*& minionDancing, SDL_Surface*& heart);

int LoadGraphicsLvl2(SDL_Surface*& minion, SDL_Surface*& minionShield, SDL_Surface*& banana, SDL_Surface*& bananaEast, SDL_Surface*& bananaWest, SDL_Surface*& bananaNorth, SDL_Surface*& heart, SDL_Surface*& minionDancing, SDL_Surface*& bananaSouth,  SDL_Surface*& grave, SDL_Surface*& purpleFireball, SDL_Surface*& sun, SDL_Surface*& evilMinion, SDL_Surface*& angryMinionR, SDL_Surface*& angryMinionL);

int loadGraphicsLvl3(SDL_Surface*& minion, SDL_Surface*& minionShield, SDL_Surface*& banana, SDL_Surface*& bananaEast, SDL_Surface*& bananaWest, SDL_Surface*& bananaNorth, SDL_Surface*& heart, SDL_Surface*& minionDancing, SDL_Surface*& bananaSouth, SDL_Surface*& grave, SDL_Surface*& mars, SDL_Surface*& iceEnemy, SDL_Surface*& iceBall, SDL_Surface*& smalliceBall);

int LoadStaticGraphics(SDL_Surface*& minion, SDL_Surface*& minionShield, SDL_Surface*& banana, SDL_Surface*& bananaEast, SDL_Surface*& bananaWest, SDL_Surface*& bananaNorth, SDL_Surface*& heart, SDL_Surface*& minionDancing, SDL_Surface*& bananaSouth, SDL_Surface*& grave);

int CreateWindow(int& rc, SDL_Window*& window, SDL_Renderer*& renderer);

void Game(SDL_Surface* screen, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Event& event, int level);

void Level1(int& bananaNumber, SDL_Event& event, int& quit, Player& player, Banana  banan[8], int shot, int& t2, double& delta, int& t1, double& worldTime, double& fpsTimer, double& fps, int& frames, SDL_Surface* screen, int red, int black, char  text[128], SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Rect& camera, Enemy& gruberto, double& t3, Fireball  ball[16], int white, Heart& HPboost, int& level);

void Level2(Enemy& gruberto, int& quit, int& bananaNumber, SDL_Event& event, Player& player, Banana  banan[8], int shot, int& t2, double& delta, int& t1, double& worldTime, double& fpsTimer, double& fps, int& frames, SDL_Surface* screen, int red, int black, char  text[128], SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Rect& camera, double& t3, int white, Heart& HPboost);

void PurpleBallLimiter(int& j);

void BadMinionMoveDirection(Enemy& badMinion, SDL_Surface* screen, SDL_Rect& camera);

void EvilMinionShooting(double& worldTime, double& t4, int& j, Fireball  purpleball[30], Enemy& badMinion, SDL_Surface* screen, SDL_Rect& camera, double& t3, Player& player);

void StaticInLevels(int& bananaNumber, SDL_Event& event, int& quit, Player& player, Banana  banan[8], int shot, int& t2, double& delta, int& t1, double& worldTime, double& fpsTimer, double& fps, int& frames, SDL_Surface* screen, int red, int black, char  text[128], SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Rect& camera);

void ClearAllLvl1();

void EnemyWin(SDL_Surface* screen, Player& player, SDL_Rect& camera, Enemy& gruberto, int red, int black, char  text[128], SDL_Surface* charset, SDL_Surface* character);

void PlayerWin(SDL_Surface* screen, Enemy& gruberto, SDL_Rect& camera, Player& player, int red, int black, char  text[128], SDL_Surface* charset, SDL_Event& event, int& quit, SDL_Texture* scrtex, SDL_Renderer* renderer);

void RandomHPBoosts(Heart& HPboost, Player& player, SDL_Surface* screen, SDL_Rect& camera);

void ScoreDisplay(SDL_Surface* screen, SDL_Rect& camera, int red, int black, char  text[128], Player& player, SDL_Surface* charset, SDL_Surface* background);

void AfterGameChoice(SDL_Event& event, int& quit, SDL_Surface* screen, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer);

void ShotsLimiter(int& bananaNumber);

void PlayerInvincibleImage(double worldTime, double t3, SDL_Surface* screen, Player& player, SDL_Rect& camera);

void KeyControl(SDL_Event& event, int& quit, Player& player, Banana banan[NUMBER_OF_SHOTS], int shot, int &bananaNumber);

void GruShooting(SDL_Surface* screen, Fireball  ball[16], SDL_Rect& camera, Player& player, Enemy& gruberto, SDL_Surface* charset, double& t3, double &worldTime/*, SDL_Surface* fireball*/);

void PlayerShooting(SDL_Surface* screen, Banana  banan[8], SDL_Rect& camera, Player& player, Enemy& gruberto, SDL_Surface* charset);

void PrintBananas(SDL_Surface* screen, Banana  banan[8], int i, SDL_Rect& camera, Enemy& gruberto, SDL_Surface* banana, Player& player);

void ShootingPattern1(int i, Fireball  ball[8], int a, int PosX, int PosY);

void PlayerInvincible(double& worldTime, double& t3, Player& player, Fireball ball[16], int i, Enemy& gruberto);

void ClearAllLvl2();

void ClearAllLvl3();

void ShootingPattern2(int i, Fireball  purpleball[NUMBER_OF_PURPLEBALLS], int a);

void ShootingPattern3(int i, Megaball bigiceball[NUMBER_OF_BIGICEBALLS], int a);

void GetTime(int& t2, double& delta, int& t1, double& worldTime, double& fpsTimer, double& fps, int& frames);

void GameInfo(SDL_Surface* screen, int red, int black, char  text[128], double worldTime, double fps, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer);

bool checkCollision(SDL_Rect a, SDL_Rect b);

void CameraMove(SDL_Rect& camera, Player& player);

void RenderHPPlayer(SDL_Surface* screen, int red, int white, int hp, SDL_Rect& camera, Player& object);

void RenderHPEnemy(SDL_Surface* screen, int red, int white, int hp, SDL_Rect& camera, Enemy& object);

int menu();

void WorkingMenu(int& quit, SDL_Event& event, SDL_Surface* screen, SDL_Surface*& charset, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Surface*& menuIMG);

void LevelChoice(SDL_Surface* screen, int& quit, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Event& event, SDL_Surface*& charset);

void RendererActions(SDL_Texture* scrtex, SDL_Surface* screen, SDL_Renderer* renderer);
