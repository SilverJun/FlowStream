
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdAFX.h"
#include "FlowStream.h"

#include "MainFrm.h"

#include "FlowObject.h"

#include "FlowStreamDoc.h"
#include "ProjectCreation.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern BOOL	bStart;


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_MOVE()
	ON_WM_GETMINMAXINFO()
	ON_WM_EXITSIZEMOVE()
	ON_WM_SIZE()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_COMMAND(ID_INTERPRETER_STOP, &CMainFrame::OnInterpreterStop)
	ON_UPDATE_COMMAND_UI(ID_INTERPRETER_STOP, &CMainFrame::OnUpdateInterpreterStop)
	ON_COMMAND(ID_FILE_NEW, &CMainFrame::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
	ON_COMMAND(ID_INTERPRETER_BUILD, &CMainFrame::OnInterpreterBuild)
	ON_COMMAND(ID_INTERPRETER_START, &CMainFrame::OnInterpreterStart)
	ON_COMMAND(ID_INTERPRETER_BUILDANDSTART, &CMainFrame::OnInterpreterBuildandstart)
	ON_UPDATE_COMMAND_UI(ID_INTERPRETER_BUILD, &CMainFrame::OnUpdateInterpreterBuild)
	ON_UPDATE_COMMAND_UI(ID_INTERPRETER_START, &CMainFrame::OnUpdateInterpreterStart)
	ON_UPDATE_COMMAND_UI(ID_INTERPRETER_BUILDANDSTART, &CMainFrame::OnUpdateInterpreterBuildandstart)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸
ULONG_PTR	gdiplusToken;

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_WINDOWS_7);
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	GdiplusStartupInput gdiplusStartInput;

	if (::GdiplusStartup(&gdiplusToken, &gdiplusStartInput, NULL) != Ok)
	{
		AfxMessageBox(_T("ERROR : Failed to Initialize GDI+ Libary!"));
		return FALSE;
	}

	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("메뉴 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// 메뉴 모음을 활성화해도 포커스가 이동하지 않게 합니다.
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// 사용자 정의 도구 모음 작업을 허용합니다.
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	// TODO: 도구 모음 및 메뉴 모음을 도킹할 수 없게 하려면 이 다섯 줄을 삭제하십시오.
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// Visual Studio 2005 스타일 도킹 창 동작을 활성화합니다.
	CDockingManager::SetDockingMode(DT_SMART);
	// Visual Studio 2005 스타일 도킹 창 자동 숨김 동작을 활성화합니다.
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	// 보관된 값에 따라 비주얼 관리자 및 스타일을 설정합니다.
	OnApplicationLook(theApp.m_nAppLook);

	// 도구 모음 및 도킹 창 메뉴 바꾸기를 활성화합니다.
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 빠른(<Alt> 키를 누른 채 끌기) 도구 모음 사용자 지정을 활성화합니다.
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// 사용자 정의 도구 모음 이미지를 로드합니다.
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	bIsStart = FALSE;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.cx = WINDOW_XSIZE;
	cs.cy = WINDOW_YSIZE;

	// //창 크기 조절 기능 비활성화
	//cs.style &= ~WS_THICKFRAME; 
	////창 최대화버튼 비활성화
	//cs.style &= ~WS_MAXIMIZEBOX;

	//제목없음 비활성화.
	cs.style &= ~FWS_ADDTOTITLE;
	if (!CFrameWndEx::PreCreateWindow(cs))
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.


	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 메뉴를 검색합니다. */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp, LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp, lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_xP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_xP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
	// 기본 클래스가 실제 작업을 수행합니다.

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// 모든 사용자 도구 모음에 사용자 지정 단추를 활성화합니다.
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// 1행 2열로 윈도우를 정적 분할한다.
	if (!mainSplittedSection.CreateStatic(this, 1, 3))
		return FALSE;

	// 메인 윈도우의 첫번째 분할 윈도우를 2행 1열로 분할한다.
	if (!firstSplittedSection.CreateStatic(&mainSplittedSection, 2, 1, WS_CHILD | WS_VISIBLE,
		mainSplittedSection.IdFromRowCol(0, 0)))
		return FALSE;

	// 첫번째 분할 윈도우의 1행을 CSymbolTree를 할당한다.
	if (!firstSplittedSection.CreateView(0, 0, RUNTIME_CLASS(CSymbolTree), CSize(250, 260), pContext))
		return FALSE;

	// 첫번째 분할 윈도우의 2행을 CSymbolProperty를 할당한다.
	if (!firstSplittedSection.CreateView(1, 0, RUNTIME_CLASS(CSymbolProperty), CSize(250, 300), pContext))
		return FALSE;

	// 메인 윈도우의 두번째 분할 윈도우에 CObjectFlow를 할당한다.
	if (!mainSplittedSection.CreateView(0, 1, RUNTIME_CLASS(CObjectFlowView), CSize(510, 780), pContext))
		return FALSE;

	// 메인 윈도우의 세번째 분할 윈도우를 3행 1열로 분할한다.
	if (!thirdSplittedSection.CreateStatic(&mainSplittedSection, 3, 1, WS_CHILD | WS_VISIBLE,
		mainSplittedSection.IdFromRowCol(0, 2)))
		return FALSE;

	// 세번째 분할 윈도우의 1행을 CPlay를 할당한다.
	if (!thirdSplittedSection.CreateView(0, 0, RUNTIME_CLASS(CPlayView), CSize(0, 0), pContext))
		return FALSE;

	// 세번째 분할 윈도우의 2행을 CObjectList를 할당한다.
	if (!thirdSplittedSection.CreateView(1, 0, RUNTIME_CLASS(CObjectListView), CSize(250, 260), pContext))
		return FALSE;

	// 세번째 분할 윈도우의 3행을 CObjectProperty를 할당한다.
	if (!thirdSplittedSection.CreateView(2, 0, RUNTIME_CLASS(CObjectPropertyView), CSize(250, 260), pContext))
		return FALSE;

	// 메인 윈도우의 첫번째 분할 윈도우의 X좌표, 최소 X값을 설정한다.
	mainSplittedSection.SetColumnInfo(0, 250, 200);
	mainSplittedSection.SetColumnInfo(1, WINDOW_XSIZE - 400, 0);
	thirdSplittedSection.SetRowInfo(0, 270, 0);
	thirdSplittedSection.SetRowInfo(1, 80, 0);

	symbolTree = dynamic_cast<CSymbolTree*>(firstSplittedSection.GetPane(0, 0));
	symbolProperty = dynamic_cast<CSymbolProperty*>(firstSplittedSection.GetPane(1, 0));
	objectFlow = dynamic_cast<CObjectFlowView*>(mainSplittedSection.GetPane(0, 1));
	play = dynamic_cast<CPlayView*>(thirdSplittedSection.GetPane(0, 0));
	objectList = dynamic_cast<CObjectListView*>(thirdSplittedSection.GetPane(1, 0));
	objectProperty = dynamic_cast<CObjectPropertyView*>(thirdSplittedSection.GetPane(2, 0));


	//return CFrameWndEx::OnCreateClient(lpcs, pContext);
}


