#pragma once

class Sound
{
	
public:
	Sound(void);
	~Sound(void);

	
CSoundManager* g_pSoundManager;
CSound*		m_Bk1;
//CSound*		m_Loadbg;
CSound*		m_Gamebg;
CSound*		m_Menubg;
CSound*		m_overbg;
CSound*		m_Impact;
CSound*		m_HitHard;
CSound*		m_HitIce;
CSound*		m_bird;
CSound*		m_Steps;
CSound*		m_Hitbody;
CSound*		m_Jump;
CSound*		m_Death;
CSound*		Select;
CSound*		Select2;
CSound*		Select3;

int m_Select;

	

	void Init();
	
	
};

extern Sound sound;