#pragma once

//===========================================
// CFCWhileStart : �ݺ��� ���� �ɺ� Ŭ����
class CFCWhileStart :	public CSymbol,
										public CLoop
{
public:
	CFCWhileStart();
	virtual ~CFCWhileStart();

public :
	// CSymbol�� ���� ���� �Լ�, �ʱ�ȭ�� �Ѵ�.
	BOOL	Initialize(Point position, Size size);
	// CSymbol�� ���� ���� �Լ�, 
	VOID	Draw(Graphics* graphics, CPoint scrollPosition);
	// CSymbol�� ���� ���� �Լ�, ���������͸� �����ϴµ� ���ȴ�.
	std::string	InterpreterLabel();

};

