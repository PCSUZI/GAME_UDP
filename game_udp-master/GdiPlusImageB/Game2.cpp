#include "Game2.h"



Game2::Game2()
{
}


Game2::~Game2()
{
}

void Game2::GameImageLoding()
{
	dsSpriteManager *Sprite = GetSpriteManager();

	pbg = Sprite->Create("가위바위보게임", "가위바위보게임.png");
	pRCP[0][0] = Sprite->Create("가위", "가위.png");
	pRCP[0][1] = Sprite->Create("가위선택", "가위선택.png");

	pRCP[1][0] = Sprite->Create("바위", "바위.png");
	pRCP[1][1] = Sprite->Create("바위선택", "바위선택.png");

	pRCP[2][0] = Sprite->Create("보", "보.png");
	pRCP[2][1] = Sprite->Create("보선택", "보선택.png");
}
void Game2::Game_Image_Init(Graphics *BackBuffer) //0일때 일반
{
	pbg->Draw(BackBuffer, 0, 0);

	pRCP[0][0]->Draw(BackBuffer, 0, 250);
	pRCP[1][0]->Draw(BackBuffer, 200, 250);
	pRCP[2][0]->Draw(BackBuffer, 400, 250);

	if (0 <= my_choic&&my_choic<3)
		pRCP[my_choic][1]->Draw(BackBuffer, 200, 500);


}

//0 = 아무상태X , 1 = 이김 , 2 = 짐 , 3 = 비김 
int Game2::GameWinCheck(int my_c, int other_c)
{
	int result = 0;

	(my_c == other_c) ? (result = 3) : (((my_c + 1) % 3 == other_c) ? (result = 2) : (result = 1));

	return result;

}

void Game2::Game_Init()
{
	my_choic = 3;
}