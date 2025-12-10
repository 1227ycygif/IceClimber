/*

□ Chap 클래스 □
Game Chapter, Scene, Condition 공통 인터페이스

각 챕터별 동작(타이틀, 인게임, 게임오버 등)을 상속 받아 개별적으로 구현하게 만들어준다 

상태별 코드가 분리되어 유지와 보수와 확장이 편리하다

각 상태(챕터)에 맞는 로직을 상속받은 클래스에서 구현하고 
Chap 포인터(혹은 배열/벡터)로 관리하면서 필요할 때 전환

*/

#ifndef __Chap_H__
#define __Chap_H__

class Chap
{
public :
	Chap() {};
	~Chap() {};

	// 챕터가 처음 시작할 때 초기화
	virtual void Init() = 0;
	// 챕터의 매 프레임 업데이트 
	virtual void Update(double frame) = 0;
	// 챕터별 그리기 - 렌더링
	virtual void Draw() = 0;
	// 입력 및 이벤트 처리(윈도우 메시지 등)
	virtual void OnMessage(MSG* msg) = 0;
};

#endif