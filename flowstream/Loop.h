#pragma once

#define LOOP_XGAP		6
#define LOOP_YGAP		6

//===========================================
// CLoop : 반복 기호를 구현한 클래스
class CLoop : public CShape
{
public:
	CLoop();
	virtual ~CLoop();

public :
	//==========================================
	// DrawSymbol
	// 심볼을 그린다. CShape의 순수 가상 함수.
	VOID DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag = FALSE);
};

