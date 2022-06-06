#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

#include "MyRect.h"
#include "GameIntro.h"
#include "Game1.h"
#include "Game2.h"
#include "Game3.h"
#include "Game4.h"
#include "Game3_Item.h"

#define PLAYER_ME		0 //0번 배열에는 내정보 
#define PLAYER_OTHER	1 // 1번 배열에는 상대방 정보 

#define Game_TIME 1

//게임 플레이 상태 체크
enum class Estate { Intro = 0, GameSelect = 1, GameLoding = 2, Game = 3, GameWin = 4, GameOver = 5, GameDraw = 6 };
enum class EGame { Null_Game = 0, Initial_Game = 1, RCP_Game = 2, Snack_Game = 3, Touch_Game = 4 };


//메인 게임 상태 클래스 
Estate State;
EGame Game_Type;

//게임 클래스 모음
GameIntro C_gameIntro;
Game1 Initial_Game;
Game2 RCP_Game;
Game3 Snack_Game;
Game4 Touch_Game;
Game3_Item item[5];



Graphics *g_BackBuffer;
Graphics *g_MainBuffer;
Bitmap   *g_Bitmap;


bool answer_check;
bool check_Enter;
bool Dice_check;
bool Dice_Music_check;
bool Move_check;

char Score_My_char[2];
char Score_Other_char[2];

char my_stage[2];

DWORD g_balloonCount;

struct Snake_Game_User
{
	int score=1;
	int Dice; // 0 == 내차례 ( Dice =true )  , 1 == 친구차례 Dice =flase 
};
Snake_Game_User Snake_User[2];

int Game4_score[2];

//초기화 , 이미지 로딩
void Init()
{
	State = Estate::Intro;
	Game_Type = EGame::Null_Game;

	C_gameIntro.GameImageLoding();
	Initial_Game.GameImageLoding();
	RCP_Game.GameImageLoding();
	Snack_Game.GameImageLoding();
	Touch_Game.GameImageLoding();
	
	for (int i = 0; i < 5; i++)
	{
		item[i].GameImageLoding();
	}
	
	g_balloonCount = GetTickCount();

	Snake_User[PLAYER_ME].Dice = 0;
	Snake_User[PLAYER_OTHER].Dice = 1;

	item[0].srcX = 100;
	item[1].srcX = 300;
	item[2].srcX = 200;
	item[3].srcX = 400;
	item[4].srcX = 100;
	item[0].srcY = -100;
	item[1].srcY = -300;
	item[2].srcY = -600;
	item[3].srcY = -400;
	item[4].srcY = -100;
}

