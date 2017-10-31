#pragma once

//===========================================
// CFCSet : �� ���� �ɺ� Ŭ����
class CFCPrint :	public CSymbol,
							public CDataIO
{
public:
	CFCPrint();
	virtual ~CFCPrint();

public :
	// CSymbol�� ���� ���� �Լ�, �ʱ�ȭ�� �Ѵ�.
	BOOL	Initialize(Point position, Size size);
	// CSymbol�� ���� ���� �Լ�, 
	VOID	Draw(Graphics* graphics, CPoint scrollPosition);
	// CSymbol�� ���� ���� �Լ�, ���������͸� �����ϴµ� ���ȴ�.
	std::string	InterpreterLabel();

};

