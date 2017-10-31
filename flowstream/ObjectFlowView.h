#pragma once

// CObjectFlowView ���Դϴ�.

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
// CObjectFlowView : ������Ʈ�� �帧�� ��Ÿ�� �ɺ����� �����ϴ� Ŭ����
class CObjectFlowView : public CScrollView
{
	DECLARE_DYNCREATE(CObjectFlowView)

protected:
	CObjectFlowView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CObjectFlowView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public :
	// ������Ʈ�� �ɺ����� �����ϴ� ��ü
	std::vector<CObjectFlow*>	objectFlows;
	// ���� ������Ʈ�� �帧
	CObjectFlow*							selectedObjectFlow;

	// ������Ʈ�� �����Ǿ� ���������Ϳ� �帧�� �����Ѵ�.
	CObjectFlow*		CreateFlow(CFlowObject* object);
	// ���õ� ������Ʈ�� �ٲ۴�.
	BOOL					ChangeFlow(CObjectFlow* object);
	// ���õ� ������Ʈ�� �����Ѵ�.
	BOOL					DeleteFlow(CObjectFlow* object);

private :
	// ��ũ�� �������� ��ġ
	CPoint			scrollPosition;

	// ���� �׸��� ���ΰ�
	bool		bLineDrawing;
	// �� ���� ��ġ
	Point	lineStartPosition;
	// �� �� ��ġ
	Point	lineEndPosition;
	// ���� ��
	Color	linecolor;

public :
	// �ɺ� ���� �Լ���
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

	// �� ���� ���� �� �Լ���
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
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual void OnInitialUpdate();     // ������ �� ó���Դϴ�.

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


