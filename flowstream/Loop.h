#pragma once

#define LOOP_XGAP		6
#define LOOP_YGAP		6

//===========================================
// CLoop : �ݺ� ��ȣ�� ������ Ŭ����
class CLoop : public CShape
{
public:
	CLoop();
	virtual ~CLoop();

public :
	//==========================================
	// DrawSymbol
	// �ɺ��� �׸���. CShape�� ���� ���� �Լ�.
	VOID DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag = FALSE);
};

