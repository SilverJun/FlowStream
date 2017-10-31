#pragma once

//===========================================
// CFCCreate : ���� ���� �ɺ� Ŭ����
class CFCCreate :	public CSymbol,
								public CPrepare
{
public:
	CFCCreate();
	virtual ~CFCCreate();

public :
	// CSymbol�� ���� ���� �Լ�, �ʱ�ȭ�� �Ѵ�.
	BOOL	Initialize(Point position, Size size);
	// CSymbol�� ���� ���� �Լ�, �׸��⸦ �Ѵ�.
	VOID	Draw(Graphics* graphics, CPoint scrollPosition);
	// CSymbol�� ���� ���� �Լ�, ���������͸� �����ϴµ� ���ȴ�.
	std::string	InterpreterLabel();
};

