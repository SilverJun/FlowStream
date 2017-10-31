#pragma once


// CObjectPropertyView ���Դϴ�.

class CFlowObject;
class CObjectFlow;

class CObjectPropertyView : public CView
{
	DECLARE_DYNCREATE(CObjectPropertyView)

protected:
	CObjectPropertyView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
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


