// ObjectFlowView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "ObjectFlowView.h"
#include "Interpreter.h"
#include "resource.h"
#include "FlowObject.h"
#include "Program.h"

#include "BufferDC.h"

// CObjectFlowView

IMPLEMENT_DYNCREATE(CObjectFlowView, CScrollView)

CObjectFlowView::CObjectFlowView()
{

}

CObjectFlowView::~CObjectFlowView()
{
}


BEGIN_MESSAGE_MAP(CObjectFlowView, CScrollView)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CObjectFlowView 그리기입니다.

void CObjectFlowView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = MAX_WINDOWXSIZE;
	sizeTotal.cy = MAX_WINDOWYSIZE;

	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CObjectFlowView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.

}


// CObjectFlowView 진단입니다.

#ifdef _DEBUG
void CObjectFlowView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CObjectFlowView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


CObjectFlow*	 CObjectFlowView::CreateFlow(CFlowObject* object)
{
	CObjectFlow*	objectFlow = new CObjectFlow();

	selectedObjectFlow = objectFlow;

	CSymbol*	start = CreateSymbolStart(Point(200, 20), Size(SYMBOL_XSIZE, SYMBOL_YSIZE));
	CSymbol*	end = CreateSymbolEnd(Point(200, 500), Size(SYMBOL_XSIZE, SYMBOL_YSIZE));

	objectFlow->Initialize(start, end, object);

	objectFlows.push_back(objectFlow);

	return objectFlow;
}

BOOL CObjectFlowView::ChangeFlow(CObjectFlow* object)
{
	if (object == nullptr)
	{
		selectedObjectFlow = nullptr;

		Invalidate();

		return TRUE;
	}

	for each (CObjectFlow* flow in objectFlows)
	{
		if (object == flow)
		{
			selectedObjectFlow = flow;

			Invalidate();

			return TRUE;
		}

	}

	return FALSE;
}

BOOL CObjectFlowView::DeleteFlow(CObjectFlow* object)
{
	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	for each (CSymbol* symbol in object->symbols)
	{
		mainFrame->symbolProperty->PropertyDelete(symbol);
	}

	std::vector<CObjectFlow*>::iterator iter = std::find(objectFlows.begin(), objectFlows.end(), object);

	objectFlows.erase(iter);

	return TRUE;
}

// 심볼 생성 함수들
BOOL CObjectFlowView::CreateSymbolProc(CString itemtext, Point position, Size size)
{
	if (selectedObjectFlow != nullptr)
	{
		if (itemtext == "If")
		{
			CreateSymbolIf(position, size);
			CreateSymbolIfEnd(position + Point(0, 80), size);

			return TRUE;
		}
		else if (itemtext == "Set")
		{
			CreateSymbolSet(position, size);

			return TRUE;
		}
		else if (itemtext == "Print")
		{
			CreateSymbolPrint(position, size);

			return TRUE;
		}
		else if (itemtext == "Create")
		{
			CreateSymbolCreate(position, size);

			return TRUE;
		}
		else if (itemtext == "While")
		{
			CreateSymbolWhile(position, size);
			CreateSymbolWhileEnd(position + Point(0, 80), size);

			return TRUE;
		}
		else if (itemtext == "Input")
		{
			CreateSymbolInput(position, size);

			return TRUE;
		}
		else if (itemtext == "Output")
		{
			CreateSymbolOutput(position, size);

			return TRUE;
		}
	}

	return FALSE;
}

// Start
CSymbol* CObjectFlowView::CreateSymbolStart(Point position, Size size)
{
	CFCStart* start;
	start = new CFCStart();

	if (!start->Initialize(position, size))
		return nullptr;

	selectedObjectFlow->PushSymbol(dynamic_cast<CSymbol*>(start));

	return dynamic_cast<CSymbol*>(start);
}

// End
CSymbol* CObjectFlowView::CreateSymbolEnd(Point position, Size size)
{
	CFCEnd* end;
	end = new CFCEnd();

	if (!end->Initialize(position, size))
	{
		return nullptr;
	}

	selectedObjectFlow->PushSymbol(dynamic_cast<CSymbol*>(end));

	return dynamic_cast<CSymbol*>(end);
}


// If
VOID CObjectFlowView::CreateSymbolIf(Point position, Size size)
{
	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	CFCIf* If;
	If = new CFCIf();

	if (!If->Initialize(position, size))
		return;

	// IF 심볼 특수화 적용
	If->bSymbolFlag = TRUE;

	selectedObjectFlow->PushSymbol(dynamic_cast<CSymbol*>(If));

	mainFrame->symbolProperty->PushProperty(0, dynamic_cast<CSymbol*>(If));

	//CreateSymbolIfEnd(Point(position.X, position.Y + 80), size);
}

