#pragma once

class CLockSplitterView : public CSplitterWnd
{
public:
	CLockSplitterView();
	virtual ~CLockSplitterView();
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);
};

