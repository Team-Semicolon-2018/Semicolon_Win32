#include "stdafx.h"
#include "2018_Semicolon.h"

int counter = 0;

bool aorb = true;


int spawnEnemy(int x, int y, int level) {
	for(int i=0;i<MAX_ENEMY;i++) {
		if (Enemy[i].Live != 0) continue;
		else {
			
			Enemy[i].Live = 1;
			if (level == 3) {
				Enemy[i].Live = 2;
			}
			Enemy[i].x = x;
			Enemy[i].y = y;
			Enemy[i].level = level;
			std::cout << "Enemy #" << i << " spawned at (" << x << ", " << y << ")" << std::endl;
			return RET_SUCCESS;
		}
	}
	std::cout << "Enemy spawn failed!" << std::endl;
	return RET_ERROR;

}

void chkEnemyHit() {
	for(int i=0; i< MAX_ENEMY; i++) {
		if (Enemy[i].Live != 0) {
			for(int j=0; j<MAXBULLET; j++) {
				if (Enemy[i].x >= PBullet[j].x - 30 && Enemy[i].x <= PBullet[j].x + 30 && Enemy[i].y >= PBullet[j].y - 10 && Enemy[i].y <= PBullet[j].y + 10) {
					if (Enemy[i].Live > 0) Enemy[i].Live--;
					PBullet[j].isUsed = 0;
				}
			}
		}else {
			continue;
		}

	}
}

void chkEnemyFuckedThePlayer() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (Enemy[i].Live != 0) {
			if (Enemy[i].x >= Player.x - 30 && Enemy[i].x <= Player.x + 30 && Enemy[i].y >= Player.y - 10 && Enemy[i].y <= Player.y + 10) {
				if (Player.Live > 0) {
					Player.Live--;
					Sound_Play(S_LIVEMM);

				}
				Enemy[i].Live = 0;
				
			}
			
		}
		else {
			continue;
		}

	}
}

bool chkLevelClear() {
	if (levelclearhack) return true;
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (Enemy[i].Live != 0) return false;
		else continue;
	}
	for(int i=0; i<MAXEBULLET; i++) {
		if (EBullet[i].isUsed != false) return false;
		else continue;
	}

	return true;
}

void CtrlEnemy() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (Enemy[i].Live == 0) continue;
		else {
			//Enemy[i].y += ENEMYSPEED;
			if (Enemy[i].x < WIN_X_SIZE / 2) {
				if(aorb) {
					Enemy[i].x -= (int)((WIN_X_SIZE / 2) - Enemy[i].x) / 20;

				}else {
					Enemy[i].x += (int)((WIN_X_SIZE / 2) - Enemy[i].x) / 20;
				}
			}
			else if (Enemy[i].x > WIN_X_SIZE / 2) {
				if(aorb) Enemy[i].x += (int)((Enemy[i].x) - (WIN_X_SIZE/2))/20;
				else Enemy[i].x -= (int)((Enemy[i].x) - (WIN_X_SIZE / 2)) / 20;
				
			}
			
			
			if (Enemy[i].y > WIN_Y_SIZE - 100)
			{
				Enemy[i].Live = 0;
				if (Player.Live > 0) {
					Player.Live--;
				
					Sound_Play(S_LIVEMM);
				}
			}
		}
	}
	counter++;
	if (counter > 8) {
		counter = 0;
		aorb = !aorb;
	}
	
	
}

void EnemyFire(int index)	//에너미 너는 오늘 해고야
{
	for (int i = 0; i < MAXEBULLET; i++)
		if (EBullet[i].isUsed == 0)
		{
			EBullet[i].isUsed = 1;
			EBullet[i].x = (int)Enemy[index].x;
			EBullet[i].y = (int)Enemy[index].y;
			Sound_Play(S_PL_BULLET);
			break;
		}
}

void CtrlEBullet()
{
//	미안해요~~ 저는 당신과 사랑할 수 없어요~~~~~
//	2018.10.20 특수절도죄 집행유예 15년
//	2018.10.20 특수사기죄 징역 25년
//	기모띠
	for (int i = 0; i < MAXEBULLET; i++) {
		if (EBullet[i].isUsed == 0) continue;
		else if (EBullet[i].y >= WIN_Y_SIZE)
			EBullet[i].isUsed = 0;
		else {
			chkPlayerHit(i);
			EBullet[i].y += EBULLETFUCKINGLOVERSTHATSMESPEED;
		}
	}

	
	
}

bool Percentage(int percent)
{
	int dlgowhagowntpasjanrnlcksgdma = rand() % 100;
	std::cout << std::endl << dlgowhagowntpasjanrnlcksgdma << std::endl;
	if (dlgowhagowntpasjanrnlcksgdma < percent)
		return TRUE;
	return FALSE;
}

void chkPlayerHit(int i)
{

	if (EBullet[i].x >= Player.x - 30 && EBullet[i].x <= Player.x + 30 && EBullet[i].y >= Player.y - 10 && EBullet[i].y <= Player.y + 10) {
		if (Player.Live > 0) {
			Sound_Play(S_LIVEMM);
			Player.Live--;
		}
		EBullet[i].isUsed = 0;
//		마마, 황송하옵니다
		//-- == 마마

	}
}

void chkBulletHit() {
	for (int i = 0; i < MAXEBULLET; i++) {
		for (int j = 0; j < MAXBULLET; j++) {
			if (EBullet[i].isUsed && PBullet[j].isUsed) {
				if (EBullet[i].x >= PBullet[j].x - 30 && EBullet[i].x <= PBullet[j].x + 30 && EBullet[i].y >= PBullet[j].y - 10 && EBullet[i].y <= PBullet[j].y + 10) {
					std::cout << "bullet hit";
					EBullet[i].isUsed = FALSE;
					PBullet[j].isUsed = FALSE;
				}
			}
		}
	}
	
}