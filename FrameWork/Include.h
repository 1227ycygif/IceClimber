#pragma once

/* ---------------------------------------------------
///////////////// 프로그램 파일 //////////////////////

		라이브러리에 필요한 파일입니다.
		지우면 안돼요~~^^;

//////////////////////////////////////////////////////
-----------------------------------------------------*/

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dsound.lib")
//데이타 베이스//////
#include <winsock2.h>
#include <mysql.h>
#pragma comment(lib, "libmySQL.lib")
/////////////////////
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <iostream>
using namespace std;

#include <d3d9.h>
#include <d3dx9.h>
#include <dsound.h>
#include "DXUTsound.h"

#include <windows.h>
#include "Define.h"
#include "DeviceFont.h"
#include "Sprite.h"
#include "Chap.h"


/* ---------------------------------------------------
///////////////// 사용자 추가 파일 ///////////////////

		새로 클래스 만들 때 마다
		헤더파일을 추가해 주세요~

//////////////////////////////////////////////////////
-----------------------------------------------------*/
#include "Game.h"
#include "Logo.h"
#include "Menu.h"
#include "Over.h"
#include "CMng.h"
#include "Device.h"
#include <tchar.h>
//#include "Night.h"

#include "Data.h"

#include "Map.h"

#include "Collider.h"
#include "Monster.h"
#include "Block.h"
#include "Character.h"
#include "BlockManager.h"
#include "MapManager.h"

#include "Sound.h"


#include "GameManager.h"
// 데이타베이스////////////////
#include "mysql.h"

/* ---------------------------------------------------
///////////////// 사용자 추가 파일 ///////////////////

		키 입력 처리 함수입니다.

//////////////////////////////////////////////////////
-----------------------------------------------------*/

inline int KeyDown	( int vk ) 
{ 
	return ( (GetAsyncKeyState(vk) & 0x8000) ? 1:0 ); 
}

inline int KeyUp	( int vk ) 
{ 
	return ( (GetAsyncKeyState(vk) & 0x8000) ? 0:1 ); 
}