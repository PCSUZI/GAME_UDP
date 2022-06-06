#include "Game3.h"



Game3::Game3()
{
	Dice_sprite = 0;
	Dice_Number=0;
	Info_Other.Dice = 0;
	Info_Player.Dice = 1;

	float SetX = 0;
	float SetY = 672;

	bool dec = true;

	for (int i = 1; i <= 101; i++)
	{
		Board[i].x = SetX;
		Board[i].y = SetY;

		if (i == 10)
			SetX -= 60, SetY -= 74.7;
		if (i == 11)
			dec = false;
		if (i == 20)
			SetX += 60, SetY -= 74.7;
		if (i == 21)
			dec = true;
		if (i == 30)
			SetX -= 60, SetY -= 74.7;
		if (i == 31)
			dec = false;
		if (i == 40)
			SetX += 60, SetY -= 74.7;
		if (i == 41)
			dec = true;
		if (i == 50)
			SetX -= 60, SetY -= 74.7;
		if (i == 51)
			dec = false;
		if (i == 60)
			SetX += 60, SetY -= 74.7;
		if (i == 61)
			dec = true;
		if (i == 70)
			SetX -= 60, SetY -= 74.7;
		if (i == 71)
			dec = false;
		if (i == 80)
			SetX += 60, SetY -= 74.7;
		if (i == 81)
			dec = true;
		if (i == 90)
			SetX -= 60, SetY -= 74.7;
		if (i == 91)
			dec = false;


		if (dec == true)
			SetX += 60;
		if (dec == false)
			SetX -= 60;

	}
	Board[1].move = 0;
	Board[4].move = 16;
	Board[8].move = 12;
	Board[18].move = 38;
	Board[20].move = 74;
	Board[22].move = 2;
	Board[24].move = 36;
	Board[28].move = 6;
	Board[30].move = 10;
	Board[32].move = 56;
	Board[34].move = 46;
	Board[40].move = 60;
	Board[44].move = 26;
	Board[48].move = 54;
	Board[58].move = 42;
	Board[66].move = 14;
	Board[68].move = 52;
	Board[70].move = 88;
	Board[72].move = 50;
	Board[76].move = 86;
	Board[80].move = 100;
	Board[84].move = 62;
	Board[90].move = 92;
	Board[94].move = 64;
	Board[96].move = 82;
	Board[98].move = 78;
}


Game3::~Game3()
{
}

void Game3::GameImageLoding()
{
	dsSpriteManager *Sprite = GetSpriteManager();

	pboard = Sprite->Create("¹ìÁÖ»çÀ§º¸µå", "¹ìÁÖ»çÀ§º¸µå.png");
	pPlayer = Sprite->Create("¸»_°³", "¸»_°³.png");
	pOther = Sprite->Create("¸»_µÅÁö", "¸»_µÅÁö.png");

	pDice[0] = Sprite->Create("dice1", "dice1.png");
	pDice[1] = Sprite->Create("dice2", "dice2.png");
	pDice[2] = Sprite->Create("dice3", "dice3.png");
	pDice[3] = Sprite->Create("dice4", "dice4.png");
	pDice[4] = Sprite->Create("dice5", "dice5.png");
	pDice[5] = Sprite->Create("dice6", "dice6.png");
	pDice[6] = Sprite->Create("dice7", "dice7.png");
	pDice[7] = Sprite->Create("dice8", "dice8.png");
	pDice[8] = Sprite->Create("dice9", "dice9.png");
	pDice[9] = Sprite->Create("dice10", "dice10.png");

	pWho[0] = Sprite->Create("³»Â÷·Ê", "³»Â÷·Ê.png");
	pWho[1] = Sprite->Create("Ä£±¸Â÷·Ê", "Ä£±¸Â÷·Ê.png");

	pDiceNumber[0] = Sprite->Create("00", "00.png");
	pDiceNumber[1] = Sprite->Create("1", "1.png");
	pDiceNumber[2] = Sprite->Create("2", "2.png");
	pDiceNumber[3] = Sprite->Create("3", "3.png");
	pDiceNumber[4] = Sprite->Create("4", "4.png");
	pDiceNumber[5] = Sprite->Create("5", "5.png");
	pDiceNumber[6] = Sprite->Create("6", "6.png");
}

void Game3::Game_Image_Init(Graphics *BackBuffer)
{
	pboard->Draw(BackBuffer, 0, 0);
	pOther->Draw(BackBuffer, Info_Other.x, Info_Other.y);
	pPlayer->Draw(BackBuffer, Info_Player.x, Info_Player.y);

	pDice[Dice_sprite]->Draw(BackBuffer, 0, 730);

	pWho[Info_Player.Dice]->Draw(BackBuffer, 400, 750);

	pDiceNumber[Dice_Number]->Draw(BackBuffer, 80, 740);
}

void Game3::Info_Setting()
{
	
	Info_Other.x = Board[Info_Other.score].x;
	Info_Other.y = Board[Info_Other.score].y;

	Info_Player.x = Board[Info_Player.score].x;
	Info_Player.y = Board[Info_Player.score].y;
}

void  Game3::Board_xy(int My_score, int friend_score)
{
	Info_Other.score = friend_score;
	Info_Player.score = My_score;

	Info_Setting();
}

void Game3::Board_Move()
{
	if (Board[Info_Player.score].move != 0)
	{
		Info_Player.score = Board[Info_Player.score].move;

		Info_Player.x = Board[Info_Player.score].x;
		Info_Player.y = Board[Info_Player.score].y;
	}
}

void Game3::Dice_set(int dice)
{
	Info_Player.Dice = dice;
}