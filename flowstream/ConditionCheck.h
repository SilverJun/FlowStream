#pragma once
#include "afxwin.h"


// CConditionCheck 대화 상자입니다.

const int m_nLineSize = 15;
const int m_nBasic = 95;
const int m_nRepeat = 10;

class CSymbol;

class CConditionCheck : public CFCDialog
{
	DECLARE_DYNAMIC(CConditionCheck)

public:
	CConditionCheck(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CConditionCheck();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ConditionCheck };
#endif

public :
	// 동적 대화상자 생성
	//BOOL		Create(CSymbol* _symbol);

public :
	// 대화상자 초기화
	BOOL		Initialize(CSymbol* symbol);
	// 변수 사용 검사
	VOID		UpdateActivate();

	// 대화상자와 연결된 심볼
	CSymbol*	symbol;

public:
	// FCDialog의 순수 가상 함수
	VOID	UpdateProperty();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	
	//	첫번째 
	BOOL			firstCheck;
	CComboBox		firstList;
	CEdit			firstEdit;
	CString			firstVariable;
	CString			firstValue;
	// 두번째
	BOOL			secondCheck;
	CComboBox		secondList;
	CEdit			secondEdit;
	CString			secondVariable;
	CString			secondValue;
	// 연산자
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
