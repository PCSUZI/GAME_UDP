#pragma once
#include "dsSpriteManager.h"

class Game1
{
public:
	int stage = 1;


	char Qz[20] = "ghfkddl";
	char stage1[20] = "ghfkddl"; //ȣ����
	char stage2[20] = "vosej"; //�Ҵ�
	char stage3[20] = "tkwk"; //����
	char stage4[20] = "dnjstnddl"; //������
	char stage5[20] = "rhdiddl";//�����
	char stage6[20] = "rkddkwl";//������
	char stage7[20] = "skansmfqh";//�����ú�
	char stage8[20] = "rlfls";//�⸰
	char stage9[20] = "ehowl";//����
	char stage10[20] = "wjwth";//����

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

	int GameWinCheck(int my_score, int other_score, int my_stage, int other_stage);	//�̱�� 1, ���� 2
	bool GameingCheck(int my_score, int other_score, int my_stage, int other_stage); //������ ���������� üũ
	void game_Init();
};