void CMainFrame::OnMove(int x, int y)
{
	CFrameWndEx::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	lpMMI->ptMinTrackSize.x = WINDOW_XSIZE;
	lpMMI->ptMinTrackSize.y = WINDOW_YSIZE;

	CFrameWndEx::OnGetMinMaxInfo(lpMMI);
}


void CMainFrame::OnExitSizeMove()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CFrameWndEx::OnExitSizeMove();
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWndEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CRect clientRect;
	GetWindowRect(&clientRect);
	ScreenToClient(clientRect);

	if (bStart && cx != 0)
	{
		INT xSize, xMin;

		firstSplittedSection.SetRowInfo(0, clientRect.bottom - 400, 0);
		firstSplittedSection.GetColumnInfo(0, xSize, xMin);
		mainSplittedSection.SetColumnInfo(1, clientRect.right - 400 - xSize, 0);
	}

	symbolProperty->PropertyResize();
}


void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//CRect clientRect;
	//GetWindowRect(&clientRect);
	//ScreenToClient(clientRect);

	//if (nID == SC_MAXIMIZE)
	//{
	//	firstSplittedSection.SetRowInfo(0, 200, 0);
	//}
	//else if (nID == SC_MINIMIZE)
	//{
	//	firstSplittedSection.SetRowInfo(0, clientRect.bottom - 500, 0);
	//}
	//else if (nID == SC_RESTORE)
	//{
	//	firstSplittedSection.SetRowInfo(0, clientRect.bottom - 500, 0);
	//}

	CFrameWndEx::OnSysCommand(nID, lParam);
}


