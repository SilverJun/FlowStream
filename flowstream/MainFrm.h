
// MainFrm.h : CMainFrame 클래스의 인터페이스
//

#pragma once

#include "LockSpliterView.h"

#include "SymbolTree.h"
#include "SymbolProperty.h"
#include "ObjectFlowView.h"
#include "ObjectListView.h"
#include "ObjectPropertyView.h"
#include "PlayView.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:
	//
	CLockSplitterView		mainSplittedSection;
	// 첫 번째 분할 윈도우 (CSymbolTree, CSymbolProperty) 
	CLockSplitterView		firstSplittedSection;
	CLockSplitterView		secondSplittedSection;
	CLockSplitterView		thirdSplittedSection;

	// 심볼 트리 뷰 포인터
	CSymbolTree*				symbolTree;
	// 심볼 속성 뷰 포인터
	CSymbolProperty*			symbolProperty;
	// 오브젝트 흐름 뷰 포인터
	CObjectFlowView*			objectFlow;
	// 플레이 뷰 포인터
	CPlayView*						play;
	// 오브젝트 리스트 뷰 포인터
	CObjectListView*			objectList;
	// 오브젝트 속성 뷰 포인터
	CObjectPropertyView*	objectProperty;

	BOOL	bIsStart;

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

	

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnMove(int x, int y);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnExitSizeMove();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();

//	afx_msg void OnInterpreterStart();
	afx_msg void OnInterpreterStop();
//	afx_msg void OnUpdateInterpreterStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInterpreterStop(CCmdUI *pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
//	afx_msg void OnInterpreterBuild();
//	afx_msg void OnUpdateInterpreterBuild(CCmdUI *pCmdUI);
//	afx_msg void OnInterpreterBuildandstart();
//	afx_msg void OnUpdateInterpreterBuildandstart(CCmdUI *pCmdUI);
	afx_msg void OnInterpreterBuild();
	afx_msg void OnInterpreterStart();
	afx_msg void OnInterpreterBuildandstart();
	afx_msg void OnUpdateInterpreterBuild(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInterpreterStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInterpreterBuildandstart(CCmdUI *pCmdUI);
};


