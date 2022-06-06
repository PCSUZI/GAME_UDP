//packet.h
#ifndef _PACKET_H_
#define _PACKET_H_
//데이터 주고 받을꺼 여기에 보내면 됨 
#include <Windows.h>

#pragma  pack(push)
#pragma  pack(1)

#define PKTHEADERSIZE          sizeof(PACKETHEADER) // 패킷헤더의 크기

typedef struct _tgPacketHeader
{
	DWORD  PktID;
	WORD   PktSize;
}PACKETHEADER;

#define PKT_READY		0xa0000011
typedef struct _tgReady : PACKETHEADER
{
	char name[30];
	int State;
	int Game_type;

}ST_READY;

#define PKT_GAME1 0xc0000011
typedef struct _tgGame1 : PACKETHEADER
{
	char answer[20];
	int userScore;
	int Game1_stage;

}ST_GAME1;


#define PKT_GAME2		0xb0000011
typedef struct _tgPointMove : PACKETHEADER
{
	int choice;

}ST_GAME2;


#define PKT_GAME3	0xd0000011
typedef struct _tgGame3 : PACKETHEADER
{
	int score;
	int Dice;

}ST_GAME3;

#define PKT_GAME4	0xf0000011
typedef struct _tgGame4 : PACKETHEADER
{
	int score;

}ST_GAME4;


#pragma pack(pop)

#endif