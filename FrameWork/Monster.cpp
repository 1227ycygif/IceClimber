#pragma once
#include "Include.h"
/*
기능 :		생성자
*/
Monster::Monster(void)
{
	// 기존 변수 초기화
	blockMgr = nullptr;
	state = MON_SEARCH;
	hasIcicle = false;
	targetX = targetY = -1;
}
/*
기능 :		소멸자
*/
Monster::~Monster(void)
{
}
/*
기능 :		초기화
매개변수 :	몬스터 종류(아직 1종류밖에...), 맵 y좌표, 렌더링 스케일, 맵생성시 몬스터 생성여부
반환 :		없음
특이사항 :	각종 변수 초기화 및 스트라이프 이미지 연결
*/
void Monster::Init(int monKind, int mapY, double scale, bool start)
{
	MonMoveTime = MonCountTime = AttCountTime = GetTickCount();
	create = start;
	onoff = true;
	boom = false;
	this->monKind = monKind;
	this->mapY = mapY;
	this->scale = scale;
	// 방향
	srand((unsigned)time(NULL) + mapY);
	pos = rand() % 2;
	if (pos == 0)
		this->mapX = 6;
	else if (pos == 1)
		this->mapX = 26;
	// 충돌범위
	monx = (mapX * 40) - 39;			// 좌
	monX = (mapX * 40) + 39;			// 우
	mony = (mapY * 34) - 74;			// 상
	monY = (mapY * 34);					// 하

	col_front_turn = false;
	col_down_turn = false;

	char FileName[256];
	for (int i = 0; i < 3; i++)
	{// 물개, 새 이미지 로딩
		sprintf_s(FileName, "./resource/Img/mon/seal_walk%d.png", i + 1);
		seal_walk[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	/*for (int i = 0; i < 2; i++)
	{
		sprintf_s(FileName, "./resource/Img/mon/bird_fly%d.png", i + 1);
		bird_fly[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}*/
	for (int i = 0; i < 3; i++)
	{// 물개 공격당할 때 이미지 로딩
		sprintf_s(FileName, "./resource/Img/mon/attackEffect%d.png", i + 1);
		attackEffect[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	/*sprintf_s(FileName, "./resource/Img/mon/bird_attacked.png");
	bird_attacked.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));*/

	// ----------- 고드름 스프라이트 추가 -----------
	sprintf_s(FileName, "./resource/Img/ice/icicle.png");
	icicle.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	hasIcicle = false;
	targetX = targetY = -1;
	state = MON_SEARCH;
}
/*
기능 :		몬스터의 상태와 시간에 따른 멤버변수 조작
매개변수 :	없음
반환 :		없음
특이사항 :	몬스터의 이동량, 스프라이트 인덱스를 변환
*/
void Monster::Update()
{
	if (!create || !blockMgr) return;

	DWORD now = GetTickCount();
	if (!create) return;

	if (onoff && !boom)
	{
		switch (state)
		{
		case MON_SEARCH:
		{
			// 이동
			if (now - MonMoveTime > 30) {
				if (pos == LEFT) {
					move_x -= 2; monx -= 2; monX -= 2;
					if (monx < 20) onoff = false;
				}
				else {
					move_x += 2; monx += 2; monX += 2;
					if (monX > 1260) onoff = false;
				}
				MonMoveTime = now;
			}

			if (now - MonCountTime > 200) {
				m_count++; 
				if (m_count > 1) m_count = 0;
				MonCountTime = now;
			}

			if (col_front_turn || col_down_turn) {
				pos = (pos + 1) % 2;
				col_front_turn = false;
				col_down_turn = false;
			}

			// ◆ 앞에 블럭이 없는지 확인 (실제 좌표 기준)
			int frontMapX = (pos == LEFT) ? (monx - 1) / 40 : (monX + 1) / 40;
			int frontMapY = mapY;

			bool frontEmpty = true;
			for (int i = 0; i < blockMgr->getIndex(); ++i) {
				Block* blk = blockMgr->getBlock(i);
				if (!blk || !blk->getOnoff()) continue;

				if (blk->getMapX() == frontMapX && blk->getMapY() == frontMapY) {
					frontEmpty = false;
					break;
				}
			}

			if (frontEmpty && !hasIcicle && targetX == -1 && targetY == -1) {
				targetX = frontMapX;
				targetY = frontMapY;

				int distLeft = abs(mapX - 4);
				int distRight = abs(mapX - 28);
				if (distLeft <= distRight) {
					pos = LEFT;
					caveX = 4;
				}
				else {
					pos = RIGHT;
					caveX = 28;
				}

				state = MON_RETURN;
			}

			if (col_floor) {
				onoff = false;
				boom = true;
				col_floor = false;
			}
			break;
		}
		case MON_RETURN:
		{
			char log[128];
			sprintf_s(log, "[STATE] time=%d State=%d mapX=%d mapY=%d target=(%d,%d) hasIcicle=%d\n",
				now, state, mapX, mapY, targetX, targetY, hasIcicle);
			OutputDebugStringA(log);
			OutputDebugStringA("[STATE] MON_RETURN\n");

			// 동굴 방향 계산
			int caveX = 4;
			int distLeft = abs(mapX - 4);
			int distRight = abs(mapX - 28);

			if (distLeft <= distRight) {
				pos = LEFT;
				caveX = 4;
			}
			else {
				pos = RIGHT;
				caveX = 28;
			}

			// 이동 타이밍 조절 (속도 느리게)
			/*if (now - MonMoveTime >= 200) 
			{
				if (mapX < caveX) mapX++;
				else if (mapX > caveX) mapX--;

				move_x = 0;
				MonMoveTime = now;

				monx = (mapX * 40) - 39;
				monX = (mapX * 40) + 39;
			}*/

			if (now - MonMoveTime >= 30) {
				if (pos == LEFT) {
					move_x -= 2;
					monx -= 2;
					monX -= 2;

					// 이동 완료 여부 확인
					if (move_x <= -40) {
						mapX--;
						move_x = 0;
						monx = (mapX * 40) - 39;
						monX = (mapX * 40) + 39;
					}
				}
				else {
					move_x += 2;
					monx += 2;
					monX += 2;

					if (move_x >= 40) {
						mapX++;
						move_x = 0;
						monx = (mapX * 40) - 39;
						monX = (mapX * 40) + 39;
					}
				}

				MonMoveTime = now;
			}

			//// ◆ 도착하면 고드름 획득
			//if (mapX == caveX)
			//{
			//	hasIcicle = true;

			//	// ◆ 고드름 들고 나갈 때는 원래 targetX 바라보게 전환
			//	if (targetX != -1)
			//	{
			//		if (mapX < targetX) pos = RIGHT;
			//		else if (mapX > targetX) pos = LEFT;
			//	}

			//	state = MON_BRING;
			//}

			if (now - MonCountTime > 200) {
				m_count++;
				if (m_count > 1) m_count = 0;
				MonCountTime = now;
			}

			// ◆ 도착하면 고드름 획득
			if (mapX == caveX && move_x == 0)
			{
				hasIcicle = true;

				// ◆ 고드름 들고 나갈 때는 원래 targetX 바라보게 전환
				if (targetX != -1)
				{
					if (mapX < targetX) pos = RIGHT;
					else if (mapX > targetX) pos = LEFT;
				}

				state = MON_BRING;
			}
			break;
		}
		break;

		case MON_BRING:
		{
			if (now - MonMoveTime >= 240) {
				int nextX = mapX + (mapX < targetX ? 1 : -1);

				bool blocked = false;
				for (int i = 0; i < blockMgr->getIndex(); ++i) {
					Block* blk = blockMgr->getBlock(i);
					if (!blk || !blk->IsSolidForMonster()) continue;

					int next_monx = (nextX * 40) - 39;
					int next_monX = (nextX * 40) + 39;
					int blkx = blk->getBlockx(), blkX = blk->getBlockX();
					int blky = blk->getBlocky(), blkY = blk->getBlockY();

					if (next_monX > blkx && next_monx < blkX &&
						monY > blky && mony < blkY) {
						blocked = true;
						break;
					}
				}

				if (!blocked) {
					// 정상 이동
					if (mapX < targetX) mapX++;
					else if (mapX > targetX) mapX--;

					move_x = 0;
					monx = (mapX * 40) - 39;
					monX = (mapX * 40) + 39;
				}
				else {
					// ◆ 막혔으면 포기하고 상태 초기화
					OutputDebugStringA("[INFO] 벽에 막혀서 고드름 배달 포기\n");
					targetX = -1;
					targetY = -1;
					hasIcicle = false;
					state = MON_SEARCH;
				}

				MonMoveTime = now;
			}

			if (mapX == targetX)
				state = MON_PLACE;

			break;
		}
		case MON_PLACE:
		{
			if (hasIcicle && targetX != -1 && targetY != -1) {
				// ◆ 정확히 그 칸에 살아있는 블럭이 없을 때만 추가
				bool isReallyEmpty = true;

				for (int i = 0; i < blockMgr->getIndex(); ++i) {
					Block* b = blockMgr->getBlock(i);
					if (!b) continue;

					// ◆ 죽은(onoff==false) 블럭은 무시해야 함!
					if (b->getOnoff() && b->getMapX() == targetX && b->getMapY() == targetY) {
						isReallyEmpty = false;
						break;
					}
				}

				if (isReallyEmpty) {
					blockMgr->AddBlock(ICE, targetX, targetY, true);  // ◆ 설치
				}

				hasIcicle = false;
				targetX = -1;
				targetY = -1;
				state = MON_SEARCH;
			}
			break;
		}
		}
		// ◆ 바닥 꺼짐 체크 – 블럭 놓은 직후 예외 처리
		if (col_floor)
		{
			bool justPlacedBlockHere = (state == MON_PLACE && !hasIcicle &&
				targetX == -1 && targetY == -1 && blockMgr &&
				[&] {
					for (int i = 0; i < blockMgr->getIndex(); ++i) {
						Block* b = blockMgr->getBlock(i);
						if (b && b->getMapX() == mapX && b->getMapY() == mapY && b->getOnoff())
							return true;
					}
					return false;
				}()
					);

			if (!justPlacedBlockHere) {
				OutputDebugStringA("[INFO] 몬스터 바닥 꺼짐 - 사망\n");
				onoff = false;
				boom = true;
			}
			else {
				OutputDebugStringA("[INFO] 방금 설치한 블럭 위 - 죽지 않음\n");
			}
			col_floor = false;
		}
	}
	else if (!onoff && boom)
	{
		if (now - AttCountTime > 200)
		{
			a_count++; if (a_count > 3) { a_count = 0; boom = false; RezCountTime = now; }
			AttCountTime = now;
		}
	}
	else
	{
		if (now - RezCountTime > 1000)
		{
			Reset();
		}
	}
}


/*
기능 :		몬스터의 상태에 따른 스트라이프 출력
매개변수 :	없음
반환 :		없음
특이사항 :	없음
*/
void Monster::Draw()
{
	if (!create) return;

	if (onoff && !boom)
	{
		if (pos == LEFT)
			seal_walk[m_count].Render((mapX * 40) - 38 + move_x, (mapY * 34) - 74, 0, scale, scale);
		else
			seal_walk[m_count].Render((mapX * 40) + 38 + move_x, (mapY * 34) - 74, 0, -scale, scale);

		// 고드름 들고 있을 때
		if (hasIcicle)
			icicle.Render((mapX * 40), (mapY * 34) - 100, 0, 0.8, 0.8);
	}
	else if (!onoff && boom)
	{
		if (pos == LEFT)
			attackEffect[a_count].Render((mapX * 40) - 38 + move_x, (mapY * 34) - 74, 0, scale, scale);
		else
			attackEffect[a_count].Render((mapX * 40) + 38 + move_x, (mapY * 34) - 74, 0, -scale, scale);
	}

	if (Gmanager.m_GameStart == true)
	{
		/*if (Gmanager.m_bShowCollider) {
			RECT monCollider = { monx, mony, monX, monY };
			coll.BoxSow(monCollider, 0, 0, D3DCOLOR_ARGB(255, 0, 255, 0));
		}*/
		// ◆ 
		sprite.Draw(x, y);
		DrawCollider();
	}
	
}

// ◆ 몬스터 디버그 박스 그리는 함수
void Monster::DrawCollider()
{
	if (!Gmanager.m_bShowCollider)
		return;
	
	RECT r = { monx, mony, monX, monY };
	const int offset = 20; // ← 테스트하면서 조정해야함 ◆ 폰트 위치 조정용 / -3 ~ 3 정도씩 
	
	dv_font.DrawString("┌ ", r.left - offset, r.top - (offset + 1), D3DCOLOR_ARGB(255, 0, 255, 0));
	dv_font.DrawString("┐ ", r.right - offset, r.top - (offset + 1), D3DCOLOR_ARGB(255, 0, 255, 0));
	dv_font.DrawString("└", r.left - offset, r.bottom - (offset + 3), D3DCOLOR_ARGB(255, 0, 255, 0));
	dv_font.DrawString("┘", r.right - offset, r.bottom - (offset + 3), D3DCOLOR_ARGB(255, 0, 255, 0));
}

/*
기능 :		몬스터의 상태에 따른 스트라이프 출력(맵 이동중)
매개변수 :	없음
반환 :		없음
특이사항 :	없음
*/
void Monster::Floor(int floorY)
{
	if (create)		// 생성됐을때
	{
		if (onoff && !boom)							// 살았을때
		{
			if (pos == LEFT)						// 방향에따라
				seal_walk[m_count].Render((mapX * 40) - 38 + move_x, (mapY * 34) - 74 + (floorY), 0, scale, scale);
			else
				seal_walk[m_count].Render((mapX * 40) + 38 + move_x, (mapY * 34) - 74 + (floorY), 0, -scale, scale);
		}
		else if (!onoff && boom) {					// 맞았을때
			if (pos == LEFT)
				attackEffect[a_count].Render((mapX * 40) - 38 + move_x, (mapY * 34) - 74 + (floorY), 0, scale, scale);
			else
				attackEffect[a_count].Render((mapX * 40) + 38 + move_x, (mapY * 34) - 74 + (floorY), 0, -scale, scale);
		}
		// 맵이동 마지막시 변수 조정
		if (floorY >= 204)
		{
			mapY += 6;
			mony = (mapY * 34) - 74;		// 상
			monY = (mapY * 34);				// 하
		}
	}
}

/*
기능 :		다시 출현하기위해 위치 재설정
매개변수 :	없음
반환 :		없음
특이사항 :	없음
*/
void Monster::Reset()	
{
	// 시간 초기화
	MonMoveTime = MonCountTime = AttCountTime = GetTickCount();

	// 몬스터 파괴 초기화
	onoff = true;
	boom = false;
	
	// 상태 초기화
	hasIcicle = false;
	targetX = targetY = -1;
	state = MON_SEARCH;

	// 방향
	srand((unsigned)time(NULL) + mapY);
	int pos_t = rand() % 2;
	if (pos_t == pos)
		pos_t = rand() % 2;
	pos = pos_t;
	if (pos == 0)
		this->mapX = 28;
	else if (pos == 1)
		this->mapX = 4;
	
	// 위치
	move_x = 0;
	monx = (mapX * 40) - 39;			// 좌
	monX = (mapX * 40) + 39;			// 우
}

/*
기능 :		방향전환을 위한 충돌판정
매개변수 :	충돌을 판단하기위한 블럭의 충돌범위, 블럭의 onoff
반환 :		충돌판정 결과 - 블럭과 충돌시 1,2 / 블럭 충돌 없을시 0 
특이사항 :	없음
*/
int Monster::Collision_turn(int blockx, int blockX, int blocky, int blockY, bool onoff)
{	
	// 방향에 따라 다름
	if (pos == RIGHT)
	{
		if ((monX + 5 >= blockx && monX + 5 <= blockX) &&		// 몬스터의 앞쪽 정면에 충돌점을 만들어 충돌했는지 판단
			(monY - 10 >= blocky && mony - 10 <= blockY))
			return 1;											// 블럭과 충돌시 1
		if (monX + 10 >= blockx &&								// 몬스터의 약간 앞쪽아래에 충돌점을 만들어 충돌했는지 판단(블럭상태가 off일경우만)
			monX + 10 <= blockX &&
			monY + 17 >= blocky &&
			monY + 17 <= blockY &&
			!onoff)
			return 2;											// 블럭과충돌시 2
		return 0;												// 충돌없을시 0
	}
	else if (pos == LEFT)
	{
		if ((monx - 5 >= blockx && monx - 5 <= blockX) &&
			(monY - 10 >= blocky && mony - 10 <= blockY))
			return 1;
		if (monx - 10 >= blockx &&
			monx - 10 <= blockX &&
			monY + 17 >= blocky &&
			monY + 17 <= blockY &&
			!onoff)
			return 2;
		return 0;
	}
}
/*
기능 :		바닥파괴을 위한 충돌판정
매개변수 :	충돌을 판단하기위한 블럭의 충돌범위, 블럭의 onoff
반환 :		충돌판정 결과 - 블럭과 충돌시 1 / 블럭 충돌 없을시 0
특이사항 :	없음
*/
int Monster::Collision_floor(int blockx, int blockX, int blocky, int blockY, bool onoff)
{
	if (((monx + 7 >= blockx && monx + 7 <= blockX) || (monX - 7 >= blockx && monX - 7 <= blockX)) &&		// 몬스터보다 약간좁은 아래부분에 충돌범위가 블록에 충돌했는지 판단(블럭이 off일때만)
		(monY + 17 >= blocky && monY + 17 <= blockY) &&
		!onoff)
	{
		return 1;																							// 충돌했으면 1
	}
	return 0;																								// 충돌안했으면 0
}

/*
기능 :		플레이어에게 공격단한 충돌판정
매개변수 :	충돌을 판단하기위한 플레이어의 충돌범위, 플레이어의 방향
반환 :		충돌판정 결과 - 충돌시 1 / 충돌 없을시 0
특이사항 :	없음
*/
int Monster::Collision_attacked(int chax, int chaX, int chay, int chaY, int pos)
{
	if (pos == LEFT)				// 플레이어의 방향에따라 플레이어 앞쪽에 충돌범위 생성
	{
		chaX = chax;
		chax -= 45;
	}
	else
	{
		chax = chaX;
		chaX += 45;
	}
	if (((monx >= chax && monx <= chaX) || (monX >= chax && monX <= chaX)) &&							// 충돌범위에 몬스터가 들어갈경우
		((mony >= chay - 10 && mony <= chaY + 10) || (monY >= chay - 10 && monY <= chaY + 10)))
	{
		sound.m_Impact->Play(0, NULL);																	// 사운드 출력
		onoff = false;																					// 상태 변환
		boom = true;
		return 1;																						// 충돌시 1
	}
	return 0;																							// 비충돌시 0
}

/*
기능 :		몬스터 충돌 범위 좌 반환
매개변수 :	없음
반환 :		몬스터 충돌 범위 좌(상수화)
특이사항 :	없음
*/
const int Monster::getMonx() {
	if (hasIcicle) return monx - 16; // 고드름 들고 있을 땐 좀 더 왼쪽까지 판정!
	return monx;
}
/*
기능 :		몬스터 충돌 범위 우 반환
매개변수 :	없음
반환 :		몬스터 충돌 범위 우(상수화)
특이사항 :	없음
*/
const int Monster::getMonX() {
	if (hasIcicle) return monX + 16; // 고드름 들고 있을 땐 좀 더 오른쪽까지 판정!
	return monX;
}
/*
기능 :		몬스터 충돌 범위 상 반환
매개변수 :	없음
반환 :		몬스터 충돌 범위 상(상수화)
특이사항 :	없음
*/
const int Monster::getMony()
{
	if (hasIcicle) return mony - 40; // 고드름 sprite 위로 커졌다면
	return mony;
}
/*
기능 :		몬스터 충돌 범위 하 반환
매개변수 :	없음
반환 :		몬스터 충돌 범위 하(상수화)
특이사항 :	없음
*/
const int Monster::getMonY()
{
	return monY;
}
/*
기능 :		몬스터 생성여부 반환
매개변수 :	없음
반환 :		몬스터 생성여부(상수화)
특이사항 :	없음
*/
const bool Monster::getCreate()
{
	return create;
}
/*
기능 :		몬스터 파괴여부 반환
매개변수 :	없음
반환 :		몬스터 파괴여부(상수화)
특이사항 :	없음
*/
const bool Monster::getOnoff()
{
	return onoff;
}
/*
기능 :		몬스터 폭발여부 반환
매개변수 :	없음
반환 :		몬스터 폭발여부(상수화)
특이사항 :	없음
*/
const bool Monster::getBoom()
{
	return boom;
}
/*
기능 :		몬스터의 정면 충돌 상태 변환
매개변수 :	상태
반환 :		없음
특이사항 :	없음
*/
void Monster::setCol_front_turn(bool state)
{
	col_front_turn = state;
}
/*
기능 :		몬스터의 바닥 충돌 상태 변환
매개변수 :	상태
반환 :		없음
특이사항 :	없음
*/
void Monster::setCol_down_turn(bool state)
{
	col_down_turn = state;
}
/*
기능 :		몬스터의 바닥 폭발 상태 변환
매개변수 :	상태
반환 :		없음
특이사항 :	없음
*/
void Monster::setCol_floor(bool state)
{
	col_floor = state;
}

/*

	기본 충돌처리

	= 사각형 출동 판정 처리
	플레이어기의 충돌 판정 좌표를 (ML, MT) ~ (MR, MB), 탄의 충돌 판정 좌표를 (BL, BT) ~ (BR, BB)라고 해보자.
	(ML, MT), (BL, BT)는 각각의 사각형의 왼쪽 위 좌표이고 (MR. MB), (BR, BB)는 사각형의 오른쪽 아래 좌표이다.
	이 경우, 플레이어기에 탄의 충돌 조건은 다음과 같다.
	* ML < BR && BL < MR && MT < BB && BT < MB

	= 원을 이용한 충돌 판정 처리
	원을 이용한 충돌 판정 처리는 다음과 같다.
	플레이어기의 중심좌표를 (MX, MY), 탄의 중심좌표를 (BX, BY)라고 하고, 플레이어기의 충돌 판정 반경을 MR,
	탄의 충돌 판정 반경을 BR이라고 하자. 이때 플레이어기와 탄의 충돌 조건은 아래와 같다.
	* (MX-BX)*(MX-BX) + (MY-BY)*(MY-BY) < (MR+BR)*(MR+BR)

*/