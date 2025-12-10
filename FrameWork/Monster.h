#pragma once
#include "Include.h"
class BlockManager;  // BlockManager*만 쓸 때 forward 선언
// 만약 BlockManager의 함수/멤버까지 쓰면 반드시 #include "BlockManager.h"로 바꿀 것

/*
용도 :		게임 씬내 캐릭터 클래스
맴버 변수 :	주석 참조
맴버 함수 :	생성자
			소멸자

			초기화
			업데이트
			드로우
			리셋

			멤버변수 get,set

			몬스터의 방향전환 충돌
			몬스터의 바닥파괴 충돌
			몬스터가 캐릭터에게 충돌

			층이동
*/

enum MonsterState
{
	MON_IDLE, //동굴 대기
	MON_SEARCH, //탐색
	MON_RETURN, //동굴로 복귀
	MON_BRING, //고드름 들고 이동
	MON_PLACE //블럭 설치

};

const int MAX_MONSTER = 6;

// ◆ 길찾기 알고리즘
struct BFSNode 
{
	int x, prev; // x : mapX 좌표, prev : 어디서 왔는지
};

class Monster
{
	int						monKind;			// 해당 박스 객체의 종류
	int						mapX;				// 맵의 x좌표
	int						mapY;				// 맵의 y좌표
	double					scale;				// 렌더링 스케일
	int						pos;				// 향하는 방향
	int						move_x;				// 좌 우 이동
	bool					create;				// 맵생성시 생성될지 안될지
	bool					onoff;				// 죽었니 살았니
	bool					boom;				// 터짐


	int						monx, mony, monX, monY;		// 충돌범위 blockx:좌, blockX:우, blocky:상 , blockY:하


	//방향전환
	bool					col_front_turn, col_down_turn;								// 앞부분 충돌, 앞 바닥부분 충돌
	//바닥
	bool					col_floor;													// 바닥 사라짐 수직 충돌방향							
	//1p
	bool					col_h_Up, col_h_Down, col_h_Left, col_h_Right;				// 1플레이어 망치 수평 충돌방향																		
	//2p
	bool					col_h_Up2, col_h_Down2, col_h_Left2, col_h_Right2;			// 2플레이어 망치 수평 충돌방향

	BlockManager* blockMgr;//자기 층의 블럭매니저
	int state;//MonsterState
	bool hasIcicle;
	int targetX, targetY; //블록 생성 목표 좌표
	
	// ◆
	int monsterCount;
	Monster* monsterList[MAX_MONSTER];

	// ◆
	Sprite sprite;
	float x, y;

	int lastPlacedX = -1;
	int lastPlacedY = -1;

	int caveX; // ◆ MON_SEARCH

	int nextX;
	bool blocked; // ◆ MON_BRING


public:

	Monster(void);

	~Monster(void);

	DWORD MonMoveTime, MonCountTime, AttCountTime, RezCountTime;				// 몬스터 이동및 스프라이트 시간
	Sprite seal_walk[3],attackEffect[3], bird_fly[2], bird_attacked,icicle;	// 몬스터 스프라이트
	int m_count, a_count;														// 몬스터 스프라이트 인덱스

	void Init(int monKind, int mapY, double scale, bool start);
	void Update();
	void Draw();
	void Reset();

	void SetBlockManager(BlockManager* mgr) { blockMgr = mgr; }

	const int getMonx();
	const int getMonX();
	const int getMony();
	const int getMonY();
	const bool getCreate();
	const bool getOnoff();
	const bool getBoom();
	void setCol_front_turn(bool state);
	void setCol_down_turn(bool state);
	void setCol_floor(bool state);

	int Collision_turn(int blockx, int blockX, int blocky, int blockY, bool onoff);		
	int Collision_floor(int blockx, int blockX, int blocky, int blockY, bool onoff);	
	int Collision_attacked(int chax, int chaX, int chay, int chaY, int pos);

	int getState() const { return state; }
	bool getHasIcicle() const { return hasIcicle; }
	int getLastPlacedX() const { return lastPlacedX; }
	int getLastPlacedY() const { return lastPlacedY; }

	void Floor(int floorY);
	void DrawCollider(); // ◆ 디버그 박스 그리기
};