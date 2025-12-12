#pragma once
#include "Include.h"
/*
용도 :		게임 배경을 그려주는 클래스
맴버 변수 :	게임 배경 스트라이프

맴버 함수 :	생성자
			소멸자

			초기화
			업데이트
			드로우
*/
class Map
{

public :

	Map();
	~Map();

	Sprite background;

	void Init();
	void Update(double frame);
	void Draw();
};

extern Map map;