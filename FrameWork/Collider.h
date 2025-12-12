#pragma once
#include "Include.h"

class Collider
{
	RECT m_rc;

public:

	Collider();
	~Collider();

	// 디버그 박스 
	const RECT& GetRect() const { return m_rc; } 

	void Init();
	void Update(float x, float y, float width, float height); 
	void Draw();
	void BoxSow(RECT m_rc, long x, long y, D3DCOLOR color = D3DCOLOR_ARGB(255, 0, 255, 0));
};

extern Collider coll;