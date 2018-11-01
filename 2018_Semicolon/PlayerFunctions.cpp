#include "stdafx.h"
#include "2018_Semicolon.h"


bool alreadyhappened = false;

void CALLBACK Control(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	chkEnemyHit();
	CtrlPBullet();
	CtrlEBullet();
	chkBulletHit();
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
		Player.x += (int)speed;
		
	}
	else {
		speed = 0;
	}

	if (!((GetKeyState(VK_RIGHT) & 0x8000) || (GetKeyState(VK_LEFT) & 0x8000))) {
		if (speed > 0) speed -= SPEEDBREAK;
		if (speed < 0) speed += SPEEDBREAK;
	}

	chkEnemyFuckedThePlayer();
	score++;
	if(chkLevelClear()) {
		Sound_Play(S_CLEAR);
		HWND hBtn = GetDlgItem(hWnd, BTN_PAUSE); // 1. 버튼의 핸들을 구함
		EnableWindow(hBtn, FALSE); // 2. 핸들에 활성화(TRUE)/비활성화(FALSE) 값을 줌
		ShowWindow(hBtn, SW_HIDE);
		HWND hBtn2 = GetDlgItem(hWnd, BTN_RESUME); // 1. 버튼의 핸들을 구함
		EnableWindow(hBtn2, FALSE); // 2. 핸들에 활성화(TRUE)/비활성화(FALSE) 값을 줌
		ShowWindow(hBtn2, SW_HIDE);
		std::cout << "Level Clear!";
		KillTimer(hWnd, TM_CTRL);
		KillTimer(hWnd, TM_NEWFRM);
		KillTimer(hWnd, TM_ENEMYCTRL);
		KillTimer(hWnd, TM_ENMFIRE);

		TerminateThread(hThread_BG, 5);
		TerminateThread(DIVEMOVEThread, 5);
		TerminateThread(DIVEControlThread, 5);


		HFONT hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Press Start 2P"));
		HDC hMemDC = GetDC(hWnd);

		SetTextColor(hMemDC, RGB(255, 0, 0));
		SetBkColor(hMemDC, RGB(0, 0, 0));
		SelectObject(hMemDC, hFont);
		std::wstring str_level = (std::wstring)L"LEVEL CLEAR!";
		TextOut(hMemDC, WIN_X_SIZE / 2 - 150, WIN_Y_SIZE / 2 - 50, str_level.c_str(), str_level.length());

		//MessageBox(g_hWnd, LPCWSTR(L"레벨 클리어"), LPCWSTR(L"ㅇㅇ"), MB_ICONINFORMATION | MB_OK);
	}
	
}

