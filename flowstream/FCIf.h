#pragma once

//=========================================
// CFCIf : ������ ��ȣ Ŭ����
class CFCIf :	public CSymbol,
						public CDecision
{
public:
	CFCIf();
	virtual ~CFCIf();

public :
	// CSymbol�� ���� ���� �Լ�, �ʱ�ȭ�� �Ѵ�.
	BOOL	Initialize(Point position, Size size);
	// CSymbol�� ���� ���� �Լ�, 
	VOID	Draw(Graphics* graphics, CPoint scrollPosition);
	// CSymbol�� ���� ���� �Լ�, ���������͸� �����ϴµ� ���ȴ�.
	std::string	InterpreterLabel();
};

