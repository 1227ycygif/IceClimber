#ifndef __Logo_H__
#define __Logo_H__

class Logo : public Chap
{
public:

	Logo();
	~Logo();

	HWND hWnd;
	Sprite loadimg;

	float alpha;

	virtual void Init();
	virtual void Update(double frame);
	virtual void Draw();
	virtual void OnMessage(MSG* msg);
};

#endif