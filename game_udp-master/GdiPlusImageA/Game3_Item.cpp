#include "Game3_Item.h"



Game3_Item::Game3_Item()
{

	is_Draw = false;
	is_Draw = TRUE;



}


Game3_Item::~Game3_Item()
{
}

void Game3_Item::Apple_set(Graphics *BackBuffer) //그림 
{
	if (is_Draw == TRUE)
		pItem->Draw(BackBuffer, srcX, srcY);
}

void Game3_Item::Loding()
{
	srand((unsigned)time(NULL));

	is_Draw = TRUE;

	srcX = (rand() % 440);
	srcY = 200;
}

void Game3_Item::reset(DWORD tick)
{

	srcX = (rand() % 440);

	is_Draw = TRUE;


	srcY = -200;

}

void Game3_Item::move()
{
	srcY += 5;

}

void Game3_Item::GameImageLoding()
{
	dsSpriteManager *Sprite = GetSpriteManager();

	pItem = Sprite->Create("사과", "사과.png");
}