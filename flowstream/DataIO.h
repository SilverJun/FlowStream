#pragma once

#define DATAIO_XGAP		7
#define DATAIO_YGAP		6	

//===========================================
// CDataIO : 데이터 입출력 기호를 구현한 클래스
class CDataIO : public CShape
{
public:
	CDataIO();
	virtual ~CDataIO();

public :
	//==========================================
	// DrawSymbol
	// 심볼을 그린다. CShape의 순수 가상 함수.
	VOID DrawSymbol(Graphics* graphics, INT xPos, INT yPos, BOOL selected, Size size, BOOL flag = FALSE);
};

