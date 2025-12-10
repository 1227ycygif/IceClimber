#pragma once
#include"Include.h"
/*
기능 :		생성자
*/
Character::Character()
{
}
/*
기능 :		소멸자
*/
Character::~Character()
{
}
/*
기능 :		초기화
매개변수 :	맵 x좌표, 맵 y좌표, 렌더링 스케일, 플레이어 번호
반환 :		없음
특이사항 :	각종 변수 초기화 및 스트라이프 이미지 연결
*/
void Character::Init(int mapchX, int mapchY, double scale, int player)
{
	this->player = player;
	this->scale = scale;
	this->mapchX = mapchX;
	this->mapchY = mapchY;
	// 이동
	pos = RIGHT;				
	move_x = 0;
	move_collision_l = false;
	move_collision_r = false;
	move_able_l = true;
	move_able_r = true;
	move_state_l = false;
	move_state_r = false;
	// 자동이동
	automove_state = false;
	automove_able = true;
	// 중력
	now_fall_speed = 0;				
	fall_state = true;				
	fall_able = false;
	floor_collision = false;
	floor_collision_temp = false;
	// 점프
	jump_state = false;
	jump_able = true;
	jump_collision = false;
	jump_collision_temp = false;
	jump_speed = 0;
	// 몬스터
	col_mon = false;
	dead = false;
	gameover_y = -80;
	// 공격
	attack_state = false;
	// 스트라이프 시간
	StandCountTime = GetTickCount();
	// 충돌범위
	col.chx = (mapchX * 40) - 14;		// 좌
	col.chX = (mapchX * 40) + 14;		// 우
	col.chy = (mapchY * 34) - 80;		// 상
	col.chY = (mapchY * 34);			// 하

	col_temp.chx = col.chx;				// 좌
	col_temp.chX = col.chX;				// 우
	col_temp.chy = col.chy;				// 상
	col_temp.chY = col.chY;				// 하

	char FileName[256];

	for (int i = 0; i < 3; i++)
	{
		sprintf_s(FileName, "./resource/Img/char/%dplayer_run%d.png", this->player, i + 1);
		run[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

		sprintf_s(FileName, "./resource/Img/char/%dplayer_attack%d.png", this->player, i + 1);
		attack[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(FileName, "./resource/Img/char/%dplayer_stand%d.png", this->player, i + 1);
		stand[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

		sprintf_s(FileName, "./resource/Img/char/%dplayer_jump%d.png", this->player, i + 1);
		jump[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	sprintf_s(FileName, sizeof(FileName), "./resource/Img/char/%dplayer_stop.png", this->player);
	stopImg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	for (int i = 0; i < 4; i++)
	{
		sprintf_s(FileName, "./resource/Img/mon/attackEffect%d.png", i + 1);
		cha_dead[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	sprintf_s(FileName, "./resource/Img/char/gameover.png");
	gameover.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}
/*
기능 :		캐릭터의 충돌범위 반환
매개변수 :	없음
반환 :		캐릭터의 충돌범위 (상수화)
특이사항 :	없음
*/
const Col Character::getCol()
{
	Col a = col;
	return a;
}
/*
기능 :		캐릭터의 임시 충돌범위 반환
매개변수 :	없음
반환 :		캐릭터의 임시 충돌범위 (상수화)
특이사항 :	없음
*/
const Col Character::getCol_temp()
{
	Col a = col_temp;
	return a;
}
/*
기능 :		캐릭터의 방향 반환
매개변수 :	없음
반환 :		캐릭터의 방향 (상수화)
특이사항 :	없음
*/
const int Character::getPos()
{
	return pos;
}
/*
기능 :		캐릭터의 이동 상태 좌 반환
매개변수 :	없음
반환 :		캐릭터의 이동 상태 좌 (상수화)
특이사항 :	없음
*/
const bool Character::getMove_state_l()
{
	return move_state_l;
}
/*
기능 :		캐릭터의 이동 상태 우 반환
매개변수 :	없음
반환 :		캐릭터의 이동 상태 우 (상수화)
특이사항 :	없음
*/
const bool Character::getMove_state_r()
{
	return move_state_r;
}
/*
기능 :		캐릭터의 이동 상태 좌 변환
매개변수 :	상태
반환 :		없음
특이사항 :	없음
*/
void Character::setMove_collision_l(bool state)
{
	move_collision_l = state;
}
/*
기능 :		캐릭터의 이동 상태 우 변환
매개변수 :	상태
반환 :		없음
특이사항 :	없음
*/
void Character::setMove_collision_r(bool state)
{
	move_collision_r = state;
}
/*
기능 :		캐릭터의 좌 우 이동량 변환
매개변수 :	이동량
반환 :		없음
특이사항 :	맵 끝까지 이동시 반대쪽으로 이동
*/
void Character::setMove_x(int move)
{
	move_x += move;
	col.chx += move;
	col.chX += move;
	col_temp.chx += move;
	col_temp.chX += move;

	if ((mapchX * 40) + (move_x) >= 1276)
	{
		move_x = 1 - (mapchX * 40);
		col.chx = 1 - 14;
		col.chX = 1 + 14;
		col_temp.chx = 1 - 14;
		col_temp.chX = 1 + 14;
	}
	else if ((mapchX * 40) + (move_x) <= 4)
	{
		move_x = 1279 - (mapchX * 40);
		col.chx = 1279 - 14;
		col.chX = 1279 + 14;
		col_temp.chx = 1279 - 14;
		col_temp.chX = 1279 + 14;
	}
}
/*
기능 :		캐릭터의 자동이동 상태 변환
매개변수 :	상태
반환 :		없음
특이사항 :	없음
*/
void Character::setAutomove_state(bool state)
{
	automove_state = state;
}
/*
기능 :		캐릭터의 자동이동 상태 반환
매개변수 :	없음
반환 :		캐릭터의 자동이동 상태 (상수화)
특이사항 :	없음
*/
const bool Character::getAutomove_state()
{
	return automove_state;
}
/*
기능 :		캐릭터의 자동이동 가능상태 변환
매개변수 :	상태
반환 :		없음
특이사항 :	없음
*/
void Character::setAutomove_able(bool state)
{
	automove_able = state;
}
/*
기능 :		캐릭터의 자동이동 가능상태 반환
매개변수 :	없음
반환 :		캐릭터의 자동이동 가능상태 (상수화)
특이사항 :	없음
*/
const bool Character::getAutomove_able()
{
	return automove_able;
}
/*
기능 :		캐릭터의 바닥 충돌 상태 변환
매개변수 :	상태
반환 :		없음
특이사항 :	없음
*/
void Character::setFloor_collision(bool state)
{
	floor_collision = state;
}
/*
기능 :		캐릭터의 바닥 충돌 반환
매개변수 :	없음
반환 :		캐릭터의 바닥 충돌 (상수화)
특이사항 :	없음
*/
const bool Character::getFloor_collision()
{
	return floor_collision;
}
/*
기능 :		캐릭터의 임시 바닥 충돌 상태 변환
매개변수 :	상태
반환 :		없음
특이사항 :	없음
*/
void Character::setFloor_collision_temp(bool state)
{
	floor_collision_temp = state;
}
/*
기능 :		캐릭터의 임시 바닥 충돌 반환
매개변수 :	없음
반환 :		캐릭터의 임시 바닥 충돌 (상수화)
특이사항 :	없음
*/
const bool Character::getFloor_collision_temp()
{
	return floor_collision_temp;
}
/*
기능 :		캐릭터의 떨어지는 상태 반환
매개변수 :	없음
반환 :		캐릭터의 떨어지는 상태 (상수화)
특이사항 :	없음
*/
const bool Character::getFall_state()
{
	return fall_state;
}
/*
기능 :		캐릭터의 떨어짐 상태 변환
매개변수 :	상태
반환 :		없음
특이사항 :	없음
*/
void Character::setFall_state(bool state)
{
	fall_state = state;
}
/*
기능 :		캐릭터의 떨어짐 가능 상태 반환
매개변수 :	없음
반환 :		캐릭터의 떨어짐 가능 상태 (상수화)
특이사항 :	없음
*/
const bool Character::getFall_able()
{
	return fall_able;
}
/*
기능 :		캐릭터의 떨어짐 가능 상태 변환
매개변수 :	상태
반환 :		없음
특이사항 :	없음
*/
void Character::setFall_able(bool state)
{
	fall_able = state;
}
/*
기능 :		캐릭터의 점프 충돌 상태 변환
매개변수 :	상태
반환 :		없음
특이사항 :	없음
*/
void Character::setJump_collision(bool state)
{
	jump_collision = state;
}
/*
기능 :		캐릭터의 점프 충돌 반환
매개변수 :	없음
반환 :		캐릭터의 점프 충돌 (상수화)
특이사항 :	없음
*/
const bool Character::getJump_collision()
{
	return jump_collision;
}
/*
기능 :		캐릭터의 임시 점프 충돌 상태 변환
매개변수 :	상태
반환 :		없음
특이사항 :	없음
*/
void Character::setJump_collision_temp(bool state)
{
	jump_collision_temp = state;
}
/*
기능 :		캐릭터의 점프 상태 반환
매개변수 :	없음
반환 :		캐릭터의 점프 상태 (상수화)
특이사항 :	없음
*/
const bool Character::getJump_state()
{
	return jump_state;
}
/*
기능 :		캐릭터의 점프가능 상태 반환
매개변수 :	없음
반환 :		캐릭터의 점프가능 상태 (상수화)
특이사항 :	없음
*/
const bool Character::getJump_able()
{
	return jump_able;
}
/*
기능 :		캐릭터의 여분의 떨어짐 이동량 변환
매개변수 :	상태
반환 :		없음
특이사항 :	없음
*/
void Character::setExtra_fall_y(int a)
{
	extra_fall_Y = a;
}
/*
기능 :		캐릭터의 여분의 점프 이동량 변환
매개변수 :	상태
반환 :		없음
특이사항 :	없음
*/
void Character::setExtra_jump_y(int a)
{
	extra_jump_y = a;
}
/*
기능 :		캐릭터의 공격 상태 반환
매개변수 :	없음
반환 :		캐릭터의 공격 상태 (상수화)
특이사항 :	없음
*/
const bool Character::getAttack_state()
{
	return attack_state;
}
/*
기능 :		캐릭터의 죽음 상태 반환
매개변수 :	없음
반환 :		캐릭터의 죽음 상태 (상수화)
특이사항 :	없음
*/
const bool Character::getDead()
{
	return dead;
}
/*
기능 :		캐릭터 플레이어 반환
매개변수 :	없음
반환 :		캐릭터 플레이어 반환(상수화)
특이사항 :	없음
*/
const int Character::getPlayer()
{
	return player;
}

/*
기능 :		캐릭터간의 수직방향 충돌 판정
매개변수 :	다른 캐릭터의 충돌범위
반환 :		충돌의 종류 / 비충돌 - 8 / 상하좌우에 위치 - 7 / 갑작스런 충돌 - 6 / 좌에서충돌 - 0 / 우에서충돌 - 1 / 위에서충돌 - 2 / 아래서충돌 - 3
특이사항 :	없음
*/
int Character::Collision_V(int chx, int chX, int chy, int chY)
{
	if (col_temp.chX < chx && ((col_temp.chy > chy && col_temp.chy < chY) || (col_temp.chY > chy && col_temp.chY < chY)))		// 블럭의 왼쪽 방향인 경우
	{
		col_v_Left = true;

		col_v_Right = false;
		col_v_Up = false;
		col_v_Down = false;
		return 7;
	}
	else if (col_temp.chx > chX && ((col_temp.chy > chy && col_temp.chy < chY) || (col_temp.chY > chy && col_temp.chY < chY)))	// 블럭의 오른쪽 방향인 경우
	{
		col_v_Right = true;

		col_v_Left = false;
		col_v_Up = false;
		col_v_Down = false;
		return 7;
	}
	else if (col_temp.chY < chy && ((col_temp.chx > chx && col_temp.chx < chX) || (col_temp.chX > chx && col_temp.chX < chX)))	// 블럭의 위 방향인 경우
	{
		col_v_Up = true;

		col_v_Right = false;
		col_v_Left = false;
		col_v_Down = false;
		return 7;
	}
	else if (col_temp.chy > chY && ((col_temp.chx > chx && col_temp.chx < chX) || (col_temp.chX > chx && col_temp.chX < chX)))	// 블럭의 아래 방향인 경우
	{
		col_v_Down = true;

		col_v_Right = false;
		col_v_Left = false;
		col_v_Up = false;
		return 7;
	}
	else if (((col_temp.chx >= chx && col_temp.chx <= chX) || (col_temp.chX >= chx && col_temp.chX <= chX)) &&					// 블럭과 충돌한경우
		((col_temp.chy >= chy && col_temp.chy <= chY) || (col_temp.chY >= chy && col_temp.chY <= chY)))
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
/*
기능 :		캐릭터간의 수평방향 충돌 판정
매개변수 :	다른 캐릭터의 충돌범위
반환 :		충돌의 종류 / 비충돌 - 8 / 상하좌우에 위치 - 7 / 갑작스런 충돌 - 6 / 좌에서충돌 - 0 / 우에서충돌 - 1 / 위에서충돌 - 2 / 아래서충돌 - 3
특이사항 :	없음
*/
int Character::Collision_H(int chx, int chX, int chy, int chY)
{
	col.chy++;
	col.chY--;
	if (col.chX < chx && ((col.chy > chy && col.chy < chY) || (col.chY > chy && col.chY < chY)))		// 블럭의 왼쪽 방향인 경우
	{
		col_h_Left = true;

		col_h_Right = false;
		col_h_Up = false;
		col_h_Down = false;
		col.chy--;
		col.chY++;
		return 7;
	}
	else if (col.chx > chX && ((col.chy > chy && col.chy < chY) || (col.chY > chy && col.chY < chY)))	// 블럭의 오른쪽 방향인 경우
	{
		col_h_Right = true;

		col_h_Left = false;
		col_h_Up = false;
		col_h_Down = false;
		col.chy--;
		col.chY++;
		return 7;
	}
	else if (col.chY < chy && ((col.chx > chx && col.chx < chX) || (col.chX > chx && col.chX < chX)))	// 블럭의 위 방향인 경우
	{
		col_h_Up = true;

		col_h_Right = false;
		col_h_Left = false;
		col_h_Down = false;
		col.chy--;
		col.chY++;
		return 7;
	}
	else if (col.chy > chY && ((col.chx > chx && col.chx < chX) || (col.chX > chx && col.chX < chX)))	// 블럭의 아래 방향인 경우
	{
		col_h_Down = true;

		col_h_Right = false;
		col_h_Left = false;
		col_h_Up = false;
		col.chy--;
		col.chY++;
		return 7;
	}
	else if (((col.chx >= chx && col.chx <= chX) || (col.chX >= chx && col.chX <= chX)) &&				// 블럭과 충돌한경우
		((col.chy >= chy && col.chy <= chY) || (col.chY >= chy && col.chY <= chY)))
	{
		if (col_h_Up)
		{
			col.chy--;
			col.chY++;
			col_h_Up = false;
			return UP;
		}
		else if (col_h_Down)
		{
			col.chy--;
			col.chY++;
			col_h_Down = false;
			return DOWN;
		}
		else if (col_h_Left)
		{
			col.chy--;
			col.chY++;
			col_h_Left = false;
			return LEFT;
		}
		else if (col_h_Right)
		{
			col.chy--;
			col.chY++;
			col_h_Right = false;
			return RIGHT;
		}
		else
		{
			col.chy--;
			col.chY++;
			return 6;																				// 갑작스런 충돌일때
		}
	}
	else																							// 아무것도아닐때
	{
		col_h_Down = false;
		col_h_Right = false;
		col_h_Left = false;
		col_h_Up = false;

		col.chy--;
		col.chY++;
		return 8;
	}
}
/*
기능 :		캐릭터와 몬스터간의 충돌 판정
매개변수 :	몬스터의 충돌범위
반환 :		충돌의 종류 / 비충돌 - 0 / 충돌 - 1
특이사항 :	몬스터가 가려져있을경우 충돌안함
*/
int Character::Collision_mon(int monx, int monX, int mony, int monY)
{
	if ((mapchX * 40) + (move_x) < 220 || (mapchX * 40) + (move_x) > 1060)							// 몬스터가 숨으면 충돌안함
		return 0;
	if (!col_mon)
		if (((col.chx >= monx && col.chx <= monX) || (col.chX >= monx && col.chX <= monX)) &&		// 몬스터와 충돌한경우
			((col.chy >= mony && col.chy <= monY) || (col.chY >= mony && col.chY <= monY)))
		{
			sound.m_Death->Play(0, NULL);			// 죽음 사운드
			col_mon = true;							// 몬스터 충돌 상태 전환												
			dead = false;							// 죽음 상태 전환
			DeadCountTime = GetTickCount();			// 죽음 스프라이트 시간계산시작
			EndCountTime = GetTickCount();			// 다음씬 시간계산시작
			return 1;
		}
	return 0;
}

/*
기능 :		캐릭터의 상태와 시간, 키입력에 따른 멤버변수 조작
매개변수 :	없음
반환 :		없음
특이사항 :	캐릭터의 이동량, 스프라이트 인덱스를 변환
*/
void Character::Update()
{
	// 맵의 바닥에 충돌시 죽음처리
	if (!col_mon && col.chy > 768)
	{
		sound.m_Death->Play(0, NULL);
		col_mon = true;
		dead = false;
		attack_state = false;
		DeadCountTime = GetTickCount();
		EndCountTime = GetTickCount();
	}
	// 몬스터 충돌시 죽음처리
	if (col_mon)
	{
		attack_state = false;
		if ((mapchY * 34) - 114 + (move_y)+(gameover_y) > 60)
			gameover_y -= 2;
		if (GetTickCount() - EndCountTime > 4000)
		{
			sound.m_overbg->Play(0, DSBPLAY_LOOPING);
			sound.m_Bk1->Reset();
			sound.m_Bk1->Stop();
			sound.m_Gamebg->Reset();
			sound.m_Gamebg->Stop();
			g_Mng.n_Chap = OVER;
			g_Mng.chap[g_Mng.n_Chap]->Init();
		}
		// 스프라이트
		if (GetTickCount() - DeadCountTime > 200 && dead)
		{
			d_count++;

			if (d_count > 3) {
				d_count = 0;
				dead = false;
			}
			DeadCountTime = GetTickCount();
		}
	}
	// 몬스터 비충돌시 입력에 따른 조작
	else
	{
		// 기본 스프라이트
		if (GetTickCount() - StandCountTime > 800)
		{
			s_count++;

			if (s_count > 1) {
				s_count = 0;
			}
			StandCountTime = GetTickCount();
		}
		// 평상시 = 떨어지는 상태
		if (!jump_state)
		{
			if (!floor_collision_temp)		// 바닥충돌도 아니고 임시 바닥충돌도 아닐때
			{
				if (now_fall_speed < max_fall_speed)
				{
					now_fall_speed += gravity;
				}
				// 이전거 저장
				move_y = move_y_temp;
				col.chy = col_temp.chy;
				col.chY = col_temp.chY;
				// 임시이동
				move_y_temp += now_fall_speed;
				col_temp.chy += now_fall_speed;
				col_temp.chY += now_fall_speed;
				attack_state = false;
				jump_able = false;
			}
			else if (floor_collision_temp)	// 임시 바닥충돌 했을때
			{
				// 여분만큼 적용
				move_y += extra_fall_Y;
				col.chy += extra_fall_Y;
				col.chY += extra_fall_Y;
				// 임시위치도 적용
				move_y_temp = move_y;
				col_temp.chy = col.chy;
				col_temp.chY = col.chY;
				//초기화
				now_fall_speed = 0;
				extra_fall_Y = 0;
				//상태변환
				jump_able = true;						// 일단 한번 바닥에 착지하면 점프가능 상태
				floor_collision_temp = false;			// 바닥 임시충돌을 끄면 다시 충돌검사가 가능
			}
		}
		// 플레이어 1일경우
		if (player == PLAYER1)
		{	
			// 공격시 변수 조작
			if (KeyUp('S'))
			{
				// 상태 전환
				attack_state = false;
			}
			if (KeyDown('S') && jump_able)				// 바닥에있는 상태에서
			{
				// 공격 스프라이트
				if (GetTickCount() - AttackCountTime > 200)
				{
					a_count++;

					if (a_count > 1) {
						a_count = 0;
					}
					AttackCountTime = GetTickCount();
				}
				// 상태 전환
				attack_state = true;
			}
			// 점프시 변수 조작
			if (KeyUp('W'))
			{
				Wkey_check = false;
			}
			if (KeyDown('W') && jump_able && !Wkey_check)		// W키 다운중 && 점프가 가능할때 && 이전에 W 키가 눌린적 없으면
			{
				sound.m_Jump->Play(0, NULL);
				JumpCountTime = GetTickCount();
				j_count = 0;

				// 상태 전환
				Wkey_check = true;								// W 키가 눌렸던 적이 있다
				jump_able = false;								// 더이상 점프는 불가능하다
				jump_state = true;								// 점프 상태로 전환
				attack_state = false;
				//floor_collision = false;						// 바닥충돌도 아니다
				// 초기화
				jump_speed = -22;
			}
			// 점프 스프라이트
			if (GetTickCount() - JumpCountTime > 75 && jump_state)		// 일정시간 지나면 변화
			{
				j_count = 1;
			}
			// 우로 이동시 변수 조작
			if (KeyUp('D') && !attack_state)							// 키가 올라갔을때
			{
				//상태변환
				move_state_r = false;									// 우로 이통 키가 안눌림
			}
			if (KeyDown('D') && !attack_state)							// 키가 눌러지고 움직일 수 있을때
			{
				// 이동 스프라이트
				if (GetTickCount() - RunCountTime > 100)
				{
					r_count++;

					if (r_count > 1) {
						r_count = 0;
					}
					RunCountTime = GetTickCount();
				}
				// 상태변환
				move_state_r = true;					
				pos = RIGHT;
				// 이동량
				int move = 4;
				if (move_collision_r)
				{
					move = 0;
					move_collision_r = false;
				}
				move_x += move;					
				col.chx += move;
				col.chX += move;
				col_temp.chx += move;
				col_temp.chX += move;

				if ((mapchX * 40) + (move_x) >= 1276)
				{
					move_x = 1 - (mapchX * 40);
					col.chx = 1 - 14;
					col.chX = 1 + 14;
					col_temp.chx = 1 - 14;
					col_temp.chX = 1 + 14;
				}
			}
			// 좌로이동시 변수 조작
			if (KeyUp('A') && !attack_state)					// 키가 올라갔을때
			{
				//상태변환
				move_state_l = false;							// 우로 이통 키가 안눌림
			}
			if (KeyDown('A') && !attack_state)
			{
				// 스프라이트
				if (GetTickCount() - RunCountTime > 100)
				{
					r_count++;

					if (r_count > 1) {
						r_count = 0;
					}
					RunCountTime = GetTickCount();
				}
				// 상태변환
				move_state_l = true;					
				pos = LEFT;
				// 이동량
				int move = -4;
				if (move_collision_l)
				{
					move = 0;
					move_collision_l = false;
				}
				move_x += move;			
				col.chx += move;
				col.chX += move;
				col_temp.chx += move;
				col_temp.chX += move;

				if ((mapchX * 40) + (move_x) <= 4)
				{
					move_x = 1279 - (mapchX * 40);
					col.chx = 1279 - 14;
					col.chX = 1279 + 14;
					col_temp.chx = 1279 - 14;
					col_temp.chX = 1279 + 14;
				}
			}
		}
		// 플레이어 2일 경우
		else
		{
			// 공격시 변수 조작
			if (KeyDown(VK_DOWN) && jump_able)				// 바닥에있는상태에서
			{
				// 공격 스프라이트
				if (GetTickCount() - AttackCountTime > 200)
				{
					a_count++;

					if (a_count > 1) {
						a_count = 0;
					}
					AttackCountTime = GetTickCount();
				}
				// 상태 전환
				attack_state = true;
			}
			if (KeyUp(VK_DOWN))
			{
				// 상태 전환
				attack_state = false;
			}
			// 점프시 변수 조작
			if (KeyUp(VK_UP))
			{
				Wkey_check = false;
			}
			if (KeyDown(VK_UP) && jump_able && !Wkey_check)		// z키 다운중 && 점프가 가능할때 && 이전에 z 키가 눌린적 없으면
			{
				sound.m_Jump->Play(0, NULL);
				JumpCountTime = GetTickCount();
				j_count = 0;

				// 상태 전환
				Wkey_check = true;								// z 키가 눌렸던 적이 있다
				jump_able = false;								// 더이상 점프는 불가능하다
				jump_state = true;								// 점프 상태로 전환
																//floor_collision = false;						// 바닥충돌도 아니다
																// 초기화
				jump_speed = -22;
			}
			// 점프 스프라이트
			if (GetTickCount() - JumpCountTime > 75 && jump_state)		// 일정시간 지나면 변화
			{
				j_count = 1;
			}
			// 우로이동시 변수 조작
			if (KeyUp(VK_RIGHT) && !attack_state)						// 키가 올라갔을때
			{
				//상태변환
				move_state_r = false;									// 우로 이통 키가 안눌림
			}
			if (KeyDown(VK_RIGHT) && !attack_state)						// 키가 눌러지고 움직일 수 있을때
			{
				// 스프라이트
				if (GetTickCount() - RunCountTime > 100)
				{
					r_count++;

					if (r_count > 1) {
						r_count = 0;
					}
					RunCountTime = GetTickCount();
				}
				// 상태변환
				move_state_r = true;					
				pos = RIGHT;
				// 이동량
				int move = 4;
				if (move_collision_r)
				{
					move = 0;
					move_collision_r = false;
				}
				move_x += move;				// 좌 우 이동
				col.chx += move;
				col.chX += move;
				col_temp.chx += move;
				col_temp.chX += move;

				if ((mapchX * 40) + (move_x) >= 1276)
				{
					move_x = 1 - (mapchX * 40);
					col.chx = 1 - 14;
					col.chX = 1 + 14;
					col_temp.chx = 1 - 14;
					col_temp.chX = 1 + 14;
				}
			}
			// 좌로이동시 변수 조작
			if (KeyUp(VK_LEFT) && !attack_state)						// 키가 올라갔을때
			{
				//상태변환
				move_state_l = false;									// 우로 이통 키가 안눌림
			}
			if (KeyDown(VK_LEFT) && !attack_state)
			{
				// 스프라이트
				if (GetTickCount() - RunCountTime > 100)
				{
					r_count++;

					if (r_count > 1) {
						r_count = 0;
					}
					RunCountTime = GetTickCount();
				}
				// 상태변환
				move_state_l = true;			
				pos = LEFT;
				// 이동량
				int move = -4;
				if (move_collision_l)
				{
					move = 0;
					move_collision_l = false;
				}
				move_x += move;			
				col.chx += move;
				col.chX += move;
				col_temp.chx += move;
				col_temp.chX += move;

				if ((mapchX * 40) + (move_x) <= 4)
				{
					move_x = 1279 - (mapchX * 40);
					col.chx = 1279 - 14;
					col.chX = 1279 + 14;
					col_temp.chx = 1279 - 14;
					col_temp.chX = 1279 + 14;
				}
			}
		}
		// 점프시 변수 조작
		if (jump_collision_temp)						// 머리맞으면 
		{
			// 상태 전환
			jump_state = false;							// 떨어지는 상태로 전환
			jump_collision_temp = false;				// 임시는 꺼둠
														// 남은양 적용
														//move_y += extra_jump_y;
														//col.chy += extra_jump_y;
														//col.chY += extra_jump_y;
														// 임시위치 적용
			move_y_temp = move_y;
			col_temp.chy = col.chy;
			col_temp.chY = col.chY;
			//초기화
			extra_jump_y = 0;
			//now_fall_speed = -jump_speed/2;
			jump_speed = 0;
			//jump_collision = true;					// 점프충돌은 했던상태로
		}
		else if (jump_state)							// 머리안맞고 점프중일때
		{
			jump_speed += gravity;
			// 이전거 저장
			move_y = move_y_temp;
			col.chy = col_temp.chy;
			col.chY = col_temp.chY;
			// 임시로 이동
			move_y_temp += jump_speed;
			col_temp.chy += jump_speed;
			col_temp.chY += jump_speed;

			if (jump_speed >= 0)						// 점프가 최대일경우
			{
				jump_collision_temp = true;				// 머리맞은것으로 판정
			}
		}
		// 자동이동중 변수 조작
		if (automove_state)		
		{
			automove_state = false;
			move_x -= 2;
			col.chx -= 2;
			col.chX -= 2;
			col_temp.chx -= 2;
			col_temp.chX -= 2;

			if ((mapchX * 40) + (move_x) >= 1276)
			{
				move_x = 1 - (mapchX * 40);
				col.chx = 1 - 14;
				col.chX = 1 + 14;
				col_temp.chx = 1 - 14;
				col_temp.chX = 1 + 14;
			}
			else if ((mapchX * 40) + (move_x) <= 4)
			{
				move_x = 1279 - (mapchX * 40);
				col.chx = 1279 - 14;
				col.chX = 1279 + 14;
				col_temp.chx = 1279 - 14;
				col_temp.chX = 1279 + 14;
			}
		}
	}
}
/*
기능 :		캐릭터의 상태에 따른 스트라이프 출력
매개변수 :	없음
반환 :		없음
특이사항 :	없음
*/
void Character::Draw()
{
	// 죽었을경우 터지는스트라이프, 게임오버스트라이프 출력
	if (dead)
	{
		cha_dead[d_count].Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y), 0, 1.2, 1.2);
		gameover.Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y)+(gameover_y), 0, 1, 1);
	}
	// 터지는 스트라이프 출력후, 게임오버스트라이프 출력
	else if (col_mon)
	{
		gameover.Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y)+(gameover_y), 0, 1, 1);
	}
	// 죽지 않은경우
	else if (!col_mon)
	{
		// 방향에 따라 스프라이트 반전
		if (pos == RIGHT)
		{
			// 각종 상태에 따라 다른 스프라이트
			if (attack_state)
				attack[a_count].Render((mapchX * 40) + 59 + (move_x), (mapchY * 34) - 114 + (move_y), 0, -scale, scale);
			else if (jump_state)
				jump[j_count].Render((mapchX * 40) + 59 + (move_x), (mapchY * 34) - 114 + (move_y), 0, -scale, scale);
			else if (!jump_able)
				jump[j_count].Render((mapchX * 40) + 59 + (move_x), (mapchY * 34) - 114 + (move_y), 0, -scale, scale);
			else if (move_state_r)
				run[r_count].Render((mapchX * 40) + 59 + (move_x), (mapchY * 34) - 114 + (move_y), 0, -scale, scale);
			else
				stand[s_count].Render((mapchX * 40) + 59 + (move_x), (mapchY * 34) - 114 + (move_y), 0, -scale, scale);

		}
		else if (pos == LEFT)
		{
			if (attack_state)
				attack[a_count].Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y), 0, scale, scale);
			else if (jump_state)
				jump[j_count].Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y), 0, scale, scale);
			else if (!jump_able)
				jump[j_count].Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y), 0, scale, scale);
			else if (move_state_l)
				run[r_count].Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y), 0, scale, scale);
			else
				stand[s_count].Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y), 0, scale, scale);
		}
	}
	
	if (Gmanager.m_GameStart == true)
	{ 
		sprite.Draw(x, y);
		DrawCollider();
	}
}

