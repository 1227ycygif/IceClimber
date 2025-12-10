#ifndef __Menu_H__
#define __Menu_H__

class Menu : public Chap
{
	Sprite menuimg;

public:
	Menu();
	~Menu();
	int count;			//스프라이트 카운트
	int index;			//알파벳 이미지 인덱스
	int cnt;			//이니셜 카운트
	bool Mwind;			//메뉴창
	bool select;		//메뉴창 메뉴선택
	bool Rwind;			//랭킹창 
	bool nameset1;		//1p 이니셜 설정창 on/off
	bool nameset2;		//2p 이니셜 설정창 on/off
	
	//캐릭터 이미지 출력 위한 변수
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

	//동시키 입력위해
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