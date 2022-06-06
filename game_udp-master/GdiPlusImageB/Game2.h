#pragma once
#include "dsSpriteManager.h"


class Game2
{
public:

	dsSprite *pRCP[4][2];
	dsSprite *pbg;



	//가위 =0 , 바위 =1 , 보 = 2
	int my_choic = 3;

	void GameImageLoding();
	void Game_Image_Init(Graphics *BackBuffer);


	int GameWinCheck(int my_c, int other_c);	//0 = 아무상태X , 1 = 이김 , 2 = 짐 , 3 = 비김 
	void Game_Init();


	Game2();
	~Game2();
};

