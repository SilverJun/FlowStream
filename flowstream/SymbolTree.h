#pragma once


// CSymbolTree 뷰입니다.

//=========================================
// CSymbolTree : 심볼을 생성을 담당할 TreeCtrl을 관리할 클래스
class CSymbolTree : public CTreeView
{
	DECLARE_DYNCREATE(CSymbolTree)

protected:
	CSymbolTree();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CSymbolTree();

public :
	// 사용자가 작업을 하기 위해 새로 선택한 상태인가
	bool		bSelected;
	// 처음 실행 시 심볼 생성 처리를 안하기 위해
	bool		bStartFlag;

	// 심볼 트리 아이템
	HTREEITEM hSymbols;
	// 심볼의 if 아이템
	HTREEITEM	hIf;
	// 심볼의 set 아이템
	HTREEITEM hSet;
	// 심볼의 print 아이템
	HTREEITEM hPrint;
	// 심볼의 create 아이템
	HTREEITEM hCreate;
	// 심볼의 while 아이템
	HTREEITEM hWhile;
	// 심볼의 input 아이템
	HTREEITEM hInput;
	// 심볼의 output 아이템
	HTREEITEM hOutput;

	// 라인 트리 아이템
	HTREEITEM hLines;
	// 보통 라인 트리 아이템
	HTREEITEM hLine;
	// 거짓 라인 트리 아이템
	HTREEITEM hTrueLine;
	// 참 라인 트리 아이템
	HTREEITEM hFalseLine;

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSingleExpand(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
//	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
//	virtual void OnDraw(CDC* /*pDC*/);
};