//그리기 담당 함수
void My_Game_Draw(DWORD tick)
{
	switch (State)
	{
	case Estate::Intro:
	{
		C_gameIntro.Game_Image_Init(g_BackBuffer);
	}
	break;
	case Estate::GameSelect:
	{
		C_gameIntro.Game_Select_Draw(g_BackBuffer);
	}
	break;
	case Estate::GameLoding:
		break;
	case Estate::Game:
		switch (Game_Type)
		{
		case EGame::Null_Game:
			break;

		case EGame::Touch_Game:

		
	
		/*for (int i = 0; i < 5; i++)
			item[i].Loding();
*/
		for (int i = 0; i < 5; i++)
			item[i].Apple_set(g_BackBuffer);

		Touch_Game.Number_Draw(Game4_score[PLAYER_ME] / 10, 50, 450, g_BackBuffer);
		Touch_Game.Number_Draw(Game4_score[PLAYER_ME] % 10, 100, 450, g_BackBuffer);

		Touch_Game.Number_Draw(Game4_score[PLAYER_OTHER] / 10, 450, 450, g_BackBuffer);
		Touch_Game.Number_Draw(Game4_score[PLAYER_OTHER] % 10, 500, 450, g_BackBuffer);

	
			for (int i = 0; i<5; i++)
				item[i].move();

		
		for (int i = 0; i < 5; i++)
		{
			if (MyRect::Collision(item[i].srcX, item[i].srcY, Touch_Game.Bag_X, 700, 150, 78))
			{
				item[i].is_Draw = false;
				Game4_score[PLAYER_ME] += 1;

			}
			if (item[i].is_Draw == false)
				item[i].reset(tick);
		}

		for (int i = 0; i < 5; i++)
			if (item[i].srcY >= 700)
			{
				item[i].reset(tick);
			}


			Touch_Game.Game_Image_Init(g_BackBuffer);


			break;
		case EGame::Initial_Game:
			itoa(Initial_Game.stage, my_stage, 10);

			Initial_Game.Game_Image_Init(g_BackBuffer, answer_check, check_Enter);
			Initial_Game.Number_Draw(Score_My_char[0], 50, 650, g_BackBuffer);
			Initial_Game.Number_Draw(Score_My_char[1], 100, 650, g_BackBuffer);
			Initial_Game.Number_Draw(Score_Other_char[0], 450, 650, g_BackBuffer);
			Initial_Game.Number_Draw(Score_Other_char[1], 500, 650, g_BackBuffer);

			Initial_Game.Number_Draw(my_stage[0], 470, 0, g_BackBuffer);
			Initial_Game.Number_Draw(my_stage[1], 520, 0, g_BackBuffer);
			break;
		case EGame::RCP_Game:
			RCP_Game.Game_Image_Init(g_BackBuffer);
			break;
		case EGame::Snack_Game:
			Snack_Game.Game_Image_Init(g_BackBuffer);
			break;
		default:
			break;
		}

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
	switch (State)
	{
	case Estate::Intro:
		if (MyRect::Collision(x, y, 200, 500, 200, 64))
			C_gameIntro.start_check = 1;
		else
			C_gameIntro.start_check = 0;


		if (MyRect::Collision(x, y, 200, 600, 200, 64))
			C_gameIntro.Exit_check = 1;
		else
			C_gameIntro.Exit_check = 0;




		break;
	case Estate::GameSelect:
		if (MyRect::Collision(x, y, 10, 100, 258, 68))
			C_gameIntro.G_init_check = 1;
		else
			C_gameIntro.G_init_check = 0;

		if (MyRect::Collision(x, y, 0, 200, 258, 68))/////////////////
			C_gameIntro.G_RCP_check = 1;
		else
			C_gameIntro.G_RCP_check = 0;

		//뱀게임 제목 클릭 추가
		if (MyRect::Collision(x, y, 0, 300, 258, 68))
			C_gameIntro.G_dbc_check = 1;
		else
			C_gameIntro.G_dbc_check = 0;

		//뱀게임 제목 클릭 추가
		if (MyRect::Collision(x, y, 0, 400, 258, 68))
			C_gameIntro.G_touch_check = 1;
		else
			C_gameIntro.G_touch_check = 0;

		break;
	case Estate::GameLoding:
		break;
	case Estate::Game:
		switch (Game_Type)
		{
		case EGame::Null_Game:
			break;
		case EGame::Touch_Game:
			Touch_Game.Bag_set(x-70, g_BackBuffer);
			break;
		case EGame::Snack_Game:
		{
			if (MyRect::Collision(x, y, 0, 730, 71, 94))
			{


				if (Snake_User[PLAYER_ME].Dice == 0)
				{
					Dice_check = true;
					Snack_Game.Dice_Number = 0;

					Snack_Game.Dice_sprite++;
					if (Snack_Game.Dice_sprite == 9)
						Snack_Game.Dice_sprite = 0;
				}
			}
			else
			{
				Dice_check = false;
				Snack_Game.Dice_sprite = 0;
			}
		}
		break;
		case EGame::Initial_Game:
			if (MyRect::Collision(x, y, 180, 400, 249, 86))
				Initial_Game.pass_check = 1;
			else
				Initial_Game.pass_check = 0;
			break;
		default:
			break;
		}
		break;
	case Estate::GameWin:
		break;
	case Estate::GameOver:
		break;
	default:
		break;
	}

}
void MouseClick(int x, int y)
{
	switch (State)
	{
	case Estate::Intro:
		if (MyRect::Collision(x, y, 200, 500, 200, 64))
			State = Estate::GameSelect;


		if (MyRect::Collision(x, y, 200, 600, 200, 64))
			exit(1);


		break;
	case Estate::GameSelect:
		if (MyRect::Collision(x, y, 10, 100, 258, 68))
		{
			State = Estate::GameLoding;
			Game_Type = EGame::Initial_Game;
		}

		if (MyRect::Collision(x, y, 0, 200, 258, 68))/////////////////
		{
			State = Estate::GameLoding;
			Game_Type = EGame::RCP_Game;
		}

		if (MyRect::Collision(x, y, 0, 300, 258, 68))
		{
			State = Estate::GameLoding;
			Game_Type = EGame::Snack_Game;
		}

		if (MyRect::Collision(x, y, 0, 400, 258, 68))
		{
			State = Estate::GameLoding;
			Game_Type = EGame::Touch_Game;
		}

		break;
	case Estate::GameLoding:
		State = Estate::GameSelect;
		Game_Type = EGame::Null_Game;
		break;
	case Estate::Game:
		switch (Game_Type)
		{
		case EGame::Null_Game:
			break;
		case EGame::Touch_Game:
			break;
		case EGame::Snack_Game:
			if (MyRect::Collision(x, y, 0, 730, 71, 94))
			{

				if (Snake_User[PLAYER_ME].Dice == 0)
				{
					Move_check = true;
					srand(time(NULL));
					Snack_Game.Dice_Number = 1 + rand() % 6;
					Snake_User[PLAYER_ME].score += Snack_Game.Dice_Number;

					Snack_Game.Board_xy(Snake_User[PLAYER_ME].score, Snake_User[PLAYER_OTHER].score);

					Snake_User[PLAYER_ME].Dice = 1;
					Snack_Game.Dice_set(Snake_User[PLAYER_ME].Dice);
				}
				else
				{
					Move_check = false;
				}
			
			}

			break;
		case EGame::Initial_Game:
			if (MyRect::Collision(x, y, 180, 400, 249, 86))
				Initial_Game.stage++;
			break;
		case EGame::RCP_Game:
			if (MyRect::Collision(x, y, 0, 250, 173, 173))
				RCP_Game.my_choic = 0;
			if (MyRect::Collision(x, y, 200, 250, 173, 173))
				RCP_Game.my_choic = 1;
			if (MyRect::Collision(x, y, 400, 250, 173, 173))
				RCP_Game.my_choic = 2;
			break;
		default:
			break;
		}
		break;
	case Estate::GameWin:
		State = Estate::Intro;
		break;
	case Estate::GameOver:
		State = Estate::Intro;
		break;
	case Estate::GameDraw:
		State = Estate::Intro;
		break;
	default:
		break;
	}
}

//키보드 값

//종료
void Remove()
{

}


