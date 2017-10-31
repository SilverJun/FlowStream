
// FlowStreamView.cpp : CFlowStreamView Ŭ������ ����
//

#include "stdAFX.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CFlowStreamView ����/�Ҹ�

CFlowStreamView::CFlowStreamView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CFlowStreamView::~CFlowStreamView()
{
}

BOOL CFlowStreamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CFlowStreamView �׸���

void CFlowStreamView::OnDraw(CDC* /*pDC*/)
{
	CFlowStreamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
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


// CFlowStreamView ����

#ifdef _DEBUG
void CFlowStreamView::AssertValid() const
{
	CView::AssertValid();
}

void CFlowStreamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFlowStreamDoc* CFlowStreamView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFlowStreamDoc)));
	return (CFlowStreamDoc*)m_pDocument;
}
#endif //_DEBUG


// CFlowStreamView �޽��� ó����


void CFlowStreamView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnLButtonDown(nFlags, point);
}


void CFlowStreamView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CView::OnPaint()��(��) ȣ������ ���ʽÿ�.
}
