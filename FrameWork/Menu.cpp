#pragma once

#include "Include.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::Init()
{
	//////데이터 베이스 사용시
	//// mysql 구조체 변수 초기화
	mysql_init(&sql.conn);
	// ip, 접속 id , pass, 데이타 베이스명, 포트번호 등으로 접속
	sql.connection = mysql_real_connect(&sql.conn, DB_HOST,
		DB_USER, DB_PASS,
		DB_NAME, 3306,
		(char *)NULL, 0);

	// 로비화면에 필요한 이미지들
	char FileName[256];
	sprintf_s(FileName, "./resource/Img/town/bg_town.png");
	background.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/UI/bubble_bg.png");
	mback.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));			// 메뉴창
	for (int i = 0; i < 2; i++) {
		sprintf_s(FileName, "./resource/Img/UI/hammer_%d.png", i + 1);
		hammer[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));	// 메뉴선택 망치이미지
	}
	sprintf_s(FileName, "./resource/Img/UI/ranking_.png");
	rback.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));			// 랭킹창

	sprintf_s(FileName, "./resource/Img/UI/name_bg.png");
	nameback.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));		// 이름 생성창
	for (int i = 0; i < 29; i++) {
		sprintf_s(FileName, "./resource/Img/alp/ranking_%02d.png",i+1);
		alp[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));		//알파벳 이미지
	}

	// 로비에서 캐릭터 이미지
	sprintf_s(FileName, "./resource/Img/char/1player_stand1.png");
	charac1.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	for (int i = 0; i < 2; i++) {
		sprintf_s(FileName, "./resource/Img/char/1player_run%d.png", i + 1);
		charac1run[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	sprintf_s(FileName, "./resource/Img/char/2player_stand1.png");
	charac2.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	for (int i = 0; i < 2; i++) {
		sprintf_s(FileName, "./resource/Img/char/2player_run%d.png", i + 1);
		charac2run[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
}

void Menu::Update(double frame)
{
	// 메뉴선택 망치 스프라이트
	if (GetTickCount() - HamTime > 250) {
		count++;
		if (count > 1) {
			count = 0;
		}
		HamTime = GetTickCount();
	}
	// 두 캐릭터가 왼쪽 끝으로 가면 게임시작, 이름 생성했는지도 확인
	if (cha1X < 10 && cha2X < 10
			&& playdata.namecheck1 == true && playdata.namecheck2 == true) {

		sound.m_Menubg->Reset();
		sound.m_Menubg->Stop();
		playdata.Reset();
		g_Mng.n_Chap = GAME;
		g_Mng.chap[g_Mng.n_Chap]->Init();
		sound.m_Bk1->Play(0, DSBPLAY_LOOPING);
		sound.m_Gamebg->Play(0, DSBPLAY_LOOPING);
	}
}

void Menu::Draw()
{
	background.Render(0, 0, 0, 1, 1); //이미지출력
	dv_font.DrawString("1P : 방향_W,A,S,D/ 점프_W/ 공격_S/ 선택_SPACE", 0, 0);
	dv_font.DrawString("2P : 방향_방향키/ 점프_↑/ 공격_↓/ 선택_ENTER", 0, 50);
	// 1player 좌우이동
	if (KeyDown('A') && !nameset2 && !Mwind && !Rwind) {
		if (GetTickCount() - KeyTime > 10) {
			left = true;
			right = false;
			center = false;
			cen = 1;
			cha1X <= -10? cha1X = -10: cha1X -= 4;
			KeyTime = GetTickCount();
		}
	}
	if (KeyUp('A') && !nameset2 && !Mwind && !Rwind) {
		left = false;
		center = true;
	}
	if (left == true) {
		charac1run[count].Render(cha1X, 535, 0, 1, 1);
	}
	if (KeyDown('D') && !nameset2 && !Mwind && !Rwind) {
		if (GetTickCount() - KeyTime > 10) {
			left = false;
			right = true;
			center = false;
			cen = 0;
			cha1X >= 1180? cha1X = 1180 : cha1X += 4;
			KeyTime = GetTickCount();
		}
	}
	if (KeyUp('D') && !nameset2 && !Mwind && !Rwind) {
		right = false;
		center = true;
	}
	if (right == true) {
		charac1run[count].Render(cha1X + 118, 535, 0, -1, 1);
	}
	if (center == true && !KeyDown('A') && !KeyDown('D')) {
		cen == 1 ? charac1.Render(cha1X, 535, 0, 1, 1): charac1.Render(cha1X+118, 535, 0, -1, 1);
	}
	// 2player 좌우이동
	if (KeyDown(VK_LEFT) && !nameset1 && !Mwind && !Rwind) {
		if (GetTickCount() - KeyTime2 > 10) {
			left2 = true;
			right2 = false;
			center2 = false;
			cen2 = 1;
			cha2X <= -10? cha2X = -10 : cha2X -= 4;
			KeyTime2 = GetTickCount();
		}
	}
	if (KeyUp(VK_LEFT) && !nameset1 && !Mwind && !Rwind) {
		left2 = false;
		center2 = true;
	}
	if (left2 == true) {
		charac2run[count].Render(cha2X, 535, 0, 1, 1);
	}
	if (KeyDown(VK_RIGHT) && !nameset1 && !Mwind && !Rwind) {
		if (GetTickCount() - KeyTime2 > 10) {
			left2 = false;
			right2 = true;
			center2 = false;
			cen2 = 0;
			cha2X >= 1180? cha2X = 1180 : cha2X += 4;
			KeyTime2 = GetTickCount();
		}
	}
	if (KeyUp(VK_RIGHT) && !nameset1 && !Mwind && !Rwind) {
		right2 = false;
		center2 = true;
	}
	if (right2 == true) {
		charac2run[count].Render(cha2X + 118, 535, 0, -1, 1);
	}
	if (center2 == true && !KeyDown(VK_LEFT) && !KeyDown(VK_RIGHT)) {
		cen2 == 1 ? charac2.Render(cha2X, 535, 0, 1, 1) : charac2.Render(cha2X + 118, 535, 0, -1, 1);
	}

	//npc 근처에서 말걸기 1p
	if (cha1X > 100 && cha1X < 200) {
		if (!nameset1 && !nameset2 && !Mwind && !Rwind) {
			dv_font.DrawString("Press C", cha1X + 90, 540);
		}
		if (KeyDown('C') && !nameset1 && !nameset2
			&& !Mwind && !Rwind) {
			sound.Select3->Play(0, NULL);
			Mwind = true;
			select = true;
		}
		if (Mwind == true) {
			mback.Render(240, 200, 0, 1, 1);
			select == true ? hammer[count].Render(290, 295, 0, 1, 1) : hammer[count].Render(295, 415, 0, 1, 1);
			if (KeyDown('W') || KeyDown('S')) {
				if (GetTickCount() - KeyTime3 > 200) {
					sound.Select->Play(0, NULL);
					select == true ? select = false : select = true;
					KeyTime3 = GetTickCount();
				}
			}
			if (KeyDown(VK_SPACE) && select == true) {
				if (GetTickCount() - KeyTime3 > 300) {
					sound.Select2->Play(0, NULL);
					nameset1 = true;				// 1p 이름생성
					KeyTime3 = GetTickCount();
				}
				Mwind = false;
			}
			else if (KeyDown(VK_SPACE) && select == false) {
				if (GetTickCount() - KeyTime3 > 200) {
					sound.Select2->Play(0, NULL);
					Rwind = true;					// 랭킹확인
					KeyTime3 = GetTickCount();
				}
				Mwind = false;
			}
		}
	}
	//npc 근처에서 말걸기 2p
	if (cha2X > 100 && cha2X < 200) {
		if (!nameset1 && !nameset2 && !Mwind && !Rwind) {
			dv_font.DrawString("Press SHIFT", cha2X + 90, 540);
		}
		if (KeyDown(VK_SHIFT) && !nameset1 && !nameset2
			&& !Mwind && !Rwind) {
			sound.Select3->Play(0, NULL);
			Mwind = true;
			select = true;
		}
		if (Mwind == true) {
			mback.Render(240, 200, 0, 1, 1);
			select == true ? hammer[count].Render(290, 295, 0, 1, 1) : hammer[count].Render(295, 415, 0, 1, 1);
			if (KeyDown(VK_UP) || KeyDown(VK_DOWN)) {
				if (GetTickCount() - KeyTime4 > 200) {
					sound.Select->Play(0, NULL);
					select == true ? select = false : select = true;
					KeyTime4 = GetTickCount();
				}
			}
			if (KeyDown(VK_RETURN) && select == true) {
				if (GetTickCount() - KeyTime4 > 200) {
					sound.Select2->Play(0, NULL);
					nameset2 = true;				// 2p 이름생성
					KeyTime4 = GetTickCount();
				}
				Mwind = false;
			}
			else if (KeyDown(VK_RETURN) && select == false) {
				if (GetTickCount() - KeyTime4 > 200) {
					sound.Select2->Play(0, NULL);
					Rwind = true;					// 랭킹확인
					KeyTime4 = GetTickCount();
				}
				Mwind = false;
			}
		}
	}

	//1p name
	if (nameset1 == true) {
		int x = 370;
		nameback.Render(240, 200, 0, 1, 1);
		if (cnt == 0) {									//첫번째 이니셜
			alp[index].Render(x, 370, 0, 1, 1);
		}
		else if (cnt == 1) {								//두번째 이니셜
			alp[playdata.p1_name[0]].Render(x, 370, 0, 1, 1);
			alp[index].Render(x + 80, 370, 0, 1, 1);
		}
		else if (cnt == 2) {									//세번째 이니셜
			alp[playdata.p1_name[0]].Render(x, 370, 0, 1, 1);
			alp[playdata.p1_name[1]].Render(x + 80, 370, 0, 1, 1);
			alp[index].Render(x + 160, 370, 0, 1, 1);
		}
		else if (cnt == 3 ) {									//전체 확인
			alp[playdata.p1_name[0]].Render(x, 370, 0, 1, 1);
			alp[playdata.p1_name[1]].Render(x + 80, 370, 0, 1, 1);
			alp[playdata.p1_name[2]].Render(x + 160, 370, 0, 1, 1);
		}
		if (KeyDown('W')) {		//이니셜 설정 오름차순 이동
			if (GetTickCount() - KeyTime > 200)	{
				index < 28 ? index++ : index = 0;
				KeyTime = GetTickCount();
			}
		}
		if (KeyDown('S')) {		//이니셜 설정 내림차순 이동
			if (GetTickCount() - KeyTime > 200) {
				index > 0 ? index-- : index = 28;
				KeyTime = GetTickCount();
			}
		}
		if (KeyDown(VK_SPACE)) {	// 이니셜 결정
			if (GetTickCount() - KeyTime3 > 200) {
				if (index == 28) {
					cnt <= 1 ? (cnt == 0 ? (playdata.p1_name[cnt] = 26, playdata.p1_name[cnt+1] = 26, cnt = 2)
							: (playdata.p1_name[cnt] = 26, cnt = 2 )): cnt = 2;
					index = 26;
				}
				else if (index == 27) {
					index = playdata.p1_name[cnt-2];
					cnt -= 2;
				}
				playdata.p1_name[cnt] = index;
				cnt < 3 ? cnt++ : (sound.Select3->Play(0, NULL),nameset1 = false,cnt = 0,playdata.namecheck1 = true);
				index = 0;
				KeyTime3 = GetTickCount();
			}
		}
	}
	//2p name
	if (nameset2 == true) {
		int x = 370;
		nameback.Render(240, 200, 0, 1, 1);
		if (cnt == 0) {
			alp[index].Render(x, 370, 0, 1, 1);
		}
		else if (cnt == 1) {
			alp[playdata.p2_name[0]].Render(x, 370, 0, 1, 1);
			alp[index].Render(x + 80, 370, 0, 1, 1);
		}
		else if (cnt == 2) {
			alp[playdata.p2_name[0]].Render(x, 370, 0, 1, 1);
			alp[playdata.p2_name[1]].Render(x + 80, 370, 0, 1, 1);
			alp[index].Render(x + 160, 370, 0, 1, 1);
		}
		else if (cnt == 3) {
			alp[playdata.p2_name[0]].Render(x, 370, 0, 1, 1);
			alp[playdata.p2_name[1]].Render(x + 80, 370, 0, 1, 1);
			alp[playdata.p2_name[2]].Render(x + 160, 370, 0, 1, 1);
		}
		if (KeyDown(VK_UP)) {
			if (GetTickCount() - KeyTime > 200) {
				index < 28 ? index++ : index = 0;
				KeyTime = GetTickCount();
			}
		}
		if (KeyDown(VK_DOWN)) {
			if (GetTickCount() - KeyTime > 200) {
				index > 0 ? index-- : index = 28;
				KeyTime = GetTickCount();
			}
		}
		if (KeyDown(VK_RETURN)) {
			if (GetTickCount() - KeyTime4 > 200) {
				if (index == 28) {
					cnt <= 1 ? (cnt == 0 ? (playdata.p2_name[cnt] = 26, playdata.p2_name[cnt + 1] = 26, cnt = 2)
						: (playdata.p2_name[cnt] = 26, cnt = 2)) : cnt = 2;
					index = 26;
				}
				else if (index == 27) {
					index = playdata.p2_name[cnt - 2];
					cnt -= 2;
				}
				playdata.p2_name[cnt] = index;
				cnt < 3 ? cnt++ : (sound.Select3->Play(0, NULL),nameset2 = false, cnt = 0,playdata.namecheck2 = true);
				index = 0;
				KeyTime4 = GetTickCount();
			}
		}
	}

	//// 랭킹 확인 
	int count1 = 0;
	if (Rwind == true){
		rback.Render(150, 20, 0, 1, 1);
		////// 데이터 베이스 사용시
		//// score기준 내림차순 정렬로 불러오기
		sql.query_start = mysql_query(sql.connection, "select * from rank order by score desc");
		sql.sql_result = mysql_store_result(sql.connection);
		while ((sql.sql_row = mysql_fetch_row(sql.sql_result)) != NULL)
		{
			// sql.sql_row[0] 인덱스로 해당 칼럼(열,필드)값 가져옴
				sprintf_s(sql.ranking[count1].first, 10, "%s", sql.sql_row[0]);
				sprintf_s(sql.ranking[count1].middle, 10, "%s", sql.sql_row[1]);
				sprintf_s(sql.ranking[count1].last, 10, "%s", sql.sql_row[2]);
				sprintf_s(sql.ranking[count1].score, 10, "%s", sql.sql_row[3]);

				sprintf_s(sql.ranking[count1].first2, 10, "%s", sql.sql_row[4]);
				sprintf_s(sql.ranking[count1].middle2, 10, "%s", sql.sql_row[5]);
				sprintf_s(sql.ranking[count1].last2, 10, "%s", sql.sql_row[6]);
				sprintf_s(sql.ranking[count1].score2, 10, "%s", sql.sql_row[7]);

			
			// 레코드 수만큼 증가 
			count1++;
			if (count1 == 8) {
				break;
			}
		}
		// sql.sql_result 값 해제
		mysql_free_result(sql.sql_result);
		int first;
		int middle;
		int last;

		int first2;
		int middle2;
		int last2;

		for (int i = 0; i < count1; i++) {
			first = atoi(sql.ranking[i].first);
			middle = atoi(sql.ranking[i].middle);
			last = atoi(sql.ranking[i].last);

			first2 = atoi(sql.ranking[i].first2);
			middle2 = atoi(sql.ranking[i].middle2);
			last2 = atoi(sql.ranking[i].last2);

			// 랭킹 문자열
			alp[first].Render(350, 210 + (i * 85), 0, 1, 1);
			alp[middle].Render(400, 210 + (i * 85), 0, 1, 1);
			alp[last].Render(450, 210 + (i * 85), 0, 1, 1);
			dv_font.DrawString(sql.ranking[i].score, 520, 220 + (i * 85));

			alp[first2].Render(700, 210 + (i * 85), 0, 1, 1); 
			alp[middle2].Render(750, 210 + (i * 85), 0, 1, 1);
			alp[last2].Render(800, 210 + (i * 85), 0, 1, 1);
			dv_font.DrawString(sql.ranking[i].score2, 870, 220 + (i * 85));

		}

		// 랭킹창 종료
		if (KeyDown(VK_SPACE)) {
			if (GetTickCount() - KeyTime3 > 200) {
				sound.Select3->Play(0, NULL);
				Rwind = false;
				KeyTime3 = GetTickCount();
			}
		}
		if(KeyDown(VK_RETURN)){
			if (GetTickCount() - KeyTime4 > 200) {
				sound.Select3->Play(0, NULL);
				Rwind = false;
				KeyTime4 = GetTickCount();
			}
		}
	}
}

void Menu::OnMessage(MSG* msg)
{

}