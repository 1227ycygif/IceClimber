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
	BoundCheckArray<BlockManager*> blockMap;			// 블럭매니저클래스포인터 배열
	Character* cha;										// 캐릭터클래스 포인터 플레이어1
	Character* cha2;									// 캐릭터클래스 포인터 플레이어2
	BoundCheckArray<Monster*> seal;						// 몬스터클래스 포인터 배열

public:
	int floorY;											// 맵이동중 이동량
	bool floor_move;									// 맵이동 상태 true: 이동중, false: 이동해제
	int floor_move_now, floor_skip_1, floor_skip_2;		// 맵이동이 일어날 층, 이번 맵이동시 스킵될층(아래), 이번 맵이동시 스킵될층(아래)

	MapManager();
	~MapManager();

	void Init();
	void Update();
	void Draw();
	void Collision();
};

extern MapManager mapManager;