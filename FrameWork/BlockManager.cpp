#pragma once
#include "Include.h"
//#include "BlockManager.h"
//#include "Block.h"
//#include "Monster.h"
//#include "Character.h"
/*
기능 :		소멸자
특이사항 :	생성된 블럭 객체 모두 해제
*/
BlockManager::~BlockManager()
{
	for (int i = 0; i< index; i++)
		delete blockArr[i];
}
/*
기능 :		초기화
매개변수 :	층 높이, 몬스터 객체포인터
반환 :		없음
특이사항 :	몬스터 객체가 초기화됨, 블럭 객체 생성 및 초기화
*/
void BlockManager::Init(int level, Monster* seal)
{
	index = 0;
	this->level = level;
	// 0층일때
	if (this->level == 0)
	{
		// 몬스터 초기화
		seal->Init(1, 26 - (level * 6), 1, false);	
		for (int j = 0; j < 6; j++)
		{
			for (int i = 0; i < 32; i++)
			{
				if (bottom[j][i] != 0)
				{
					// 블럭 객체 생성 및 초기화
					blockArr[index] = new Block;
					blockArr[index++]->Init(bottom[j][i], i, 26 - (6 - j) - (level * 6), 1);
				}
			}
		}
	}
	// 1층일때
	else if (this->level == 1)
	{
		seal->Init(1, 26 - (level * 6), 1, false);
		for (int j = 0; j < 6; j++)
		{
			for (int i = 0; i < 32; i++)
			{
				if (floors[3][j][i] != 0)
				{
					// 블럭 객체 생성 및 초기화
					blockArr[index] = new Block;
					blockArr[index++]->Init(floors[3][j][i], i, 27 - (6 - j) - (level * 6), 1);
				}
			}
		}
	}
	// 2~5층일때
	else
	{
		int select = rand() % 8;		// 0~7까지 맵중에 랜덤 생성
		if (select < 4)					// 기본맵일경우에만 몬스터 생성
		{
			bool s = rand() % 2;
			seal->Init(1, 26 - (level * 6), 1, s);	 // 몬스터는 랜덤으로 생성
		}
		else
			seal->Init(1, 26 - (level * 6), 1, true);
		for (int j = 0; j < 6; j++)
		{
			for (int i = 6; i < 26; i++)	// 구름블럭의 스프라이트이미지 순서를 처리하기위해 가운데부터 생성
			{
				if (floors[select][j][i] != 0)
				{
					// 블럭 객체 생성 및 초기화
					blockArr[index] = new Block;
					blockArr[index++]->Init(floors[select][j][i], i, 27 - (6 - j) - (level * 6), 1);
				}
			}
			for (int i = 26; i < 32; i++)
			{
				if (floors[select][j][i] != 0)
				{
					// 블럭 객체 생성 및 초기화
					blockArr[index] = new Block;
					blockArr[index++]->Init(floors[select][j][i], i, 27 - (6 - j) - (level * 6), 1);
				}
			}
			for (int i = 0; i < 6; i++)
			{
				if (floors[select][j][i] != 0)
				{
					// 블럭 객체 생성 및 초기화
					blockArr[index] = new Block;
					blockArr[index++]->Init(floors[select][j][i], i, 27 - (6 - j) - (level * 6), 1);
				}
			}
		}
	}
}
/*
기능 :		맵 리셋
매개변수 :	몬스터 객체포인터
반환 :		없음
특이사항 :	몬스터 객체가 초기화됨, 블럭 객체 생성 및 초기화
*/
//void BlockManager::Reset(Monster* seal)
//{
//	index = 0;
//	this->level = 6;			// 무조건 6층
//
//	int select = rand() % 12;	
//	if (select < 4)				// 기본맵일경우에만 몬스터 생성
//	{
//		bool s = rand() % 2;
//		seal->Init(1, 26 - (level * 6), 1, s);		// 몬스터는 랜덤을 생성됨
//	}
//	else
//		seal->Init(1, 26 - (level * 6), 1, false);
//	for (int j = 0; j < 6; j++)
//	{
//		for (int i = 6; i < 26; i++)
//		{
//			if (floors[select][j][i] != 0)
//			{
//				blockArr[index] = new Block;
//				blockArr[index++]->Init(floors[select][j][i], i, 27 - (6 - j) - (level * 6), 1);
//			}
//		}
//		for (int i = 26; i < 32; i++)
//		{
//			if (floors[select][j][i] != 0)
//			{
//				blockArr[index] = new Block;
//				blockArr[index++]->Init(floors[select][j][i], i, 27 - (6 - j) - (level * 6), 1);
//			}
//		}
//		for (int i = 0; i < 6; i++)
//		{
//			if (floors[select][j][i] != 0)
//			{
//				blockArr[index] = new Block;
//				blockArr[index++]->Init(floors[select][j][i], i, 27 - (6 - j) - (level * 6), 1);
//			}
//		}
//	}
//
//}

