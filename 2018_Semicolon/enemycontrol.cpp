#include "stdafx.h"
#include "2018_Semicolon.h"

int spawnEnemy(int x, int y) {
	for(int i=0;i<MAX_ENEMY;i++) {
		if (Enemy[i].Live != 0) continue;
		else {
			Enemy[i].Live = 1;
			Enemy[i].x = x;
			Enemy[i].y = y;
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

bool chkLevelClear() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (Enemy[i].Live != 0) return false;
		else continue;
	}
	return true;
}