// PlayView.cpp : 구현 파일입니다.
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


// CPlayView 그리기입니다.

void CPlayView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CPlayView 진단입니다.

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


// CPlayView 메시지 처리기입니다.
VOID CPlayView::PushObject(CFlowObject* object)
{
	objects.push_back(object);
}

void CPlayView::OnPaint()
{
	CBufferDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CPlayView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	// 삭제 버튼

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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}
