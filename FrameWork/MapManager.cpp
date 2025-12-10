#pragma once
#include"Include.h"


MapManager mapManager;
/*
기능 :		생성자
특이사항 :	없음
*/
MapManager::MapManager()
{
}
/*
기능 :		소멸자
특이사항 :	생성된 블럭매니저, 몬스터, 플레이어 객체 모두 해제
*/
MapManager::~MapManager()
{
	for (int i = 0; i < 6; i++)
	{
		delete seal[i];
		delete blockMap[i];
	}
	delete cha;
	delete cha2;
}

/*
기능 :		초기화
매개변수 :	없음
반환 :		없음
특이사항 :	몬스터 객체 생성, 블럭매니저 객체 생성 및 초기화, 플레이어 객체 생성 및 초기화
*/
void MapManager::Init()
{
	floor_move_now = 3;
	floor_skip_1 = 0;
	floor_skip_2 = 5;
	floorY = 0;
	floor_move = false;
	for (int i = 0; i < 6; i++)
	{
		seal[i] = new Monster;
		blockMap[i] = new BlockManager;
		blockMap[i]->Init(i, seal[i]);
		seal[i]->SetBlockManager(blockMap[i]);
	}
	cha = new Character;
	cha2 = new Character;
	cha->Init(5, 18, 1, PLAYER1);
	cha2->Init(28, 18, 1, PLAYER2);
}

/*
기능 :		업데이트
매개변수 :	없음
반환 :		없음
특이사항 :	몬스터 객체 업데이트 호출, 블럭매니저 객체 업데이트 호출, 플레이어 객체 업데이트 호출
*/
void MapManager::Update()
{
	if (playdata.winner == 0) {	// 플레이어가 위너가 결정되면 더이상 변경안함
		if (cha->getDead())
		{
			playdata.winner = PLAYER2;
		}
		else if (cha2->getDead())
		{
			playdata.winner = PLAYER1;
		}
	}
	if (!floor_move)			// 맵이동중이 아닐때만 업데이트(이동중 조작불가)
	{
		for (int i = 0; i < 6; i++)
		{
			seal[i]->Update();
			blockMap[i]->Update();
		}
		cha->Update();
		cha2->Update();
	}
}

/*
기능 :		드로우
매개변수 :	없음
반환 :		없음
특이사항 :	맵이동중엔 드로우말고 Floor함수 호출
*/
void MapManager::Draw()
{
	if (floor_move)
	{
		for (int i = 0; i < 6; i++)
		{
			seal[i]->Floor(floorY);
			blockMap[i]->Floor(floorY);
		}
		cha->Floor(floorY);
		cha2->Floor(floorY);
		floorY += 4;
		if (floorY > 204)
		{
			floorY = 0;
			floor_move = false;
		}
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			seal[i]->Draw();
			blockMap[i]->Draw();
		}
		cha->Draw();
		cha->DrawCollider(); // ◆ 
		cha2->Draw();
		cha2->DrawCollider(); // ◆ 
	}
}

