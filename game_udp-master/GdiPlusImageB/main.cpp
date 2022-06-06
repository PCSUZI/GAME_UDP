#include <winsock2.h>
#include "CirQueue.h"
#include "MyImage.h"
#include "dsSpriteManager.h"
#include "dsOpenALSoundManager.h"
#include "MyDraw.h"
#include "resource.h"



#pragma comment(lib, "ws2_32")

#define WM_SOCKET (WM_USER+1)
SOCKET g_hSocket = INVALID_SOCKET;


dsSound *pSound[4];
CCirQueue g_CirQueue;

static char szEditBox[20]; //사용자로 입력





struct USER
{
	char answer[20];
	int Score;
	int State;
	int Game_type;
	int Game1_stage;

	int Game2_choic=3;
};
USER user[2];
int g_curUserCount = 1;



SOCKADDR_IN g_ToClientaddr; //내가 보내고자 하는 상대방의 주소 

void OnUpdate(HWND hWnd, DWORD tick);
void CreateBuffer(HWND hWnd, HDC hDC);
void ReleaseBuffer(HWND hWnd, HDC hDC);

void OnPacket(PACKETHEADER *pHeader);

BOOL CreateSocket(HWND hWnd);
void ReleaseSocket();

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,     int nCmdShow)
{
	WNDCLASS   wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wndclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = "HelloWin";
	
	if(RegisterClass(&wndclass) == 0)
	{
		return 0;		
	}

	HWND hwnd = CreateWindow("HelloWin", "친구랑 하는 게임!!", 
                              WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT, CW_USEDEFAULT, 
		620, 850,
                              NULL, NULL, hInstance, NULL);

	if(hwnd == NULL)
	{
		return 0;
	}

	dsOpenALSoundManager *pSoundManger = GetOpenALSoundManager();
	pSound[0] = pSoundManger->LoadSound("클릭.wav", false);
	pSound[1] = pSoundManger->LoadSound("주사위.wav", true);
	pSound[2] = pSoundManger->LoadSound("큰이동.wav", false);
	pSound[3] = pSoundManger->LoadSound("이동.wav", false);

		user[PLAYER_ME].State = (int)State;
		user[PLAYER_ME].Game_type = (int)Game_Type;


	HDC hDC = GetDC(hwnd);

	CreateBuffer(hwnd, hDC);
	CreateSocket(hwnd);

	Init();

	


	ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

	MSG msg;
	DWORD tick = GetTickCount(); //저 함수가 호출되는 시점에 윈도우가 호출되는 숫자 
	while(1)
	{	
		//윈도우 메세지가 있을경우 메세지를 처리한다.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) //소켓 이벤트
		{
			if(msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else //메세지가 없을 경우 게임 루프를 실행한다.
		{		//여기서 겜 만드는거임 
			DWORD curTick = GetTickCount(); //얘가 더 나중 카운트값 

			Color color(255, 255, 255);
			g_BackBuffer->Clear(color);

			My_Game_Draw(curTick - tick);

			OnUpdate(hwnd, curTick - tick); //시간이 얼마나 갔는지에 대한 체크 --> 한바퀴 돌았을때 걸리는시간 넣어주는거임 ( curTick-tick) 이거 계속 저장하면 몇초 저장했는지 알 수 있음
			tick = curTick; // 얘 넣어줘서 한바퀴 

		
			g_MainBuffer->DrawImage(g_Bitmap, 0, 0);
		}
	}
	ReleaseSocket();
	ReleaseBuffer(hwnd, hDC);

	return 0;
}

//소켓 관련 윈도우 메시지 처리
void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 오류 발생 여부 확인
	if (WSAGETSELECTERROR(lParam))
	{
		//err_display(WSAGETSELECTERROR(lParam));
		return;
	}

	// 메시지 처리
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
	{
		#define BUFSIZE   1024
		char buf[BUFSIZE];
		int len=sizeof(SOCKADDR_IN);
		SOCKADDR_IN clientAddr;

		int ret = recvfrom(wParam, buf, BUFSIZE, 0,(sockaddr *)&clientAddr,&len);
		if (ret == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{

			}
			break;
		}	
		g_CirQueue.OnPutData(buf, ret);
		PACKETHEADER *pHeader = g_CirQueue.GetPacket();
		while (pHeader != NULL)
		{
			OnPacket(pHeader);

			g_CirQueue.OnPopData(pHeader->PktSize);
			pHeader = g_CirQueue.GetPacket();
		}

	}
	break;
	case FD_CLOSE:
	{
		closesocket(wParam);
	}
	break;
	}
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_CHAR:
	{

		int nKey;
		nKey = (int)wParam;


		if (nKey == VK_BACK)
		{
			szEditBox[strlen(szEditBox) - 1] = '\0';
		}


		if (nKey == VK_RETURN)
		{
			check_Enter = true;
			strcpy(user[PLAYER_ME].answer, szEditBox);
			strcpy(szEditBox, ""); //초기화

			if (strcmp(user[PLAYER_ME].answer, Initial_Game.Qz) == 0) //같다면
			{
				user[PLAYER_ME].Score++;
				answer_check = true;
				Initial_Game.stage ++;
			}
			else
				answer_check = false;


		}
		else
			sprintf(szEditBox, "%s%c", szEditBox, (char)nKey);
	}
	break;
	case WM_LBUTTONDOWN:
		{		
			if (pSound)
			{
				pSound[0]->Play();
			}

			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			MouseClick(x, y);

			switch (State)
			{
			case Estate::Intro:
				break;
			case Estate::GameSelect:
				break;
			case Estate::GameLoding:
				break;
			case Estate::Game:
				switch (Game_Type)
				{
				case EGame::Null_Game:
					break;
				case EGame::Initial_Game:
					break;
				case EGame::RCP_Game:
					break;
				case EGame::Snack_Game:
					ST_GAME3 S_game3;
					S_game3.score = Snake_User[PLAYER_ME].score;
					S_game3.Dice = Snake_User[PLAYER_ME].Dice;
					S_game3.PktID = PKT_GAME3;
					S_game3.PktSize = sizeof(ST_GAME3);

					sendto(g_hSocket, (char*)&S_game3, S_game3.PktSize, 0, (sockaddr *)&g_ToClientaddr, sizeof(g_ToClientaddr));
					if (pSound)
					{
						if (Move_check)
						pSound[3]->Play();
					}

					break;
				default:
					break;
				}
				break;
			case Estate::GameWin:
				break;
			case Estate::GameOver:
				break;
			case Estate::GameDraw:
				break;
			default:
				break;
			}

			user[PLAYER_ME].State = (int)State;
			user[PLAYER_ME].Game_type = (int)Game_Type;

			ST_READY ready;
			ready.PktID = PKT_READY;
			ready.PktSize = sizeof(ST_READY);
			ready.State = user[PLAYER_ME].State;
			ready.Game_type = user[PLAYER_ME].Game_type;

			int retval = sendto(g_hSocket, (char *)&ready, ready.PktSize, 0, (sockaddr*)&g_ToClientaddr, sizeof(g_ToClientaddr)); //( 소컷 , 내가 보내보자하는 데이터 , 데이터의 길이 , 0 , 상대방의 주소, 주소의 크기 ) 
			if (retval == SOCKET_ERROR)
			{
				//	::MessageBox(hWnd, "SEND ERROR!", "ERROR", MB_ICONSTOP | MB_OK);
			}

		
		}
		break;
	case WM_KEYDOWN:
		{
			
		}
		break;
	case WM_CREATE:
		break;
	case WM_MOUSEMOVE:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		MouseMove(x, y);
	}
	case WM_SOCKET: // 소켓 관련 윈도우 메시지
		ProcessSocketMessage(hWnd, msg, wParam, lParam);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}


	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void CreateBuffer(HWND hWnd, HDC hDC)
{
	GdiplusStartupInput			gdiplusStartupInput;
	ULONG_PTR					gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	RECT rc;
	GetClientRect(hWnd, &rc);

	g_Bitmap = new Bitmap(rc.right - rc.left, rc.bottom - rc.top);
	g_BackBuffer = new Graphics(g_Bitmap);
	g_BackBuffer->SetPageUnit(Gdiplus::Unit::UnitPixel);
	
	g_MainBuffer = new Graphics(hDC);
	g_MainBuffer->SetPageUnit(Gdiplus::Unit::UnitPixel);
}

