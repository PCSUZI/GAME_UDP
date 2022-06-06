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

	pTitle = pSpriteManager->Create("bird", "타이틀.png");
	pGameStart[0] = pSpriteManager->Create("게임시작1", "게임시작1.png");
	pGameStart[1] = pSpriteManager->Create("게임시작2", "게임시작2.png");

	pGameExit[0] = pSpriteManager->Create("나가기1", "나가기1.png");
	pGameExit[1] = pSpriteManager->Create("나가기2", "나가기2.png");

	pGame_inst_bg = pSpriteManager->Create("배경", "배경.png");
	ptitle = pSpriteManager->Create("방선택", "방선택.png"); ////////////
	pRCP[0] = pSpriteManager->Create("가위바위보", "가위바위보.png");
	pRCP[1] = pSpriteManager->Create("가위바위보2", "가위바위보2.png");
	pEem = pSpriteManager->Create("빈공간", "빈공간.png");
	pGame_inst_RCP = pSpriteManager->Create("가위바위보설명", "가위바위보설명.png");


	pGame_M_Init[0] = pSpriteManager->Create("초성게임1", "초성게임1.png");
	pGame_M_Init[1] = pSpriteManager->Create("초성게임2", "초성게임2.png");
	pGame_inst = pSpriteManager->Create("초성게임 설명", "초성게임설명.png");

	pFriend[1] = pSpriteManager->Create("대기중", "대기중.png");
	pFriend[0] = pSpriteManager->Create("노대기중", "노대기중.png");

	pTwo_player = pSpriteManager->Create("입장완료", "입장완료.png");
	pNo_player = pSpriteManager->Create("노입장", "노입장.png");
	pGame_play = pSpriteManager->Create("겜시작", "겜시작.png");


	pWin = pSpriteManager->Create("승리", "승리.png");
	pLose = pSpriteManager->Create("패배", "패배.png");
	pDraw = pSpriteManager->Create("비김", "비김.png");
	pPick = pSpriteManager->Create("당첨", "당첨.png");
	pWait[0] = pSpriteManager->Create("친구기다림1", "친구기다림1.png");
	pWait[1] = pSpriteManager->Create("친구기다림2", "친구기다림2.png");


	//새로 추가
	pdbc[0] = pSpriteManager->Create("윷놀이제목1", "윷놀이제목1.png");
	pdbc[1] = pSpriteManager->Create("윷놀이제목2", "윷놀이제목2.png");
	pdbc_inst = pSpriteManager->Create("윷놀이설명", "윷놀이설명.png");

	pTouchG[0] = pSpriteManager->Create("순발력게임1", "순발력게임1.png");
	pTouchG[1] = pSpriteManager->Create("순발력게임2", "순발력게임2.png");

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

	//윷놀이 메뉴
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