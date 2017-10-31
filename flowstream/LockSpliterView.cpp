#include "stdafx.h"
#include "LockSpliterView.h"


CLockSplitterView::CLockSplitterView()
{
}


CLockSplitterView::~CLockSplitterView()
{
}

BEGIN_MESSAGE_MAP(CLockSplitterView, CSplitterWnd)
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


BOOL CLockSplitterView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}


void CLockSplitterView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnMouseMove(nFlags, point);
}


void CLockSplitterView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnLButtonDown(nFlags, point);
}


void CLockSplitterView::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (nType == splitBorder) {
		CClientDC dc(this);
		CPen *pBorderPen, *pOldPen;
		pBorderPen = new CPen(PS_SOLID,8, RGB(160,160,160));
		pOldPen = dc.SelectObject(pBorderPen);
		dc.SelectStockObject(HOLLOW_BRUSH);

		dc.Rectangle(rect);
		dc.SelectObject(pOldPen);
		if (pBorderPen) delete pBorderPen;
	}
	if (nType == splitBar)
	{
		CSplitterWnd::OnDrawSplitter(pDC, nType, rect);
	}
}
