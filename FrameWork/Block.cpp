#pragma once
#include "Include.h"

/*
기능 :	생성자
*/
Block::Block(void)
{
	CloudMoveTime = GetTickCount();
	dx = 0;
}

/*
기능 :	소멸자
*/
Block::~Block(void)
{

}

/*
기능 :		블록 파괴
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
	// -200 ~ +100 px/sec
	vx = (float)((rand() % 301) - 150);    

	// 위로 튀어올랐다가 떨어짐
	vy = -600.0f;

	// 중력 강화 - 끌어당김 
	// 1500 ~ 3000
	gravity = 2000.0f;  

	// 낙하 여부 : 참 
	isFalling = true;
	fallStartTime = GetTickCount();
}

/*
기능 :		블록 재생성
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
매개변수 :	블록 종류, 맵 x좌표, 맵 y좌표, 렌더링 스케일
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

	// 일반 블록
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
	// 맵 끝 벽
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
	if (boxKind == ICE) 
	{
		sprintf_s(FileName, "./resource/Img/ice/ice1.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == HARDICE) 
	{
		sprintf_s(FileName, "./resource/Img/ice/hardIce1.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == SPEEDICE) 
	{
		sprintf_s(FileName, "./resource/Img/ice/speedBlock1.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == CLOUD1) 
	{
		sprintf_s(FileName, "./resource/Img/ice/cloud1.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == CLOUD2) 
	{
		sprintf_s(FileName, "./resource/Img/ice/cloud2.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == ROCKL) 
	{
		sprintf_s(FileName, "./resource/Img/ice/rock1l.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == ROCKR) 
	{
		sprintf_s(FileName, "./resource/Img/ice/rock1r.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == ROCK2L) 
	{
		sprintf_s(FileName, "./resource/Img/ice/rock2l.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == ROCK2R) 
	{
		sprintf_s(FileName, "./resource/Img/ice/rock2r.png");
		img.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (boxKind == BOTTOM) 
	{
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
기능 :		플레이어1과 상하 충돌
매개변수 :	플레이어1의 충돌 범위
반환 :		충돌의 종류 / off거나 비충돌 블록 - 5 / 비충돌 - 8 / 상하좌우에 위치 - 7 / 갑작스런 충돌 - 6 
						/ 좌측에서 충돌 - 0 / 우측에서 충돌 - 1 / 위에서 충돌 - 2 / 아래에서 충돌 - 3
특이사항 :	없음
*/
int Block::Collision_V(int chx, int chX, int chy, int chY)
{
	// 복구 중일 때는
	if (restoring)
	{
		// 충돌 없음
		return 8;
	}

	// 블록이 안 깨진 상태일 경우 && 충돌을 가지는 블록
	if (onoff && blockKind != 6 && blockKind != 7 && blockKind != 20)											
	{
		// 블록의 왼쪽 방향인 경우
		if (chX < blockx && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))			
		{
			col_v_Left = true;
			col_v_Right = false;
			col_v_Up = false;
			col_v_Down = false;
			return 7;
		}
		// 블록의 오른쪽 방향인 경우
		else if (chx > blockX && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))	
		{
			col_v_Right = true;
			col_v_Left = false;
			col_v_Up = false;
			col_v_Down = false;
			return 7;
		}
		// 블록의 위 방향인 경우
		else if (chY < blocky && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	
		{
			col_v_Up = true;
			col_v_Right = false;
			col_v_Left = false;
			col_v_Down = false;
			return 7;
		}
		// 블록의 아래 방향인 경우
		else if (chy > blockY && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	
		{
			col_v_Down = true;
			col_v_Right = false;
			col_v_Left = false;
			col_v_Up = false;
			return 7;
		}
		// 블록과 충돌한 경우
		else if (((chx >= blockx && chx <= blockX) || (chX >= blockx && chX <= blockX)) &&				
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
			{
				// 갑작스런 충돌일 때
				return 6;
			} 
		}
		// 아무것도 아닐 때
		else																							
		{
			col_v_Down = false;
			col_v_Right = false;
			col_v_Left = false;
			col_v_Up = false;
			return 8;
		}
	}
	// off 거나 충돌이 아니면 5 리턴
	return 5;																							
}

