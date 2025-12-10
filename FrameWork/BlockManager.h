#pragma once
#include "Include.h"          // 모든 타입/기본 선언을 위해 가장 먼저!

class Monster;                // 헤더 파일에서 Monster* 사용만 할 경우 Forward 선언!
class Block;
class Character;

#include "BoundCheckArray.h"  // 템플릿 배열 사용

/*
용도 :		맥
맴버 변수 :	블럭클래스포인터 배열
			층 높이
			블럭 인덱스
맴버 함수 :	소멸자

			초기화
			리셋
			업데이트
			드로우

			블럭과 캐릭터간 충돌
			블럭과 캐릭터간 충돌(맵이동층일경우)
			블럭과 몬스터간 충돌

			층이동
*/
class BlockManager
{
private:
	BoundCheckArray<Block*> blockArr;
	int level;
	//static int index;
	int index;
	
public:
	~BlockManager();

	void Init(int level, Monster* seal);
	void Reset(Monster* seal);
	void Update();
	void Draw();

	void Collision(Character* cha, Character* cha2);
	bool Collision3(Character* cha, Character* cha2);
	void Collision_seal(Monster* mon);
	//void Collision2(Character* cha);
	//void AddBlock(int blockKind, int mapX, int mapY);
	void AddBlock(int blockKind, int mapX, int mapY, bool restoring);

	int getIndex() const { return index; }
	Block* getBlock(int i) const { return blockArr[i]; }
	//!
	void Floor(int floorY);
};
