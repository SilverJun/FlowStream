#pragma once

#define	PEN_SIZE	10

//===========================================
// CLine : 선의 기본 기능을 구현한 클래스
class CLine
{
public:
	CLine();
	virtual ~CLine();

public :
	// 시작 선 심볼
	CSymbol*	startSymbol;
	// 끝 심볼
	CSymbol*	endSymbol;
	// 선택된 상태인가
	bool				bSelected;
	// 선 색깔
	Color			color;

	// 특수화된 선에 사용, 참 거짓을 나타냄. (IF문)
	BOOL			bFlag;

public :
	// 왼쪽 마우스가 클릭되었을 때
	BOOL	LMouseDown(CPoint mousePosition, CPoint scrollPosition);
	// 마우스가 이동 중 일 때
	BOOL	MouseMove(CPoint mousePosition);
	// 왼쪽 마우스의 클릭이 완료되었을 때
	BOOL	LMouseUp(CPoint mousePosition);

public :
	VOID	Draw(Graphics* graphics, CPoint scrollPosition, BOOL flag = FALSE);
};

