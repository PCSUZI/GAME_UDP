#pragma once
#include "dsSpriteManager.h"

//enum class EGame3_State { Null_Game = 0,  = 1, RCP_Game = 2, DBC_Game = 3 };
struct Char_info
{
	float x=0, y=672;
	int score;
	int Dice;
};
struct Stage_info
{
	float x = 0, y = 672;
	int move=0;
};

class Game3
{
public:
	Game3();
	~Game3();

	//보드
	dsSprite *pboard;
	//주사위
	dsSprite *pDice[10];
	dsSprite *pDiceNumber[7];
	int Dice_sprite;
	int Dice_Number;


	//차례알림이
	dsSprite *pWho[2];

	//말
	dsSprite *pPlayer;
	dsSprite *pOther;

	//말 정보
	Char_info Info_Player;
	Char_info Info_Other;


	//스테이지
	Stage_info Board[101];

	void GameImageLoding();
	void Game_Image_Init(Graphics *BackBuffer);
	
	void Info_Setting();
	void Board_xy(int My_score, int friend_score);
	void Board_Move();
	void Dice_set(int dice);

};

