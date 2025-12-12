#pragma once
#include "Include.h"

Map map;

/*
기능 :		생성자
*/
Map::Map()
{

}

/*
기능 :		소멸자
*/
Map::~Map()
{

}

/*
기능 :		초기화
매개변수 :	없음
반환 :		없음
특이사항 :	배경 스트라이프 연결
*/
void Map::Init()
{
	char FileName[256];
	sprintf_s(FileName, "./resource/Img/ice/background.png");
	background.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	
}

/*
기능 :		업데이트
매개변수 :	없음
반환 :		없음
특이사항 :	없음
*/
void Map::Update(double frame)
{

}

/*
기능 :		드로우
매개변수 :	몬스터 종류(아직 1종류밖에...), 맵 y좌표, 렌더링 스케일, 맵생성시 몬스터 생성여부
반환 :		없음
특이사항 :	각종 변수 초기화 및 스트라이프 이미지 연결
*/
void Map::Draw()
{
	background.Render(0, 0, 0, 1, 1);
}
