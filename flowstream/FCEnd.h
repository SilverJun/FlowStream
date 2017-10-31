#pragma once

//===========================================
// CFCEnd : ���� �ɺ� Ŭ����
class CFCEnd :	public CSymbol,
							public CTerminal
{
public:
	CFCEnd();
	virtual ~CFCEnd();

public:
	// CSymbol�� ���� ���� �Լ�, �ʱ�ȭ�� �Ѵ�.
	BOOL	Initialize(Point position, Size size);
	// CSymbol�� ���� ���� �Լ�, 
	VOID	Draw(Graphics* graphics, CPoint scrollPosition);
	// CSymbol�� ���� ���� �Լ�, ���������͸� �����ϴµ� ���ȴ�.
	std::string	InterpreterLabel();

};

