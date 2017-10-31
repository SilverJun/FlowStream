#pragma once

//===========================================
// CFCCreate : 변수 생성 심볼 클래스
class CFCCreate :	public CSymbol,
								public CPrepare
{
public:
	CFCCreate();
	virtual ~CFCCreate();

public :
	// CSymbol의 순수 가상 함수, 초기화를 한다.
	BOOL	Initialize(Point position, Size size);
	// CSymbol의 순수 가상 함수, 그리기를 한다.
	VOID	Draw(Graphics* graphics, CPoint scrollPosition);
	// CSymbol의 순수 가상 함수, 인터프리터를 생성하는데 사용된다.
	std::string	InterpreterLabel();
};

