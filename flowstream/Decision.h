#pragma once

#define DECISION_XGAP		10
#define DECISION_YGAP		6

//===========================================
// CDecision : 판단 기호를 구현한 클래스
class CDecision : public CShape
{
public:
	CDecision();
	virtual ~CDecision();

public:
	//==========================================
	// DrawSymbol
	// 심볼을 그린다. CShape의 순수 가상 함수.
	VOID DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag = FALSE);
};

