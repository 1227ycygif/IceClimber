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
	//승패
	sprintf_s(FileName, "./resource/Img/over/win_tex.png");
	/*win.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(FileName, "./resource/Img/over/loss_tex.png");
	lose.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));*/
}

//// ◆ 여기를 주석처리하면 로비화면 안 나옴
//void Over::Update(double frame)
//{
//	// ◆ 메뉴화면 복귀
//	if (KeyDown('M'))
//	{
//		sql.save();
//		g_Mng.n_Chap = MENU;
//		sound.m_overbg->Reset();
//		sound.m_overbg->Stop();
//		sound.m_Menubg->Play(0, DSBPLAY_LOOPING);
//		g_Mng.chap[g_Mng.n_Chap]->Init();
//		playdata.namecheck1 = false;
//		playdata.namecheck2 = false;
//	}
//	//// ◆ 게임 저장, 재시작..
//	//if (KeyDown('R'))
//	//{
//	//	sql.save();
//	//	g_Mng.n_Chap = GAME;
//	//	sound.m_overbg->Reset();
//	//	sound.m_overbg->Stop();
//	//	sound.m_Menubg->Play(0, DSBPLAY_LOOPING);
//	//	g_Mng.chap[g_Mng.n_Chap]->Init();
//	//	playdata.namecheck1 = false;
//	//	playdata.namecheck2 = false;
//	//}
//}

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
	//dv_font.DrawString("Press 'M' : Back to Menu", 0, 45);
	p1.Render(200, 170, 0, 1, 1);
	p2.Render(700, 170, 0, 1, 1);
	char aa[200];
	//int bonus = 3000;
	// total 점수 계산
	playdata.p1_total_score = (playdata.p1_seal_count * 500) + (playdata.p1_block_count * 10);
	playdata.p2_total_score = (playdata.p2_seal_count * 500) + (playdata.p2_block_count * 10);

	/*playdata.p1_total_score = (playdata.p1_block_count * 10) + (playdata.p1_seal_count * 500);
	playdata.p2_total_score = (playdata.p2_block_count * 10) + (playdata.p2_seal_count * 500);*/

	////승리시 추가 보너스
	//if (playdata.winner == 1) {
	//	playdata.p1_total_score += bonus;
	//	sprintf_s(aa, "%d", bonus);
	//	dv_font.DrawString(aa, 400, 540);
	//	win.Render(330, 70, 0, 1.6, 1.6);
	//	lose.Render(832, 83, 0, 1.1, 1.1);
	//}
	//else if (playdata.winner == 2) {
	//	playdata.p2_total_score += bonus;
	//	sprintf_s(aa, "%d",bonus);
	//	dv_font.DrawString(aa, 900, 540);
	//	win.Render(830, 70, 0, 1.6, 1.6);
	//	lose.Render(332, 83, 0, 1.1, 1.1);
	//}
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

	/*sprintf_s(aa, "%d", playdata.p1_block_count);
	dv_font.DrawString(aa, 465, 341);
	sprintf_s(aa, "%d", playdata.p1_seal_count);
	dv_font.DrawString(aa, 465, 435);
	sprintf_s(aa, "%d", playdata.p1_total_score);
	dv_font.DrawString(aa, 400, 618);

	sprintf_s(aa, "%d", playdata.p2_block_count);
	dv_font.DrawString(aa, 965, 341);
	sprintf_s(aa, "%d", playdata.p2_seal_count);
	dv_font.DrawString(aa, 965, 435);
	sprintf_s(aa, "%d", playdata.p2_total_score);
	dv_font.DrawString(aa, 900, 618);*/
}

void Over::OnMessage(MSG* msg)
{

}