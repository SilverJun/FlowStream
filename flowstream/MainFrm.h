
// MainFrm.h : CMainFrame Ŭ������ �������̽�
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
	
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:
	//
	CLockSplitterView		mainSplittedSection;
	// ù ��° ���� ������ (CSymbolTree, CSymbolProperty) 
	CLockSplitterView		firstSplittedSection;
	CLockSplitterView		secondSplittedSection;
	CLockSplitterView		thirdSplittedSection;

	// �ɺ� Ʈ�� �� ������
	CSymbolTree*				symbolTree;
	// �ɺ� �Ӽ� �� ������
	CSymbolProperty*			symbolProperty;
	// ������Ʈ �帧 �� ������
	CObjectFlowView*			objectFlow;
	// �÷��� �� ������
	CPlayView*						play;
	// ������Ʈ ����Ʈ �� ������
	CObjectListView*			objectList;
	// ������Ʈ �Ӽ� �� ������
	CObjectPropertyView*	objectProperty;

	BOOL	bIsStart;

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

	

// ������ �޽��� �� �Լ�
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


