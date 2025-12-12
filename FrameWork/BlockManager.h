#pragma once
#include "Include.h" 
// 템플릿 배열 사용
#include "BoundCheckArray.h"  

// 헤더 파일에서 Monster* 사용만 할 경우 Forward 선언!
class Monster;    
class Block;
class Character;

/*
용도 :		맥
맴버 변수 :	블록 클래스 포인터 배열
			층 높이
			블록 인덱스

맴버 함수 :	소멸자

			초기화
			리셋
			업데이트
			드로우

			블록과 캐릭터 간 충돌
			블록과 캐릭터 간 충돌(맵 이동 층일 경우)
			블록과 몬스터 간 충돌

			층 이동
*/
class BlockManager
{
private:

	BoundCheckArray<Block*> blockArr;
	int level;
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

	void AddBlock(int blockKind, int mapX, int mapY, bool restoring);

	int getIndex() const { return index; }
	Block* getBlock(int i) const { return blockArr[i]; }
	void Floor(int floorY);
};
