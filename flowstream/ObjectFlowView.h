#pragma once

// CObjectFlowView 뷰입니다.

#include "MainFrm.h"

#define MAX_WINDOWXSIZE		2000
#define MAX_WINDOWYSIZE		1600

class CObjectFlow;
class CConditionCheck;
class CCreateVariable;
class CAllocation;
class CDataInput;
class CDataOutput;
class CFlowObject;


//=========================================
// CObjectFlowView : 오브젝트의 흐름을 나타낼 심볼들을 관리하는 클래스
class CObjectFlowView : public CScrollView
{
	DECLARE_DYNCREATE(CObjectFlowView)

protected:
	CObjectFlowView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CObjectFlowView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public :
	// 오브젝트의 심볼들을 관리하는 객체
	std::vector<CObjectFlow*>	objectFlows;
	// 현재 오브젝트의 흐름
	CObjectFlow*							selectedObjectFlow;

	// 오브젝트가 생성되어 인터프리터와 흐름을 생성한다.
	CObjectFlow*		CreateFlow(CFlowObject* object);
	// 선택된 오브젝트를 바꾼다.
	BOOL					ChangeFlow(CObjectFlow* object);
	// 선택된 오브젝트를 삭제한다.
	BOOL					DeleteFlow(CObjectFlow* object);

private :
	// 스크롤 윈도우의 위치
	CPoint			scrollPosition;

	// 선을 그리는 중인가
	bool		bLineDrawing;
	// 선 시작 위치
	Point	lineStartPosition;
	// 선 끝 위치
	Point	lineEndPosition;
	// 선의 색
	Color	linecolor;

public :
	// 심볼 생성 함수들
	// Proc
	BOOL			CreateSymbolProc(CString itemtext, Point position, Size size);
	// Start
	CSymbol*		CreateSymbolStart(Point position, Size size);
	// End
	CSymbol*		CreateSymbolEnd(Point position, Size size);
	// If
	VOID			CreateSymbolIf(Point position, Size size);
	VOID			CreateSymbolIfEnd(Point position, Size size);
	// Set
	VOID			CreateSymbolSet(Point position, Size size);
	// Print
	VOID			CreateSymbolPrint(Point position, Size size);
	// Create
	VOID			CreateSymbolCreate(Point position, Size size);
	// while
	VOID			CreateSymbolWhile(Point position, Size size);
	VOID			CreateSymbolWhileEnd(Point position, Size size);
	//intput
	VOID			CreateSymbolInput(Point position, Size size);
	//output
	VOID			CreateSymbolOutput(Point position, Size size);

	// 선 생성 변수 및 함수들
	CString lastLinetext;

	// Proc
	BOOL	CreateLineProc(CString itemtext, Point startPosition, Point endPosition);
	// Start			 
	VOID	CreateLine(Point startPosition, Point endPosition);
	// End				
	VOID	CreateTrueLine(Point startPosition, Point endPosition);
	// If				   
	VOID	CreateFalseLine(Point startPosition, Point endPosition);

protected:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual void OnInitialUpdate();     // 생성된 후 처음입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


