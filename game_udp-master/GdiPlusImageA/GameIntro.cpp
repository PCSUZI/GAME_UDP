#include "GameIntro.h"



GameIntro::GameIntro()
{
}


GameIntro::~GameIntro()
{
}

void GameIntro::GameImageLoding()
{

	dsSpriteManager *pSpriteManager = GetSpriteManager();

	pTitle = pSpriteManager->Create("bird", "Ÿ��Ʋ.png");
	pGameStart[0] = pSpriteManager->Create("���ӽ���1", "���ӽ���1.png");
	pGameStart[1] = pSpriteManager->Create("���ӽ���2", "���ӽ���2.png");

	pGameExit[0] = pSpriteManager->Create("������1", "������1.png");
	pGameExit[1] = pSpriteManager->Create("������2", "������2.png");

	pGame_inst_bg = pSpriteManager->Create("���", "���.png");
	ptitle = pSpriteManager->Create("�漱��", "�漱��.png"); ////////////
	pRCP[0] = pSpriteManager->Create("����������", "����������.png");
	pRCP[1] = pSpriteManager->Create("����������2", "����������2.png");
	pEem = pSpriteManager->Create("�����", "�����.png");
	pGame_inst_RCP = pSpriteManager->Create("��������������", "��������������.png");


	pGame_M_Init[0] = pSpriteManager->Create("�ʼ�����1", "�ʼ�����1.png");
	pGame_M_Init[1] = pSpriteManager->Create("�ʼ�����2", "�ʼ�����2.png");
	pGame_inst = pSpriteManager->Create("�ʼ����� ����", "�ʼ����Ӽ���.png");

	pFriend[1] = pSpriteManager->Create("�����", "�����.png");
	pFriend[0] = pSpriteManager->Create("������", "������.png");

	pTwo_player = pSpriteManager->Create("����Ϸ�", "����Ϸ�.png");
	pNo_player = pSpriteManager->Create("������", "������.png");
	pGame_play = pSpriteManager->Create("�׽���", "�׽���.png");


	pWin = pSpriteManager->Create("�¸�", "�¸�.png");
	pLose = pSpriteManager->Create("�й�", "�й�.png");
	pDraw = pSpriteManager->Create("���", "���.png");
	pPick = pSpriteManager->Create("��÷", "��÷.png");
	pWait[0] = pSpriteManager->Create("ģ����ٸ�1", "ģ����ٸ�1.png");
	pWait[1] = pSpriteManager->Create("ģ����ٸ�2", "ģ����ٸ�2.png");


	//���� �߰�
	pdbc[0] = pSpriteManager->Create("����������1", "����������1.png");
	pdbc[1] = pSpriteManager->Create("����������2", "����������2.png");
	pdbc_inst = pSpriteManager->Create("�����̼���", "�����̼���.png");

	pTouchG[0] = pSpriteManager->Create("���߷°���1", "���߷°���1.png");
	pTouchG[1] = pSpriteManager->Create("���߷°���2", "���߷°���2.png");

}

void GameIntro::Game_Image_Init(Graphics *BackBuffer)
{
	pTitle->Draw(BackBuffer, 0, 0);
	pGameStart[start_check]->Draw(BackBuffer, 200, 500);
	pGameExit[Exit_check]->Draw(BackBuffer, 200, 600);
}

void GameIntro::Game_Select_Draw(Graphics *BackBuffer)
{
	

	pGame_M_Init[G_init_check]->Draw(BackBuffer, 0, 100);
	pGame_inst_bg->Draw(BackBuffer, 300, 100);

	ptitle->Draw(BackBuffer, 180, 20);////////////
	pRCP[G_RCP_check]->Draw(BackBuffer, 0, 200);

	//������ �޴�
	pdbc[G_dbc_check]->Draw(BackBuffer, 0, 300);

	pTouchG[G_touch_check]->Draw(BackBuffer, 0, 400);

	if (G_RCP_check == 1)
		pGame_inst_RCP->Draw(BackBuffer, 330, 100);


	if (G_init_check == 1)
		pGame_inst->Draw(BackBuffer, 330, 100);

	if (G_dbc_check == 1)
		pdbc_inst->Draw(BackBuffer, 300, 100);


		
	pEem->Draw(BackBuffer, 10, 500);
}

void GameIntro::Friend_OK(Graphics *BackBuffer)
{
	pFriend[1]->Draw(BackBuffer, 330, 400);
}
void GameIntro::Friend_NO(Graphics *BackBuffer)
{
	pFriend[0]->Draw(BackBuffer, 330, 400);
}