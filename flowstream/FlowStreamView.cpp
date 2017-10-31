
// FlowStreamView.cpp : CFlowStreamView 클래스의 구현
//

#include "stdAFX.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "FlowStream.h"
#endif

#include "FlowStreamDoc.h"
#include "FlowStreamView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFlowStreamView

IMPLEMENT_DYNCREATE(CFlowStreamView, CView)

BEGIN_MESSAGE_MAP(CFlowStreamView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CFlowStreamView 생성/소멸

CFlowStreamView::CFlowStreamView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CFlowStreamView::~CFlowStreamView()
{
}

BOOL CFlowStreamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CFlowStreamView 그리기

void CFlowStreamView::OnDraw(CDC* /*pDC*/)
{
	CFlowStreamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CFlowStreamView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFlowStreamView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFlowStreamView 진단

#ifdef _DEBUG
void CFlowStreamView::AssertValid() const
{
	CView::AssertValid();
}

void CFlowStreamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFlowStreamDoc* CFlowStreamView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFlowStreamDoc)));
	return (CFlowStreamDoc*)m_pDocument;
}
#endif //_DEBUG


// CFlowStreamView 메시지 처리기


void CFlowStreamView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDown(nFlags, point);
}


void CFlowStreamView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
}
