#pragma once
#include "dsSpriteManager.h"


class Game2
{
public:

	dsSprite *pRCP[4][2];
	dsSprite *pbg;



	//���� =0 , ���� =1 , �� = 2
	int my_choic = 3;

	void GameImageLoding();
	void Game_Image_Init(Graphics *BackBuffer);


	int GameWinCheck(int my_c, int other_c);	//0 = �ƹ�����X , 1 = �̱� , 2 = �� , 3 = ��� 
	void Game_Init();


	Game2();
	~Game2();
};

