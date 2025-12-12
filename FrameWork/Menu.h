#ifndef __Menu_H__
#define __Menu_H__

class Menu : public Chap
{
	Sprite menuimg;

public:

	Menu();
	~Menu();

	// 스프라이트 카운트
	int count;			
	// 알파벳 이미지 인덱스
	int index;			
	// 이니셜 카운트
	int cnt;			
	// 메뉴 창
	bool Mwind;			
	// 메뉴 창 메뉴 선택
	bool select;		
	// 랭킹 창
	bool Rwind;			 
	// 1p 이니셜 설정 창 on/off
	bool nameset1;		
	// 2p 이니셜 설정 창 on/off
	bool nameset2;		
	
	// 캐릭터 이미지 출력 위한 변수
	bool center;
	int cen;
	bool left;
	bool right;
	bool center2;
	int cen2;
	bool left2;
	bool right2;
	int cha1X = 450, cha2X = 550;

	Sprite background;
	Sprite mback;
	Sprite rback;
	Sprite hammer[2];
	Sprite nameback;
	Sprite alp[29];
	Sprite charac1;
	Sprite charac2;
	Sprite charac1run[2];
	Sprite charac2run[2];

	//동시 키 입력 위해
	DWORD KeyTime;
	DWORD KeyTime2;
	DWORD KeyTime3;
	DWORD KeyTime4;

	DWORD HamTime;

	virtual void Init();
	virtual void Update(double frame);
	virtual void Draw();
	virtual void OnMessage(MSG* msg);
};

#endif