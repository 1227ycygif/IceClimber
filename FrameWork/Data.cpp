#pragma once
#include"Include.h"

Data playdata;
/*
기능 :		생성자
특이사항 :	각 변수 초기화
*/
Data::Data()
{
	winner = 0;

	p1_name[0] = 'A';
	p1_name[1] = 'A';
	p1_name[2] = 'A';
	p1_seal_count = 0;
	p1_block_count = 0;
	p1_total_score = 0;

	p2_name[0] = 'A';
	p2_name[1] = 'A';
	p2_name[2] = 'A';
	p2_seal_count = 0;
	p2_block_count = 0;
	p2_total_score = 0;
}
/*
기능 :		소멸자
*/
Data::~Data()
{
}
/*
기능 :		게임 데이타 리셋
매개변수 :	없음
반환 :		없음
특이사항 :	승리 플레이어 및 각플레이어 카운트 초기화
*/
void Data::Reset()
{
	winner = 0;

	p1_seal_count = 0;
	p1_block_count = 0;
	p1_total_score = 0;

	p2_seal_count = 0;
	p2_block_count = 0;
	p2_total_score = 0;
}
