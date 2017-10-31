#pragma once

//=========================================
// CFCIf : 이프문 기호 클래스
class CFCIf :	public CSymbol,
						public CDecision
{
public:
	CFCIf();
	virtual ~CFCIf();

public :
	// CSymbol의 순수 가상 함수, 초기화를 한다.
	BOOL	Initialize(Point position, Size size);
	// CSymbol의 순수 가상 함수, 
	VOID	Draw(Graphics* graphics, CPoint scrollPosition);
	// CSymbol의 순수 가상 함수, 인터프리터를 생성하는데 사용된다.
	std::string	InterpreterLabel();
};

