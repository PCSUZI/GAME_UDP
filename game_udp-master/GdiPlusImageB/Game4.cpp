#include "Game4.h"



Game4::Game4()
{
	game_over = false;
	Item_Y = -50;
}


Game4::~Game4()
{
}

void Game4::GameImageLoding()
{
	dsSpriteManager *Sprite = GetSpriteManager();

	ppScore[0] = Sprite->Create("00", "0.png");
	ppScore[1] = Sprite->Create("11", "1.png");
	ppScore[2] = Sprite->Create("22", "2.png");
	ppScore[3] = Sprite->Create("33", "3.png");
	ppScore[4] = Sprite->Create("44", "4.png");
	ppScore[5] = Sprite->Create("55", "5.png");
	ppScore[6] = Sprite->Create("66", "6.png");
	ppScore[7] = Sprite->Create("77", "7.png");
	ppScore[8] = Sprite->Create("88", "8.png");
	ppScore[9] = Sprite->Create("99", "9.png");

	pVs = Sprite->Create("Vs", "vs.png");

	pBag = Sprite->Create("바구니", "바구니.png");
	pItem = Sprite->Create("사과", "사과.png");

}
void Game4::Game_Image_Init(Graphics *BackBuffer)
{
	pVs->Draw(BackBuffer, 0, 400);
	pBag->Draw(BackBuffer, Bag_X, 700);
}

void Game4::OnUpdateTime(DWORD tick, Graphics *BackBuffer)
{
	if (g_time <= 0) {
		game_over = true;
		return;
	}

	static DWORD interval = 0;

	interval += tick;
	if (interval >= 1000)
	{
		g_time--;
		interval -= 1000;
	}

	char imgIndex[2];
	imgIndex[0] = g_time / 10;
	imgIndex[1] = g_time % 10;


	int _x = 240;

	for (int i = 0; i < 2; i++)
	{
		ppScore[imgIndex[i]]->Draw(BackBuffer, _x, 10, 80, 80);
		_x += 70;
	}
}

void Game4::Number_Draw(int a, int x, int y, Graphics *BackBuffer)
{
	switch (a)
	{
	case 0:
		ppScore[0]->Draw(BackBuffer, x, y);
		break;
	case 1:
		ppScore[1]->Draw(BackBuffer, x, y);
		break;
	case 2:
		ppScore[2]->Draw(BackBuffer, x, y);
		break;
	case 3:
		ppScore[3]->Draw(BackBuffer, x, y);
		break;
	case 4:
		ppScore[4]->Draw(BackBuffer, x, y);
		break;
	case 5:
		ppScore[5]->Draw(BackBuffer, x, y);
		break;
	case 6:
		ppScore[6]->Draw(BackBuffer, x, y);
		break;
	case 7:
		ppScore[7]->Draw(BackBuffer, x, y);
		break;
	case 8:
		ppScore[8]->Draw(BackBuffer, x, y);
		break;
	case 9:
		ppScore[9]->Draw(BackBuffer, x, y);
		break;
	default:
		break;
	}
}


void Game4::Bag_set(int x, Graphics *BackBuffer)
{
	Bag_X = x;
}


void Game4::Apple_set(Graphics *BackBuffer)
{

}