#include "stdafx.h"
#include "2018_Semicolon.h"


void Control(void)
{
	chkEnemyHit();
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
	if (int(Player.x + speed) < WIN_X_SIZE - 100 && int(Player.x + speed) > 50) {
		Player.x += speed;
		
	}
	else {
		speed = 0;
	}
	if(chkLevelClear()) {
		MessageBox(g_hWnd, LPCWSTR(L"레벨 클리어"), LPCWSTR(L"ㅇㅇ"), MB_ICONINFORMATION | MB_OK);
	}
}

void DrawScreen(void)
{
	HDC drawDC = GetDC(g_hWnd);
	HDC hMemDC = CreateCompatibleDC(drawDC);
	HBITMAP PlayerBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	HBITMAP BulletBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	HBITMAP EnemyBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));

	

	for (int i = 0; i < MAX_ENEMY; i++)	//Enemy를 그린다
	{
		if (Enemy[i].Live != 0)
		{
			SelectObject(hMemDC, HBITMAP(EnemyBitmap));	//비트맵 연결
			BitBlt(drawDC, int(Enemy[i].x), Enemy[i].y, int(Enemy[i].x) + 40, Enemy[i].y + 40, hMemDC, 0, 0, SRCCOPY);
		}
		else {
			continue;
		}
	}
	for (int i = 0; i < MAXBULLET; i++)	//불릿을 먼저 그린다
	{
		if (PBullet[i].isUsed)
		{
			SelectObject(hMemDC, HBITMAP(BulletBitmap));	//비트맵 연결
			BitBlt(drawDC, PBullet[i].x, PBullet[i].y, PBullet[i].x + 40, PBullet[i].y + 40, hMemDC, 0, 0, SRCCOPY);
		}else {
			continue;
		}
	}
	
	SelectObject(hMemDC, HBITMAP(PlayerBitmap));
	BitBlt(drawDC, int(Player.x), Player.y, int(Player.x) + 40, Player.y + 40, hMemDC, 0, 0, SRCCOPY);

	DeleteDC(hMemDC);	//CreateCompatibleDC() --> DeleteDC()
	ReleaseDC(g_hWnd, drawDC);

	DeleteObject(PlayerBitmap);
	DeleteObject(BulletBitmap);
	DeleteObject(EnemyBitmap);

}

void MoveRight(void)
{
	speed += PlayerSpeed;
	lastmovedtime = time(NULL);
}

void MoveLeft(void)
{
	speed -= PlayerSpeed;
	lastmovedtime = time(NULL);
}

void MoveUp(void)
{
	//Player.y -= PlayerSpeed;
}

void MoveDown(void)
{
	//Player.y += PlayerSpeed;
}

void PlayerFired(void)
{
	canFire = 0;
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (PBullet[i].isUsed == 0)
		{
			PBullet[i].isUsed = 1;
			PBullet[i].x = int(Player.x);
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