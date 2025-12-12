#include "Include.h"
#include "mysql.h"
#define _CRT_NONSTDC_NO_DEPRECATE 
Mysql sql;

Mysql::Mysql()
{
}

Mysql::~Mysql()
{
}

void Mysql::Init()
{
}

void Mysql::Update(double frame)
{
}

void Mysql::Draw()
{
	// 데이타 베이스 처리 상태 표시
	if (sql.mysql_Success)
	{
		dv_font.DrawString("Success", 550, 0);
	}
	else
	{
		dv_font.DrawString("Error", 500, 0);
		dv_font.DrawString(sql.state, 700, 0);
	}
}

void Mysql::save()
{
	// 테이블 저장 값 입력
	sprintf_s(first, "%d", playdata.p1_name[0]);
	sprintf_s(middle, "%d", playdata.p1_name[1]);
	sprintf_s(last, "%d", playdata.p1_name[2]);
	sprintf_s(score, "%d", playdata.p1_total_score);

	sprintf_s(first2, "%d", playdata.p2_name[0]);
	sprintf_s(middle2, "%d", playdata.p2_name[1]);
	sprintf_s(last2, "%d", playdata.p2_name[2]);
	sprintf_s(score2, "%d", playdata.p2_total_score);

	// 전달 할 쿼리값 셋팅
	sprintf_s(query, "insert into rank values "
		"('%s','%s','%s','%s','%s','%s','%s','%s')", 
		first, middle, last, score, first2, middle2, last2, score2);

	// ◆ 원래 초기에 작성했던 코드처럼 변수만 추가해서 쿼리값을 전달하게 되면, 
	//    한 번에 8개의 컬럼이 들어가는 게 아니라 쿼리문이 두 번 실행되면서 4개씩만 들어가게 됨
	//    4개 보내고 또 4개 보내고. 
	//    첫 저장에 1p 것이 들어가고 두 번째 저장에 2p 것이 같은 위치에 들어감
	//    1p 값 사라짐 2p도 테이블에 존재하지 않음 
	// ★ insert 문이 8 컬럼에 맞춰 1번 실행되어야 함
	// ★ 실제 출력 때는 8개를 한 번에 읽으려 함 → DB 구조와 코드가 불일치 (4 ≠ 8) 

	// 다음 mysql_query() 함수로 MYSQL 구조체를 통한 쿼리문 전송
	query_start = mysql_query(connection, query);

	//// 테이블 저장 값 입력
	//sprintf_s(first, "%d", playdata.p2_name[0]);
	//sprintf_s(middle, "%d", playdata.p2_name[1]);
	//sprintf_s(last, "%d", playdata.p2_name[2]);
	//sprintf_s(score, "%d", playdata.p2_total_score);

	//// 전달 할 쿼리값 셋팅
	//sprintf_s(query, "insert into rank values "
	//	"('%s','%s','%s','%s')", first2, middle2, last2, score2);

	//// 다음 mysql_query() 함수로 MYSQL 구조체를 통한 쿼리문 전송
	//query_start = mysql_query(connection, query);

	// 전송 실패시
	if (query_start != 0) 
	{
		sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
		sql.mysql_Success = false;
	}
	// 성공 시
	else 
	{
		mysql_Success = true;
	}
}

// ◆ 데이터베이스 연동 Query
// create database ICE; 데이터베이스 아이스를 만들어요 
// use ICE; 아이스를 사용해요 
// create table login ( id varchar(10), pw varchar(10)); 테이블 로그인을 만들어요 
// 
// create table rank( 테이블 랭크를 만들어요, 내용물은 이렇게 구성해요
//   first varchar(10),
//   middle varchar(10),
//   last varchar(10),
//   score int(11)
// ); 
//
// desc rank; 테이블 안 내용물을 보여주세요 
// select * from rank; 랭크에서 모든 걸 선택 
//
// truncate table rank; 테이블 랭크를 초기화