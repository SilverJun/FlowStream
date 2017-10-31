#pragma once


// CPlayView 뷰입니다.

class CFlowObject;

class CPlayView : public CView
{
	DECLARE_DYNCREATE(CPlayView)

protected:
	CPlayView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CPlayView();

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public :
	// 오브젝트를 관리할 벡터
	std::vector<CFlowObject*>	objects;
	// 선택된 오브젝트 
	CFlowObject*				selectedObject;

	// 오브젝트를 관리하기 위해 벡터에 푸쉬한다.
	VOID	PushObject(CFlowObject* object);
	// 선택된 오브젝트를 바꾼다.
	VOID	ChangeSelectedObject(CFlowObject* object);
	// 오브젝트를 삭제한다.
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


