#include "Game1.h"



Game1::Game1()
{
	stage = 1;
}


Game1::~Game1()
{
}

void Game1::GameImageLoding()
{
	dsSpriteManager *Sprite = GetSpriteManager();

	pR = Sprite->Create("ㄱ", "ㄱ.png");
	pS = Sprite->Create("ㄴ", "ㄴ.png");
	pE = Sprite->Create("ㄷ", "ㄷ.png");
	pF = Sprite->Create("ㄹ", "ㄹ.png");
	pA = Sprite->Create("ㅁ", "ㅁ.png");
	pQ = Sprite->Create("ㅂ", "ㅂ.png");
	pT = Sprite->Create("ㅅ", "ㅅ.png");
	pD = Sprite->Create("ㅇ", "ㅇ.png");
	pW = Sprite->Create("ㅈ", "ㅈ.png");
	pC = Sprite->Create("ㅊ", "ㅊ.png");
	pZ = Sprite->Create("ㅋ", "ㅋ.png");
	pX = Sprite->Create("ㅌ", "ㅌ.png");
	pV = Sprite->Create("ㅍ", "ㅍ.png");
	pG = Sprite->Create("ㅎ", "ㅎ.png");

	pOK = Sprite->Create("정답", "정답.png");
	pNO = Sprite->Create("오답", "오답.png");


	pScore[0] = Sprite->Create("0", "0.png");
	pScore[1] = Sprite->Create("1", "1.png");
	pScore[2] = Sprite->Create("2", "2.png");
	pScore[3] = Sprite->Create("3", "3.png");
	pScore[4] = Sprite->Create("4", "4.png");
	pScore[5] = Sprite->Create("5", "5.png");
	pScore[6] = Sprite->Create("6", "6.png");
	pScore[7] = Sprite->Create("7", "7.png");
	pScore[8] = Sprite->Create("8", "8.png");
	pScore[9] = Sprite->Create("9", "9.png");

	pPass[0] = Sprite->Create("넘어가기", "넘어가기.png");
	pPass[1] = Sprite->Create("넘어가기2", "넘어가기2.png");
	pVs = Sprite->Create("Vs", "vs.png");
	pST = Sprite->Create("설명", "설명.png");

}

void Game1::Game_Image_Init(Graphics *BackBuffer, bool answer_check, bool Enter_check, DWORD tick)
{

	pVs->Draw(BackBuffer, 0, 550);
	pPass[pass_check]->Draw(BackBuffer, 150, 400);
	pST->Draw(BackBuffer, 0, 0);

	switch (stage)
	{
	case 1:
		strcpy(Qz, stage1);
		pG->Draw(BackBuffer, 180, 250);
		pF->Draw(BackBuffer, 240, 250);
		pD->Draw(BackBuffer, 300, 250);
		break;
	case 2:
		strcpy(Qz, stage2);
		pV->Draw(BackBuffer, 200, 250);
		pE->Draw(BackBuffer, 270, 250);
		break;
	case 3:
		strcpy(Qz, stage3);
		pT->Draw(BackBuffer, 200, 250);
		pW->Draw(BackBuffer, 270, 250);
		break;
	case 4:
		strcpy(Qz, stage4);
		pD->Draw(BackBuffer, 180, 250);
		pT->Draw(BackBuffer, 240, 250);
		pD->Draw(BackBuffer, 300, 250);
		break;
	case 5:
		strcpy(Qz, stage5);
		pR->Draw(BackBuffer, 180, 250);
		pD->Draw(BackBuffer, 240, 250);
		pD->Draw(BackBuffer, 300, 250);
		break;
	case 6:
		strcpy(Qz, stage6);
		pR->Draw(BackBuffer, 180, 250);
		pD->Draw(BackBuffer, 240, 250);
		pW->Draw(BackBuffer, 300, 250);
		break;
	case 7:
		strcpy(Qz, stage7);
		pS->Draw(BackBuffer, 150, 250);
		pA->Draw(BackBuffer, 220, 250);
		pS->Draw(BackBuffer, 290, 250);
		pQ->Draw(BackBuffer, 360, 250);
		break;
	case 8:
		strcpy(Qz, stage8);
		pR->Draw(BackBuffer, 200, 250);
		pF->Draw(BackBuffer, 270, 250);
		break;
	case 9:
		strcpy(Qz, stage9);
		pE->Draw(BackBuffer, 200, 250);
		pW->Draw(BackBuffer, 270, 250);
		break;
	case 10:
		strcpy(Qz, stage10);
		pW->Draw(BackBuffer, 200, 250);
		pT->Draw(BackBuffer, 270, 250);
		break;
	default:
		break;
	}

}
void Game1::Number_Draw(char a, int x, int y, Graphics *BackBuffer)
{
	switch (a)
	{
	case '0':
		pScore[0]->Draw(BackBuffer, x, y);
		break;
	case '1':
		pScore[1]->Draw(BackBuffer, x, y);
		break;
	case '2':
		pScore[2]->Draw(BackBuffer, x, y);
		break;
	case '3':
		pScore[3]->Draw(BackBuffer, x, y);
		break;
	case '4':
		pScore[4]->Draw(BackBuffer, x, y);
		break;
	case '5':
		pScore[5]->Draw(BackBuffer, x, y);
		break;
	case '6':
		pScore[6]->Draw(BackBuffer, x, y);
		break;
	case '7':
		pScore[7]->Draw(BackBuffer, x, y);
		break;
	case '8':
		pScore[8]->Draw(BackBuffer, x, y);
		break;
	case '9':
		pScore[9]->Draw(BackBuffer, x, y);
		break;
	default:
		break;
	}
}

//이기면 1 , 지면 2 , 아직 암꺼도 X , 비기면 3 
int Game1::GameWinCheck(int my_score, int other_score,int my_stage, int other_stage)
{
	int result=0;

	if (GameingCheck(my_score, other_score,my_stage, other_stage) == true) //게임이 끝났다면
	{
		if (my_score > other_score)
			result = 1;
		else if (my_score < other_score)
			result = 2;
		else if (my_score == other_score)
			result = 3;

		return result;
	}
	else
	{
		result = 0;
		return result;
	}
}

//게임 진행 체크 진행중이면 false
bool Game1::GameingCheck(int my_score, int other_score, int my_stage,int other_stage)
{
	if (0 < my_stage&&my_stage <= 10) //게임 진행중
	{
		if (my_score == 7 || other_score == 7)
		{
			return true; //게임 끝났다
		}
		else //게임 진행중
			return false;
	}
	else if(my_stage>10&& other_stage>10)
	{
		return true; //게임 끝났다
	}
}
void Game1::game_Init()
{
	stage = 1;
}