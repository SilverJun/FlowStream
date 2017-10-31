#pragma once

#include "MainFrm.h"

class CSymbol;
class CSymbolProperty;
class CLine;

#include "Interpreter.h"

//=========================================
// CObjectFlow : 오브젝트의 흐름을 나타낼 클래스
class CObjectFlow
{
public:
	CObjectFlow();
	virtual ~CObjectFlow();

private :
	CSymbol*	startSymbol;
	CSymbol*	endSymbol;

public :
	// 인터프리터
	CInterpreter*	Interpreter;

public :
	// 초기화
	BOOL			Initialize(CSymbol* start, CSymbol*	end, CFlowObject* object);

public :
	// 심볼을 관리할 벡터 객체
	std::vector<CSymbol*>	symbols;
	// 현재 선택된 심볼
	CSymbol*	selectedSymbol;

public :
	// 심볼을 관리하기 위해 벡터에 푸쉬한다.
	BOOL	PushSymbol(CSymbol* symbol);

	// 그리기 이벤트 처리
	BOOL	SymbolDraw(Graphics* graphics, CPoint scrollPosition);
	// 왼쪽 마우스 클릭 이벤트 처리
	BOOL	LMouseDown(CPoint MousePosition, CPoint scrollPosition);
	// 마우스 이동 이벤트 처리
	BOOL	MouseMove(CPoint MousePosition);
	// 왼쪽 마우스 클릭 종료 이벤트 처리
	BOOL	LMouseUp(CPoint MousePosition);

private :
	// 선을 관리할 벡터 객체
	std::vector<CLine*> lines;
	// 현재 선택된 선
	CLine* selectedLine;

public :
	// 선의 위치를 검사하여 선을 만들수 있는지 검사한다.
	BOOL	CreateLine(Point startPos, Point endPos, CPoint scrollPosition, Color color);
	// 특수화된 선을 그린다. (IF 심볼)
	BOOL	CreateFlagLine(Point startPos, Point endPos, CPoint scrollPosition, Color color, BOOL flag);
	// 선을 그린다.CreateFlagLine
	VOID	DrawLines(Graphics* graphics, CPoint scrollPosition);

public :
	// 만들어진 변수들을 관리할 벡터, 접근을 위해 public
	std::vector<FCVariable*> variables;

public :
	// 변수를 관리하기 위해 벡터에 푸쉬한다.
	BOOL	PushVariable(FCVariable* variable);

public :
	BOOL	DeleteSelectedObject();
};
