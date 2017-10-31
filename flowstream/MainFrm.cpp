
// MainFrm.cpp : CMainFrame Ŭ������ ����
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
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/�Ҹ�
ULONG_PTR	gdiplusToken;

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
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
		TRACE0("�޴� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// �޴� ������ Ȱ��ȭ�ص� ��Ŀ���� �̵����� �ʰ� �մϴ�.
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// ����� ���� ���� ���� �۾��� ����մϴ�.
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	// TODO: ���� ���� �� �޴� ������ ��ŷ�� �� ���� �Ϸ��� �� �ټ� ���� �����Ͻʽÿ�.
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// Visual Studio 2005 ��Ÿ�� ��ŷ â ������ Ȱ��ȭ�մϴ�.
	CDockingManager::SetDockingMode(DT_SMART);
	// Visual Studio 2005 ��Ÿ�� ��ŷ â �ڵ� ���� ������ Ȱ��ȭ�մϴ�.
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	// ������ ���� ���� ���־� ������ �� ��Ÿ���� �����մϴ�.
	OnApplicationLook(theApp.m_nAppLook);

	// ���� ���� �� ��ŷ â �޴� �ٲٱ⸦ Ȱ��ȭ�մϴ�.
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ����(<Alt> Ű�� ���� ä ����) ���� ���� ����� ������ Ȱ��ȭ�մϴ�.
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// ����� ���� ���� ���� �̹����� �ε��մϴ�.
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

	// //â ũ�� ���� ��� ��Ȱ��ȭ
	//cs.style &= ~WS_THICKFRAME; 
	////â �ִ�ȭ��ư ��Ȱ��ȭ
	//cs.style &= ~WS_MAXIMIZEBOX;

	//������� ��Ȱ��ȭ.
	cs.style &= ~FWS_ADDTOTITLE;
	if (!CFrameWndEx::PreCreateWindow(cs))
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.


	return TRUE;
}

// CMainFrame ����

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


// CMainFrame �޽��� ó����

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* �޴��� �˻��մϴ�. */);
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
	// �⺻ Ŭ������ ���� �۾��� �����մϴ�.

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// ��� ����� ���� ������ ����� ���� ���߸� Ȱ��ȭ�մϴ�.
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	// 1�� 2���� �����츦 ���� �����Ѵ�.
	if (!mainSplittedSection.CreateStatic(this, 1, 3))
		return FALSE;

	// ���� �������� ù��° ���� �����츦 2�� 1���� �����Ѵ�.
	if (!firstSplittedSection.CreateStatic(&mainSplittedSection, 2, 1, WS_CHILD | WS_VISIBLE,
		mainSplittedSection.IdFromRowCol(0, 0)))
		return FALSE;

	// ù��° ���� �������� 1���� CSymbolTree�� �Ҵ��Ѵ�.
	if (!firstSplittedSection.CreateView(0, 0, RUNTIME_CLASS(CSymbolTree), CSize(250, 260), pContext))
		return FALSE;

	// ù��° ���� �������� 2���� CSymbolProperty�� �Ҵ��Ѵ�.
	if (!firstSplittedSection.CreateView(1, 0, RUNTIME_CLASS(CSymbolProperty), CSize(250, 300), pContext))
		return FALSE;

	// ���� �������� �ι�° ���� �����쿡 CObjectFlow�� �Ҵ��Ѵ�.
	if (!mainSplittedSection.CreateView(0, 1, RUNTIME_CLASS(CObjectFlowView), CSize(510, 780), pContext))
		return FALSE;

	// ���� �������� ����° ���� �����츦 3�� 1���� �����Ѵ�.
	if (!thirdSplittedSection.CreateStatic(&mainSplittedSection, 3, 1, WS_CHILD | WS_VISIBLE,
		mainSplittedSection.IdFromRowCol(0, 2)))
		return FALSE;

	// ����° ���� �������� 1���� CPlay�� �Ҵ��Ѵ�.
	if (!thirdSplittedSection.CreateView(0, 0, RUNTIME_CLASS(CPlayView), CSize(0, 0), pContext))
		return FALSE;

	// ����° ���� �������� 2���� CObjectList�� �Ҵ��Ѵ�.
	if (!thirdSplittedSection.CreateView(1, 0, RUNTIME_CLASS(CObjectListView), CSize(250, 260), pContext))
		return FALSE;

	// ����° ���� �������� 3���� CObjectProperty�� �Ҵ��Ѵ�.
	if (!thirdSplittedSection.CreateView(2, 0, RUNTIME_CLASS(CObjectPropertyView), CSize(250, 260), pContext))
		return FALSE;

	// ���� �������� ù��° ���� �������� X��ǥ, �ּ� X���� �����Ѵ�.
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	lpMMI->ptMinTrackSize.x = WINDOW_XSIZE;
	lpMMI->ptMinTrackSize.y = WINDOW_YSIZE;

	CFrameWndEx::OnGetMinMaxInfo(lpMMI);
}


void CMainFrame::OnExitSizeMove()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CFrameWndEx::OnExitSizeMove();
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWndEx::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CFrameWndEx::OnPaint()��(��) ȣ������ ���ʽÿ�.

	mainSplittedSection.RecalcLayout();
	firstSplittedSection.RecalcLayout();
}

void CMainFrame::OnInterpreterStart()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(!bIsStart);
}


void CMainFrame::OnUpdateInterpreterStop(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(bIsStart);
}


void CMainFrame::OnFileNew()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CFlowStreamDoc* pDoc = (CFlowStreamDoc*)this->GetActiveDocument();

	CProjectCreation newProjectFolder;

	while (true)
	{
		if (newProjectFolder.DoModal() == IDOK)
		{
			pDoc->projectName = newProjectFolder.projectNameString;
			if (!pDoc->NewProjectFile(newProjectFolder.projectFolderPathString))
			{
				AfxMessageBox(_T("�� ������Ʈ ��������!"));
			}
			else return;
		}
		else
			return;
	}
}


void CMainFrame::OnFileOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CFileDialog dlg(true, _T("*.json"), NULL, OFN_HIDEREADONLY, _T("FlowStream ProjectFile|Project.json||"), NULL);

	if (dlg.DoModal() == IDOK)
	{
		CFlowStreamDoc* pDoc = (CFlowStreamDoc*)this->GetActiveDocument();

		CString path = dlg.GetFolderPath();
		path += "\\";
		if (pDoc->filePath != path)	//���� ������Ʈ ���� üũ.
		{
			pDoc->OnOpenDocument(dlg.GetPathName());
		}
	}
}


void CMainFrame::OnInterpreterBuild()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(!bIsStart);
}


void CMainFrame::OnInterpreterBuildandstart()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(!bIsStart);
}

