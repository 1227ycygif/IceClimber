#pragma once 
#include "Include.h" 

g_DeviceFont dv_font; 

g_DeviceFont::g_DeviceFont(void) 
{
} 

g_DeviceFont::~g_DeviceFont(void) 
{
} 

bool g_DeviceFont::Create( HWND g_hWnd ) 
{

	Direct3D = Direct3DCreate9( D3D_SDK_VERSION ); 

	ZeroMemory( &d3dpp, sizeof( d3dpp ) ); 
	d3dpp.Windowed = TRUE; 
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; 
	d3dpp.hDeviceWindow = g_hWnd; 
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8; 
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE ; 
	d3dpp.BackBufferWidth = SCREEN_WITH; 
	d3dpp.BackBufferHeight = SCREEN_HEIGHT; 

	Direct3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &Device9 ); 



	D3DXCreateSprite( Device9 , &Sprite ); 

	ZeroMemory( &fdesc , sizeof(fdesc) ); 
	fdesc.Height = 40; 
	fdesc.Width = 22; 
	fdesc.Weight = 2000; 
	fdesc.Italic = FALSE; 
	fdesc.CharSet = DEFAULT_CHARSET; 
	strcpy( fdesc.FaceName , "µ¸¿ò" ); 

	D3DXCreateFontIndirect( Device9 , &fdesc , &Fonts ); 

	return true;

} 

bool g_DeviceFont::DrawString( const char* msg , int x , int y , D3DCOLOR color) 
{
	RECT rect = { x , y , fdesc.Width*strlen(msg) , fdesc.Height }; 

	Sprite->Begin( D3DXSPRITE_ALPHABLEND ); 
	//Fonts->DrawText( Sprite , msg , strlen( msg ) , &rect , DT_NOCLIP , D3DCOLOR_XRGB(250,250,250) ) ;
	Fonts->DrawText( Sprite , msg , strlen( msg ) , &rect , DT_NOCLIP , color ); 
	Sprite->End(); 
	
	return true; 
} 