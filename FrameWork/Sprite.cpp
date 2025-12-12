#pragma once
#include "Include.h"

Sprite g_Load;

Sprite::Sprite(void)
{

}

Sprite::~Sprite(void)
{

}
bool Sprite::Create(const char* filename, bool bUseTransparency, D3DCOLOR TransparencyColor)
{
	D3DXGetImageInfoFromFile(filename, &imagesinfo);

	color = D3DCOLOR_ARGB( 255, 255, 255, 255 ) ;

	HRESULT hr = E_FAIL ;

	D3DCOLOR transparencycolor;
	if (bUseTransparency)
	{
		transparencycolor = TransparencyColor | 0xff000000;
	}
	else
	{
		transparencycolor = 0;
	}
	hr = D3DXCreateTextureFromFileEx(dv_font.Device9 ,
		filename , imagesinfo.Width , imagesinfo.Height , 1 , 0 , 	D3DFMT_UNKNOWN , D3DPOOL_MANAGED,
		D3DX_DEFAULT, 	D3DX_DEFAULT, transparencycolor,	&imagesinfo , 	NULL, 	&Texture ) ; 

	return TRUE;
}

// 화면의 x, y 에 출력해라.
void Sprite::Draw(float x, float y)		
{
	D3DXVECTOR3 pos;
	pos.x = x;
	pos.y = y;
	pos.z = 1.0f;

	dv_font.Sprite->Begin( D3DXSPRITE_ALPHABLEND ) ;
	dv_font.Sprite->Draw( Texture ,NULL ,	NULL , &pos , color ) ;
	dv_font.Sprite->End() ;
}

// 회전, 확대 출력
// sx -1 : 좌우 반전, sy -1 = 상하 반전
// sx 0 : 없어짐, 1 : 그대로, 2 : x축으로 2배 확대
void Sprite::Render( float x , float y , float radian, float sx, float sy) 
{																	   
	RECT Rect ;														   
	ID3DXSprite* pSprite ;

	pSprite = dv_font.Sprite ;

	Rect.left   = 0 ;
	Rect.top    = 0 ;
	Rect.right  = Rect.left + imagesinfo.Width ;
	Rect.bottom = Rect.top  + imagesinfo.Height ;

	D3DXMATRIX rot , trans, scale ;
	D3DXMatrixScaling(&scale , sx ,sy ,1) ;
	D3DXMatrixRotationZ( &rot , radian ) ;
	D3DXMatrixTranslation( &trans , x , y , 1.0f ) ;
	//pSprite->SetTransform( &( scale * rot * trans ) ) ;
	D3DXMATRIX matWorld = scale * rot * trans;
	pSprite->SetTransform(&matWorld);


	dv_font.Sprite->Begin(D3DXSPRITE_ALPHABLEND) ;
	pSprite->Draw( Texture , &Rect, NULL, NULL , 0xFFFFFFFF ) ;
	pSprite->Flush() ;
	dv_font.Sprite->End() ;

	D3DXMATRIX identity ;
	D3DXMatrixIdentity( &identity ) ;
	pSprite->SetTransform( &identity ) ;
}

void Sprite::SetColor( int r, int g , int b , int a )
{
	color = D3DCOLOR_ARGB( a, r, g, b ) ;
}