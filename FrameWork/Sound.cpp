#include "Include.h"

Sound sound;



Sound::Sound(void)
{
	//g_pSoundManager = NULL; 사용 안했다
}

Sound::~Sound(void)
{
}

void Sound::Init()
{
	g_pSoundManager->Create(&m_Bk1, (LPWSTR)L"./resource/Sound/bgm1.wav", 0, GUID_NULL);
	//g_pSoundManager->Create(&m_Loadbg, (LPWSTR)L"./resource/Sound/loading.wav", 0, GUID_NULL);
	g_pSoundManager->Create(&m_Gamebg, (LPWSTR)L"./resource/Sound/Casual_Theme.wav", 0, GUID_NULL);
	g_pSoundManager->Create(&m_Menubg, (LPWSTR)L"./resource/Sound/Casual_Theme2.wav", 0, GUID_NULL);
	g_pSoundManager->Create(&m_overbg, (LPWSTR)L"./resource/Sound/Casual_over.wav", 0, GUID_NULL);
	g_pSoundManager->Create(&m_HitIce, (LPWSTR)L"./resource/Sound/HitIce.wav", 0, GUID_NULL);
	g_pSoundManager->Create(&m_HitHard, (LPWSTR)L"./resource/Sound/HitHard.wav", 0, GUID_NULL);
	g_pSoundManager->Create(&m_Impact, (LPWSTR)L"./resource/Sound/IMPACT.wav", 0, GUID_NULL);
	g_pSoundManager->Create(&m_Jump, (LPWSTR)L"./resource/Sound/Jump.wav", 0, GUID_NULL);
	g_pSoundManager->Create(&m_Death, (LPWSTR)L"./resource/Sound/Death.wav", 0, GUID_NULL);
	g_pSoundManager->Create(&Select, (LPWSTR)L"./resource/Sound/Select4.wav", 0, GUID_NULL);
	g_pSoundManager->Create(&Select2, (LPWSTR)L"./resource/Sound/Select3.wav", 0, GUID_NULL);
	g_pSoundManager->Create(&Select3, (LPWSTR)L"./resource/Sound/pping.wav", 0, GUID_NULL);
}

