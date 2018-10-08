#include "stdafx.h"
#include "2018_Semicolon.h"
#include "sndenum.h"



FMOD_SYSTEM *g_System; //FMOD system 변수선언
FMOD_SOUND *g_Sound[10];
FMOD_CHANNEL *channel = nullptr;
FMOD_BOOL IsPlaying;

float volume = 1; //볼륨 0~1 


void SoundInit(void) {
	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System, 10, FMOD_INIT_NORMAL, nullptr); //최대 10개의 소리재생가능 

															   /*사운드 생성*/
	FMOD_System_CreateSound(g_System, "..\\res\\bgm.wav", FMOD_LOOP_NORMAL, nullptr, &g_Sound[S_BGM]);
	FMOD_System_CreateSound(g_System, "..\\res\\bullet.wav", FMOD_DEFAULT, nullptr, &g_Sound[S_PL_BULLET]);
	FMOD_System_CreateSound(g_System, "..\\res\\enemyhit1.wav", FMOD_DEFAULT, nullptr, &g_Sound[S_ENEMYDIE1]);
	FMOD_System_CreateSound(g_System, "..\\res\\enemyhit2.wav", FMOD_DEFAULT, nullptr, &g_Sound[S_ENEMYDIE2]);
	FMOD_System_CreateSound(g_System, "..\\res\\enemyhit3.wav", FMOD_DEFAULT, nullptr, &g_Sound[S_ENEMYHIT3]);
	FMOD_System_CreateSound(g_System, "..\\res\\enemy3die.wav", FMOD_DEFAULT, nullptr, &g_Sound[S_ENEMYDIE3]);

	//FMOD_System_CreateSound(g_System, "..\\sound\\NewPlayerInit.wav", FMOD_DEFAULT, 0, &g_Sound[S_START]);
	//FMOD_System_CreateSound(g_System, ".\\sound\\enemybullet.wav", FMOD_DEFAULT, 0, &g_Sound[S_EN_BULLET]);
}


void StopSound(void) {
	FMOD_Channel_Stop(channel); //채널의 소리 모두정지 
}


void VolumeSetSound(void) {
	FMOD_Channel_SetVolume(channel, volume); //설정 볼륨으로 소리크기 지정 
}


void SoundUpdate(void) {
	if (IsPlaying == 1)
		FMOD_System_Update(g_System);
}

/*
void VolumeCtrl(void) {
	//char n;
	system("cls");
	prn_xy("↑: 볼륨 증가 ◈ MAX 10 ◈", 27, 8, CR_LGREEN, CR_BLACK, false);

	prn_xy("↓: 볼륨 감소 ◈ MIN 0  ◈", 27, 10, CR_RED, CR_BLACK, false);

	prn_xy("[ESC] : 설정 나가기", 30, 12, CR_WHITE, CR_BLACK, false);

	prn_xy("소리 볼륨: ", 32, 16, CR_WHITE, CR_BLACK, false);
	while (true) {
		gotoxy(44, 16);
		printf("%02d", (int)(volume * 10));


		if (GetAsyncKeyState(VK_UP) < 0 && volume < 1.0f) {
			// 화살표 위쪽 키를 눌렀을 때 
			volume += 0.1f;
			FMOD_Channel_SetVolume(channel, volume);
		}


		if (GetAsyncKeyState(VK_DOWN) < 0 && volume > 0.0f) {
			// 화살표 아래쪽 키를 눌렀을 때 
			volume -= 0.1f;
			FMOD_Channel_SetVolume(channel, volume);
		}

		if (GetAsyncKeyState(VK_ESCAPE) < 0) break;
		Sleep(50);
	}
	title();

}
*/

/*-----해당 사운드 재생-----*/
void Sound_Play(int n) {
	FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[n], 0, &channel);
}
