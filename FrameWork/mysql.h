#pragma once
#include "Include.h"

struct Rank
{
	char first[10];
	char middle[10];
	char last[10];
	char score[10];

	char first2[10];
	char middle2[10];
	char last2[10];
	char score2[10];
};

class Mysql
{

public:
	Mysql();
	~Mysql();

	// MYSQL 구조체 변수 (Logo 챕터에서 1 단계 테스트 접속 확인을 위함...)
	MYSQL mysql;

	// MYSQL 연결 및 구동 변수
	MYSQL		*connection = NULL, conn;
	MYSQL_RES	*sql_result;
	MYSQL_ROW	sql_row;
	int query_start;

	// 데이타 베이스 칼럼 저장 변수
	char first[10];
	char middle[10];
	char last[10];
	char score[200];

	char first2[10];
	char middle2[10];
	char last2[10];
	char score2[200];

	
	char query[255];

	 //MYSQL 상태 변수
	char state[256];
	bool mysql_Success;

	// MYSQL 결과 확인 변수
	Rank ranking[8];

	void Init();
	void Update(double frame);
	void Draw();
	void save();
};

extern Mysql sql;