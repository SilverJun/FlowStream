#pragma once

//===========================================
// CFCSet : �� ���� �ɺ� Ŭ����
class CFCSet :	public CSymbol,
							public CProcess
{
public:
	CFCSet();
	virtual ~CFCSet();
	
public :
	// CSymbol�� ���� ���� �Լ�, �ʱ�ȭ�� �Ѵ�.
	BOOL	Initialize(Point position, Size size);
	// CSymbol�� ���� ���� �Լ�, 
	VOID	Draw(Graphics* graphics, CPoint scrollPosition);
	// CSymbol�� ���� ���� �Լ�, ���������͸� �����ϴµ� ���ȴ�.
	std::string	InterpreterLabel();

};

