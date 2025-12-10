#ifndef __Over_H__
#define __Over_H__

class Over : public Chap
{
public:
	Over();
	~Over();

	Sprite background;
	Sprite p1;
	Sprite p2;
	/*Sprite win;
	Sprite lose;*/

	virtual void Init();
	virtual void Update(double frame);
	virtual void Draw();

	virtual void OnMessage(MSG* msg);
};

#endif