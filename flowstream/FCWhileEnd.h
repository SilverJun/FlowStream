#pragma once

//===========================================
// CFCWhileEnd : �ݺ��� ���� �ɺ� Ŭ����
class CFCWhileEnd :	public CSymbol,
										public CLoop
{
public:
	CFCWhileEnd();
	virtual ~CFCWhileEnd();

public:
	// CSymbol�� ���� ���� �Լ�, �ʱ�ȭ�� �Ѵ�.
	BOOL	Initialize(Point position, Size size);
	// CSymbol�� ���� ���� �Լ�, 
	VOID	Draw(Graphics* graphics, CPoint scrollPosition);
	// CSymbol�� ���� ���� �Լ�, ���������͸� �����ϴµ� ���ȴ�.
	std::string	InterpreterLabel();

};

