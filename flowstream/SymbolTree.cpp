// SymbolTree.cpp : 구현 파일입니다.
//

#include "stdAFX.h"
#include "FlowStream.h"
#include "SymbolTree.h"


// CSymbolTree

IMPLEMENT_DYNCREATE(CSymbolTree, CTreeView)

CSymbolTree::CSymbolTree()
{
}

CSymbolTree::~CSymbolTree()
{
}

BEGIN_MESSAGE_MAP(CSymbolTree, CTreeView)
	ON_WM_CREATE()
	ON_WM_MOUSEWHEEL()
	ON_NOTIFY_REFLECT(NM_CLICK, &CSymbolTree::OnNMClick)
	ON_NOTIFY_REFLECT(TVN_SINGLEEXPAND, &CSymbolTree::OnTvnSingleExpand)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSymbolTree::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSymbolTree 진단입니다.

#ifdef _DEBUG
void CSymbolTree::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSymbolTree::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSymbolTree 메시지 처리기입니다.


int CSymbolTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	bSelected = FALSE;
	bStartFlag = FALSE;

	// 트리 컨트롤을 얻어온다.
	CTreeCtrl&	tree = GetTreeCtrl();

	//// 트리 배경색 및 UI 설정
	//tree.SetBkColor(RGB(0, 0, 0));
	//tree.SetTextColor(RGB(255, 255, 255));

	//================================================================
	// 트리 생성 및 설정

	hSymbols = tree.InsertItem(_T("Symbols"), 0, 0, TVSIL_NORMAL);
	hIf = tree.InsertItem(_T("If"), 0, 0, hSymbols);
	hSet = tree.InsertItem(_T("Set"), 0, 0, hSymbols);
	hPrint = tree.InsertItem(_T("Print"), 0, 0, hSymbols);
	hCreate = tree.InsertItem(_T("Create"), 0, 0, hSymbols);
	hWhile = tree.InsertItem(_T("While"), 0, 0, hSymbols);
	hInput = tree.InsertItem(_T("Input"), 0, 0, hSymbols);
	hOutput = tree.InsertItem(_T("Output"), 0, 0, hSymbols);

	hLines = tree.InsertItem(_T("Lines"), 0, 0, TVSIL_NORMAL);
	hLine = tree.InsertItem(_T("Line"), 0, 0, hLines);
	hTrueLine = tree.InsertItem(_T("TrueLine"), 0, 0, hLines);
	hFalseLine = tree.InsertItem(_T("FalseLine"), 0, 0, hLines);

	// 스크롤바를 사용하지 않는다.
	tree.ShowScrollBar(SB_HORZ, FALSE);

	tree.SetBkColor(RGB(80, 80, 80));
	tree.SetTextColor(RGB(255, 255, 255));

	return 0;
}


BOOL CSymbolTree::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CTreeView::OnMouseWheel(nFlags, zDelta, pt);
}


void CSymbolTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	CPoint  position;
	GetCursorPos(&position);
	::ScreenToClient(GetTreeCtrl().m_hWnd, &position);
	HTREEITEM hItem = GetTreeCtrl().HitTest(position);

	if (hItem == hIf || hItem == hSet || hItem == hPrint ||
		hItem == hCreate || hItem == hWhile || hItem == hInput || hItem == hOutput ||
		hItem == hLine || hItem == hTrueLine || hItem == hFalseLine)
		bSelected = TRUE;

	*pResult = 0;
}


void CSymbolTree::OnTvnSingleExpand(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CSymbolTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	if (bStartFlag)
		bSelected = TRUE;
	else
		bStartFlag = TRUE;
	
	*pResult = 0;
}

