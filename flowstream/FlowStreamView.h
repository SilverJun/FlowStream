
// FlowStreamView.h : CFlowStreamView Ŭ������ �������̽�
//

#pragma once


class CFlowStreamView : public CView
{
protected: // serialization������ ��������ϴ�.
	CFlowStreamView();
	DECLARE_DYNCREATE(CFlowStreamView)

// Ư���Դϴ�.
public:
	CFlowStreamDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CFlowStreamView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // FlowStreamView.cpp�� ����� ����
inline CFlowStreamDoc* CFlowStreamView::GetDocument() const
   { return reinterpret_cast<CFlowStreamDoc*>(m_pDocument); }
#endif