VOID CObjectFlowView::CreateSymbolIfEnd(Point position, Size size)
{
	CFCIfEnd* IfEnd;
	IfEnd = new CFCIfEnd();

	if (!IfEnd->Initialize(Point(position.X, position.Y), size))
		return;

	selectedObjectFlow->PushSymbol(dynamic_cast<CSymbol*>(IfEnd));
}

// Set
VOID CObjectFlowView::CreateSymbolSet(Point position, Size size)
{
	CFCSet* set;
	set = new CFCSet();

	if (!set->Initialize(position, size))
		return;

	selectedObjectFlow->PushSymbol(dynamic_cast<CSymbol*>(set));

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	mainFrame->symbolProperty->PushProperty(2, dynamic_cast<CSymbol*>(set));
}


// Print
VOID CObjectFlowView::CreateSymbolPrint(Point position, Size size)
{
	CFCPrint* print;
	print = new CFCPrint();

	if (!print->Initialize(position, size))
		return;

	selectedObjectFlow->PushSymbol(dynamic_cast<CSymbol*>(print));

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	mainFrame->symbolProperty->PushProperty(2, dynamic_cast<CSymbol*>(print));
}


// Create
VOID CObjectFlowView::CreateSymbolCreate(Point position, Size size)
{
	CFCCreate* create;
	create = new CFCCreate();

	if (!create->Initialize(position, size))
		return;

	selectedObjectFlow->PushSymbol(dynamic_cast<CSymbol*>(create));

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	mainFrame->symbolProperty->PushProperty(1, dynamic_cast<CSymbol*>(create));
}

// While
VOID CObjectFlowView::CreateSymbolWhile(Point position, Size size)
{
	CFCWhileStart* whileStart;
	whileStart = new CFCWhileStart();

	if (!whileStart->Initialize(position, size))
		return;

	selectedObjectFlow->PushSymbol(dynamic_cast<CSymbol*>(whileStart));

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	mainFrame->symbolProperty->PushProperty(0, dynamic_cast<CSymbol*>(whileStart));
	
	//CreateSymbolWhileEnd(Point(position.X, position.Y + 80), size);
}

VOID CObjectFlowView::CreateSymbolWhileEnd(Point position, Size size)
{
	CFCWhileEnd* whileEnd;
	whileEnd = new CFCWhileEnd();

	if (!whileEnd->Initialize(Point(position.X, position.Y), size))
		return;

	selectedObjectFlow->PushSymbol(dynamic_cast<CSymbol*>(whileEnd));
}

VOID CObjectFlowView::CreateSymbolInput(Point position, Size size)
{
	CFCInput* input = new CFCInput();

	if (!input->Initialize(position, size))
		return;

	selectedObjectFlow->PushSymbol(dynamic_cast<CSymbol*>(input));

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	mainFrame->symbolProperty->PushProperty(3, dynamic_cast<CSymbol*>(input));
}

VOID CObjectFlowView::CreateSymbolOutput(Point position, Size size)
{
	CFCOutput* output = new CFCOutput();

	if (!output->Initialize(position, size))
		return;

	selectedObjectFlow->PushSymbol(dynamic_cast<CSymbol*>(output));

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	mainFrame->symbolProperty->PushProperty(4, dynamic_cast<CSymbol*>(output));
}

// Proc
BOOL CObjectFlowView::CreateLineProc(CString itemtext, Point startPosition, Point endPosition)
{
	if (selectedObjectFlow != nullptr)
	{
		if (itemtext == "Line")
		{
			CreateLine(startPosition, endPosition);

			return TRUE;
		}
		else if (itemtext == "TrueLine")
		{
			CreateTrueLine(startPosition, endPosition);

			return TRUE;
		}
		else if (itemtext == "FalseLine")
		{
			CreateFalseLine(startPosition, endPosition);

			return TRUE;
		}
	}

	return FALSE;
}

// Line			 
VOID CObjectFlowView::CreateLine(Point startPosition, Point endPosition)
{
	linecolor = Color(0, 0, 0);

	selectedObjectFlow->CreateLine(startPosition, endPosition, GetScrollPosition(), Color(0, 0, 0));
}

// True				
VOID CObjectFlowView::CreateTrueLine(Point startPosition, Point endPosition)
{
	linecolor = Color(0, 255, 0);

	selectedObjectFlow->CreateFlagLine(startPosition, endPosition, GetScrollPosition(), Color(0, 255, 0), TRUE);
}