/*
기능 :		플레이어1과 좌우 충돌
매개변수 :	플레이어1의 충돌 범위
반환 :		충돌의 종류 / off거나 비충돌 블록 - 5 / 비충돌 - 8 / 상하좌우에 위치 - 7 / 갑작스런 충돌 - 6 
						/ 좌측에서 충돌 - 0 / 우측에서 충돌 - 1 / 위에서 충돌 - 2 / 아래에서 충돌 - 3
특이사항 :	없음
*/
int Block::Collision_H(int chx, int chX, int chy, int chY)
{
	// 복구 중일 때는
	if (restoring)
	{
		// 충돌 없음
		return 8;
	}

	// 블록이 안 깨진 상태일 경우 && 충돌을 가지는 블록
	if (onoff && blockKind != 6 && blockKind != 7 && blockKind != 20)											
	{
		// 블록의 왼쪽 방향인 경우
		if (chX < blockx && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))			
		{
			col_h_Left = true;
			col_h_Right = false;
			col_h_Up = false;
			col_h_Down = false;
			return 7;
		}
		// 블록의 오른쪽 방향인 경우
		else if (chx > blockX && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))	
		{
			col_h_Right = true;
			col_h_Left = false;
			col_h_Up = false;
			col_h_Down = false;
			return 7;
		}
		// 블록의 위 방향인 경우
		else if (chY < blocky && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	
		{
			col_h_Up = true;
			col_h_Right = false;
			col_h_Left = false;
			col_h_Down = false;
			return 7;
		}
		// 블록의 아래 방향인 경우
		else if (chy > blockY && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	
		{
			col_h_Down = true;
			col_h_Right = false;
			col_h_Left = false;
			col_h_Up = false;
			return 7;
		}
		// 블록과 충돌한 경우
		else if (((chx >= blockx && chx <= blockX) || (chX >= blockx && chX <= blockX)) &&				
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
			{
				// 갑작스런 충돌일 때
				return 6;
			} 
		}
		// 아무것도 아닐 때
		else																							
		{
			col_h_Down = false;
			col_h_Right = false;
			col_h_Left = false;
			col_h_Up = false;
			return 8;
		}
	}
	// off 거나 충돌 아니면 5 리턴
	return 5;																							
}

/*
기능 :		플레이어2과 상하 충돌
매개변수 :	플레이어2의 충돌 범위
반환 :		충돌의 종류 / off거나 비충돌 블록 - 5 / 비충돌 - 8 / 상하좌우에 위치 - 7 / 갑작스런 충돌 - 6 
						/ 좌측에서 충돌 - 0 / 우측에서 충돌 - 1 / 위에서충돌 - 2 / 아래에서 충돌 - 3
특이사항 :	없음
*/
int Block::Collision_V2(int chx, int chX, int chy, int chY)
{
	// 복구 중일 때는
	if (restoring)
	{
		// 충돌 없음
		return 8;
	}

	// 블록이 안 깨진 상태일 경우 && 충돌을 가지는 블록
	if (onoff && blockKind != 6 && blockKind != 7 && blockKind != 20)											
	{
		// 블록의 왼쪽 방향인 경우
		if (chX < blockx && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))			
		{
			col_v_Left2 = true;
			col_v_Right2 = false;
			col_v_Up2 = false;
			col_v_Down2 = false;
			return 7;
		}
		// 블록의 오른쪽 방향인 경우
		else if (chx > blockX && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))	
		{
			col_v_Right2 = true;
			col_v_Left2 = false;
			col_v_Up2 = false;
			col_v_Down2 = false;
			return 7;
		}
		// 블록의 위 방향인 경우
		else if (chY < blocky && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	
		{
			col_v_Up2 = true;
			col_v_Right2 = false;
			col_v_Left2 = false;
			col_v_Down2 = false;
			return 7;
		}
		// 블록의 아래 방향인 경우
		else if (chy > blockY && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	
		{
			col_v_Down2 = true;
			col_v_Right2 = false;
			col_v_Left2 = false;
			col_v_Up2 = false;
			return 7;
		}
		// 블록과 충돌한 경우
		else if (((chx >= blockx && chx <= blockX) || (chX >= blockx && chX <= blockX)) &&				
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
			{
				// 갑작스런 충돌일 때
				return 6;
			} 
		}
		// 아무것도 아닐 때
		else 
		{
			col_v_Down2 = false;
			col_v_Right2 = false;
			col_v_Left2 = false;
			col_v_Up2 = false;
			return 8;
		}
	}
	// off 거나 충돌 아니면 5 리턴
	return 5;																							
}

