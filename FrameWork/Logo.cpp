#pragma once
#include "Include.h"

Logo::Logo()
{
}

Logo::~Logo()
{
}
// 로고 이미지 alpha값 255 -> 0 으로 바뀌면서 로비로 진입
void Logo::Init()
{
	//g_Mng.n_Chap = GAME; // ◆ 게임 화면 바로 시작
	alpha = 255;

	loadimg.Create("./resource/Img/logo/logo.png", false, D3DCOLOR_XRGB(0, 0, 0));

	//////데이터 베이스 사용시 
	//// mysql 구조체 변수 초기화
	mysql_init(&sql.conn);
	// ip, 접속 id , pass, 데이타 베이스명, 포트번호 등으로 접속
	sql.connection = mysql_real_connect(&sql.conn, DB_HOST,
		DB_USER, DB_PASS,
		DB_NAME, 3306,
		(char *)NULL, 0);
	// 접속에 실패 or 성공시 실행
	if (sql.connection == NULL)
	{
		sprintf_s(sql.state, "Mysql connection error : %s", mysql_error(&sql.conn));
		sql.mysql_Success = false;
	}
	else
	{
		sql.mysql_Success = true;
	}

}

void Logo::Update(double frame)
{
	Draw();

	alpha--;

	if (alpha <= 0) {
		g_Mng.n_Chap = MENU; // ◆ 주석처리하면 바로 게임으로 감
		g_Mng.chap[g_Mng.n_Chap]->Init();
		//g_Mng.n_Chap = GAME; // ◆ 주석처리하면 메뉴화면 나옴
		sound.m_Menubg->Play(0, DSBPLAY_LOOPING);
	}
}

void Logo::Draw()
{
	loadimg.SetColor(255, 255, 255, alpha);  // 색상 변경
	loadimg.Draw(0, 0);  // 이미지출력
}

void Logo::OnMessage(MSG* msg)
{
	switch (msg->message)
	{
	case WM_LBUTTONDOWN:
		MessageBox(NULL, "", "", 0);
		break;
	}

}