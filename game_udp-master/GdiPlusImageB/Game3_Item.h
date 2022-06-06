#pragma once
#include "dsSpriteManager.h"
#include <time.h>

class Game3_Item
{
public:
	Game3_Item();
	~Game3_Item();

	dsSprite *pItem;

	bool is_Draw;
	int srcX;
	int srcY;

	void Apple_set(Graphics *BackBuffer);
	void Loding();
	void reset(DWORD tick);
	void move();
	void GameImageLoding();
};