void ReleaseBuffer(HWND hWnd, HDC hDC)
{
	ReleaseDC(hWnd, hDC);

	delete g_Bitmap;
	delete g_BackBuffer;
	delete g_MainBuffer;
}

BOOL CreateSocket(HWND hWnd)
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return FALSE;

	// socket()
	g_hSocket = socket(AF_INET, SOCK_DGRAM, 0); //UDP 소켓으로 변경
	if (g_hSocket == INVALID_SOCKET)
	{
		::MessageBox(hWnd, "INVALID SOCKET!", "ERROR", MB_ICONSTOP | MB_OK);		
		return FALSE;
	}

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(40000);//나는 사만번
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//내가 연결할 서버의 ip와 포트번호  //connect 없셈 
	int retval= bind(g_hSocket, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		::MessageBox(hWnd, "BIND ERROR!", "ERROR", MB_ICONSTOP | MB_OK);
		return FALSE;
	}

	retval = WSAAsyncSelect(g_hSocket, hWnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE); //WSAAsyncSelect함수로 비동기 방식으로 만든거임 , 소켓 잘 들어왔으면 WM_SOCKET 이거 보내줘
	if (retval == SOCKET_ERROR)
	{
		::MessageBox(hWnd, "WSAAsyncSelect ERROR!", "ERROR", MB_ICONSTOP | MB_OK);
		return FALSE;
	}

	//SOCKADDR_IN g_ToClientaddr;
	ZeroMemory(&g_ToClientaddr, sizeof(g_ToClientaddr));
	g_ToClientaddr.sin_family = AF_INET;
	g_ToClientaddr.sin_port = htons(30000); //상대방은 삼만번
	g_ToClientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ST_READY ready;
	ready.PktID = PKT_READY;
	ready.PktSize = sizeof(ST_READY);
	ready.State = user[PLAYER_ME].State;
	ready.Game_type = user[PLAYER_ME].Game_type;

	retval = sendto(g_hSocket, (char *)&ready, ready.PktSize, 0, (sockaddr*)&g_ToClientaddr, sizeof(g_ToClientaddr)); //( 소컷 , 내가 보내보자하는 데이터 , 데이터의 길이 , 0 , 상대방의 주소, 주소의 크기 ) 
	if (retval == SOCKET_ERROR)
	{
		::MessageBox(hWnd, "SEND ERROR!", "ERROR", MB_ICONSTOP | MB_OK);
	}


}

