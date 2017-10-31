#pragma once

#define PREPARE_XGAP		8
#define PREPARE_YGAP		6

//===========================================
// CPrepare : 준비 기호를 구현한 클래스
class CPrepare : public CShape
{
public:
	CPrepare();
	virtual ~CPrepare();

public :
	//==========================================
	// DrawSymbol
	// 심볼을 그린다. CShape의 순수 가상 함수.
	VOID DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag = FALSE);
};

