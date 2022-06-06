#pragma once
#include "dsSpriteManager.h"

#define MAX_TIME 45.f //20√  = 30.0f



class Game4
{
public:
	Game4();
	~Game4();

	dsSprite *ppScore[10];
	dsSprite *pSprite_bar;
	dsSprite *pVs;
	dsSprite *pBag;


	int score;

	int Bag_X;

	int g_time = 10;
	bool game_over;
	float g_Delta = 0.0f;

	void OnUpdateTime(DWORD tick, Graphics *BackBuffer);
	void GameImageLoding();
	void Game_Image_Init(Graphics *BackBuffer);
	void Number_Draw(int a, int x, int y, Graphics *BackBuffer);

	void Bag_set(int x,  Graphics *BackBuffer);

};