void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CFrameWndEx::OnPaint()을(를) 호출하지 마십시오.

	mainSplittedSection.RecalcLayout();
	firstSplittedSection.RecalcLayout();
}

void CMainFrame::OnInterpreterStart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (AllocConsole())
	{
		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
		SetConsoleTitleW(_T("FlowStream Console"));
		std::cout << "FlowStream Console DataIO" << std::endl;
	}

	for each (CFlowObject* flowObject in play->objects)
	{
		for each (CObjectFlow* objFlow in objectFlow->objectFlows)
		{
			if (flowObject->objectFlow == objFlow)
			{
				flowObject->PlayLoop();
				break;
			}
		}
	}
	bIsStart = TRUE;
	play->SetTimer(PLAY_DRAWTIME, 1000 / 33, NULL);
}

void CMainFrame::OnInterpreterStop()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	for each (CFlowObject* flowObject in play->objects)
	{
		flowObject->PlayEnd();
	}

	bIsStart = FALSE;

	play->KillTimer(PLAY_DRAWTIME);
	
	FreeConsole();
}



void CMainFrame::OnUpdateInterpreterStart(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(!bIsStart);
}


void CMainFrame::OnUpdateInterpreterStop(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(bIsStart);
}


void CMainFrame::OnFileNew()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CFlowStreamDoc* pDoc = (CFlowStreamDoc*)this->GetActiveDocument();

	CProjectCreation newProjectFolder;

	while (true)
	{
		if (newProjectFolder.DoModal() == IDOK)
		{
			pDoc->projectName = newProjectFolder.projectNameString;
			if (!pDoc->NewProjectFile(newProjectFolder.projectFolderPathString))
			{
				AfxMessageBox(_T("새 프로젝트 생성오류!"));
			}
			else return;
		}
		else
			return;
	}
}


void CMainFrame::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CFileDialog dlg(true, _T("*.json"), NULL, OFN_HIDEREADONLY, _T("FlowStream ProjectFile|Project.json||"), NULL);

	if (dlg.DoModal() == IDOK)
	{
		CFlowStreamDoc* pDoc = (CFlowStreamDoc*)this->GetActiveDocument();

		CString path = dlg.GetFolderPath();
		path += "\\";
		if (pDoc->filePath != path)	//같은 프로젝트 열기 체크.
		{
			pDoc->OnOpenDocument(dlg.GetPathName());
		}
	}
}


void CMainFrame::OnInterpreterBuild()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (AllocConsole())
	{
		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
		SetConsoleTitleW(_T("FlowStream Console"));
		std::cout << "FlowStream Console Interpreter Debug Log" << std::endl;
	}

	for each (CFlowObject* flowObject in play->objects)
	{
		for each (CObjectFlow* objFlow in objectFlow->objectFlows)
		{
			if (flowObject->objectFlow == objFlow)
			{
				flowObject->objectFlow->Interpreter->Interpret(flowObject);
				break;
			}
		}
	}
	std::cout << "FlowStream Console : Build End!" << std::endl;
	FreeConsole();
}


void CMainFrame::OnUpdateInterpreterBuild(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(!bIsStart);
}


void CMainFrame::OnInterpreterBuildandstart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (AllocConsole())
	{
		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
		SetConsoleTitleW(_T("FlowStream Console"));
		std::cout << "FlowStream Console DataIO" << std::endl;
	}

	for each (CFlowObject* flowObject in play->objects)
	{
		for each (CObjectFlow* objFlow in objectFlow->objectFlows)
		{
			if (flowObject->objectFlow == objFlow)
			{
				flowObject->objectFlow->Interpreter->Interpret(flowObject);
				flowObject->PlayLoop();
				break;
			}
		}
	}
	bIsStart = TRUE;
	play->SetTimer(PLAY_DRAWTIME, 1000 / 33, NULL);
}


void CMainFrame::OnUpdateInterpreterBuildandstart(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(!bIsStart);
}