// 디버그 박스 
void Character::DrawCollider()
{
	if (!Gmanager.m_bShowCollider)
		return;

	RECT r = { col.chx, col.chy, col.chX, col.chY };
	const int offset = 15; // 폰트 위치 조정 
	
	dv_font.DrawString("┌ ", r.left - (offset * 3.5), r.top - (offset * 1.9), D3DCOLOR_ARGB(255, 255, 0, 255));
	dv_font.DrawString(" ┐", r.right - (offset * 0.6), r.top - (offset * 1.9), D3DCOLOR_ARGB(255, 255, 0, 255));
	dv_font.DrawString("└ ", r.left - (offset * 3.5), r.bottom - (offset * 1.5), D3DCOLOR_ARGB(255, 255, 0, 255));
	dv_font.DrawString(" ┘", r.right - (offset * 0.6), r.bottom - (offset * 1.5), D3DCOLOR_ARGB(255, 255, 0, 255));
}

/*
기능 :		캐릭터의 상태에 따른 스트라이프 출력(맵 이동중)
매개변수 :	없음
반환 :		없음
특이사항 :	없음
*/
void Character::Floor(int floorY)
{
	// 죽었을경우 터지는스트라이프, 게임오버스트라이프 출력
	if (dead)
	{
		cha_dead[d_count].Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y)+(floorY), 0, 1.2, 1.2);
		gameover.Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y)+(gameover_y)+(floorY), 0, 1, 1);
	}
	// 터지는 스트라이프 출력후, 게임오버스트라이프 출력
	else if (col_mon)
	{
		gameover.Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y)+(gameover_y)+(floorY), 0, 1, 1);
	}
	// 죽지 않은경우
	else if (!col_mon)
	{
		// 방향에 따라 스프라이트 반전
		if (pos == RIGHT)
		{
			// 각종 상태에 따라 다른 스프라이트
			if (attack_state)
				attack[a_count].Render((mapchX * 40) + 59 + (move_x), (mapchY * 34) - 114 + (move_y)+(floorY), 0, -scale, scale);
			else if (jump_state)
				jump[j_count].Render((mapchX * 40) + 59 + (move_x), (mapchY * 34) - 114 + (move_y)+(floorY), 0, -scale, scale);
			else if (!jump_able)
				jump[j_count].Render((mapchX * 40) + 59 + (move_x), (mapchY * 34) - 114 + (move_y)+(floorY), 0, -scale, scale);
			else if (move_state_r)
				run[r_count].Render((mapchX * 40) + 59 + (move_x), (mapchY * 34) - 114 + (move_y)+(floorY), 0, -scale, scale);
			else
				stand[s_count].Render((mapchX * 40) + 59 + (move_x), (mapchY * 34) - 114 + (move_y)+(floorY), 0, -scale, scale);

		}
		else if (pos == LEFT)
		{
			if (attack_state)
				attack[a_count].Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y)+(floorY), 0, scale, scale);
			else if (jump_state)
				jump[j_count].Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y)+(floorY), 0, scale, scale);
			else if (!jump_able)
				jump[j_count].Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y)+(floorY), 0, scale, scale);
			else if (move_state_l)
				run[r_count].Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y)+(floorY), 0, scale, scale);
			else
				stand[s_count].Render((mapchX * 40) - 59 + (move_x), (mapchY * 34) - 114 + (move_y)+(floorY), 0, scale, scale);
		}
	}
	// 맵이동 마지막시 변수 조정
	if (floorY >= 204)
	{
		mapchY += 6;

		col.chy += (6 * 34);			// 상
		col.chY += (6 * 34);			// 하

		col_temp.chy += (6 * 34);		// 상
		col_temp.chY += (6 * 34);		// 하
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