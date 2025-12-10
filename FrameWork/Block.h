#pragma once
/*
용도 :		블럭 클래스
맴버 변수 :	주석 참조
맴버 함수 :	생성자
			소멸자

			초기화
			업데이트
			드로우

			멤버변수 get,set

			플레이어1과 좌우충돌
			플레이어1과 상하충돌
			플레이어2와 좌우충돌
			플레이어2와 상하충돌

			층이동
*/
class Block
{
private:
	
	int						blockKind;												// 해당 박스 객체의 종류
	int						mapX;													// 맵의 x좌표
	int						mapY;													// 맵의 y좌표
	int						dx;														// x 방향 이동량
	bool					onoff;													// 죽었니 살았니
	int						blockx, blocky, blockX, blockY;							// 충돌범위 blockx:좌, blockX:우, blocky:상 , blockY:하
	double					scale;
	int						player;
	//1p
	bool					col_v_Up, col_v_Down, col_v_Left, col_v_Right;			// 수직이동 충돌방향
	bool					col_h_Up, col_h_Down, col_h_Left, col_h_Right;			// 수평이동 충돌방향
	//2p
	bool					col_v_Up2, col_v_Down2, col_v_Left2, col_v_Right2;		// 수직이동 충돌방향
	bool					col_h_Up2, col_h_Down2, col_h_Left2, col_h_Right2;		// 수평이동 충돌방향

	// 블록 파괴 시 포물선 
	bool isFalling = false;        // 낙하 중인지 여부
	float fx = 0, fy = 0;        // 낙하 위치 (실수f 좌표)
	float vx = 0, vy = 0;        // 속도 (x, y)
	float gravity = 100.0f;        // 중력 가속도
	DWORD fallStartTime = 0;    // 낙하 시작 시간

	// ◆
	Sprite sprite;
	float x, y;

public:
	Sprite img, destroy[2], rockl[8], rockr[8];															// 블럭 스트라이프
	int m_Acount, m_Bcount, m_Bulletcount;											// 블럭 스트라이프 인덱스
	DWORD CloudMoveTime;															// 구름 이동 타임
	
	bool restoring;
	DWORD restoreStart;

	bool IsSolidForMonster();

	Block(void);
	~Block(void);
	

	void Init(int boxKind, int mapX, int mapY, double scale);
	void Update();
	void Draw();

	void Destroy(int player);
	void Resen();
	const int getBlockx();
	const int getBlockX();
	const int getBlocky();
	const int getBlockY();
	const int getBoxKind();
	const bool getOnoff();
	const int getPlayer();
	void setPlayer(int player);
	int getMapX() { return mapX; }
	int getMapY() { return mapY; }
	int Collision_V(int chx, int chX, int chy, int chY);
	int Collision_H(int chx, int chX, int chy, int chY);
	int Collision_V2(int chx, int chX, int chy, int chY);
	int Collision_H2(int chx, int chX, int chy, int chY);

	void Floor(int floorY);
	void SetRestoring(bool flag);
	void DrawCollider(); // ◆ 디버그 박스 그리기 함수
};