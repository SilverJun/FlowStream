#pragma once

#define PREPARE_XGAP		8
#define PREPARE_YGAP		6

//===========================================
// CPrepare : �غ� ��ȣ�� ������ Ŭ����
class CPrepare : public CShape
{
public:
	CPrepare();
	virtual ~CPrepare();

public :
	//==========================================
	// DrawSymbol
	// �ɺ��� �׸���. CShape�� ���� ���� �Լ�.
	VOID DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag = FALSE);
};

