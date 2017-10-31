// PlayView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "PlayView.h"
#include "FlowObject.h"

#include "BufferDC.h"

// CPlayView

IMPLEMENT_DYNCREATE(CPlayView, CView)

CPlayView::CPlayView()
{
	selectedObject = nullptr;
}

CPlayView::~CPlayView()
{
}

BEGIN_MESSAGE_MAP(CPlayView, CView)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CPlayView �׸����Դϴ�.

void CPlayView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CPlayView �����Դϴ�.

#ifdef _DEBUG
void CPlayView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPlayView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPlayView �޽��� ó�����Դϴ�.
VOID CPlayView::PushObject(CFlowObject* object)
{
	objects.push_back(object);
}

void CPlayView::OnPaint()
{
	CBufferDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CView::OnPaint()��(��) ȣ������ ���ʽÿ�.

	
	BOOL drawFlag = FALSE;

	Graphics graphics(dc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);

	CRect RectClient;
	GetClientRect(&RectClient);

	dc.FillSolidRect(&RectClient, RGB(255, 255, 255));

	CMainFrame*	mainFrame = (CMainFrame*)AfxGetMainWnd();

	for each (CFlowObject* object in objects)
	{
		object->Draw(&graphics);

		if (object->programFlag)
		{
			//object->UpdateValue();
			mainFrame->objectProperty->PropertyUpdate(object);
			drawFlag = TRUE;
		}
	}
}


void CPlayView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CMainFrame*		mainFrame = (CMainFrame*)AfxGetMainWnd();

	for each (CFlowObject* object in objects)
	{
		if (object->LMouseDown(point))
		{
			mainFrame->objectFlow->ChangeFlow(object->objectFlow);
			mainFrame->objectProperty->DeleteVariable();
			mainFrame->objectProperty->AddVariable(object->objectFlow);

			ChangeSelectedObject(object);

			break;
		}
	}

	CView::OnLButtonDown(nFlags, point);
}

VOID CPlayView::ChangeSelectedObject(CFlowObject* object)
{
	if (selectedObject != nullptr)
		selectedObject->bSelected = FALSE;

	selectedObject = object;

	selectedObject->bSelected = TRUE;

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	mainFrame->objectProperty->PropertyUpdate(selectedObject);

	Invalidate();
}

VOID CPlayView::DeleteObject(CString name)
{
	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	std::vector<CFlowObject*>::iterator iter = std::find(objects.begin(), objects.end(), selectedObject);

	mainFrame->objectFlow->DeleteFlow(selectedObject->objectFlow);

	objects.erase(iter);

	selectedObject->Release();

	selectedObject = nullptr;

	Invalidate();
}

void CPlayView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	for each (CFlowObject* object in objects)
	{
		if (object->MouseMove(point))
		{
			CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

			mainFrame->objectProperty->PropertyUpdate(selectedObject);

			Invalidate();
		}
	}

	CView::OnMouseMove(nFlags, point);
}


void CPlayView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	for each (CFlowObject* object in objects)
	{
		if (object->LMouseUp(point))
		{
			CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

			mainFrame->objectProperty->PropertyUpdate(selectedObject);
			
			Invalidate();
		}
	}

	CView::OnLButtonUp(nFlags, point);
}


void CPlayView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CPlayView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	// ���� ��ư

	if (!mainFrame->bIsStart || nChar == VK_DELETE || nChar == VK_BACK)
	{
		CString name = selectedObject->name;

		DeleteObject(name);
		mainFrame->objectList->DeleteObject(name);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CPlayView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (nIDEvent == PLAY_DRAWTIME)
	{
		for each (CFlowObject* object in objects)
		{
			object->UpdateValue();
		}
		Invalidate();
	}

	CView::OnTimer(nIDEvent);
}


BOOL CPlayView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}
