#pragma once

#define TERMINAL_XGAP		5
#define TERMINAL_YGAP		4

//===========================================
// CTerminal : 터미널 기호를 구현한 클래스
class CTerminal : public CShape
{
public:
	CTerminal();
	virtual ~CTerminal();

public :
	//==========================================
	// DrawSymbol
	// 심볼을 그린다. CShape의 순수 가상 함수.
	VOID DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag = FALSE);
};

