#include "stdafx.h"
#include "2018_Semicolon.h"

void Control(void)
{
	DrawScreen();
	CtrlPBullet();
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		MoveLeft();

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		MoveRight();

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		MoveDown();

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		MoveUp();

	if ((GetAsyncKeyState(32) & 0x8000) && canFire)
		PlayerFired();
}

void DrawScreen(void)
{
	HDC drawDC = GetDC(g_hWnd);
	HDC hMemDC = CreateCompatibleDC(drawDC);
	HBITMAP PlayerBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	HBITMAP BulletBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	

	for (int i = 0; i < MAXBULLET; i++)	//불릿을 먼저 그린다
	{
		if (PBullet[i].isUsed)
		{
			SelectObject(hMemDC, HBITMAP(BulletBitmap));
			BitBlt(drawDC, PBullet[i].x, PBullet[i].y, PBullet[i].x + 40, PBullet[i].y + 40, hMemDC, 0, 0, SRCCOPY);
		}
	}

	SelectObject(hMemDC, HBITMAP(PlayerBitmap));
	BitBlt(drawDC, Player.x, Player.y, Player.x + 40, Player.y + 40, hMemDC, 0, 0, SRCCOPY);


	DeleteDC(hMemDC);
	DeleteDC(drawDC);
}

void MoveRight(void)
{
	Player.x += PlayerSpeed;
}

void MoveLeft(void)
{
	Player.x -= PlayerSpeed;
}

void MoveUp(void)
{
	Player.y -= PlayerSpeed;
}

void MoveDown(void)
{
	Player.y += PlayerSpeed;
}

void PlayerFired(void)
{
	canFire = 0;
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (PBullet[i].isUsed == 0)
		{
			PBullet[i].isUsed = 1;
			PBullet[i].x = Player.x;
			PBullet[i].y = Player.y;
			break;
		}
	}
}

void CtrlPBullet(void)
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (!PBullet[i].isUsed)
			continue;
		if (PBullet[i].y < 0)
			PBullet[i].isUsed = 0;
		//chkEnemy(i);
		PBullet[i].y -= BULLETSPEED;
	}
}