#pragma once

#define DATAIO_XGAP		7
#define DATAIO_YGAP		6	

//===========================================
// CDataIO : ������ ����� ��ȣ�� ������ Ŭ����
class CDataIO : public CShape
{
public:
	CDataIO();
	virtual ~CDataIO();

public :
	//==========================================
	// DrawSymbol
	// �ɺ��� �׸���. CShape�� ���� ���� �Լ�.
	VOID DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag = FALSE);
};

