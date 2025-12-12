#include "Include.h"

Collider coll;

Collider::Collider()
{

}

Collider::~Collider()
{

}

void Collider::Init()
{
	m_rc.left = 0;
	m_rc.top = 600;
	m_rc.right = 1250;
	m_rc.bottom = 720;
}

// 디버그 박스를 위한 업데이트 함수 
void Collider::Update(float x, float y, float width, float height)
{
	m_rc.left = static_cast<LONG>(x);
	m_rc.top = static_cast<LONG>(y);
	m_rc.right = static_cast<LONG>(x + width);
	m_rc.bottom = static_cast<LONG>(y + height);
}

// 바닥
void Collider::Draw()
{
	if (Gmanager.m_GameStart == true && Gmanager.m_bShowCollider)
	{
		dv_font.DrawString("┌ ", m_rc.left, m_rc.top, D3DCOLOR_ARGB(255, 0, 255, 0));
		dv_font.DrawString(" ┐", m_rc.right, m_rc.top, D3DCOLOR_ARGB(255, 0, 255, 0));
		dv_font.DrawString("└ ", m_rc.left, m_rc.bottom, D3DCOLOR_ARGB(255, 0, 255, 0));
		dv_font.DrawString(" ┘", m_rc.right, m_rc.bottom, D3DCOLOR_ARGB(255, 0, 255, 0));
	}
}

// 디버그 콜라이더 (x, y는 오프셋)
void Collider::BoxSow(RECT m_rc, long x, long y, D3DCOLOR color)
{
	if (Gmanager.m_GameStart == true /* && 디버그 일때 처리 */)
	{
		dv_font.DrawString("┌ ", m_rc.left, m_rc.top, color);
		dv_font.DrawString(" ┐", m_rc.right, m_rc.top, color);
		dv_font.DrawString("└ ", m_rc.left, m_rc.bottom, color);
		dv_font.DrawString(" ┘", m_rc.right, m_rc.bottom, color);
	}
}