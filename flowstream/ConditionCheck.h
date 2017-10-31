#pragma once
#include "afxwin.h"


// CConditionCheck ��ȭ �����Դϴ�.

const int m_nLineSize = 15;
const int m_nBasic = 95;
const int m_nRepeat = 10;

class CSymbol;

class CConditionCheck : public CFCDialog
{
	DECLARE_DYNAMIC(CConditionCheck)

public:
	CConditionCheck(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CConditionCheck();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ConditionCheck };
#endif

public :
	// ���� ��ȭ���� ����
	//BOOL		Create(CSymbol* _symbol);

public :
	// ��ȭ���� �ʱ�ȭ
	BOOL		Initialize(CSymbol* symbol);
	// ���� ��� �˻�
	VOID		UpdateActivate();

	// ��ȭ���ڿ� ����� �ɺ�
	CSymbol*	symbol;

public:
	// FCDialog�� ���� ���� �Լ�
	VOID	UpdateProperty();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	
	//	ù��° 
	BOOL			firstCheck;
	CComboBox		firstList;
	CEdit			firstEdit;
	CString			firstVariable;
	CString			firstValue;
	// �ι�°
	BOOL			secondCheck;
	CComboBox		secondList;
	CEdit			secondEdit;
	CString			secondVariable;
	CString			secondValue;
	// ������
	CComboBox		operatorList;
	CString			compareOperator;

	CString			label;

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedConditionCheckFirst();
	afx_msg void OnBnClickedConditionCheckSecond();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
};
