#pragma once

#include "MainFrm.h"

class CSymbol;
class CSymbolProperty;
class CLine;

#include "Interpreter.h"

//=========================================
// CObjectFlow : ������Ʈ�� �帧�� ��Ÿ�� Ŭ����
class CObjectFlow
{
public:
	CObjectFlow();
	virtual ~CObjectFlow();

private :
	CSymbol*	startSymbol;
	CSymbol*	endSymbol;

public :
	// ����������
	CInterpreter*	Interpreter;

public :
	// �ʱ�ȭ
	BOOL			Initialize(CSymbol* start, CSymbol*	end, CFlowObject* object);

public :
	// �ɺ��� ������ ���� ��ü
	std::vector<CSymbol*>	symbols;
	// ���� ���õ� �ɺ�
	CSymbol*	selectedSymbol;

public :
	// �ɺ��� �����ϱ� ���� ���Ϳ� Ǫ���Ѵ�.
	BOOL	PushSymbol(CSymbol* symbol);

	// �׸��� �̺�Ʈ ó��
	BOOL	SymbolDraw(Graphics* graphics, CPoint scrollPosition);
	// ���� ���콺 Ŭ�� �̺�Ʈ ó��
	BOOL	LMouseDown(CPoint MousePosition, CPoint scrollPosition);
	// ���콺 �̵� �̺�Ʈ ó��
	BOOL	MouseMove(CPoint MousePosition);
	// ���� ���콺 Ŭ�� ���� �̺�Ʈ ó��
	BOOL	LMouseUp(CPoint MousePosition);

private :
	// ���� ������ ���� ��ü
	std::vector<CLine*> lines;
	// ���� ���õ� ��
	CLine* selectedLine;

public :
	// ���� ��ġ�� �˻��Ͽ� ���� ����� �ִ��� �˻��Ѵ�.
	BOOL	CreateLine(Point startPos, Point endPos, CPoint scrollPosition, Color color);
	// Ư��ȭ�� ���� �׸���. (IF �ɺ�)
	BOOL	CreateFlagLine(Point startPos, Point endPos, CPoint scrollPosition, Color color, BOOL flag);
	// ���� �׸���.CreateFlagLine
	VOID	DrawLines(Graphics* graphics, CPoint scrollPosition);

public :
	// ������� �������� ������ ����, ������ ���� public
	std::vector<FCVariable*> variables;

public :
	// ������ �����ϱ� ���� ���Ϳ� Ǫ���Ѵ�.
	BOOL	PushVariable(FCVariable* variable);

public :
	BOOL	DeleteSelectedObject();
};