/*
기능 :		플레이어2과 좌우 충돌
매개변수 :	플레이어2의 충돌 범위
반환 :		충돌의 종류 / off거나 비충돌 블록 - 5 / 비충돌 - 8 / 상하좌우에 위치 - 7 / 갑작스런 충돌 - 6 
						/ 좌측에서 충돌 - 0 / 우측에서 충돌 - 1 / 위에서 충돌 - 2 / 아래에서 충돌 - 3
특이사항 :	없음
*/
int Block::Collision_H2(int chx, int chX, int chy, int chY)
{
	// 복구 중일 때는
	if (restoring)
	{
		// 충돌 없음
		return 8;
	}

	// 블록이 안 깨진 상태일 경우 && 충돌을 가지는 블록
	if (onoff && blockKind != 6 && blockKind != 7 && blockKind != 20)											
	{
		// 블록의 왼쪽 방향인 경우
		if (chX < blockx && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))			
		{
			col_h_Left2 = true;
			col_h_Right2 = false;
			col_h_Up2 = false;
			col_h_Down2 = false;
			return 7;
		}
		// 블록의 오른쪽 방향인 경우
		else if (chx > blockX && ((chy > blocky && chy < blockY) || (chY > blocky && chY < blockY)))	
		{
			col_h_Right2 = true;
			col_h_Left2 = false;
			col_h_Up2 = false;
			col_h_Down2 = false;
			return 7;
		}
		// 블록의 위 방향인 경우
		else if (chY < blocky && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	
		{
			col_h_Up2 = true;
			col_h_Right2 = false;
			col_h_Left2 = false;
			col_h_Down2 = false;
			return 7;
		}
		// 블록의 아래 방향인 경우
		else if (chy > blockY && ((chx > blockx && chx < blockX) || (chX > blockx && chX < blockX)))	
		{
			col_h_Down2 = true;
			col_h_Right2 = false;
			col_h_Left2 = false;
			col_h_Up2 = false;
			return 7;
		}
		// 블록과 충돌한 경우
		else if (((chx >= blockx && chx <= blockX) || (chX >= blockx && chX <= blockX)) &&				
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
			{
				// 갑작스런 충돌일 때
				return 6;
			} 
		}
		// 아무것도 아닐 때
		else 
		{
			col_h_Down2 = false;
			col_h_Right2 = false;
			col_h_Left2 = false;
			col_h_Up2 = false;
			return 8;
		}
	}
	// off 거나 충돌 아니면 5 리턴
	return 5;																							
}

/*
기능 :		블록의 충돌 범위 좌 반환
매개변수 :	없음
반환 :		블록의 충돌 범위 좌 (상수화)
특이사항 :	없음
*/
const int Block::getBlockx()
{
	return blockx;
}

/*
기능 :		블록의 충돌 범위 우 반환
매개변수 :	없음
반환 :		블록의 충돌 범위 우 (상수화)
특이사항 :	없음
*/
const int Block::getBlockX()
{
	return blockX;
}

/*
기능 :		블록의 충돌 범위 상 반환
매개변수 :	없음
반환 :		블록의 충돌 범위 상 (상수화)
특이사항 :	없음
*/
const int Block::getBlocky()
{
	return blocky;
}

/*
기능 :		블록의 충돌 범위 하 반환
매개변수 :	없음
반환 :		블록의 충돌 범위 하 (상수화)
특이사항 :	없음
*/
const int Block::getBlockY()
{
	return blockY;
}

/*
기능 :		블록의 종류 반환
매개변수 :	없음
반환 :		블록의 종류 (상수화)
특이사항 :	없음
*/
const int Block::getBoxKind()
{
	return blockKind;
}

/*
기능 :		블록의 파괴상태 반환
매개변수 :	없음
반환 :		블록의 파괴상태 (상수화)
특이사항 :	없음
*/
const bool Block::getOnoff()
{
	return onoff;
}

/*
기능 :		블록을 파괴한 플레이어 반환
매개변수 :	없음
반환 :		블록을 파괴한 플레이어 (상수화)
특이사항 :	없음
*/
const int Block::getPlayer()
{
	return player;
}

/*
기능 :		블록을 파괴한 플레이어 변환
매개변수 :	플레이어
반환 :		없음
특이사항 :	없음
*/
void Block::setPlayer(int player)
{
	this->player = player;
}

