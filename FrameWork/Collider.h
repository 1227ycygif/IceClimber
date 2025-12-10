#pragma once
#include "Include.h"

class Collider
{
	RECT m_rc;

public:
	Collider();
	~Collider();

	//RECT m_rc;
	const RECT& GetRect() const { return m_rc; } // ◆ 디버그 박스 자동 그리기

	void Init();
	void Update(float x, float y, float width, float height); // ◆
	void Draw();

	void BoxSow(RECT m_rc, long x, long y, D3DCOLOR color = D3DCOLOR_ARGB(255, 0, 255, 0));

};

extern Collider coll;