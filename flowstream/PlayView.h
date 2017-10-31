#pragma once


// CPlayView ���Դϴ�.

class CFlowObject;

class CPlayView : public CView
{
	DECLARE_DYNCREATE(CPlayView)

protected:
	CPlayView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CPlayView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public :
	// ������Ʈ�� ������ ����
	std::vector<CFlowObject*>	objects;
	// ���õ� ������Ʈ 
	CFlowObject*				selectedObject;

	// ������Ʈ�� �����ϱ� ���� ���Ϳ� Ǫ���Ѵ�.
	VOID	PushObject(CFlowObject* object);
	// ���õ� ������Ʈ�� �ٲ۴�.
	VOID	ChangeSelectedObject(CFlowObject* object);
	// ������Ʈ�� �����Ѵ�.
	VOID	DeleteObject(CString name);

public :
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