/*
기능 :		블록의 상태와 시간에 따른 멤버변수 조작
매개변수 :	없음
반환 :		없음
특이사항 :	구름 블록의 이동량을 변환
*/
void Block::Update()
{
	// 블록이 on 상태일 때만
	if (onoff == true)										
	{
		// 블록이 구름1, 구름2일 경우
		if (blockKind == 4 || blockKind == 5)				
		{
			// 시간마다
			if (GetTickCount() - CloudMoveTime > 10)		
			{
				// 위치 이동
				dx -= 2;			
				// 충돌 이동
				blockx -= 2;								
				blockX -= 2;

				// 맵의 특정 범위 벗어나면 리셋
				if (mapX * 40 + dx < 80)					
				{
					dx = (30 - mapX) * 40;
					blockx = 30 * 40;
					blockX = blockx + 80;
					if (blockKind == 5)
					{
						blockX += 40;
					}
				}
				CloudMoveTime = GetTickCount();
			}
		}

		// onoff = true로 실제 충돌 가능하게
		if (restoring && GetTickCount() - restoreStart > 300)
		{
			restoring = false;
		}
	}

	// 포물선 낙하 처리
	if (isFalling)
	{
		DWORD now = GetTickCount();
		// 시간 재기
		float dt = (now - fallStartTime) / 1000.0f; 

		// 중력에 의한 속도 증가
		vy += gravity * dt;

		// 위치 계산 - vx 일정, vy 누적  
		fx += vx * dt;
		fy += vy * dt;

		// 화면 아래로 완전히 떨어지면 낙하 종료
		// 화면 바깥 아래로 충분히 벗어나면
		if (fy > 720) 
		{
			isFalling = false;
		}
		// 시간을 계속 갱신
		fallStartTime = now; 
		// 낙하 중일 땐 다른 처리 생략
		return; 
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
	if (!onoff)
	{
		// 블록 꺼져있으면 그리지 않음
		return; 
	}
		
	// 블록이 on 상태일 때만
	if (onoff == true)															
	{
		// 구름 블록이 아닐 경우
		if (blockKind != 4 && blockKind != 5)									
		{
			img.Render(mapX * 40, mapY * 34, 0, scale, scale);
		}
		// 구름 블록일 경우
		else if (blockKind == 4 || blockKind == 5)								
		{
			img.Render(mapX * 40 + dx, mapY * 34, 0, scale, scale);
		}
	}

	if (Gmanager.m_GameStart == true)
	{
		sprite.Draw(x, y);
		DrawCollider();
	}
}

// 블록 디버그 박스 
void Block::DrawCollider()
{
	if (!Gmanager.m_bShowCollider)
	{
		return;
	}

	RECT r = { blockx, blocky, blockX, blockY };
	// 폰트 위치
	const int offset = 6; 

	dv_font.DrawString("┌", r.left - (offset * 3.6), r.top - (offset * 3.6), D3DCOLOR_ARGB(255, 255, 128, 0));
	dv_font.DrawString("┐ ", r.right - (offset * 3.6), r.top - (offset * 3.6), D3DCOLOR_ARGB(255, 255, 128, 0));
	dv_font.DrawString("└", r.left - (offset * 3.6), r.bottom - (offset * 4), D3DCOLOR_ARGB(255, 255, 128, 0));
	dv_font.DrawString("┘", r.right - (offset * 3.6), r.bottom - (offset * 4), D3DCOLOR_ARGB(255, 255, 128, 0));
}

bool Block::IsSolidForMonster() 
{
	if (!onoff || restoring)
	{
		return false;
	}
	// ROCK 제외
	return blockKind != 6 && blockKind != 7 && blockKind != 20; 
}

/*
기능 :		캐릭터의 상태에 따른 스트라이프 출력(맵 이동중)
매개변수 :	없음
반환 :		없음
특이사항 :	없음
*/
void Block::Floor(int floorY)
{
	// 블록이 on 상태일 때만
	if (onoff == true)															
	{
		// 구름 블록이 아닐경우
		if (blockKind != 4 && blockKind != 5)									
		{
			img.Render(mapX * 40, mapY * 34 + (floorY), 0, scale, scale);
		}
		// 구름 블록일 경우
		else if (blockKind == 4 || blockKind == 5)								
		{
			img.Render(mapX * 40 + dx, mapY * 34 + (floorY), 0, scale, scale);	
		}
	}
	// 맵 이동 마지막 시 변수 조정
	if (floorY >= 204)															
	{
		mapY += 6;

		if (blockKind == 8 || blockKind == 9)
		{
			blocky += (6 * 34);		// 상
			blockY += (6 * 34);		// 하
		}
		else
		{
			blocky += (6 * 34);		// 상
			blockY += (6 * 34);		// 하
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