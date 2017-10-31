// ObjectProperty.cpp : 구현 파일입니다.
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


// CObjectPropertyView 그리기입니다.

void CObjectPropertyView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	CView::OnDraw(pDC);
}


// CObjectPropertyView 진단입니다.

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


// CObjectPropertyView 메시지 처리기입니다.
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

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	
	CRect rect;
	GetClientRect(rect);

	propertyGridControl.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
		CRect(0, 0, rect.right, rect.bottom), this, 1234);
	// 헤더 유무
	propertyGridControl.EnableHeaderCtrl(FALSE);
	// 특정 항복에 대한 윈도우 표시 설정
	propertyGridControl.EnableDescriptionArea(FALSE);
	// 비쥬얼 스튜디오 닷넷 스타일로 Grid 컨트롤을 보이도록 할 것인가.
	propertyGridControl.SetVSDotNetLook(FALSE);
	// 초기에 설정한 값을 수정한 경우에 글꼴을 굵게 할 것인지
	propertyGridControl.MarkModifiedProperties(TRUE);
	// 알파벳 순으로 나열할 것인가
	propertyGridControl.SetAlphabeticMode(FALSE);

	//// 색깔 조정
	//propertyGridControl.SetCustomColors();

	objectGroup = new CMFCPropertyGridProperty(_T("Object Condition"));

	propertyGridControl.AddProperty(objectGroup);

	name = new CMFCPropertyGridProperty(
		_T("이름"),
		_T(""),
		_T(""));

	name->AllowEdit(FALSE);

	xSize = new CMFCPropertyGridProperty(
		_T("가로"),
		(_variant_t)(long int)0,
		_T(""));

	xSize->AllowEdit(FALSE);

	ySize = new CMFCPropertyGridProperty(
		_T("세로"),
		(_variant_t)(long int)0,
		_T(""));

	ySize->AllowEdit(FALSE);

	xPosition = new CMFCPropertyGridProperty(
		_T("X좌표"),
		(_variant_t)(long int)0,
		_T(""));

	xPosition->AllowEdit(FALSE);

	yPosition = new CMFCPropertyGridProperty(
		_T("Y좌표"),
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
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}



//void CObjectPropertyView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//
//	CView::OnPrint(pDC, pInfo);
//}


void CObjectPropertyView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	CView::OnDraw(&dc);
}
