#pragma once

#include "FCDialog.h"
#include "afxwin.h"

// CDataOutput ��ȭ �����Դϴ�.

class CDataOutput : public CFCDialog
{
	DECLARE_DYNAMIC(CDataOutput)

public:
	CDataOutput(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDataOutput();


// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OUTPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// ��ȭ���ڿ� ����� �ɺ�
	CSymbol*	symbol;
	CEdit Expression;
	CString ExpressionText;

	BOOL Initialize(CSymbol*symbol);

	VOID	UpdateProperty();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton();
};