void DrawScreen(HWND hWnd)
{
	if(alreadyhappened == false) {
		FMOD_Channel_IsPlaying(channel, &IsPlaying);
		if (Player.Live == 0) {

			HWND hBtn = GetDlgItem(hWnd, BTN_PAUSE); // 1. 버튼의 핸들을 구함
			EnableWindow(hBtn, FALSE); // 2. 핸들에 활성화(TRUE)/비활성화(FALSE) 값을 줌
			ShowWindow(hBtn, SW_HIDE);
			HWND hBtn2 = GetDlgItem(hWnd, BTN_RESUME); // 1. 버튼의 핸들을 구함
			EnableWindow(hBtn2, FALSE); // 2. 핸들에 활성화(TRUE)/비활성화(FALSE) 값을 줌
			ShowWindow(hBtn2, SW_HIDE);
			KillTimer(hWnd, TM_CTRL);
			//
			KillTimer(hWnd, TM_ENEMYCTRL);
			KillTimer(hWnd, TM_ENMFIRE);

			TerminateThread(hThread_BG, 5);
			TerminateThread(DIVEMOVEThread, 5);
			TerminateThread(DIVEControlThread, 5);

			HFONT hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Press Start 2P"));
			HDC hMemDC = GetDC(hWnd);

			HDC drawDC = GetDC(g_hWnd);
			HDC hMemDC1 = CreateCompatibleDC(drawDC);

			SetTextColor(hMemDC, RGB(255, 0, 0));
			SetBkColor(hMemDC, RGB(0, 0, 0));
			SelectObject(hMemDC, hFont);
			std::wstring str_level = (std::wstring)L"GAME OVER";
			TextOut(hMemDC, WIN_X_SIZE / 2 - 150, WIN_Y_SIZE / 2 - 50, str_level.c_str(), str_level.length());
			HBITMAP PlayerExplode1 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP14));
			HBITMAP PlayerExplode2 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP15));
			HBITMAP PlayerExplode3 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP16));
			HBITMAP PlayerExplode4 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP17));
			Sound_Play(S_EXPLODE);
			SelectObject(hMemDC1, HBITMAP(PlayerExplode1));	//비트맵 연결
			BitBlt(drawDC, (int)Player.x - 20, (int)Player.y - 20, (int)Player.y + 72, (int)Player.y + 72, hMemDC1, 0, 0, SRCCOPY);
			Sleep(300);
			SelectObject(hMemDC1, HBITMAP(PlayerExplode2));	//비트맵 연결
			BitBlt(drawDC, (int)Player.x - 20, (int)Player.y - 20, (int)Player.y + 72, (int)Player.y + 72, hMemDC1, 0, 0, SRCCOPY);
			Sleep(300);
			SelectObject(hMemDC1, HBITMAP(PlayerExplode3));	//비트맵 연결
			BitBlt(drawDC, (int)Player.x - 20, (int)Player.y - 20, (int)Player.y + 72, (int)Player.y + 72, hMemDC1, 0, 0, SRCCOPY);
			Sleep(300);
			SelectObject(hMemDC1, HBITMAP(PlayerExplode4));	//비트맵 연결
			BitBlt(drawDC, (int)Player.x - 20, (int)Player.y - 20, (int)Player.y + 72, (int)Player.y + 72, hMemDC1, 0, 0, SRCCOPY);
			Sleep(300);

			//MessageBox(g_hWnd, LPCWSTR(L"레벨 클리어"), LPCWSTR(L"ㅇㅇ"), MB_ICONINFORMATION | MB_OK);
			KillTimer(hWnd, TM_NEWFRM);
			alreadyhappened = 1;
			Sound_Play(S_GAMEOVER);

			HFONT hFontn = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("나눔고딕"));
			SelectObject(hMemDC, hFontn);
			str_level = (std::wstring)L"\"감사합니다. 창을 닫아 주세요\"";
			TextOut(hMemDC, WIN_X_SIZE / 2 - 150, WIN_Y_SIZE / 2 + 50, str_level.c_str(), str_level.length());


		}
		else {
			HDC drawDC = GetDC(g_hWnd);
			HDC hMemDC = CreateCompatibleDC(drawDC);
			HBITMAP PlayerBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
			HBITMAP BulletBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));

			HBITMAP EnemyBitmap3_0 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
			HBITMAP EnemyBitmap3_1 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));

			HBITMAP EnemyBitmap3_0_HIT = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP7));
			HBITMAP EnemyBitmap3_1_HIT = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP8));


			HBITMAP EnemyBitmap2_0 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP9));
			HBITMAP EnemyBitmap2_1 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP10));

			HBITMAP EnemyBitmap1_0 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP11));
			HBITMAP EnemyBitmap1_1 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP12));


			HBITMAP EBulletBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP13));


			for (int i = 0; i < MAXBULLET; i++)	//불릿을 먼저 그린다
			{
				if (PBullet[i].isUsed)
				{
					SelectObject(hMemDC, HBITMAP(BulletBitmap));	//비트맵 연결
					BitBlt(drawDC, PBullet[i].x, PBullet[i].y, PBullet[i].x + 40, PBullet[i].y + 40, hMemDC, 0, 0, SRCCOPY);
				}
				else {
					continue;
				}
			}
			for (int i = 0; i < MAXEBULLET; i++)
			{
				if (EBullet[i].isUsed == 0)
					continue;
				else
				{
					SelectObject(hMemDC, HBITMAP(EBulletBitmap));
					BitBlt(drawDC, EBullet[i].x, EBullet[i].y, EBullet[i].x + 40, EBullet[i].y + 40, hMemDC, 0, 0, SRCCOPY);
				}
			}
			if (enemysprite) {
				for (int i = 0; i < MAX_ENEMY; i++)	//Enemy를 그린다
				{
					if (Enemy[i].Live != 0)
					{
						if (Enemy[i].level == 3) {
							if (Enemy[i].Live == 2) {
								SelectObject(hMemDC, HBITMAP(EnemyBitmap3_0));	//비트맵 연결
								BitBlt(drawDC, int(Enemy[i].x), Enemy[i].y, int(Enemy[i].x) + 40, Enemy[i].y + 40, hMemDC, 0, 0, SRCCOPY);

							}
							else {
								SelectObject(hMemDC, HBITMAP(EnemyBitmap3_0_HIT));	//비트맵 연결
								BitBlt(drawDC, int(Enemy[i].x), Enemy[i].y, int(Enemy[i].x) + 40, Enemy[i].y + 40, hMemDC, 0, 0, SRCCOPY);

							}
						}
						else if (Enemy[i].level == 2) {
							SelectObject(hMemDC, HBITMAP(EnemyBitmap2_0));	//비트맵 연결
							BitBlt(drawDC, int(Enemy[i].x), Enemy[i].y, int(Enemy[i].x) + 40, Enemy[i].y + 40, hMemDC, 0, 0, SRCCOPY);

						}
						else if (Enemy[i].level == 1) {
							SelectObject(hMemDC, HBITMAP(EnemyBitmap1_0));	//비트맵 연결
							BitBlt(drawDC, int(Enemy[i].x), Enemy[i].y, int(Enemy[i].x) + 40, Enemy[i].y + 40, hMemDC, 0, 0, SRCCOPY);
						}
					}
					else {
						continue;
					}
				}
			}
			else {
				for (int i = 0; i < MAX_ENEMY; i++)	//Enemy를 그린다
				{
					if (Enemy[i].Live != 0)
					{
						if (Enemy[i].level == 3) {
							if (Enemy[i].Live == 2) {
								SelectObject(hMemDC, HBITMAP(EnemyBitmap3_1));	//비트맵 연결
								BitBlt(drawDC, int(Enemy[i].x), Enemy[i].y, int(Enemy[i].x) + 40, Enemy[i].y + 40, hMemDC, 0, 0, SRCCOPY);

							}
							else {
								SelectObject(hMemDC, HBITMAP(EnemyBitmap3_1_HIT));	//비트맵 연결
								BitBlt(drawDC, int(Enemy[i].x), Enemy[i].y, int(Enemy[i].x) + 40, Enemy[i].y + 40, hMemDC, 0, 0, SRCCOPY);

							}

						}
						else if (Enemy[i].level == 2) {
							SelectObject(hMemDC, HBITMAP(EnemyBitmap2_1));	//비트맵 연결
							BitBlt(drawDC, int(Enemy[i].x), Enemy[i].y, int(Enemy[i].x) + 40, Enemy[i].y + 40, hMemDC, 0, 0, SRCCOPY);

						}
						else if (Enemy[i].level == 1) {
							SelectObject(hMemDC, HBITMAP(EnemyBitmap1_1));	//비트맵 연결
							BitBlt(drawDC, int(Enemy[i].x), Enemy[i].y, int(Enemy[i].x) + 40, Enemy[i].y + 40, hMemDC, 0, 0, SRCCOPY);

						}
					}
					else {
						continue;
					}
				}
			}



			SelectObject(hMemDC, HBITMAP(PlayerBitmap));
			BitBlt(drawDC, int(Player.x), (int)Player.y, int(Player.x) + 40, (int)Player.y + 40, hMemDC, 0, 0, SRCCOPY);

			DeleteDC(hMemDC);	//CreateCompatibleDC() --> DeleteDC()
			ReleaseDC(g_hWnd, drawDC);

			DeleteObject(PlayerBitmap);
			DeleteObject(BulletBitmap);
			DeleteObject(EnemyBitmap1_0);
			DeleteObject(EnemyBitmap1_1);
			DeleteObject(EnemyBitmap2_0);
			DeleteObject(EnemyBitmap2_1);
			DeleteObject(EnemyBitmap3_0);
			DeleteObject(EnemyBitmap3_1);
			DeleteObject(EnemyBitmap3_0_HIT);
			DeleteObject(EnemyBitmap3_1_HIT);

		}


	}

}

void MoveRight(void)
{
	if (speed < MAX_PLAYER_SPEED)
		speed += PlayerSpeed;
}

void MoveLeft(void)
{
	if (speed > MAX_PLAYER_SPEED * -1)
		speed -= PlayerSpeed;
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
	//
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (PBullet[i].isUsed == 0)
		{
			PBullet[i].isUsed = 1;
			PBullet[i].x = int(Player.x);
			PBullet[i].y = Player.y;
			Sound_Play(S_PL_BULLET);
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