#pragma once
#include "dsSpriteManager.h"

class Game1
{
public:
	int stage = 1;


	char Qz[20] = "ghfkddl";
	char stage1[20] = "ghfkddl"; //호랑이
	char stage2[20] = "vosej"; //팬더
	char stage3[20] = "tkwk"; //사자
	char stage4[20] = "dnjstnddl"; //원숭이
	char stage5[20] = "rhdiddl";//고양이
	char stage6[20] = "rkddkwl";//강아지
	char stage7[20] = "skansmfqh";//나무늘보
	char stage8[20] = "rlfls";//기린
	char stage9[20] = "ehowl";//돼지
	char stage10[20] = "wjwth";//젖소

	dsSprite *pR;
	dsSprite *pS;
	dsSprite *pE;
	dsSprite *pF;
	dsSprite *pA;
	dsSprite *pQ;
	dsSprite *pT;
	dsSprite *pD;
	dsSprite *pW;
	dsSprite *pC;
	dsSprite *pZ;
	dsSprite *pX;
	dsSprite *pV;
	dsSprite *pG;

	dsSprite *pOK;
	dsSprite *pNO;

	dsSprite *pScore[10];

	dsSprite *pPass[2];
	dsSprite *pVs;
	dsSprite *pST;

	int pass_check = 0;

	Game1();
	~Game1();

	void GameImageLoding();
	void Game_Image_Init(Graphics *BackBuffer, bool answer_check, bool Enter_check);
	void Number_Draw(char a, int x, int y, Graphics *BackBuffer);

	int GameWinCheck(int my_score, int other_score, int my_stage, int other_stage);	//이기면 1, 지면 2
	bool GameingCheck(int my_score, int other_score, int my_stage, int other_stage); //게임이 진행중인지 체크
	void game_Init();
};
