#pragma once
#include "afxwin.h"

//#include <Ultimate_Toolbox\include\OXCoolComboBox.h>
//#include <OXSkinnedComboBox.h>

// CAllocation ��ȭ �����Դϴ�.

class CAllocation : public CFCDialog
{
	DECLARE_DYNAMIC(CAllocation)

public:
	CAllocation(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAllocation();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Allocation };
#endif

public :
	// ��ȭ���� �ʱ�ȭ
	BOOL		Initialize(CSymbol* symbol);

	// ��ȭ���ڿ� ����� �ɺ�
	CSymbol*	symbol;

public:
	// FCDialog�� ���� ���� �Լ�
	VOID	UpdateProperty();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox		variable;
	CString			variableName;
	CEdit			allocationEdit;
	CString			allocationValue;
	CComboBox		allocationOperatorEdit;
	CString			allocationOperator;
	afx_msg void OnBnClickedButton();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
