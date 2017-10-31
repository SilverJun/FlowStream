#pragma once

#include "FCDialog.h"
#include "afxwin.h"

// CDataOutput 대화 상자입니다.

class CDataOutput : public CFCDialog
{
	DECLARE_DYNAMIC(CDataOutput)

public:
	CDataOutput(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDataOutput();


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OUTPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 대화상자와 연결된 심볼
	CSymbol*	symbol;
	CEdit Expression;
	CString ExpressionText;

	BOOL Initialize(CSymbol*symbol);

	VOID	UpdateProperty();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton();
};