void ReleaseSocket()
{
	closesocket(g_hSocket);
	g_hSocket = INVALID_SOCKET;

	WSACleanup();
}

DWORD Tick;
DWORD Animove;

int Game1_result;
int g_Animove = 0;

void OnUpdate(HWND hWnd, DWORD tick)
{
	if(hWnd == NULL)
		return;


	switch (State)
	{
	case Estate::Intro:
		break;
	case Estate::GameSelect:
		if (C_gameIntro.G_init_check == 1)
		{
			if (user[PLAYER_OTHER].State == (int)Estate::GameLoding && user[PLAYER_OTHER].Game_type == (int)EGame::Initial_Game)
			{
				C_gameIntro.Friend_OK(g_BackBuffer);
			}
			else
				C_gameIntro.Friend_NO(g_BackBuffer);
		}

		if (C_gameIntro.G_RCP_check == 1)
		{
			if (user[PLAYER_OTHER].State == (int)Estate::GameLoding && user[PLAYER_OTHER].Game_type == (int)EGame::RCP_Game)
			{
				C_gameIntro.Friend_OK(g_BackBuffer);

			}
			else
				C_gameIntro.Friend_NO(g_BackBuffer);
		}

		if (C_gameIntro.G_dbc_check == 1)
		{
			if (user[PLAYER_OTHER].State == (int)Estate::GameLoding && user[PLAYER_OTHER].Game_type == (int)EGame::Snack_Game)
			{
				C_gameIntro.Friend_OK(g_BackBuffer);

			}
			else
				C_gameIntro.Friend_NO(g_BackBuffer);
		}


		if (C_gameIntro.G_touch_check == 1)
		{
			if (user[PLAYER_OTHER].State == (int)Estate::GameLoding && user[PLAYER_OTHER].Game_type == (int)EGame::Touch_Game)
			{
				C_gameIntro.Friend_OK(g_BackBuffer);

			}
			else
				C_gameIntro.Friend_NO(g_BackBuffer);
		}


		break;
	case Estate::GameLoding:
		//방이 같다면
		if ((user[PLAYER_ME].State == (int)Estate::GameLoding&&user[PLAYER_OTHER].State == (int)Estate::GameLoding)
			&& (user[PLAYER_ME].Game_type == user[PLAYER_OTHER].Game_type))
		{

			Tick += tick;
			C_gameIntro.pTwo_player->Draw(g_BackBuffer, 130, 200);

			if (Tick > 2000)
				C_gameIntro.pGame_play->Draw(g_BackBuffer, 130, 300);
			if (Tick > 4000)
				State = Estate::Game;


		}
		else
			C_gameIntro.pNo_player->Draw(g_BackBuffer, 100, 200);

		break;
	case Estate::Game:

		Tick = 0;

		switch (Game_Type)
		{
		case EGame::Null_Game:
			break;
		case EGame::Touch_Game:
			Touch_Game.OnUpdateTime(tick, g_BackBuffer);

			ST_GAME4 S_game4;
			S_game4.score = Game4_score[PLAYER_ME];
			S_game4.PktID = PKT_GAME4;
			S_game4.PktSize = sizeof(ST_GAME4);

			sendto(g_hSocket, (char*)&S_game4, S_game4.PktSize, 0, (sockaddr *)&g_ToClientaddr, sizeof(g_ToClientaddr));
			
			if (Touch_Game.game_over == true)
			{
				if (Game4_score[PLAYER_ME]>Game4_score[PLAYER_OTHER])
					State = Estate::GameWin;
				if (Game4_score[PLAYER_ME]<Game4_score[PLAYER_OTHER])
					State = Estate::GameOver;
				if (Game4_score[PLAYER_ME] == Game4_score[PLAYER_OTHER])
					State = Estate::GameDraw;
			}
			break;
		case EGame::Snack_Game:
		{

			if (Dice_check)
			{
				if (Dice_Music_check == false)
				{
					pSound[1]->Play();
					Dice_Music_check = true;
				}
			}
			else
			{
				pSound[1]->Stop();
				Dice_Music_check = false;
			}

			if (Snack_Game.Board[Snake_User[PLAYER_ME].score].move != 0)
			{
				Sleep(5000);

				if (pSound)
				{
					pSound[2]->Play();
				}

				Snake_User[PLAYER_ME].score = Snack_Game.Board[Snake_User[PLAYER_ME].score].move;
				Snack_Game.Board_Move();

				ST_GAME3 S_game3;
				S_game3.score = Snake_User[PLAYER_ME].score;
				S_game3.Dice = Snake_User[PLAYER_ME].Dice;
				S_game3.PktID = PKT_GAME3;
				S_game3.PktSize = sizeof(ST_GAME3);

				sendto(g_hSocket, (char*)&S_game3, S_game3.PktSize, 0, (sockaddr *)&g_ToClientaddr, sizeof(g_ToClientaddr));

			}

			if (Snake_User[PLAYER_ME].score >= 100)
				State = Estate::GameWin;
			else if (Snake_User[PLAYER_OTHER].score >= 100)
				State = Estate::GameOver;

		}
		break;
		case EGame::RCP_Game:
			ST_GAME2 S_game2;
			S_game2.choice = RCP_Game.my_choic;
			S_game2.PktID = PKT_GAME2;
			S_game2.PktSize = sizeof(ST_GAME2);

			sendto(g_hSocket, (char *)&S_game2, S_game2.PktSize, 0, (sockaddr*)&g_ToClientaddr, sizeof(g_ToClientaddr));

			if (user[PLAYER_ME].Game2_choic != 3 && user[PLAYER_OTHER].Game2_choic != 3) //둘 다 선택했으면 
			{
				switch (RCP_Game.GameWinCheck(user[PLAYER_ME].Game2_choic, user[PLAYER_OTHER].Game2_choic)) //결과
				{
				case 1:
					State = Estate::GameWin;
					break;
				case 2:
					State = Estate::GameOver;
					break;
				case 3:
					State = Estate::GameDraw;
					break;
				default:
					break;
				}
			}

			break;
			break;
		case EGame::Initial_Game:

			ST_GAME1 Sand;
			Sand.PktID = PKT_GAME1;
			Sand.PktSize = sizeof(ST_GAME1);
			Sand.userScore = 0;
			Sand.Game1_stage = 0;
			strcpy(Sand.answer, "");

			user[PLAYER_ME].Game1_stage = Initial_Game.stage;
			itoa(user[PLAYER_ME].Score, Score_My_char, 10);
			itoa(user[PLAYER_OTHER].Score, Score_Other_char, 10);


			Game1_result = Initial_Game.GameWinCheck(user[PLAYER_ME].Score, user[PLAYER_OTHER].Score, user[PLAYER_ME].Game1_stage, user[PLAYER_OTHER].Game1_stage);

			Sand.Game1_stage = user[PLAYER_ME].Game1_stage;
			strcpy(Sand.answer, user[PLAYER_ME].answer);
			Sand.userScore = user[PLAYER_ME].Score;

			int retval = sendto(g_hSocket, (char *)&Sand, Sand.PktSize, 0, (sockaddr*)&g_ToClientaddr, sizeof(g_ToClientaddr));
			if (retval == SOCKET_ERROR)
			{
			//	::MessageBox(hWnd, "SEND ERROR!", "ERROR", MB_ICONSTOP | MB_OK);
			}

			Animove += tick;
			if (Animove >= 500)
			{
				g_Animove++;
				Animove = 0;
			}
			g_Animove = g_Animove % 2;

			if (Game1_result == 0 && user[PLAYER_ME].Game1_stage > 10)
			{
				C_gameIntro.pWait[g_Animove]->Draw(g_BackBuffer, 0, 0);
			}

			if (Game1_result == 1)
				State = Estate::GameWin;
			if (Game1_result == 2)
				State = Estate::GameOver;
			if (Game1_result == 3)
				State = Estate::GameDraw;
			break;

		}


		break;
	case Estate::GameWin:
		C_gameIntro.pWin->Draw(g_BackBuffer, 0, 0);
		user[PLAYER_ME].Score = 0;
		user[PLAYER_OTHER].Score = 0;
		user[PLAYER_ME].Game2_choic = 3;
		user[PLAYER_OTHER].Game2_choic = 3;
		Snake_User[PLAYER_ME].score = 1;
		Snake_User[PLAYER_OTHER].score = 1;
		Snack_Game.Board_xy(Snake_User[PLAYER_ME].score, Snake_User[PLAYER_OTHER].score);
		Initial_Game.game_Init();
		RCP_Game.Game_Init();
		pSound[3]->Stop();
		Dice_Music_check = false;
		Dice_check = false;
		break;
	case Estate::GameOver:
		C_gameIntro.pLose->Draw(g_BackBuffer, 0, 0);
		user[PLAYER_ME].Score = 0;
		user[PLAYER_OTHER].Score = 0;
		user[PLAYER_ME].Game2_choic = 3;
		user[PLAYER_OTHER].Game2_choic = 3;
		Snake_User[PLAYER_ME].score = 1;
		Snake_User[PLAYER_OTHER].score = 1;
		Snack_Game.Board_xy(Snake_User[PLAYER_ME].score, Snake_User[PLAYER_OTHER].score);
		Initial_Game.game_Init();
		RCP_Game.Game_Init();
		pSound[3]->Stop();
		Dice_Music_check = false;
		Dice_check = false;
		break;
	case Estate::GameDraw:
		C_gameIntro.pDraw->Draw(g_BackBuffer, 0, 0);
		user[PLAYER_ME].Score = 0;
		user[PLAYER_OTHER].Score = 0;
		user[PLAYER_ME].Game2_choic = 3;
		user[PLAYER_OTHER].Game2_choic = 3;
		Initial_Game.game_Init();
		RCP_Game.Game_Init();
		pSound[3]->Stop();
		Dice_Music_check = false;
		Dice_check = false;
		break;
	default:
		break;
	}

}

