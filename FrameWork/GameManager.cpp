#include "Include.h"

GameManager Gmanager;
static DWORD ALPHATime = GetTickCount();

GameManager::GameManager(void)
{
	GameTime = GetTickCount();
	m_GameSpeed = 1;
	m_Pause = false;

	//m_SysTem.m_Save1 = 100;
	//m_SysTem.m_Save2 = 200;
	//Save();

	m_GameStart = true;
}

GameManager::~GameManager(void)
{
}

void GameManager::Init()
{
	//Menuimg[0].Create("./resource/Effect/menu/1.png",false,D3DCOLOR_XRGB(0,0,0));
	//Menuimg[1].Create("./resource/Effect/menu/2.png",false,D3DCOLOR_XRGB(0,0,0));


	char seps[] = ",\n";
	char *token;

	if ((fp = fopen("C:\\SYSTEM.txt","r"))== NULL)
	{
		return ;
	}
	
	if ((fp = fopen("./Save/save.fss","rb"))== NULL)
	{
		return ;
	}
	
	fread(&m_SysTem,sizeof(SysTem),1,fp);

	fclose(fp);
	
}

// ◆ 디버그 박스 키 설정 
void GameManager::Update()
{
	static bool prevB = false;
	bool nowB = (GetAsyncKeyState('B') & 0x8000); // B키 한 번 눌렀을 때만 반응
	
		if (nowB && !prevB)
		{
			m_bShowCollider = !m_bShowCollider;
		}
		prevB = nowB;
		
		//m_bShowCollider = !m_bShowCollider;
		
	//if(게임 종료시) g_Mng.n_Chap = OVER; 
}
void GameManager::Save()
{
	if ((fp = fopen("./Save/save.fss", "wb")) == NULL)
	{
		return;
	}
	fwrite(&m_SysTem, sizeof(SysTem), 1, fp);
	fclose(fp);

}

void GameManager::Delete()
{
//	sound.g_pSoundManager->drr  

}
 



void GameManager::GameReset(void)  // 여기는 게임상 첨에 한번만  초기화되는 부분만 넣어줌.
{

}


/*
□ GameManager::Draw 역할 □ 
전체 통합 출력 제어

1. 게임 씬에 따라 각기 다른 Draw 호출 
타이틀 / 본 게임 / 게임오버 및 클리어 등

2. 공통 UI 및 전체 Overlay 출력 
- 점수, 남은 시간, 스테이지, FPS, 생명, 미니맵 등 시각 정보

3. 디버그용 출력 / 테스트용 출력 
- 각종 디버그 정보: 충돌 박스, 좌표, 게임 상태, 입력 정보, 튜토리얼, 도움말 안내, 프레임 카운터 등

4. 씬 챕터 전환 효과
- 페이드 인/아웃, 블러, 전환 효과 등

*/
void GameManager::Draw()
{

	//if(m_Alpha == 0) { Menuimg[0].SetColor(255,255, 255, 255);  Menuimg[1].SetColor(255,255, 255, 255);}
	//if(m_Alpha == 1) { Menuimg[0].SetColor(255,255,255,0); Menuimg[1].SetColor(255,255,255,0); }
	

	//map.numimg[5].Draw(50, 53);
	//map.numimg[0].Draw(65, 53);
	//map.numimg[0].Draw(80, 53);
	//map.numimg[0].Draw(95, 53);
	
}
