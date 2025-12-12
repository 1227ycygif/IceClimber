#pragma once
#include "Include.h"

/*
기능 :		소멸자
특이사항 :	생성된 블록 객체 모두 해제
*/
BlockManager::~BlockManager()
{
	for (int i = 0; i< index; i++)
		delete blockArr[i];
}

/*
기능 :		초기화
매개변수 :	층 높이, 몬스터 객체 포인터
반환 :		없음
특이사항 :	몬스터 객체가 초기화됨, 블록 객체 생성 및 초기화
*/
void BlockManager::Init(int level, Monster* seal)
{
	index = 0;
	this->level = level;

	// 0층일 때
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
					// 블록 객체 생성 및 초기화
					blockArr[index] = new Block;
					blockArr[index++]->Init(bottom[j][i], i, 26 - (6 - j) - (level * 6), 1);
				}
			}
		}
	}
	// 1층일 때
	else if (this->level == 1)
	{
		seal->Init(1, 26 - (level * 6), 1, false);

		for (int j = 0; j < 6; j++)
		{
			for (int i = 0; i < 32; i++)
			{
				if (floors[3][j][i] != 0)
				{
					// 블록 객체 생성 및 초기화
					blockArr[index] = new Block;
					blockArr[index++]->Init(floors[3][j][i], i, 27 - (6 - j) - (level * 6), 1);
				}
			}
		}
	}

	// 2~5층일 때
	else
	{
		// 0~7까지 맵중에 랜덤 생성
		int select = rand() % 8;		
		// 기본 맵일 경우에만 몬스터 생성
		if (select < 4)					
		{
			bool s = rand() % 2;
			// 몬스터는 랜덤으로 생성
			seal->Init(1, 26 - (level * 6), 1, s);	 
		}
		else
		{
			seal->Init(1, 26 - (level * 6), 1, true);
		}
			
		for (int j = 0; j < 6; j++)
		{
			// 구름 블록의 스프라이트 순서를 처리하기 위해 가운데부터 생성
			for (int i = 6; i < 26; i++)	
			{
				if (floors[select][j][i] != 0)
				{
					// 블록 객체 생성 및 초기화
					blockArr[index] = new Block;
					blockArr[index++]->Init(floors[select][j][i], i, 27 - (6 - j) - (level * 6), 1);
				}
			}

			for (int i = 26; i < 32; i++)
			{
				if (floors[select][j][i] != 0)
				{
					// 블록 객체 생성 및 초기화
					blockArr[index] = new Block;
					blockArr[index++]->Init(floors[select][j][i], i, 27 - (6 - j) - (level * 6), 1);
				}
			}

			for (int i = 0; i < 6; i++)
			{
				if (floors[select][j][i] != 0)
				{
					// 블록 객체 생성 및 초기화
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
특이사항 :	몬스터 객체가 초기화됨, 블록 객체 생성 및 초기화
*/
void BlockManager::Reset(Monster* seal)
{
	// 1. 기존 블록 완전 삭제
	for (int i = 0; i < index; ++i) 
	{
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
	{
		seal->Init(1, 26 - (level * 6), 1, false);
	}
		
	// 4. 블록 새로 생성
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
특이사항 :	생성된 블록 객체 업데이트 호출
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
특이사항 :	생성된 블록 객체 드로우 호출
*/
void BlockManager::Draw()
{
	for (int i = 0; i < index; i++)
	{
		if (!blockArr[i] || !blockArr[i]->getOnoff())
		{
			continue;
		}
		blockArr[i]->Draw();
	}
}

/*
기능 :		맵 이동
매개변수 :	없음
반환 :		없음
특이사항 :	생성된 블록 객체 맵 이동 호출
*/
void BlockManager::Floor(int floorY)
{
	for (int i = 0; i < index; i++)
	{
		blockArr[i]->Floor(floorY);
	}
}

/*
기능 :		블록과 플레이어 간 충돌
매개변수 :	없음
반환 :		없음
특이사항 :	없음
*/
void BlockManager::Collision(Character* cha, Character* cha2)
{
	// 충돌 값을 저장
	Col ch_temp = cha->getCol_temp();
	Col ch = cha->getCol();
	Col ch_temp2 = cha2->getCol_temp();
	Col ch2 = cha2->getCol();

	// 1p
	for (int i = 0; i < index; i++)
	{
		// 떨어지는 중
		if (!cha->getJump_state())
		{
			int check = blockArr[i]->Collision_V(ch_temp.chx, ch_temp.chX, ch_temp.chy, ch_temp.chY);
			// 무언가의 윗 부분에 충돌
			if (check == UP || check == 6)										
			{
				int kind = blockArr[i]->getBoxKind();
				// 구름이나 스피드 블록에 착지 시 자동 이동 적용
				if (kind == 3 || kind == 4 || kind == 5)						
				{
					cha->setAutomove_state(true);
				}
				// 충돌 전환
				cha->setFloor_collision_temp(true);								
				// 여분 값 계산
				cha->setExtra_fall_y(abs(blockArr[i]->getBlocky() - ch.chY));	
			}

			// 이전 블록들 중 자동 이동 있었으면
			if (cha->getAutomove_state())										
			{
				// 모든 블록을 처음부터 찾으면서
				for (int j = 0; j < index; j++)									
				{
					int check2 = blockArr[j]->Collision_H(ch.chx - 4, ch.chX, ch.chy + 1, ch.chY - 1);
					
					// 무언가의 오른쪽 부분에 충돌
					if (check2 == RIGHT || check2 == 6)
					{
						// 자동 이동 전환
						cha->setAutomove_state(false);
					}
				}
				int check3 = cha->Collision_H(ch2.chx, ch2.chX + 14, ch2.chy + 1, ch2.chY - 1);
				// 플레이어2의 오른쪽 부분에 충돌
				if (check3 == RIGHT || check3 == 6)
				{
					cha->setAutomove_state(false);
				}
			}
		}

		// 점프 중	
		else								
		{
			// 무언가의 아랫 부분에 충돌
			if (blockArr[i]->Collision_V(ch_temp.chx, ch_temp.chX, ch_temp.chy, ch_temp.chY) == DOWN)		
			{
				int kind = blockArr[i]->getBoxKind();
				// 일반블록 스피드블록일 경우
				if (kind == 1 || kind == 3)	
				{
					// 파괴 사운드 출력
					sound.m_HitIce->Play(0, NULL);															
					// 파괴
					blockArr[i]->Destroy(cha->getPlayer());													
					playdata.p1_block_count++;
				}
				// 벽 블록일 경우
				else if (kind == 2 || kind == 4 || kind == 5) 
				{
					// 벽 사운드 출력
					sound.m_HitHard->Play(0, NULL);															
				}
				// 충돌 전환
				cha->setJump_collision_temp(true);	
				// 여분 값 계산
				cha->setExtra_jump_y(-abs(blockArr[i]->getBlockY() - ch.chy));								
			}
		}

		// 우로 이동 중
		if (cha->getMove_state_r())
		{
			int check = blockArr[i]->Collision_H(ch.chx, ch.chX + 4, ch.chy + 1, ch.chY - 1);
			// 무언가의 왼쪽 부분에 충돌
			if (check == LEFT || check == 6)																
			{
				// 충돌 전환
				cha->setMove_collision_r(true);																
			}
		}

		// 좌로 이동중
		if (cha->getMove_state_l())
		{
			int check = blockArr[i]->Collision_H(ch.chx - 4, ch.chX, ch.chy + 1, ch.chY - 1);
			// 무언가의 오른쪽 부분에 충돌
			if (check == RIGHT || check == 6)	
			{
				// 충돌 전환
				cha->setMove_collision_l(true);																
			}
		}
	}

	// 2p
	for (int i = 0; i < index; i++)
	{
		// 떨어지는 중
		if (!cha2->getJump_state())
		{
			int check = blockArr[i]->Collision_V2(ch_temp2.chx, ch_temp2.chX, ch_temp2.chy, ch_temp2.chY);
			// 무언가의 윗 부분에 충돌
			if (check == UP || check == 6)	
			{
				int kind = blockArr[i]->getBoxKind();
				// 구름이나 스피드 블록에 착지 시 자동 이동 적용
				if (kind == 3 || kind == 4 || kind == 5)
				{
					cha2->setAutomove_state(true);																
				}
				// 충돌 전환
				cha2->setFloor_collision_temp(true);						
				// 여분 값 계산
				cha2->setExtra_fall_y(abs(blockArr[i]->getBlocky() - ch2.chY));									
			}

			// 이전 블록들 중 자동 이동 있었으면
			if (cha2->getAutomove_state())																		
			{
				// 모든 블록을 처음부터 찾으면서
				for (int j = 0; j < index; j++)																	
				{
					int check2 = blockArr[j]->Collision_H2(ch2.chx - 4, ch2.chX, ch2.chy + 1, ch2.chY - 1);
					// 무언가의 오른쪽 부분에 충돌
					if (check2 == RIGHT || check2 == 6)
					{
						cha2->setAutomove_state(false);
					}
				}

				int check3 = cha2->Collision_H(ch.chx, ch.chX + 14, ch.chy + 1, ch.chY - 1);
				// 무언가의 오른쪽 부분에 충돌
				if (check3 == RIGHT || check3 == 6)
				{
					cha2->setAutomove_state(false);
				}
			}
		}
		// 점프 중	
		else								
		{
			// 무언가의 아랫 부분에 충돌
			if (blockArr[i]->Collision_V2(ch_temp2.chx, ch_temp2.chX, ch_temp2.chy, ch_temp2.chY) == DOWN)		
			{
				int kind = blockArr[i]->getBoxKind();
				// 일반 블록, 스피드 블록
				if (kind == 1 || kind == 3)																		
				{
					// 파괴 사운드 출력	
					sound.m_HitIce->Play(0, NULL);	
					// 파괴
					blockArr[i]->Destroy(cha2->getPlayer());													
					playdata.p2_block_count++;
				}
				// 벽 블록일 경우
				else if (kind == 2 || kind == 4 || kind == 5) 
				{
					// 벽 사운드 출력
					sound.m_HitHard->Play(0, NULL);																
				}
				// 충돌 전환
				cha2->setJump_collision_temp(true);	
				// 여분 값 계산
				cha2->setExtra_jump_y(-abs(blockArr[i]->getBlockY() - ch.chy));									
			}
		}

		// 우로 이동 중
		if (cha2->getMove_state_r())
		{
			int check = blockArr[i]->Collision_H2(ch2.chx, ch2.chX + 4, ch2.chy + 1, ch2.chY - 1);
			// 무언가의 왼쪽 부분에 충돌
			if (check == LEFT || check == 6)																	
			{
				// 충돌 전환
				cha2->setMove_collision_r(true);																
			}
		}

		// 좌로 이동 중
		if (cha2->getMove_state_l())
		{
			int check = blockArr[i]->Collision_H2(ch2.chx - 4, ch2.chX, ch2.chy + 1, ch2.chY - 1);
			// 무언가의 오른쪽 부분에 충돌
			if (check == RIGHT || check == 6)																	
			{
				// 충돌 전환
				cha2->setMove_collision_l(true);																
			}
		}
	}
}

/*
기능 :		블록과 캐릭터 간 충돌(맵 이동 층일 경우)
매개변수 :	없음
반환 :		맵 이동 상태 변수
특이사항 :	떨어지는 중 충돌 시 맵 이동 상태를 전환
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
		// 떨어지는 중
		if (!cha->getJump_state())
		{
			int check = blockArr[i]->Collision_V(ch_temp.chx, ch_temp.chX, ch_temp.chy, ch_temp.chY);
			// 무언가의 윗 부분에 충돌
			if (check == UP || check == 6)										
			{
				int kind = blockArr[i]->getBoxKind();
				// 구름이나 스피드 블록에 착지 시 자동 이동 적용
				if (kind == 3 || kind == 4 || kind == 5)						
				{
					cha->setAutomove_state(true);
				}
				// 충돌 전환
				cha->setFloor_collision_temp(true);								
				// 여분 값 계산
				cha->setExtra_fall_y(abs(blockArr[i]->getBlocky() - ch.chY));	
			}

			// 떨어지는 중에 착지 시 맵 이동 상태 전환
			if (check == UP)													
			{
				floorcheck = true;
			}

			// 이전 블록들 중 자동 이동 있었으면
			if (cha->getAutomove_state())										
			{
				// 모든 블록을 처음부터 찾으면서
				for (int j = 0; j < index; j++)									
				{
					int check2 = blockArr[j]->Collision_H(ch.chx - 4, ch.chX, ch.chy + 1, ch.chY - 1);
					// 무언가의 오른쪽 부분에 충돌
					if (check2 == RIGHT || check2 == 6)
					{
						// 자동이동 전환
						cha->setAutomove_state(false);
					}							
				}
				int check3 = cha->Collision_H(ch2.chx, ch2.chX + 14, ch2.chy + 1, ch2.chY - 1);
				// 플레이어2의 오른쪽 부분에 충돌
				if (check3 == RIGHT || check3 == 6)
				{
					cha->setAutomove_state(false);
				}
			}
		}

		// 점프 중	
		else
		{
			// 무언가의 아랫 부분에 충돌
			if (blockArr[i]->Collision_V(ch_temp.chx, ch_temp.chX, ch_temp.chy, ch_temp.chY) == DOWN)		
			{
				int kind = blockArr[i]->getBoxKind();
				// 일반 블록, 스피드 블록일 경우
				if (kind == 1 || kind == 3)																	
				{
					// 파괴 사운드 출력
					sound.m_HitIce->Play(0, NULL);															
					// 파괴
					blockArr[i]->Destroy(cha->getPlayer());													
					playdata.p1_block_count++;
				}
				// 벽 블록일 경우
				else if (kind == 2 || kind == 4 || kind == 5) 
				{
					// 벽 사운드 출력
					sound.m_HitHard->Play(0, NULL);															
				}
				// 충돌 전환
				cha->setJump_collision_temp(true);															
				// 여분 값 계산
				cha->setExtra_jump_y(-abs(blockArr[i]->getBlockY() - ch.chy));								
			}
		}

		// 우로 이동 중
		if (cha->getMove_state_r())
		{
			int check = blockArr[i]->Collision_H(ch.chx, ch.chX + 4, ch.chy + 1, ch.chY - 1);
			// 무언가의 왼쪽 부분에 충돌
			if (check == LEFT || check == 6)																
			{
				// 충돌 전환
				cha->setMove_collision_r(true);																
			}
		}

		// 좌로 이동 중
		if (cha->getMove_state_l())
		{
			int check = blockArr[i]->Collision_H(ch.chx - 4, ch.chX, ch.chy + 1, ch.chY - 1);
			// 무언가의 오른쪽 부분에 충돌
			if (check == RIGHT || check == 6)																
			{
				// 충돌 전환
				cha->setMove_collision_l(true);																
			}
		}
	}

	// 2p
	for (int i = 0; i < index; i++)
	{
		// 떨어지는 중
		if (!cha2->getJump_state())
		{
			int check = blockArr[i]->Collision_V2(ch_temp2.chx, ch_temp2.chX, ch_temp2.chy, ch_temp2.chY);
			// 무언가의 윗 부분에 충돌
			if (check == UP || check == 6)																		
			{
				int kind = blockArr[i]->getBoxKind();
				// 구름이나 스피드 블록에 착지 시 자동 이동 적용
				if (kind == 3 || kind == 4 || kind == 5)														
				{
					cha2->setAutomove_state(true);
				}
				// 충돌 전환
				cha2->setFloor_collision_temp(true);															
				// 여분 값 계산
				cha2->setExtra_fall_y(abs(blockArr[i]->getBlocky() - ch2.chY));									
			}

			// 떨어지는 중에 착지 시 맵 이동 상태 전환
			if (check == UP)																					
			{
				floorcheck = true;
			}

			// 이전 블록들 중 자동 이동 있었으면
			if (cha2->getAutomove_state())																		
			{
				// 모든 블록을 처음부터 찾으면서
				for (int j = 0; j < index; j++)																	
				{
					int check2 = blockArr[j]->Collision_H2(ch2.chx - 4, ch2.chX, ch2.chy + 1, ch2.chY - 1);
					// 무언가의 오른쪽 부분에 충돌
					if (check2 == RIGHT || check2 == 6)
					{
						cha2->setAutomove_state(false);
					}
				}
				int check3 = cha2->Collision_H(ch.chx, ch.chX + 14, ch.chy + 1, ch.chY - 1);
				// 무언가의 오른쪽 부분에 충돌
				if (check3 == RIGHT || check3 == 6)
				{
					cha2->setAutomove_state(false);
				}
			}
		}
		// 점프 중
		else 									
		{
			// 무언가의 아랫 부분에 충돌
			if (blockArr[i]->Collision_V2(ch_temp2.chx, ch_temp2.chX, ch_temp2.chy, ch_temp2.chY) == DOWN)		
			{
				int kind = blockArr[i]->getBoxKind();
				// 일반 블록, 스피드 블록
				if (kind == 1 || kind == 3)																		
				{
					// 파괴 사운드 출력
					sound.m_HitIce->Play(0, NULL);																	
					// 파괴
					blockArr[i]->Destroy(cha2->getPlayer());													
					playdata.p2_block_count++;
				}
				// 벽 블록일 경우
				else if (kind == 2 || kind == 4 || kind == 5) 
				{													
					// 벽 사운드 출력
					sound.m_HitHard->Play(0, NULL);																
				}
				// 충돌 전환
				cha2->setJump_collision_temp(true);																
				// 여분 값 계산
				cha2->setExtra_jump_y(-abs(blockArr[i]->getBlockY() - ch.chy));									
			}
		}

		// 우로 이동 중
		if (cha2->getMove_state_r())
		{
			int check = blockArr[i]->Collision_H2(ch2.chx, ch2.chX + 4, ch2.chy + 1, ch2.chY - 1);
			// 무언가의 왼쪽 부분에 충돌
			if (check == LEFT || check == 6)																	
			{
				// 충돌 전환
				cha2->setMove_collision_r(true);																
			}
		}

		// 좌로 이동 중
		if (cha2->getMove_state_l())
		{
			int check = blockArr[i]->Collision_H2(ch2.chx - 4, ch2.chX, ch2.chy + 1, ch2.chY - 1);
			// 무언가의 오른쪽 부분에 충돌
			if (check == RIGHT || check == 6)																	
			{
				// 충돌 전환
				cha2->setMove_collision_l(true);																
			}
		}
	}
	return floorcheck;
}

/*
기능 :		블록과 몬스터간 충돌
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
		if (blockArr[i]->IsSolidForMonster()) 
		{
			int check = mon->Collision_floor(
				blockArr[i]->getBlockx(),
				blockArr[i]->getBlockX(),
				blockArr[i]->getBlocky(),
				blockArr[i]->getBlockY(),
				true
			);

			if (check == 6 || check == 1) 
			{
				mon->setCol_floor(true);
			}
		}
	}

	// 턴 충돌은 유지
	for (int i = 0; i < index; i++) 
	{
		if (!blockArr[i])
		{
			continue;
		}

		if (blockArr[i]->IsSolidForMonster()) 
		{
			int check = mon->Collision_turn(
				blockArr[i]->getBlockx(),
				blockArr[i]->getBlockX(),
				blockArr[i]->getBlocky(),
				blockArr[i]->getBlockY(),
				true
			);

			if (check == 1)
			{
				mon->setCol_front_turn(true);
			}
			else if (check == 2) 
			{
				mon->setCol_down_turn(true);
			}
		}
	}
}

void BlockManager::AddBlock(int blockKind, int mapX, int mapY, bool restoring)
{
	blockArr[index] = new Block;
	blockArr[index]->Init(blockKind, mapX, mapY, 1);

	if (restoring)
	{
		blockArr[index]->SetRestoring(true);
	}
	index++; 
}