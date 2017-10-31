// ObjectProperty.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ObjectPropertyView.h"
#include "FlowObject.h"
#include "ObjectFlow.h"

// CObjectPropertyView

IMPLEMENT_DYNCREATE(CObjectPropertyView, CView)

CObjectPropertyView::CObjectPropertyView()
{

}

CObjectPropertyView::~CObjectPropertyView()
{
}

BEGIN_MESSAGE_MAP(CObjectPropertyView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CObjectPropertyView �׸����Դϴ�.

void CObjectPropertyView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
	CView::OnDraw(pDC);
}


// CObjectPropertyView �����Դϴ�.

#ifdef _DEBUG
void CObjectPropertyView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CObjectPropertyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CObjectPropertyView �޽��� ó�����Դϴ�.
BOOL CObjectPropertyView::PropertyUpdate(CFlowObject* object)
{
	name->SetValue((_variant_t)(CString)object->name);
	xSize->SetValue((_variant_t)(long int)object->size.Width);
	ySize->SetValue((_variant_t)(long int)object->size.Height);
	xPosition->SetValue((_variant_t)(long int)object->position.X);
	yPosition->SetValue((_variant_t)(long int)object->position.Y);

	INT count = 0;
	std::vector<FCVariable*> variableItem = object->objectFlow->variables;

	for each (CMFCPropertyGridProperty* propertyItem in variables)
	{
		propertyItem->SetValue((_variant_t)(CString)variableItem[count]->value);
		count++;
	}

	return TRUE;
}

VOID CObjectPropertyView::AddVariable(CObjectFlow* objectFlow)
{
	for each (FCVariable* variable in objectFlow->variables)
	{
		CMFCPropertyGridProperty* propertyItem = new CMFCPropertyGridProperty(
			variable->name,
			(_variant_t)(CString)variable->value,
			_T(""));

		variableGroup->AddSubItem(propertyItem);

		variables.push_back(propertyItem);
	}
}

VOID CObjectPropertyView::DeleteVariable()
{
	for each (CMFCPropertyGridProperty* variableItem in variables)
	{
		variableGroup->RemoveSubItem(variableItem);
	}

	variables.clear();
}

int CObjectPropertyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	
	CRect rect;
	GetClientRect(rect);

	propertyGridControl.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
		CRect(0, 0, rect.right, rect.bottom), this, 1234);
	// ��� ����
	propertyGridControl.EnableHeaderCtrl(FALSE);
	// Ư�� �׺��� ���� ������ ǥ�� ����
	propertyGridControl.EnableDescriptionArea(FALSE);
	// ����� ��Ʃ��� ��� ��Ÿ�Ϸ� Grid ��Ʈ���� ���̵��� �� ���ΰ�.
	propertyGridControl.SetVSDotNetLook(FALSE);
	// �ʱ⿡ ������ ���� ������ ��쿡 �۲��� ���� �� ������
	propertyGridControl.MarkModifiedProperties(TRUE);
	// ���ĺ� ������ ������ ���ΰ�
	propertyGridControl.SetAlphabeticMode(FALSE);

	//// ���� ����
	//propertyGridControl.SetCustomColors();

	objectGroup = new CMFCPropertyGridProperty(_T("Object Condition"));

	propertyGridControl.AddProperty(objectGroup);

	name = new CMFCPropertyGridProperty(
		_T("�̸�"),
		_T(""),
		_T(""));

	name->AllowEdit(FALSE);

	xSize = new CMFCPropertyGridProperty(
		_T("����"),
		(_variant_t)(long int)0,
		_T(""));

	xSize->AllowEdit(FALSE);

	ySize = new CMFCPropertyGridProperty(
		_T("����"),
		(_variant_t)(long int)0,
		_T(""));

	ySize->AllowEdit(FALSE);

	xPosition = new CMFCPropertyGridProperty(
		_T("X��ǥ"),
		(_variant_t)(long int)0,
		_T(""));

	xPosition->AllowEdit(FALSE);

	yPosition = new CMFCPropertyGridProperty(
		_T("Y��ǥ"),
		(_variant_t)(long int)0,
		_T(""));

	yPosition->AllowEdit(FALSE);

	objectGroup->AddSubItem(name);
	objectGroup->AddSubItem(xSize);
	objectGroup->AddSubItem(ySize);
	objectGroup->AddSubItem(xPosition);
	objectGroup->AddSubItem(yPosition);

	variableGroup = new CMFCPropertyGridProperty(_T("Variables"));

	propertyGridControl.AddProperty(variableGroup);
	propertyGridControl.SetCustomColors(RGB(80, 80, 80), RGB(255, 255, 255), RGB(80, 80, 80), RGB(255, 255, 255), RGB(80, 80, 80), RGB(255, 255, 255), RGB(0, 0, 0));

	return 0;
}


void CObjectPropertyView::OnSize(UINT nType, int cx, int cy)
{
	CRect rect;
	GetClientRect(rect);

	propertyGridControl.MoveWindow(0, 0, rect.right, rect.bottom);

	CView::OnSize(nType, cx, cy);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}



//void CObjectPropertyView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
//{
//	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
//
//	CView::OnPrint(pDC, pInfo);
//}


void CObjectPropertyView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CView::OnPaint()��(��) ȣ������ ���ʽÿ�.

	CView::OnDraw(&dc);
}
