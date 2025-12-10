#pragma once
//#include "Include.h"
struct SysTem
{
	int m_Save1;
	int m_Save2;

};

class GameManager
{
	Sprite Menuimg[2];
public:
	GameManager(void);
	~GameManager(void);

	FILE* fp;
	SysTem m_SysTem;

	bool m_Pause;
	int m_GameSpeed;

	DWORD GameTime;
	bool m_GameStart;

	bool m_Collision;
	bool m_bShowCollider = true; // 디버그 충돌박스 표시 여부

	//std::list<Player2*>	myList;
	bool Respawn;


	void GameReset(void);
	void Init();
	void Update();
	void Draw();
	void Save();
	void Delete();


};

extern GameManager Gmanager;