#pragma once

#define PROCESS_XGAP		6
#define PROCESS_YGAP		6

//===========================================
// CProcess : ó�� ��ȣ�� ������ Ŭ����
class CProcess : public CShape
{
public:
	CProcess();
	virtual ~CProcess();

public :
	//==========================================
	// DrawSymbol
	// �ɺ��� �׸���. CShape�� ���� ���� �Լ�.
	VOID DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag = FALSE);
};

