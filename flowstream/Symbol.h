#pragma once

class CFCDialog;

//===========================================
// CSymbol : �ɺ��� �⺻ ����� ������ Ŭ����
class CSymbol
{
public:
	CSymbol();
	virtual ~CSymbol();

public :
	// ��ǥ
	Point	position;
	// ũ��
	Size		size;
	// ���õ� �����ΰ�
	bool		bSelected;
	// �̵� ���ΰ�
	bool		bMove;
	// Ŭ���� ��ġ
	Point	clickPosition;
	// ��
	CString			label;

	// ����� ���� �ɺ� 
	CSymbol*		beforeSymbol;
	// ����� ���� �ɺ� 
	CSymbol*		nextSymbol;
	// �ɺ��� ��ȭ����
	CFCDialog*	dialog;

	// Ư��ȭ�� ��Ȳ���� (IF �ɺ�)
	BOOL				bSymbolFlag;
	// IF �ɺ������� ����ϴ� �ɺ���
	// ���϶��� �ɺ�
	CSymbol*		trueSymbol;
	// �����϶��� �ɺ�
	CSymbol*		falseSymbol;

	// ������ ������ �ɺ�����
	BOOL				bVariableFlag;
	// ����
	FCVariable*	variable;

protected :
	// �ʱ�ȭ�� ����ϴ� ���� ���� �Լ�
	virtual BOOL	Initialize(Point position, Size size) = 0;

public :
	// �׸��⸦ ����ϴ� ���� ���� �Լ�
	virtual VOID		Draw(Graphics* graphics, CPoint scrollPosition) = 0;
	// ���������͸� �����ϴµ� ���Ǵ� ���� ���� �Լ�.
	virtual std::string	InterpreterLabel() = 0;

public :
	// ���� ���콺�� Ŭ���Ǿ��� ��
	BOOL	LMouseDown(CPoint	 mousePosition, CPoint scrollPosition);
	// ���콺�� �̵� �� �� ��
	BOOL	MouseMove(CPoint mousePosition);
	// ���� ���콺�� Ŭ���� �Ϸ�Ǿ��� ��
	BOOL	LMouseUp(CPoint mousePosition);

	// �ɺ��� ũ�⸦ �����Ѵ�.
	BOOL	ResizeSymbol();

	// �ɺ��� ���� �׸���.
	BOOL	DrawLabel(Graphics* graphics, CPoint scrollPosition);
};

