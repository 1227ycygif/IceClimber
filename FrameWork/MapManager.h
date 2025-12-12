#pragma once
#include "Include.h"
#include"BoundCheckArray.h"
/*
용도 :		전체 맵을 관리하는 클래스
맴버 변수 :	주석 참조

맴버 함수 :	생성자
			소멸자

			초기화
			업데이트
			드로우
			충돌
*/
class MapManager
{
private:
	// 블록매니저 클래스 포인터 배열
	BoundCheckArray<BlockManager*> blockMap;			
	// 캐릭터 클래스 포인터 플레이어1
	Character* cha;										
	// 캐릭터 클래스 포인터 플레이어2
	Character* cha2;									
	// 몬스터 클래스 포인터 배열
	BoundCheckArray<Monster*> seal;						

public:
	// 맵 이동 중 이동량
	int floorY;											
	// 맵 이동 상태 true: 이동 중, false: 이동 해제
	bool floor_move;									
	// 맵 이동이 일어날 층, 이번 맵 이동시 스킵될 층(아래), 이번 맵 이동시 스킵될 층(아래)
	int floor_move_now, floor_skip_1, floor_skip_2;		

	MapManager();
	~MapManager();

	void Init();
	void Update();
	void Draw();
	void Collision();
};

extern MapManager mapManager;