#pragma once

//===========================================
// CFCStart : ���� �ɺ� Ŭ����
class CFCStart :	public CSymbol,
							public CTerminal
{
public:
	CFCStart();
	virtual ~CFCStart();

public :
	// CSymbol�� ���� ���� �Լ�, �ʱ�ȭ�� �Ѵ�.
	BOOL	Initialize(Point position, Size size);
	// CSymbol�� ���� ���� �Լ�, 
	VOID	Draw(Graphics* graphics, CPoint scrollPosition);
	// CSymbol�� ���� ���� �Լ�, ���������͸� �����ϴµ� ���ȴ�.
	std::string	InterpreterLabel();

};