/*
기능 :		충돌
매개변수 :	없음
반환 :		없음
특이사항 :	각 객체간의 충돌처리
*/
void MapManager::Collision()
{
	if (!floor_move)		//  맵이동 중에는 충돌하지않음
	{
		Col ch_temp = cha->getCol_temp();
		Col ch = cha->getCol();
		Col ch_temp2 = cha2->getCol_temp();
		Col ch2 = cha2->getCol();

		//1p
		// 떨어지는중
		if (!cha->getJump_state())
		{
			int check = cha->Collision_V(ch2.chx, ch2.chX, ch2.chy, ch2.chY);
			if (check == UP || check == 6)											// 2p의 윗부분에 충돌
			{
				cha->setFloor_collision_temp(true);									// 상태 변환
				cha->setExtra_fall_y(abs(ch2.chy - ch.chY));						// 여분 계산
			}
		}
		// 점프 중	
		else								
		{
			if (cha->Collision_V(ch2.chx, ch2.chX, ch2.chy, ch2.chY) == DOWN)		// 2p의 아래부분에 충돌
			{
				cha->setJump_collision_temp(true);									// 상태 변환
				cha->setExtra_jump_y(-abs(ch2.chY - ch.chy));						// 여분 계산
			}
		}
		// 우로 이동중
		if (cha->getMove_state_r())
		{
			int check = cha->Collision_H(ch2.chx - 14, ch2.chX, ch2.chy, ch2.chY);
			if (check == LEFT || check == 6)										// 2p의 왼쪽부분에 충돌
			{
				cha->setMove_collision_r(true);										// 상태변환
			}
		}
		// 좌로 이동중
		if (cha->getMove_state_l())
		{
			int check = cha->Collision_H(ch2.chx, ch2.chX + 14, ch2.chy, ch2.chY);
			if (check == RIGHT || check == 6)										// 2p의 오른쪽부분에 충돌
			{
				cha->setMove_collision_l(true);										// 상태변환
			}
		}
		//2p
		// 떨어지는중
		if (!cha2->getJump_state())
		{
			int check = cha2->Collision_V(ch.chx, ch.chX, ch.chy - 10, ch.chY);
			if (check == UP || check == 6)											// 1p의 윗부분에 충돌
			{
				cha2->setFloor_collision_temp(true);								// 상태 변환
				cha2->setExtra_fall_y(abs(ch.chy - ch2.chY));						// 여분 계산
			}
		}
		// 점프 중
		else									
		{
			if (cha2->Collision_V(ch.chx, ch.chX, ch.chy, ch.chY + 10) == DOWN)		// 1p의 아래부분에 충돌
			{
				cha2->setJump_collision_temp(true);									// 상태 변환
				cha2->setExtra_jump_y(-abs(ch.chY - ch2.chy));						// 여분 계산
			}
		}

		// 우로 이동중
		if (cha2->getMove_state_r())
		{
			int check = cha2->Collision_H(ch.chx - 14, ch.chX, ch.chy, ch.chY);
			if (check == LEFT || check == 6)										// 1p의 왼쪽부분에 충돌
			{
				cha2->setMove_collision_r(true);									// 상태 변환
			}
		}
		// 좌로 이동중
		if (cha2->getMove_state_l())
		{
			int check = cha2->Collision_H(ch.chx, ch.chX + 14, ch.chy, ch.chY);
			if (check == RIGHT || check == 6)										// 1p의 오른쪽부분에 충돌
			{
				cha2->setMove_collision_l(true);									// 상태 변환
			}
		}
		// 몬스터와 플레이어 간 충돌
		for (int i = 0; i < 6; i++)
		{
			// ★항상 create, onoff, boom 체크만! (isOnMission, 별도 분기 없음)
			if (seal[i]->getBoom() || !seal[i]->getCreate() || !seal[i]->getOnoff())
				continue;

			if (cha->Collision_mon(seal[i]->getMonx(), seal[i]->getMonX(), seal[i]->getMony(), seal[i]->getMonY()) == 1)
			{
				if (playdata.winner == 0)
					playdata.winner = PLAYER2;
				break;
			}
			if (cha2->Collision_mon(seal[i]->getMonx(), seal[i]->getMonX(), seal[i]->getMony(), seal[i]->getMonY()) == 1)
			{
				if (playdata.winner == 0)
					playdata.winner = PLAYER1;
				break;
			}
			// 공격 처리도 동일
			if (cha->getAttack_state())
			{
				if (seal[i]->Collision_attacked(cha->getCol().chx, cha->getCol().chX, cha->getCol().chy, cha->getCol().chY, cha->getPos()) == 1)
				{
					playdata.p1_seal_count++;
					continue;
				}
			}
			if (cha2->getAttack_state())
			{
				if (seal[i]->Collision_attacked(cha2->getCol().chx, cha2->getCol().chX, cha2->getCol().chy, cha2->getCol().chY, cha2->getPos()) == 1)
				{
					playdata.p2_seal_count++;
					continue;
				}
			}
		}
		// 블럭과 오브젝트의 충돌
		for (int i = 0; i < 6; i++)
		{
			if (i == floor_move_now)							// 맵이동이 일어날수있는 층만 따로 처리
			{
				if (blockMap[i]->Collision3(cha, cha2))			// 캐릭터가 착지 하면
				{
					floor_move = true;							// 층에 한번이라도 바닥착지하면 층이동 가능
					floor_move_now = (floor_move_now + 1) % 6;
					floor_skip_1 = (floor_skip_1 + 1) % 6;
					floor_skip_2 = (floor_skip_2 + 1) % 6;
				}
			}
			else
				blockMap[i]->Collision(cha, cha2);				// 나머지층은 기본 충돌
			blockMap[i]->Collision_seal(seal[i]);				// 모든층과 몬스터의 충돌
		}
		if (floor_move)											// 층이동이 된 경우 한번만 실행됨
		{
			delete seal[(floor_skip_1 + 5) % 6];				// 맨밑층의 몬스터을 지움
			seal[(floor_skip_1 + 5) % 6] = new Monster;			// 새로 객체생성
			blockMap[(floor_skip_1 + 5) % 6]->Reset(seal[(floor_skip_1 + 5) % 6]);		// 맨밑층을 맨위로 리셋
		}
	}
}
