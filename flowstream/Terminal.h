#pragma once

#define TERMINAL_XGAP		5
#define TERMINAL_YGAP		4

//===========================================
// CTerminal : �͹̳� ��ȣ�� ������ Ŭ����
class CTerminal : public CShape
{
public:
	CTerminal();
	virtual ~CTerminal();

public :
	//==========================================
	// DrawSymbol
	// �ɺ��� �׸���. CShape�� ���� ���� �Լ�.
	VOID DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag = FALSE);
};

