#pragma once

#include "resource.h"
#define MAX_LOADSTRING 100

#define TM_NEWFRM 1	//invalidateRect
#define TM_FIRECTRL 2	//PlayerFiring --> Player의 불릿의 가용성을 정의합니다
#define TM_MLEAKCHK 3
#define TM_PLSPEEDCTRL 4
#define FRAMEPERSEC 100
#define BULLETSPEED 8
#define MAXBULLET 10
#define MAXENEMY 30
#define BULLETDELAY 300
#define MEMCHKCYCLE 1000 * 5

#define PlayerSpeed 0.7
#define SPEEDCTRLDELAY 20
#define SPEEDBREAK 0.3
#define WIN_X_SIZE 1400

#define WIN_Y_SIZE 800

typedef struct _Jet {
	double x;
	int y;
	int Live;
} Jet;

typedef struct _Bullet {
	int x;
	int y;
	int isUsed;
} Bullet;

extern Jet Player;
extern Jet Enemy[MAXENEMY];
extern HINSTANCE hInst;                                // 현재 인스턴스입니다.
extern WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
extern WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
extern HWND g_hWnd;

extern Bullet PBullet[MAXBULLET];
extern bool canFire;

extern double speed;
void DrawScreen(void);
void CtrlEnemy(void);
void Control(void);
void MoveLeft(void);
void MoveRight(void);
void MoveUp(void);
void MoveDown(void);
void PlayerFired(void);
void CtrlPBullet(void);
void chkEnemy(int indexOfBullet);