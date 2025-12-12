#pragma once
/*
용도 :		캐릭터의 충돌 범위 구조체
맴버 변수 :	충돌 범위 chx : 좌, chX : 우, chy : 상, chY : 하
*/
struct Col
{
	int	chx, chy, chX, chY;			
};

/*
용도 :		게임 씬 내 캐릭터 클래스
맴버 변수 :	주석 참조
맴버 함수 :	생성자
			소멸자

			초기화
			업데이트
			드로우

			멤버변수 get,set

			캐릭터 간 좌우 충돌
			캐릭터 간 상하 충돌
			몬스터 충돌

			층 이동
*/
class Character
{
private: 

	// 플레이어 정보
	// 1p, 2p
	int	player;					
	// 캐릭터의 맵 초기 위치
	int	mapchX, mapchY;			
	// 충돌 범위
	Col	col;					
	// 임시 충돌 범위
	Col	col_temp;				
	// 텍스처 크기
	double scale;					
	
	// 이동
	// 향하는 방향
	int	pos;					
	// 좌 우 이동량
	int	move_x;					
	// 이동 충돌 - 좌 - true : 충돌, false : 비충돌
	bool move_collision_l;		
	// 이동 충돌 - 우 - true : 충돌, false : 비충돌
	bool move_collision_r;		
	// 이동 가능 - 좌 - true : 가능, false : 불가능
	bool move_able_l;			
	// 이동 가능 - 우 - true : 가능, false : 불가능
	bool move_able_r;			
	// 이동 상태 - 좌 - true : 가능, false : 불가능
	bool move_state_l;			
	// 이동 상태 - 좌 - true : 가능, false : 불가능
	bool move_state_r;			
	
	// 자동 이동
	// 자동 이동 중 - true : 이동 중, false: 이동 아님
	bool automove_state;			
	// 자동 이동 가능 - true : 가능, false : 불가능
	bool automove_able;			
	
	// 중력
	// 여분의 떨어진 정도
	int	extra_fall_Y;			
	// 상 하 이동량
	int	move_y;					
	// 임시 상 하 이동량
	int	move_y_temp;			
	// 현재 떨어지는 속도
	int	now_fall_speed;			
	// 최대 떨어지는 속도
	const int max_fall_speed = 14;	
	// 중력가속도
	const int gravity = 1;			
	// 떨어지는 상태 - true : 떨어짐, false : 떨어지지 않음 
	bool fall_state;				
	// 떨어짐 가능한 상태 - true : 가능, false : 불가능
	bool fall_able;				
	// 바닥 충돌 - true : 충돌, false : 비충돌
	bool floor_collision;		
	// 바닥 충돌 임시 - true : 충돌, false : 비충돌
	bool floor_collision_temp;	
	
	// 점프
	// 여분의 점프 뛴 정도
	int	extra_jump_y;			
	// 점프 상태 - true : 점프 중, false : 점프 아님
	bool jump_state;				
	// 점프 가능 상태 - true: 가능, false : 불가능
	bool jump_able;				
	// 점프 충돌 - true : 충돌, false : 비충돌
	bool jump_collision;			
	// 점프 충돌 임시 - true : 충돌, false : 비충돌
	bool jump_collision_temp;	
	// 점프 속도
	int	jump_speed;				
	// z 키 연속 눌림 방지 - true : 눌림, false : 눌리지 않음 
	bool Wkey_check;				
	
	// 캐릭터 간 충돌
	// 수직 이동 시 충돌 방향
	bool col_v_Up, col_v_Down, col_v_Left, col_v_Right;				
	// 수평 이동 시 충돌 방향
	bool col_h_Up, col_h_Down, col_h_Left, col_h_Right;				
	
	// 몬스터 충돌
	// 몬스터와 충돌 - true : 충돌, false : 비충돌
	bool col_mon;				
	// 죽음 - true : 죽음, false : 생존
	bool dead;					
	// 게임 오버 후 이동량
	int	gameover_y;				
	
	// 공격
	// 공격 상태
	bool attack_state;			

	// 충돌 박스 관련 변수 
	float x, y;
	float width = 118, height = 114;
	Collider collider;

	Sprite sprite;

public:
	Character();
	~Character();

	// 캐릭터 스프라이트
	Sprite stand[2], run[3], jump[2], attack[3], cha_dead[4], stopImg, gameover;		
	// 캐릭터 스프라이트 인덱스
	int d_count, r_count, s_count, j_count, a_count;											
	// 캐릭터 스프라이트 타임
	DWORD EndCountTime, DeadCountTime, RunCountTime, StandCountTime, JumpCountTime, AttackCountTime;	

	void Init(int mapchX, int mapchY, double scale, int player);
	void Update();
	void Draw();

	const int getPlayer();
	const Col getCol();
	const Col getCol_temp();
	const int getPos();

	const bool getMove_state_l();
	const bool getMove_state_r();
	void setMove_collision_l(bool state);
	void setMove_collision_r(bool state);
	void setMove_x(int a);

	void setAutomove_state(bool state);
	const bool getAutomove_state();
	void setAutomove_able(bool state);
	const bool getAutomove_able();

	void setFloor_collision(bool state);
	const bool getFloor_collision();
	void setFloor_collision_temp(bool state);
	const bool getFloor_collision_temp();
	const bool getFall_state();
	void setFall_state(bool state);
	const bool getFall_able();
	void setFall_able(bool state);
	void setExtra_fall_y(int a);

	void setJump_collision(bool state);
	const bool getJump_collision();
	void setJump_collision_temp(bool state);
	const bool getJump_state();
	const bool getJump_able();
	void setExtra_jump_y(int a);

	const bool getAttack_state();
	const bool getDead();

	int Collision_V(int chx, int chX, int chy, int chY);
	int Collision_H(int chx, int chX, int chy, int chY);
	int Collision_mon(int monx, int monX, int mony, int monY);

	void Floor(int floorY);
	void DrawCollider(); 
};


