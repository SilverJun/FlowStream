#pragma once

#define DECISION_XGAP		10
#define DECISION_YGAP		6

//===========================================
// CDecision : �Ǵ� ��ȣ�� ������ Ŭ����
class CDecision : public CShape
{
public:
	CDecision();
	virtual ~CDecision();

public:
	//==========================================
	// DrawSymbol
	// �ɺ��� �׸���. CShape�� ���� ���� �Լ�.
	VOID DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag = FALSE);
};

