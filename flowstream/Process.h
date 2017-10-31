#pragma once

#define PROCESS_XGAP		6
#define PROCESS_YGAP		6

//===========================================
// CProcess : 처리 기호를 구현한 클래스
class CProcess : public CShape
{
public:
	CProcess();
	virtual ~CProcess();

public :
	//==========================================
	// DrawSymbol
	// 심볼을 그린다. CShape의 순수 가상 함수.
	VOID DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag = FALSE);
};

