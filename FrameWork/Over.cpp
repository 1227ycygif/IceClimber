#pragma once
#include "Include.h"

Over::Over()
{
}

Over::~Over()
{
}

void Over::Init()
{
	char FileName[256];
	sprintf_s(FileName, "./resource/Img/over/Score_B.png");
	background.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	// 1p, 2p 점수창
	sprintf_s(FileName, "./resource/Img/over/Score_1P.png");
	p1.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(FileName, "./resource/Img/over/Score_2P.png");
	p2.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}

// ◆ 재시작 시 메뉴화면으로 안 나감
void Over::Update(double frame)
{
	// 저장, 재시작..
	if (KeyDown('A'))
	{
		sql.save();
		g_Mng.n_Chap = MENU;
		sound.m_overbg->Reset();
		sound.m_overbg->Stop();
		sound.m_Menubg->Play(0, DSBPLAY_LOOPING);
		g_Mng.chap[g_Mng.n_Chap]->Init();
		playdata.namecheck1 = false;
		playdata.namecheck2 = false;
	}
}

void Over::Draw()
{
	background.Render(0, 0, 0, 1, 1);
	dv_font.DrawString("Press 'A' : Save and Restart", 0, 0);
	p1.Render(200, 170, 0, 1, 1);
	p2.Render(700, 170, 0, 1, 1);
	char aa[200];

	// total 점수 계산
	playdata.p1_total_score = (playdata.p1_seal_count * 500) + (playdata.p1_block_count * 10);
	playdata.p2_total_score = (playdata.p2_seal_count * 500) + (playdata.p2_block_count * 10);
	
	// 점수 출력
	sprintf_s(aa, "%d", playdata.p1_seal_count);
	dv_font.DrawString(aa, 480, 355);
	sprintf_s(aa, "%d", playdata.p1_block_count);
	dv_font.DrawString(aa, 480, 430);
	sprintf_s(aa, "%d", playdata.p1_total_score);
	dv_font.DrawString(aa, 275, 583);

	sprintf_s(aa, "%d", playdata.p2_seal_count);
	dv_font.DrawString(aa, 980, 355);
	sprintf_s(aa, "%d", playdata.p2_block_count);
	dv_font.DrawString(aa, 980, 430);
	sprintf_s(aa, "%d", playdata.p2_total_score);
	dv_font.DrawString(aa, 775, 583);

}

void Over::OnMessage(MSG* msg)
{

}