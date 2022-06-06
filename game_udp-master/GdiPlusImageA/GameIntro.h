#pragma once
#include "dsSpriteManager.h"

class GameIntro
{

public:
	//인트로
	dsSprite *pTitle;
	dsSprite *pGameStart[2];
	dsSprite *pGameExit[2];

	//게임 고르기
	dsSprite *pGame_M_Init[2];
	dsSprite *pGame_inst_bg;
	dsSprite *pGame_inst;
	dsSprite *pFriend[2];

	dsSprite *ptitle;///////////////
	dsSprite *pRCP[2];
	dsSprite *pEem;
	dsSprite *pGame_inst_RCP;


	//게임 로딩
	dsSprite *pTwo_player;
	dsSprite *pNo_player;
	dsSprite *pGame_play;

	//게임 마무리 이미지
	dsSprite *pWin;
	dsSprite *pLose;
	dsSprite *pDraw;
	dsSprite *pPick;
	dsSprite *pWait[2];

	dsSprite *pdbc[2];
	dsSprite *pdbc_inst;

	dsSprite *pTouchG[2];
	

	//인트로
	int start_check = 0;
	int Exit_check = 0;
	//메뉴선택
	int G_init_check = 0;
	int G_RCP_check = 0;
	int G_dbc_check = 0;
	int G_touch_check = 0;

	void GameImageLoding();
	void Game_Image_Init(Graphics *BackBuffer);
	void Game_Select_Draw(Graphics *BackBuffer);

	void Friend_OK(Graphics *BackBuffer);
	void Friend_NO(Graphics *BackBuffer);

	GameIntro();
	~GameIntro();
};

