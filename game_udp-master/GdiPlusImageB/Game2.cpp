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

	pbg = Sprite->Create("��������������", "��������������.png");
	pRCP[0][0] = Sprite->Create("����", "����.png");
	pRCP[0][1] = Sprite->Create("��������", "��������.png");

	pRCP[1][0] = Sprite->Create("����", "����.png");
	pRCP[1][1] = Sprite->Create("��������", "��������.png");

	pRCP[2][0] = Sprite->Create("��", "��.png");
	pRCP[2][1] = Sprite->Create("������", "������.png");
}
void Game2::Game_Image_Init(Graphics *BackBuffer) //0�϶� �Ϲ�
{
	pbg->Draw(BackBuffer, 0, 0);

	pRCP[0][0]->Draw(BackBuffer, 0, 250);
	pRCP[1][0]->Draw(BackBuffer, 200, 250);
	pRCP[2][0]->Draw(BackBuffer, 400, 250);

	if (0 <= my_choic&&my_choic<3)
		pRCP[my_choic][1]->Draw(BackBuffer, 200, 500);


}

//0 = �ƹ�����X , 1 = �̱� , 2 = �� , 3 = ��� 
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