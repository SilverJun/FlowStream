#pragma once

class CSymbol;

class CFCIfEnd :	public CSymbol,
								public CDecision
{
public:
	CFCIfEnd();
	virtual ~CFCIfEnd();

public:
	// CSymbol의 순수 가상 함수, 초기화를 한다.
	BOOL	Initialize(Point position, Size size);
	// CSymbol의 순수 가상 함수, 
	VOID	Draw(Graphics* graphics, CPoint scrollPosition);
	// CSymbol의 순수 가상 함수, 인터프리터를 생성하는데 사용된다.
	std::string	InterpreterLabel();

};

