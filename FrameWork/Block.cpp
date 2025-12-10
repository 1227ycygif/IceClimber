#pragma once
#include "Include.h"
/*
기능 :		생성자
*/
Block::Block(void)
{
	CloudMoveTime = GetTickCount();
	dx = 0;
}
/*
기능 :		소멸자
*/
Block::~Block(void)
{
}
/*
기능 :		블럭파괴
매개변수 :	파괴한 플레이어
반환 :		없음
특이사항 :	없음
*/
void Block::Destroy(int player)
{
	onoff = false;
	this->player = player;


	// 포물선 낙하 초기화

	// 초기 위치 
	fx = (float)(mapX * 40);
	fy = (float)(mapY * 34);

	// 랜덤 방향으로 날아감
	vx = (float)((rand() % 301) - 150);    // -200 ~ +100 px/sec

	// 위로 튀어올랐다가 떨어짐
	vy = -600.0f;

	// 중력 강화 - 끌어당김 
	gravity = 2000.0f; // 1500 ~ 3000 

	// 낙하 여부 : 참 
	isFalling = true;
	fallStartTime = GetTickCount();

}
/*
기능 :		블럭재생성
매개변수 :	없음
반환 :		없음
특이사항 :	없음
*/
void Block::Resen()
{
	onoff = true;

}
/*
기능 :		초기화
매개변수 :	블럭종류, 맵 x좌표, 맵 y좌표, 렌더링 스케일
반환 :		없음
특이사항 :	각종 변수 초기화 및 스트라이프 이미지 연결
*/
void Block::Init(int boxKind, int mapX, int mapY, double scale)
{
	this->blockKind = boxKind;
	this->mapX = mapX;
	this->mapY = mapY;
	this->scale = scale;
	player = 0;
	onoff = true;
	// 일반블럭
	blockx = (mapX * 40);				// 좌
	blockX = (mapX * 40) + 40;			// 우
	blocky = (mapY * 34);				// 상	
	blockY = (mapY * 34) + 34;			// 하
	// 구름1
	if (blockKind == 4)
	{
		blockx = (mapX * 40);			// 좌
		blockX = (mapX * 40) + 80;		// 우
		blocky = (mapY * 34);			// 상	
		blockY = (mapY * 34) + 34;		// 하
	}
	// 구름2
	else if (blockKind == 5)
	{
		blockx = (mapX * 40);			// 좌
		blockX = (mapX * 40) + 120;		// 우
		blocky = (mapY * 34);			// 상	
		blockY = (mapY * 34) + 34;		// 하
	}
	// 맵끝벽
	else if (blockKind == 8 || blockKind == 9)
	{
		blockx = (mapX * 40);			// 좌
		blockX = (mapX * 40) + (40 * 6);// 우
		blocky = (mapY * 34);			// 상	
		blockY = (mapY * 34) + (34 * 5);// 하
	}
	col_v_Up = false;
	col_v_Down = false;
	col_v_Left = false;
	col_v_Right = false;
	col_v_Up2 = false;
	col_v_Down2 = false;
	col_v_Left2 = false;
	col_v_Right2 = false;

	char FileName[256];
	if (boxKind == ICE) {
		sprintf_s(FileName, "./resource/Img/ice/ice1.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == HARDICE) {
		sprintf_s(FileName, "./resource/Img/ice/hardIce1.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == SPEEDICE) {
		sprintf_s(FileName, "./resource/Img/ice/speedBlock1.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == CLOUD1) {
		sprintf_s(FileName, "./resource/Img/ice/cloud1.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == CLOUD2) {
		sprintf_s(FileName, "./resource/Img/ice/cloud2.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == ROCKL) {
		sprintf_s(FileName, "./resource/Img/ice/rock1l.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	/*else if (boxKind == ROCKL) {
		for (int i = 0; i < 8; i++)
		{
			sprintf_s(FileName, "./resource/Img/ice/rockl%d.png", i + 1);
			rockl[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
		}
	}*/
	else if (boxKind == ROCKR) {
		sprintf_s(FileName, "./resource/Img/ice/rock1r.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	/*else if (boxKind == ROCKR) {
		for (int i = 0; i < 8; i++)
		{
			sprintf_s(FileName, "./resource/Img/ice/rockr%d.png", i + 1);
			rockr[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
		}
	}*/
	else if (boxKind == ROCK2L) {
		sprintf_s(FileName, "./resource/Img/ice/rock2l.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == ROCK2R) {
		sprintf_s(FileName, "./resource/Img/ice/rock2r.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == BOTTOM) {
		sprintf_s(FileName, "./resource/Img/ice/bottom.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i<2; i++)
	{
		sprintf_s(FileName, "./resource/Img/Monster/2/fish_002_00%02d.png", i);
		destroy[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
}

/*
기능 :		플레이어1과 상하충돌
매개변수 :	플레이어1의 충돌범위
반환 :		충돌의 종류 / off거나 비충돌블럭 - 5 / 비충돌 - 8 / 상하좌우에 위치 - 7 / 갑작스런 충돌 - 6 / 좌에서충돌 - 0 / 우에서충돌 - 1 / 위에서충돌 - 2 / 아래서충돌 - 3
특이사항 :	없음
*/
int Block::Collision_V(int chx, int chX, int chy, int chY)
{
	// 복구 중일 때는,
	if (restoring)
	{
		// 충돌 없음
		return 8;
	}

	if (onoff
		&& blockKind != 6 && blockKind != 7 && blockKind != 20)											// 블럭이 안 깨진 상태일경우 && 충돌을 가지는 블럭
	{
		if (chX < blockx && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))			// 블럭의 왼쪽 방향인 경우
		{
			col_v_Left = true;

			col_v_Right = false;
			col_v_Up = false;
			col_v_Down = false;
			return 7;
		}
		else if (chx > blockX && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))	// 블럭의 오른쪽 방향인 경우
		{
			col_v_Right = true;

			col_v_Left = false;
			col_v_Up = false;
			col_v_Down = false;
			return 7;
		}
		else if (chY < blocky && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	// 블럭의 위 방향인 경우
		{
			col_v_Up = true;

			col_v_Right = false;
			col_v_Left = false;
			col_v_Down = false;
			return 7;
		}
		else if (chy > blockY && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	// 블럭의 아래 방향인 경우
		{
			col_v_Down = true;

			col_v_Right = false;
			col_v_Left = false;
			col_v_Up = false;
			return 7;
		}
		else if (((chx >= blockx && chx <= blockX) || (chX >= blockx && chX <= blockX)) &&				// 블럭과 충돌한경우
			((chy >= blocky && chy <= blockY) || (chY >= blocky && chY <= blockY)))
		{
			if (col_v_Up)
			{
				col_v_Up = false;
				return UP;
			}
			else if (col_v_Down)
			{
				col_v_Down = false;
				return DOWN;
			}
			else if (col_v_Left)
			{
				col_v_Left = false;
				return LEFT;
			}
			else if (col_v_Right)
			{
				col_v_Right = false;
				return RIGHT;
			}
			else
				return 6;																				// 갑작스런 충돌일때
		}
		else																							// 아무것도아닐때
		{
			col_v_Down = false;
			col_v_Right = false;
			col_v_Left = false;
			col_v_Up = false;
			return 8;
		}
	}
	return 5;																							// off 거나 충돌아니면 5 리턴
}
/*
기능 :		플레이어1과 좌우충돌
매개변수 :	플레이어1의 충돌범위
반환 :		충돌의 종류 / off거나 비충돌블럭 - 5 / 비충돌 - 8 / 상하좌우에 위치 - 7 / 갑작스런 충돌 - 6 / 좌에서충돌 - 0 / 우에서충돌 - 1 / 위에서충돌 - 2 / 아래서충돌 - 3
특이사항 :	없음
*/
int Block::Collision_H(int chx, int chX, int chy, int chY)
{
	// 복구 중일 때는,
	if (restoring)
	{
		// 충돌 없음
		return 8;
	}

	if (onoff
		&& blockKind != 6 && blockKind != 7 && blockKind != 20)											// 블럭이 안 깨진 상태일경우 && 충돌을 가지는 블럭
	{
		if (chX < blockx && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))			// 블럭의 왼쪽 방향인 경우
		{
			col_h_Left = true;

			col_h_Right = false;
			col_h_Up = false;
			col_h_Down = false;
			return 7;
		}
		else if (chx > blockX && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))	// 블럭의 오른쪽 방향인 경우
		{
			col_h_Right = true;

			col_h_Left = false;
			col_h_Up = false;
			col_h_Down = false;
			return 7;
		}
		else if (chY < blocky && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	// 블럭의 위 방향인 경우
		{
			col_h_Up = true;

			col_h_Right = false;
			col_h_Left = false;
			col_h_Down = false;
			return 7;
		}
		else if (chy > blockY && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	// 블럭의 아래 방향인 경우
		{
			col_h_Down = true;

			col_h_Right = false;
			col_h_Left = false;
			col_h_Up = false;
			return 7;
		}
		else if (((chx >= blockx && chx <= blockX) || (chX >= blockx && chX <= blockX)) &&				// 블럭과 충돌한경우
			((chy >= blocky && chy <= blockY) || (chY >= blocky && chY <= blockY)))
		{
			if (col_h_Up)
			{
				col_h_Up = false;
				return UP;
			}
			else if (col_h_Down)
			{
				col_h_Down = false;
				return DOWN;
			}
			else if (col_h_Left)
			{
				col_h_Left = false;
				return LEFT;
			}
			else if (col_h_Right)
			{
				col_h_Right = false;
				return RIGHT;
			}
			else
				return 6;																				// 갑작스런 충돌일때
		}
		else																							// 아무것도아닐때
		{
			col_h_Down = false;
			col_h_Right = false;
			col_h_Left = false;
			col_h_Up = false;
			return 8;
		}
	}
	return 5;																							// off 거나 충돌아니면 5 리턴
}
/*
기능 :		플레이어2과 상하충돌
매개변수 :	플레이어2의 충돌범위
반환 :		충돌의 종류 / off거나 비충돌블럭 - 5 / 비충돌 - 8 / 상하좌우에 위치 - 7 / 갑작스런 충돌 - 6 / 좌에서충돌 - 0 / 우에서충돌 - 1 / 위에서충돌 - 2 / 아래서충돌 - 3
특이사항 :	없음
*/
int Block::Collision_V2(int chx, int chX, int chy, int chY)
{
	// 복구 중일 때는,
	if (restoring)
	{
		// 충돌 없음
		return 8;
	}

	if (onoff
		&& blockKind != 6 && blockKind != 7 && blockKind != 20)											// 블럭이 안 깨진 상태일경우 && 충돌을 가지는 블럭
	{
		if (chX < blockx && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))			// 블럭의 왼쪽 방향인 경우
		{
			col_v_Left2 = true;

			col_v_Right2 = false;
			col_v_Up2 = false;
			col_v_Down2 = false;
			return 7;
		}
		else if (chx > blockX && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))	// 블럭의 오른쪽 방향인 경우
		{
			col_v_Right2 = true;

			col_v_Left2 = false;
			col_v_Up2 = false;
			col_v_Down2 = false;
			return 7;
		}
		else if (chY < blocky && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	// 블럭의 위 방향인 경우
		{
			col_v_Up2 = true;

			col_v_Right2 = false;
			col_v_Left2 = false;
			col_v_Down2 = false;
			return 7;
		}
		else if (chy > blockY && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	// 블럭의 아래 방향인 경우
		{
			col_v_Down2 = true;

			col_v_Right2 = false;
			col_v_Left2 = false;
			col_v_Up2 = false;
			return 7;
		}
		else if (((chx >= blockx && chx <= blockX) || (chX >= blockx && chX <= blockX)) &&				// 블럭과 충돌한경우
			((chy >= blocky && chy <= blockY) || (chY >= blocky && chY <= blockY)))
		{
			if (col_v_Up2)
			{
				col_v_Up2 = false;
				return UP;
			}
			else if (col_v_Down2)
			{
				col_v_Down2 = false;
				return DOWN;
			}
			else if (col_v_Left2)
			{
				col_v_Left2 = false;
				return LEFT;
			}
			else if (col_v_Right2)
			{
				col_v_Right2 = false;
				return RIGHT;
			}
			else
				return 6;																				// 갑작스런 충돌일때
		}
		else																							// 아무것도아닐때
		{
			col_v_Down2 = false;
			col_v_Right2 = false;
			col_v_Left2 = false;
			col_v_Up2 = false;
			return 8;
		}
	}
	return 5;																							// off 거나 충돌아니면 5 리턴
}
/*
기능 :		플레이어2과 좌우충돌
매개변수 :	플레이어2의 충돌범위
반환 :		충돌의 종류 / off거나 비충돌블럭 - 5 / 비충돌 - 8 / 상하좌우에 위치 - 7 / 갑작스런 충돌 - 6 / 좌에서충돌 - 0 / 우에서충돌 - 1 / 위에서충돌 - 2 / 아래서충돌 - 3
특이사항 :	없음
*/
int Block::Collision_H2(int chx, int chX, int chy, int chY)
{
	// 복구 중일 때는,
	if (restoring)
	{
		// 충돌 없음
		return 8;
	}

	if (onoff
		&& blockKind != 6 && blockKind != 7 && blockKind != 20)											// 블럭이 안 깨진 상태일경우 && 충돌을 가지는 블럭
	{
		if (chX < blockx && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))			// 블럭의 왼쪽 방향인 경우
		{
			col_h_Left2 = true;

			col_h_Right2 = false;
			col_h_Up2 = false;
			col_h_Down2 = false;
			return 7;
		}
		else if (chx > blockX && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))	// 블럭의 오른쪽 방향인 경우
		{
			col_h_Right2 = true;

			col_h_Left2 = false;
			col_h_Up2 = false;
			col_h_Down2 = false;
			return 7;
		}
		else if (chY < blocky && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	// 블럭의 위 방향인 경우
		{
			col_h_Up2 = true;

			col_h_Right2 = false;
			col_h_Left2 = false;
			col_h_Down2 = false;
			return 7;
		}
		else if (chy > blockY && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	// 블럭의 아래 방향인 경우
		{
			col_h_Down2 = true;

			col_h_Right2 = false;
			col_h_Left2 = false;
			col_h_Up2 = false;
			return 7;
		}
		else if (((chx >= blockx && chx <= blockX) || (chX >= blockx && chX <= blockX)) &&				// 블럭과 충돌한경우
			((chy >= blocky && chy <= blockY) || (chY >= blocky && chY <= blockY)))
		{
			if (col_h_Up2)
			{
				col_h_Up2 = false;
				return UP;
			}
			else if (col_h_Down2)
			{
				col_h_Down2 = false;
				return DOWN;
			}
			else if (col_h_Left2)
			{
				col_h_Left2 = false;
				return LEFT;
			}
			else if (col_h_Right2)
			{
				col_h_Right2 = false;
				return RIGHT;
			}
			else
				return 6;																				// 갑작스런 충돌일때
		}
		else																							// 아무것도아닐때
		{
			col_h_Down2 = false;
			col_h_Right2 = false;
			col_h_Left2 = false;
			col_h_Up2 = false;
			return 8;
		}
	}
	return 5;																							// off 거나 충돌아니면 5 리턴
}
/*
기능 :		블럭의 충돌범위 좌 반환
매개변수 :	없음
반환 :		블럭의 충돌범위 좌 (상수화)
특이사항 :	없음
*/
const int Block::getBlockx()
{
	return blockx;
}
/*
기능 :		블럭의 충돌범위 우 반환
매개변수 :	없음
반환 :		블럭의 충돌범위 우 (상수화)
특이사항 :	없음
*/
const int Block::getBlockX()
{
	return blockX;
}
/*
기능 :		블럭의 충돌범위 상 반환
매개변수 :	없음
반환 :		블럭의 충돌범위 상 (상수화)
특이사항 :	없음
*/
const int Block::getBlocky()
{
	return blocky;
}
/*
기능 :		블럭의 충돌범위 하 반환
매개변수 :	없음
반환 :		블럭의 충돌범위 하 (상수화)
특이사항 :	없음
*/
const int Block::getBlockY()
{
	return blockY;
}
/*
기능 :		블럭의 종류 반환
매개변수 :	없음
반환 :		블럭의 종류 (상수화)
특이사항 :	없음
*/
const int Block::getBoxKind()
{
	return blockKind;
}
/*
기능 :		블럭의 파괴상태 반환
매개변수 :	없음
반환 :		블럭의 파괴상태 (상수화)
특이사항 :	없음
*/
const bool Block::getOnoff()
{
	return onoff;
}
/*
기능 :		블럭을 파괴한 플레이어 반환
매개변수 :	없음
반환 :		블럭을 파괴한 플레이어 (상수화)
특이사항 :	없음
*/
const int Block::getPlayer()
{
	return player;
}
/*
기능 :		블럭을 파괴한 플레이어 변환
매개변수 :	플레이어
반환 :		없음
특이사항 :	없음
*/
void Block::setPlayer(int player)
{
	this->player = player;
}
/*
기능 :		블럭의 상태와 시간에 따른 멤버변수 조작
매개변수 :	없음
반환 :		없음
특이사항 :	구름 블럭의 이동량을 변환
*/
void Block::Update()
{
	if (onoff == true)										// 블럭이 on상태일때만
	{
		if (blockKind == 4 || blockKind == 5)				// 블럭이 구름1, 구름2일경우
		{
			if (GetTickCount() - CloudMoveTime > 10)		// 시간마다
			{
				dx -= 2;									// 위치이동
				blockx -= 2;								// 충돌이동
				blockX -= 2;

				if (mapX * 40 + dx < 80)					// 맵의 특정범위 벗어나면 리셋
				{
					dx = (30 - mapX) * 40;
					blockx = 30 * 40;
					blockX = blockx + 80;
					if (blockKind == 5)
						blockX += 40;
				}
				CloudMoveTime = GetTickCount();
			}
		}
		// onoff = true로 실제 충돌 가능하게.
		if (restoring && GetTickCount() - restoreStart > 300)
		{
			restoring = false;

			/*for (int i = 0; i < monsterCount; ++i)
			{
				Monster* mon = monsterList[i];

				RECT r_block = { blockx, blocky, blockX, blockY };
				RECT r_mon = { mon->getMonx(), mon->getMony(), mon->getMonX(), mon->getMonY() };
				if (IntersectRect(&r_block, &r_mon))
				{
					mon->env_invincible = true;
					mon->env_invincible_start = GetTickCount();
				}
			}*/
		}
	}

	// 포물선 낙하 처리
	if (isFalling)
	{
		DWORD now = GetTickCount();
		float dt = (now - fallStartTime) / 1000.0f; // 시간 재기

		// 중력에 의한 속도 증가
		vy += gravity * dt;

		// 위치 계산 - vx 일정, vy 누적  
		fx += vx * dt;
		fy += vy * dt;

		// 화면 아래로 완전히 떨어지면 낙하 종료
		if (fy > 720) // 화면 바깥 아래로 충분히 벗어나면
			isFalling = false;

		fallStartTime = now; // 시간을 계속 갱신
		return; // 낙하 중일 땐 다른 처리 생략
	}

}

/*
기능 :		캐릭터의 상태에 따른 스트라이프 출력
매개변수 :	없음
반환 :		없음
특이사항 :	없음
*/
void Block::Draw()
{
	if (!onoff) return; //  블럭 꺼져있으면 아예 그리지 않음

	if (onoff == true)															// 블럭이 on상태일때만
	{
		if (blockKind != 4 && blockKind != 5)									// 구름블럭이 아닐경우
		{
			img.Render(mapX * 40, mapY * 34, 0, scale, scale);
		}
		else if (blockKind == 4 || blockKind == 5)								// 구름블럭일경우
		{
			img.Render(mapX * 40 + dx, mapY * 34, 0, scale, scale);
		}
	}
	if (Gmanager.m_GameStart == true)
	{
		/*if (Gmanager.m_bShowCollider) {
			RECT BlockCollider = { getBlockx(), getBlocky(), getBlockX(), getBlockY() };
			coll.BoxSow(BlockCollider, 0, 0, D3DCOLOR_ARGB(255, 0, 0, 255));
		}*/
		// ◆ 
		sprite.Draw(x, y);
		DrawCollider();
	}

}

// ◆ 블럭 디버그 박스 그리기 함수 /////
void Block::DrawCollider()
{
	if (!Gmanager.m_bShowCollider)
		return;

	RECT r = { blockx, blocky, blockX, blockY };
	const int offset = 6; // ← 테스트하면서 조정해야함 ◆ 폰트 위치 조정용 / -3 ~ 3 정도씩

	dv_font.DrawString("┌", r.left - (offset * 3.6), r.top - (offset * 3.6), D3DCOLOR_ARGB(255, 255, 128, 0));
	dv_font.DrawString("┐ ", r.right - (offset * 3.6), r.top - (offset * 3.6), D3DCOLOR_ARGB(255, 255, 128, 0));
	dv_font.DrawString("└", r.left - (offset * 3.6), r.bottom - (offset * 4), D3DCOLOR_ARGB(255, 255, 128, 0));
	dv_font.DrawString("┘", r.right - (offset * 3.6), r.bottom - (offset * 4), D3DCOLOR_ARGB(255, 255, 128, 0));
}

bool Block::IsSolidForMonster() 
{
	if (!onoff || restoring)
		return false;

	return blockKind != 6 && blockKind != 7 && blockKind != 20; // ROCK 제외
}

/*
기능 :		캐릭터의 상태에 따른 스트라이프 출력(맵 이동중)
매개변수 :	없음
반환 :		없음
특이사항 :	없음
*/
void Block::Floor(int floorY)
{
	if (onoff == true)															// 블럭이 on상태일때만
	{
		if (blockKind != 4 && blockKind != 5)									// 구름블럭이 아닐경우
		{
			img.Render(mapX * 40, mapY * 34 + (floorY), 0, scale, scale);
		}
		else if (blockKind == 4 || blockKind == 5)								// 구름블럭일경우
		{
			img.Render(mapX * 40 + dx, mapY * 34 + (floorY), 0, scale, scale);	
		}
	}
	if (floorY >= 204)															// 맵이동 마지막시 변수 조정
	{
		mapY += 6;

		if (blockKind == 8 || blockKind == 9)
		{
			blocky += (6 * 34);					// 상
			blockY += (6 * 34);					// 하
		}
		else

		{
			blocky += (6 * 34);					// 상
			blockY += (6 * 34);					// 하
		}
	}
}

void Block::SetRestoring(bool flag)
{
	restoring = flag;
	if (flag)
	{
		// flag = true → restoring = true → (복구 시간)restoreStart = (현재 시간)GetTickCount 
		// 복구가 시작될 때만 타이머 시작
		restoreStart = GetTickCount();
	}
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