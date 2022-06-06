#include "Myfunction.h"
#include "main.c[["

Estate State; 
EGame GameType;

dsSprite *g_Title;
dsSprite *g_gamestart[2];
dsSprite *g_gameExit[2];


//초기화
void Init()
{
	dsSpriteManager *pSpriteManager = GetSpriteManager();

	State = Estate::Intro;
	GameType = EGame::Null_Game;

	g_Title = pSpriteManager->Create("bird", "타이틀.png");
	g_gamestart[0] = pSpriteManager->Create("text", "게임시작1.png");
	g_gamestart[1] = pSpriteManager->Create("text", "게임시작2.png");
	
}
void Remove()
{

}


//그리기 담당 함수
void My_Game_Draw()
{
	switch (State)
	{
	case Estate::Intro:
		g_Title->Draw(g_BackBuffer, user[i].xPos, user[i].yPos);
		break;
	case Estate::GameSelect:
		break;
	case Estate::GameLoding:
		break;
	case Estate::Game:
		break;
	case Estate::GameWin:
		break;
	case Estate::GameOver:
		break;
	default:
		break;
	}
}

//마우스 값 
void MouseMove(int x, int y)
{

}
void MouseClick(int x, int y)
{

}

//키보드 값