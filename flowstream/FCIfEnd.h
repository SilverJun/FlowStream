#pragma once

class CSymbol;

class CFCIfEnd :	public CSymbol,
								public CDecision
{
public:
	CFCIfEnd();
	virtual ~CFCIfEnd();

public:
	// CSymbol�� ���� ���� �Լ�, �ʱ�ȭ�� �Ѵ�.
	BOOL	Initialize(Point position, Size size);
	// CSymbol�� ���� ���� �Լ�, 
	VOID	Draw(Graphics* graphics, CPoint scrollPosition);
	// CSymbol�� ���� ���� �Լ�, ���������͸� �����ϴµ� ���ȴ�.
	std::string	InterpreterLabel();

};

