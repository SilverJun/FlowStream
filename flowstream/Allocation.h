#pragma once
#include "afxwin.h"

//#include <Ultimate_Toolbox\include\OXCoolComboBox.h>
//#include <OXSkinnedComboBox.h>

// CAllocation 대화 상자입니다.

class CAllocation : public CFCDialog
{
	DECLARE_DYNAMIC(CAllocation)

public:
	CAllocation(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAllocation();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Allocation };
#endif

public :
	// 대화상자 초기화
	BOOL		Initialize(CSymbol* symbol);

	// 대화상자와 연결된 심볼
	CSymbol*	symbol;

public:
	// FCDialog의 순수 가상 함수
	VOID	UpdateProperty();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