void BlockManager::Reset(Monster* seal)
{
	// 1. 기존 블럭 완전 삭제
	for (int i = 0; i < index; ++i) {
		if (blockArr[i]) {
			delete blockArr[i];
			blockArr[i] = nullptr;
		}
	}

	// 2. 인덱스 초기화
	index = 0;
	this->level = 6;

	// 3. 맵 선택 및 몬스터 초기화
	int select = rand() % 12;
	if (select < 4)
	{
		bool s = rand() % 2;
		seal->Init(1, 26 - (level * 6), 1, s);
	}
	else
		seal->Init(1, 26 - (level * 6), 1, false);

	// 4. 블럭 새로 생성
	for (int j = 0; j < 6; j++)
	{
		for (int i = 6; i < 26; i++)
		{
			if (floors[select][j][i] != 0)
			{
				blockArr[index] = new Block;
				blockArr[index++]->Init(floors[select][j][i], i, 27 - (6 - j) - (level * 6), 1);
			}
		}
		for (int i = 26; i < 32; i++)
		{
			if (floors[select][j][i] != 0)
			{
				blockArr[index] = new Block;
				blockArr[index++]->Init(floors[select][j][i], i, 27 - (6 - j) - (level * 6), 1);
			}
		}
		for (int i = 0; i < 6; i++)
		{
			if (floors[select][j][i] != 0)
			{
				blockArr[index] = new Block;
				blockArr[index++]->Init(floors[select][j][i], i, 27 - (6 - j) - (level * 6), 1);
			}
		}
	}
}


