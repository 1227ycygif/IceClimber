#pragma once
/*
용도 :		게임 내 데이타 관리 클래스
맴버 변수 :	플레이어1 이름
			플레이어1 seal 갯수
			플레이어1 block 갯수
			플레이어1 total 점수
			플레이어1 이름 생성확인

			플레이어2 이름
			플레이어2 seal 갯수
			플레이어2 block 갯수
			플레이어2 total 점수
			플레이어2 이름 생성확인

			승리 플레이어

맴버 함수 :	생성자
			소멸자

			게임 데이터 초기화
*/
class Data
{
private:

public:
	char p1_name[3];
	int p1_seal_count;
	int p1_block_count;
	int p1_total_score;
	bool namecheck1 = false;

	char p2_name[3];
	int p2_seal_count;
	int p2_block_count;
	int p2_total_score;
	bool namecheck2 = false;

	int winner;

	Data();
	~Data();

	void Reset();
};

extern Data playdata;