#pragma once

class CFCDialog;

//===========================================
// CSymbol : 심볼의 기본 기능을 구현한 클래스
class CSymbol
{
public:
	CSymbol();
	virtual ~CSymbol();

public :
	// 좌표
	Point	position;
	// 크기
	Size		size;
	// 선택된 상태인가
	bool		bSelected;
	// 이동 중인가
	bool		bMove;
	// 클릭한 위치
	Point	clickPosition;
	// 라벨
	CString			label;

	// 연결된 이전 심볼 
	CSymbol*		beforeSymbol;
	// 연결된 다음 심볼 
	CSymbol*		nextSymbol;
	// 심볼의 대화상자
	CFCDialog*	dialog;

	// 특수화된 상황인지 (IF 심볼)
	BOOL				bSymbolFlag;
	// IF 심볼에서만 사용하는 심볼들
	// 참일때의 심볼
	CSymbol*		trueSymbol;
	// 거짓일때의 심볼
	CSymbol*		falseSymbol;

	// 변수를 포함한 심볼인지
	BOOL				bVariableFlag;
	// 변수
	FCVariable*	variable;

protected :
	// 초기화를 담당하는 순수 가상 함수
	virtual BOOL	Initialize(Point position, Size size) = 0;

public :
	// 그리기를 담당하는 순수 가상 함수
	virtual VOID		Draw(Graphics* graphics, CPoint scrollPosition) = 0;
	// 인터프리터를 생성하는데 사용되는 순수 가상 함수.
	virtual std::string	InterpreterLabel() = 0;

public :
	// 왼쪽 마우스가 클릭되었을 때
	BOOL	LMouseDown(CPoint	 mousePosition, CPoint scrollPosition);
	// 마우스가 이동 중 일 때
	BOOL	MouseMove(CPoint mousePosition);
	// 왼쪽 마우스의 클릭이 완료되었을 때
	BOOL	LMouseUp(CPoint mousePosition);

	// 심볼의 크기를 조정한다.
	BOOL	ResizeSymbol();

	// 심볼의 라벨을 그린다.
	BOOL	DrawLabel(Graphics* graphics, CPoint scrollPosition);
};