/*
기능 :		업데이트
매개변수 :	없음
반환 :		없음
특이사항 :	생성된 블럭객체 업데이트호출
*/
void BlockManager::Update()
{
	for (int i = 0; i < index; i++)
	{
		blockArr[i]->Update();
	}
}
/*
기능 :		드로우
매개변수 :	없음
반환 :		없음
특이사항 :	생성된 블럭객체 드로우호출
*/
void BlockManager::Draw()
{
	for (int i = 0; i < index; i++)
	{
		if (!blockArr[i] || !blockArr[i]->getOnoff()) continue;
		blockArr[i]->Draw();
	}
}
/*
기능 :		맵 이동
매개변수 :	없음
반환 :		없음
특이사항 :	생성된 블럭객체 맵 이동호출
*/
void BlockManager::Floor(int floorY)
{
	for (int i = 0; i < index; i++)
	{
		blockArr[i]->Floor(floorY);
	}
}
/*
기능 :		블럭과 플레이어간 충돌
매개변수 :	없음
반환 :		없음
특이사항 :	없음
*/
void BlockManager::Collision(Character* cha, Character* cha2)
{
	// 충돌값을 저장
	Col ch_temp = cha->getCol_temp();
	Col ch = cha->getCol();
	Col ch_temp2 = cha2->getCol_temp();
	Col ch2 = cha2->getCol();
	// 1p
	for (int i = 0; i < index; i++)
	{
		// 떨어지는중
		if (!cha->getJump_state())
		{
			int check = blockArr[i]->Collision_V(ch_temp.chx, ch_temp.chX, ch_temp.chy, ch_temp.chY);
			if (check == UP || check == 6)										// 무언가의 윗부분에 충돌
			{
				int kind = blockArr[i]->getBoxKind();
				if (kind == 3 || kind == 4 || kind == 5)						// 구름이나 스피드 블럭에 착지시 자동이동적용
				{
					cha->setAutomove_state(true);
				}
				cha->setFloor_collision_temp(true);								// 충돌 전환
				cha->setExtra_fall_y(abs(blockArr[i]->getBlocky() - ch.chY));	// 여분값 계산
			}
			if (cha->getAutomove_state())										// 이전 블럭들중 자동이동 있었으면
			{
				for (int j = 0; j < index; j++)									// 모든 블럭을 처음부터 싹 뒤지면서
				{
					int check2 = blockArr[j]->Collision_H(ch.chx - 4, ch.chX, ch.chy + 1, ch.chY - 1);
					if (check2 == RIGHT || check2 == 6)							// 무언가의 오른쪽부분에 충돌
						cha->setAutomove_state(false);							// 자동이동 전환
				}
				int check3 = cha->Collision_H(ch2.chx, ch2.chX + 14, ch2.chy + 1, ch2.chY - 1);
				if (check3 == RIGHT || check3 == 6)								// 플레이어2의 오른쪽부분에 충돌
					cha->setAutomove_state(false);
			}
		}
		// 점프 중	
		else								
		{
			if (blockArr[i]->Collision_V(ch_temp.chx, ch_temp.chX, ch_temp.chy, ch_temp.chY) == DOWN)		// 무언가의 아래부분에 충돌
			{
				int kind = blockArr[i]->getBoxKind();
				if (kind == 1 || kind == 3)																	// 일반블럭 스피드블럭일 경우
				{
					sound.m_HitIce->Play(0, NULL);															// 파괴 사운드 출력
					blockArr[i]->Destroy(cha->getPlayer());													// 파괴
					playdata.p1_block_count++;
				}
				else if (kind == 2 || kind == 4 || kind == 5) {												// 벽블럭일 경우
					sound.m_HitHard->Play(0, NULL);															// 벽 사운드 출력
				}
				cha->setJump_collision_temp(true);															// 충돌전환
				cha->setExtra_jump_y(-abs(blockArr[i]->getBlockY() - ch.chy));								// 여분값 계산
			}
		}
		// 우로 이동중
		if (cha->getMove_state_r())
		{
			int check = blockArr[i]->Collision_H(ch.chx, ch.chX + 4, ch.chy + 1, ch.chY - 1);
			if (check == LEFT || check == 6)																// 무언가의 왼쪽부분에 충돌
			{
				cha->setMove_collision_r(true);																// 충돌전환
			}
		}
		// 좌로 이동중
		if (cha->getMove_state_l())
		{
			int check = blockArr[i]->Collision_H(ch.chx - 4, ch.chX, ch.chy + 1, ch.chY - 1);
			if (check == RIGHT || check == 6)																// 무언가의 오른쪽부분에 충돌
			{
				cha->setMove_collision_l(true);																// 충돌전환
			}
		}
	}
	// 2p
	for (int i = 0; i < index; i++)
	{
		// 떨어지는중
		if (!cha2->getJump_state())
		{
			int check = blockArr[i]->Collision_V2(ch_temp2.chx, ch_temp2.chX, ch_temp2.chy, ch_temp2.chY);
			if (check == UP || check == 6)																		// 무언가의 윗부분에 충돌
			{
				int kind = blockArr[i]->getBoxKind();
				if (kind == 3 || kind == 4 || kind == 5)														// 구름이나 스피드 블럭에 착지시 자동이동적용
				{
					cha2->setAutomove_state(true);																
				}
				cha2->setFloor_collision_temp(true);															// 충돌 전환
				cha2->setExtra_fall_y(abs(blockArr[i]->getBlocky() - ch2.chY));									// 여분값 계산
			}
			if (cha2->getAutomove_state())																		// 이전 블럭들중 자동이동 있었으면
			{
				for (int j = 0; j < index; j++)																	// 모든 블럭을 처음부터 싹 뒤지면서
				{
					int check2 = blockArr[j]->Collision_H2(ch2.chx - 4, ch2.chX, ch2.chy + 1, ch2.chY - 1);
					if (check2 == RIGHT || check2 == 6)															// 무언가의 오른쪽부분에 충돌
						cha2->setAutomove_state(false);
				}
				int check3 = cha2->Collision_H(ch.chx, ch.chX + 14, ch.chy + 1, ch.chY - 1);
				if (check3 == RIGHT || check3 == 6)																// 무언가의 오른쪽부분에 충돌
					cha2->setAutomove_state(false);
			}
		}
		else// 점프 중									
		{
			if (blockArr[i]->Collision_V2(ch_temp2.chx, ch_temp2.chX, ch_temp2.chy, ch_temp2.chY) == DOWN)		// 무언가의 아래부분에 충돌
			{
				int kind = blockArr[i]->getBoxKind();
				if (kind == 1 || kind == 3)																		// 일반블럭 스피드블럭
				{
					sound.m_HitIce->Play(0, NULL);																// 파괴 사운드 출력	
					blockArr[i]->Destroy(cha2->getPlayer());													// 파괴
					playdata.p2_block_count++;
				}
				else if (kind == 2 || kind == 4 || kind == 5) {													// 벽블럭일 경우
					sound.m_HitHard->Play(0, NULL);																// 벽 사운드 출력
				}
				cha2->setJump_collision_temp(true);																// 충돌전환
				cha2->setExtra_jump_y(-abs(blockArr[i]->getBlockY() - ch.chy));									// 여분값 계산
			}
		}
		// 우로 이동중
		if (cha2->getMove_state_r())
		{
			int check = blockArr[i]->Collision_H2(ch2.chx, ch2.chX + 4, ch2.chy + 1, ch2.chY - 1);
			if (check == LEFT || check == 6)																	// 무언가의 왼쪽부분에 충돌
			{
				cha2->setMove_collision_r(true);																// 충돌전환
			}
		}
		// 좌로 이동중
		if (cha2->getMove_state_l())
		{
			int check = blockArr[i]->Collision_H2(ch2.chx - 4, ch2.chX, ch2.chy + 1, ch2.chY - 1);
			if (check == RIGHT || check == 6)																	// 무언가의 오른쪽부분에 충돌
			{
				cha2->setMove_collision_l(true);																// 충돌전환
			}
		}
	}
}
/*
기능 :		블럭과 캐릭터간 충돌(맵이동층일경우)
매개변수 :	없음
반환 :		맵이동 상태 변수
특이사항 :	떨어지는중 충돌시 맵이동 상태를 전환
*/
bool BlockManager::Collision3(Character * cha, Character * cha2)
{
	bool floorcheck = false;
	
	Col ch_temp = cha->getCol_temp();
	Col ch = cha->getCol();
	Col ch_temp2 = cha2->getCol_temp();
	Col ch2 = cha2->getCol();
	// 1p
	for (int i = 0; i < index; i++)
	{
		// 떨어지는중
		if (!cha->getJump_state())
		{
			int check = blockArr[i]->Collision_V(ch_temp.chx, ch_temp.chX, ch_temp.chy, ch_temp.chY);
			if (check == UP || check == 6)										// 무언가의 윗부분에 충돌
			{
				int kind = blockArr[i]->getBoxKind();
				if (kind == 3 || kind == 4 || kind == 5)						// 구름이나 스피드 블럭에 착지시 자동이동적용
				{
					cha->setAutomove_state(true);
				}
				cha->setFloor_collision_temp(true);								// 충돌 전환
				cha->setExtra_fall_y(abs(blockArr[i]->getBlocky() - ch.chY));	// 여분값 계산
			}
			if (check == UP)													// 떨어지는중에 착지시 맵이동 상태전환
			{
				floorcheck = true;
			}
			if (cha->getAutomove_state())										// 이전 블럭들중 자동이동 있었으면
			{
				for (int j = 0; j < index; j++)									// 모든 블럭을 처음부터 싹 뒤지면서
				{
					int check2 = blockArr[j]->Collision_H(ch.chx - 4, ch.chX, ch.chy + 1, ch.chY - 1);
					if (check2 == RIGHT || check2 == 6)							// 무언가의 오른쪽부분에 충돌
						cha->setAutomove_state(false);							// 자동이동 전환
				}
				int check3 = cha->Collision_H(ch2.chx, ch2.chX + 14, ch2.chy + 1, ch2.chY - 1);
				if (check3 == RIGHT || check3 == 6)								// 플레이어2의 오른쪽부분에 충돌
					cha->setAutomove_state(false);
			}
		}
		// 점프 중	
		else
		{
			if (blockArr[i]->Collision_V(ch_temp.chx, ch_temp.chX, ch_temp.chy, ch_temp.chY) == DOWN)		// 무언가의 아래부분에 충돌
			{
				int kind = blockArr[i]->getBoxKind();
				if (kind == 1 || kind == 3)																	// 일반블럭 스피드블럭일 경우
				{
					sound.m_HitIce->Play(0, NULL);															// 파괴 사운드 출력
					blockArr[i]->Destroy(cha->getPlayer());													// 파괴
					playdata.p1_block_count++;
				}
				else if (kind == 2 || kind == 4 || kind == 5) {												// 벽블럭일 경우
					sound.m_HitHard->Play(0, NULL);															// 벽 사운드 출력
				}
				cha->setJump_collision_temp(true);															// 충돌전환
				cha->setExtra_jump_y(-abs(blockArr[i]->getBlockY() - ch.chy));								// 여분값 계산
			}
		}
		// 우로 이동중
		if (cha->getMove_state_r())
		{
			int check = blockArr[i]->Collision_H(ch.chx, ch.chX + 4, ch.chy + 1, ch.chY - 1);
			if (check == LEFT || check == 6)																// 무언가의 왼쪽부분에 충돌
			{
				cha->setMove_collision_r(true);																// 충돌전환
			}
		}
		// 좌로 이동중
		if (cha->getMove_state_l())
		{
			int check = blockArr[i]->Collision_H(ch.chx - 4, ch.chX, ch.chy + 1, ch.chY - 1);
			if (check == RIGHT || check == 6)																// 무언가의 오른쪽부분에 충돌
			{
				cha->setMove_collision_l(true);																// 충돌전환
			}
		}
	}
	// 2p
	for (int i = 0; i < index; i++)
	{
		// 떨어지는중
		if (!cha2->getJump_state())
		{
			int check = blockArr[i]->Collision_V2(ch_temp2.chx, ch_temp2.chX, ch_temp2.chy, ch_temp2.chY);
			if (check == UP || check == 6)																		// 무언가의 윗부분에 충돌
			{
				int kind = blockArr[i]->getBoxKind();
				if (kind == 3 || kind == 4 || kind == 5)														// 구름이나 스피드 블럭에 착지시 자동이동적용
				{
					cha2->setAutomove_state(true);
				}
				cha2->setFloor_collision_temp(true);															// 충돌 전환
				cha2->setExtra_fall_y(abs(blockArr[i]->getBlocky() - ch2.chY));									// 여분값 계산
			}
			if (check == UP)																					// 떨어지는중에 착지시 맵이동 상태전환
			{
				floorcheck = true;
			}
			if (cha2->getAutomove_state())																		// 이전 블럭들중 자동이동 있었으면
			{
				for (int j = 0; j < index; j++)																	// 모든 블럭을 처음부터 싹 뒤지면서
				{
					int check2 = blockArr[j]->Collision_H2(ch2.chx - 4, ch2.chX, ch2.chy + 1, ch2.chY - 1);
					if (check2 == RIGHT || check2 == 6)															// 무언가의 오른쪽부분에 충돌
						cha2->setAutomove_state(false);
				}
				int check3 = cha2->Collision_H(ch.chx, ch.chX + 14, ch.chy + 1, ch.chY - 1);
				if (check3 == RIGHT || check3 == 6)																// 무언가의 오른쪽부분에 충돌
					cha2->setAutomove_state(false);
			}
		}
		else// 점프 중									
		{
			if (blockArr[i]->Collision_V2(ch_temp2.chx, ch_temp2.chX, ch_temp2.chy, ch_temp2.chY) == DOWN)		// 무언가의 아래부분에 충돌
			{
				int kind = blockArr[i]->getBoxKind();
				if (kind == 1 || kind == 3)																		// 일반블럭 스피드블럭
				{
					sound.m_HitIce->Play(0, NULL);																// 파괴 사운드 출력	
					blockArr[i]->Destroy(cha2->getPlayer());													// 파괴
					playdata.p2_block_count++;
				}
				else if (kind == 2 || kind == 4 || kind == 5) {													// 벽블럭일 경우
					sound.m_HitHard->Play(0, NULL);																// 벽 사운드 출력
				}
				cha2->setJump_collision_temp(true);																// 충돌전환
				cha2->setExtra_jump_y(-abs(blockArr[i]->getBlockY() - ch.chy));									// 여분값 계산
			}
		}
		// 우로 이동중
		if (cha2->getMove_state_r())
		{
			int check = blockArr[i]->Collision_H2(ch2.chx, ch2.chX + 4, ch2.chy + 1, ch2.chY - 1);
			if (check == LEFT || check == 6)																	// 무언가의 왼쪽부분에 충돌
			{
				cha2->setMove_collision_r(true);																// 충돌전환
			}
		}
		// 좌로 이동중
		if (cha2->getMove_state_l())
		{
			int check = blockArr[i]->Collision_H2(ch2.chx - 4, ch2.chX, ch2.chy + 1, ch2.chY - 1);
			if (check == RIGHT || check == 6)																	// 무언가의 오른쪽부분에 충돌
			{
				cha2->setMove_collision_l(true);																// 충돌전환
			}
		}
	}
	return floorcheck;
}
/*
기능 :		블럭과 몬스터간 충돌
매개변수 :	없음
반환 :		없음
특이사항 :	없음
*/
void BlockManager::Collision_seal(Monster* mon)
{
	if (!mon || !mon->getOnoff()) return;
	
	for (int i = 0; i < index; i++) {
		if (!blockArr[i]) continue;

		// 기존 onoff 체크 → IsSolidForMonster()로 변경
		if (blockArr[i]->IsSolidForMonster()) {
			int check = mon->Collision_floor(
				blockArr[i]->getBlockx(),
				blockArr[i]->getBlockX(),
				blockArr[i]->getBlocky(),
				blockArr[i]->getBlockY(),
				true
			);
			if (check == 6 || check == 1) {
				mon->setCol_floor(true);
			}
		}
	}

	// 턴 충돌은 유지
	for (int i = 0; i < index; i++) {
		if (!blockArr[i]) continue;

		if (blockArr[i]->IsSolidForMonster()) {
			int check = mon->Collision_turn(
				blockArr[i]->getBlockx(),
				blockArr[i]->getBlockX(),
				blockArr[i]->getBlocky(),
				blockArr[i]->getBlockY(),
				true
			);
			if (check == 1) mon->setCol_front_turn(true);
			else if (check == 2) mon->setCol_down_turn(true);
		}
	}
}

void BlockManager::AddBlock(int blockKind, int mapX, int mapY, bool restoring)
{
	blockArr[index] = new Block;
	blockArr[index]->Init(blockKind, mapX, mapY, 1);

	if (restoring)
		blockArr[index]->SetRestoring(true);

	index++; 
}