// False				   
VOID CObjectFlowView::CreateFalseLine(Point startPosition, Point endPosition)
{
	linecolor = Color(255, 0, 0);

	selectedObjectFlow->CreateFlagLine(startPosition, endPosition, GetScrollPosition(), Color(255, 0, 0), FALSE);
}

// CObjectFlowView 메시지 처리기입니다.

int CObjectFlowView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	bLineDrawing = FALSE;

	selectedObjectFlow = nullptr;

	return 0;
}


void CObjectFlowView::OnPaint()
{
	CBufferDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CScrollView::OnPaint()을(를) 호출하지 마십시오.

	Graphics graphics(dc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);

	CRect RectClient;
	GetClientRect(&RectClient);

	dc.FillSolidRect(&RectClient, RGB(80, 80, 80));

	if (selectedObjectFlow != nullptr)
	{
		selectedObjectFlow->DrawLines(&graphics, GetScrollPosition());
		selectedObjectFlow->SymbolDraw(&graphics, GetScrollPosition());

		Pen pen(linecolor, 10.0F);
		pen.SetEndCap(LineCapArrowAnchor);

		if (bLineDrawing)
			graphics.DrawLine(&pen, lineStartPosition, lineEndPosition);
	}
}


BOOL CObjectFlowView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 마우스 휠로 뷰를 스크롤 할 수 있게.
	return DoMouseWheel(nFlags, zDelta, pt);
	//return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}


void CObjectFlowView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//HTREEITEM tt = tree.GetNextItem(item, TVGN_PARENT);

	//tree.SelectItem(tt);

	CMainFrame*		mainFrame = (CMainFrame*)AfxGetMainWnd();
	CSymbolTree*	symbolTree = mainFrame->symbolTree;
	CTreeCtrl&			tree = symbolTree->GetTreeCtrl();

	if (symbolTree->bSelected)
	{
		HTREEITEM item = tree.GetSelectedItem();
		CString itemtext = _T("");
		itemtext = tree.GetItemText(item);

		HTREEITEM parent = tree.GetNextItem(item, TVGN_PARENT);
		CString parentText = _T("");
		parentText = tree.GetItemText(parent);

		CPoint scrollPos = GetScrollPosition();

		if (parentText == "Symbols")
		{
			if (CreateSymbolProc(itemtext, Point(point.x + scrollPos.x, point.y + scrollPos.y), Size(SYMBOL_XSIZE, SYMBOL_YSIZE)))
				Invalidate();
		}
		else if (parentText == "Lines")
		{
			if (itemtext == "Line")
				linecolor = Color(0, 0, 0);
			else if (itemtext == "TrueLine")
				linecolor = Color(0, 255, 0);
			else if (itemtext == "FalseLine")
				linecolor = Color(255, 0, 0);

			lastLinetext = itemtext;

			lineStartPosition = Point(point.x, point.y);

			bLineDrawing = TRUE;
		}

		symbolTree->bSelected = FALSE;

		return;
	}

	if (selectedObjectFlow != nullptr)
	{
		if (selectedObjectFlow->LMouseDown(point, GetScrollPosition()))
			Invalidate();
	}

	CScrollView::OnLButtonDown(nFlags, point);
}


void CObjectFlowView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (selectedObjectFlow != nullptr)
	{
		if (selectedObjectFlow->MouseMove(point))
			Invalidate();
	}

	if (bLineDrawing)
	{
		CPoint scrollPos = GetScrollPosition();

		lineEndPosition = Point(point.x, point.y);

		Invalidate();
	}

	CScrollView::OnMouseMove(nFlags, point);
}


void CObjectFlowView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (selectedObjectFlow != nullptr)
	{
		if (selectedObjectFlow->LMouseUp(point))
			Invalidate();
	}

	if (bLineDrawing)
		if (CreateLineProc(lastLinetext, lineStartPosition, lineEndPosition))
			Invalidate();

	bLineDrawing = FALSE;


	CScrollView::OnLButtonUp(nFlags, point);
}


void CObjectFlowView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	if (!mainFrame->bIsStart || nChar == VK_DELETE || nChar == VK_BACK)
	{
		if (selectedObjectFlow != nullptr)
		{
			if (selectedObjectFlow->DeleteSelectedObject())
				Invalidate();
		}
	}

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}



BOOL CObjectFlowView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CScrollView::OnEraseBkgnd(pDC);
	return TRUE;
}
