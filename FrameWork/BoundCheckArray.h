#pragma once

/*
용도 :		배열 클래스 템플릿
맴버 변수 :	T 타입 포인터
			동적할당 길이
맴버 함수 :	생성자
			복사생성자
			소멸자
			대입연산자
			[]연산자 오버로딩
			[]연산자 const 오버로딩
			get-동적할당 길이
*/

template<typename T>
class BoundCheckArray
{
private:

	T * pAcc;
	int acclen;

	BoundCheckArray(const BoundCheckArray& arr) {}
	BoundCheckArray& operator=(const BoundCheckArray& arr) {}

public:
	BoundCheckArray(int len = 100);
	~BoundCheckArray();
	T& operator[](int idx);
	T operator[](int idx) const;
	int GetAcclen() const;

};

/*
기능 :		생성자
특이사항 :	객체 포인터를 동적할당
*/
template<typename T>
inline BoundCheckArray<T>::BoundCheckArray(int len) : acclen(len)
{
	pAcc = new T[len];
}

/*
기능 :		소멸자
특이사항 :	객체 포인터를 해제
*/
template<typename T>
inline BoundCheckArray<T>::~BoundCheckArray() { delete[] pAcc; }

/*
기능 :		객체포인터 객체에 대한 []연산자 오버로딩
매개변수 :	[]연산자 인덱스값
반환 :		객체포인터의 래퍼런스
특이사항 :	리턴 값으로 조작 가능
*/
template<typename T>
inline T & BoundCheckArray<T>::operator[](int idx)
{
	// 범위 초과 시
	if (idx < 0 || idx >= acclen)								
	{
		exit(1);
	}
	return pAcc[idx];
}

/*
기능 :		객체포인터 객체에 대한 []연산자 오버로딩 (상수화)
매개변수 :	[]연산자 인덱스값
반환 :		계좌 객체포인터
특이사항 :	리턴값으로 조작 불가능
*/
template<typename T>
inline T  BoundCheckArray<T>::operator[](int idx) const
{
	// 범위 초과 시
	if (idx < 0 || idx >= acclen)								
	{
		exit(1);
	}
	return pAcc[idx];
}

/*
기능 :		 get - 동적할당 길이
매개변수 :	 없음
반환 :		 동적할당 길이
특이사항 :	 없음
*/
template<typename T>
inline int BoundCheckArray<T>::GetAcclen() const { return acclen; }