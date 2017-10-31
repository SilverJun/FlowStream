#pragma once

#define	PEN_SIZE	10

//===========================================
// CLine : ���� �⺻ ����� ������ Ŭ����
class CLine
{
public:
	CLine();
	virtual ~CLine();

public :
	// ���� �� �ɺ�
	CSymbol*	startSymbol;
	// �� �ɺ�
	CSymbol*	endSymbol;
	// ���õ� �����ΰ�
	bool				bSelected;
	// �� ����
	Color			color;

	// Ư��ȭ�� ���� ���, �� ������ ��Ÿ��. (IF��)
	BOOL			bFlag;

public :
	// ���� ���콺�� Ŭ���Ǿ��� ��
	BOOL	LMouseDown(CPoint mousePosition, CPoint scrollPosition);
	// ���콺�� �̵� �� �� ��
	BOOL	MouseMove(CPoint mousePosition);
	// ���� ���콺�� Ŭ���� �Ϸ�Ǿ��� ��
	BOOL	LMouseUp(CPoint mousePosition);

public :
	VOID	Draw(Graphics* graphics, CPoint scrollPosition, BOOL flag = FALSE);
};

