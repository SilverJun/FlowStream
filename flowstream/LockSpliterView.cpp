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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}


void CLockSplitterView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CWnd::OnMouseMove(nFlags, point);
}


void CLockSplitterView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CWnd::OnLButtonDown(nFlags, point);
}


void CLockSplitterView::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

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