void OnPacket(PACKETHEADER *pHeader)
{
	switch (pHeader->PktID)
	{
	case PKT_GAME2:
	{
		ST_GAME2 *pGame2 = (ST_GAME2 *)pHeader;

		user[PLAYER_OTHER].Game2_choic = pGame2->choice;
		user[PLAYER_ME].Game2_choic = RCP_Game.my_choic;
	}
	break;
	case PKT_READY:
	{
		ST_READY *pReady = (ST_READY *)pHeader;

		user[PLAYER_OTHER].State = pReady->State;
		user[PLAYER_OTHER].Game_type = pReady->Game_type;

	}
	break;
	case PKT_GAME1:
	{
		ST_GAME1 *pGame1 = (ST_GAME1 *)pHeader;

		strcpy(user[PLAYER_OTHER].answer, pGame1->answer);
		user[PLAYER_OTHER].Score = pGame1->userScore;
		user[PLAYER_OTHER].Game1_stage = pGame1->Game1_stage;


	}
	break;
	case PKT_GAME3:
	{
		ST_GAME3 *pGame3 = (ST_GAME3 *)pHeader;

		Snake_User[PLAYER_OTHER].score = pGame3->score;
		Snake_User[PLAYER_OTHER].Dice = pGame3->Dice;

		if (Snake_User[PLAYER_OTHER].Dice == 1)
			Snake_User[PLAYER_ME].Dice = 0;
		if (Snake_User[PLAYER_OTHER].Dice == 0)
			Snake_User[PLAYER_ME].Dice = 1;


		Snack_Game.Dice_set(Snake_User[PLAYER_ME].Dice);
		Snack_Game.Board_xy(Snake_User[PLAYER_ME].score, Snake_User[PLAYER_OTHER].score);

	}
	break;
	default:
		break;
	case PKT_GAME4:

		ST_GAME4 *pGame4 = (ST_GAME4 *)pHeader;
		Game4_score[PLAYER_OTHER] = pGame4->score;

		break;
	}
}