#pragma once


// CObjectPropertyView 뷰입니다.

class CFlowObject;
class CObjectFlow;

class CObjectPropertyView : public CView
{
	DECLARE_DYNCREATE(CObjectPropertyView)

protected:
	CObjectPropertyView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CObjectPropertyView();

public :
	CMFCPropertyGridCtrl	propertyGridControl;

	CMFCPropertyGridProperty* objectGroup;
	
	CMFCPropertyGridProperty* name;
	CMFCPropertyGridProperty* xSize;
	CMFCPropertyGridProperty* ySize;
	CMFCPropertyGridProperty* xPosition;
	CMFCPropertyGridProperty* yPosition;

	CMFCPropertyGridProperty*						variableGroup;
	std::vector<CMFCPropertyGridProperty*>	variables;

public :
	BOOL		PropertyUpdate(CFlowObject* object);

	VOID		AddVariable(CObjectFlow* objectFlow);
	VOID		DeleteVariable();

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

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
};


