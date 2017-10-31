#pragma once
#include "afxwin.h"


// CDataInput ��ȭ �����Դϴ�.

class CDataInput : public CFCDialog
{
	DECLARE_DYNAMIC(CDataInput)

public:
	CDataInput(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDataInput();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Input };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// ��ȭ���ڿ� ����� �ɺ�
	CSymbol*	symbol;
	CComboBox Variable;
	CString VariableName;

	BOOL Initialize(CSymbol*symbol);

	VOID	UpdateProperty();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton();
};
