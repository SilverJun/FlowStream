// ConditionCheck.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "ConditionCheck.h"
#include "afxdialogex.h"

// CConditionCheck 대화 상자입니다.

IMPLEMENT_DYNAMIC(CConditionCheck, CDialogEx)

CConditionCheck::CConditionCheck(CWnd* pParent /*=NULL*/)
	: CFCDialog(IDD_DIALOG_ConditionCheck, pParent)
	, firstCheck(FALSE)
	, secondCheck(FALSE)
	, firstVariable(_T(""))
	, firstValue(_T(""))
	, secondVariable(_T(""))
	, secondValue(_T(""))
	, compareOperator(_T(""))
{
	
}

CConditionCheck::~CConditionCheck()
{
}

void CConditionCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CONDITION_CHECK_FIRST, firstCheck);
	DDX_Control(pDX, IDC_CONDITION_COMBO_FIRST, firstList);
	DDX_Control(pDX, IDC_CONDITION_EDIT_FIRST, firstEdit);
	DDX_Check(pDX, IDC_CONDITION_CHECK_SECOND, secondCheck);
	DDX_Control(pDX, IDC_CONDITION_COMBO_SECOND, secondList);
	DDX_Control(pDX, IDC_CONDITION_EDIT_SECOND, secondEdit);
	DDX_Control(pDX, IDC_CONDITION_COMBO_OPERATOR, operatorList);
	DDX_CBString(pDX, IDC_CONDITION_COMBO_FIRST, firstVariable);
	DDX_Text(pDX, IDC_CONDITION_EDIT_FIRST, firstValue);
	DDX_CBString(pDX, IDC_CONDITION_COMBO_SECOND, secondVariable);
	DDX_Text(pDX, IDC_CONDITION_EDIT_SECOND, secondValue);
	DDX_CBString(pDX, IDC_CONDITION_COMBO_OPERATOR, compareOperator);
}


BEGIN_MESSAGE_MAP(CConditionCheck, CDialogEx)
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, &CConditionCheck::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CONDITION_CHECK_FIRST, &CConditionCheck::OnBnClickedConditionCheckFirst)
	ON_BN_CLICKED(IDC_CONDITION_CHECK_SECOND, &CConditionCheck::OnBnClickedConditionCheckSecond)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CConditionCheck 메시지 처리기입니다.
//BOOL CConditionCheck::Create(CSymbol* _symbol)
//{
//	return CDialogEx::Create(IDD_DIALOG_ConditionCheck, this);
//}

VOID CConditionCheck::UpdateProperty()
{
	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	UpdateData();

	CString	oldFirstVariable = firstVariable;
	CString	oldSecondVariable = secondVariable;
	INT			selCount = 0;
	INT			firstSelCount = -1, secondSelCount = -1;

	firstList.ResetContent();
	secondList.ResetContent();

	for each (FCVariable* var in mainFrame->objectFlow->selectedObjectFlow->variables)
	{
		// 이전 셀을 유지한다.
		if (var->name == oldFirstVariable)
			firstSelCount = selCount;
		 
		if (var->name == oldSecondVariable)
			secondSelCount = selCount;

		firstList.AddString(var->name);
		secondList.AddString(var->name);

		selCount++;
	}

	firstList.SetCurSel(firstSelCount);
	secondList.SetCurSel(secondSelCount);
}

BOOL CConditionCheck::Initialize(CSymbol* symbol)
{
	operatorList.AddString(_T("<"));
	operatorList.AddString(_T("<="));
	operatorList.AddString(_T(">"));
	operatorList.AddString(_T(">="));
	operatorList.AddString(_T("=="));
	operatorList.AddString(_T("!="));

	UpdateActivate();

	this->symbol = symbol;

	return TRUE;
}

VOID CConditionCheck::UpdateActivate()
{
	UpdateData();

	if (firstCheck)
	{
		firstEdit.EnableWindow(FALSE);
		firstList.EnableWindow(TRUE);
	}
	else
	{
		firstEdit.EnableWindow(TRUE);
		firstList.EnableWindow(FALSE);
	}

	if (secondCheck)
	{
		secondEdit.EnableWindow(FALSE);
		secondList.EnableWindow(TRUE);
	}
	else
	{
		secondEdit.EnableWindow(TRUE);
		secondList.EnableWindow(FALSE);
	}
}

BOOL CConditionCheck::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CConditionCheck::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CConditionCheck::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CConditionCheck::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CConditionCheck::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData();

	label = _T("");

	if (firstCheck)
	{
		label += firstVariable;
	}
	else
	{
		label += firstValue;

		// 할당값은 8자리까지
		if (firstValue.GetLength() >= 8)
		{
			AfxMessageBox(_T("할당될 값을 확인해주세요. (최대 8자리)"));

			return;
		}
	}

	label += " ";
	label += compareOperator;
	label += " ";

	if (secondCheck)
	{
		label += secondVariable;
	}
	else
	{
		label += secondValue;

		// 할당값은 8자리까지
		if (secondValue.GetLength() >= 8)
		{
			AfxMessageBox(_T("할당될 값을 확인해주세요. (최대 8자리)"));

			return;
		}
	}

	symbol->label = label;

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();
	mainFrame->objectFlow->Invalidate();
	
	symbol->ResizeSymbol();
}


void CConditionCheck::OnBnClickedConditionCheckFirst()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateActivate();
}


void CConditionCheck::OnBnClickedConditionCheckSecond()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateActivate();
}


BOOL CConditionCheck::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CFCDialog::PreTranslateMessage(pMsg);
}


HBRUSH CConditionCheck::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFCDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.

	if (pWnd->GetSafeHwnd() == GetDlgItem(IDC_CONDITION_CHECK_FIRST)->GetSafeHwnd())
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,255,255));
	}
	if (pWnd->GetSafeHwnd() == GetDlgItem(IDC_CONDITION_CHECK_SECOND)->GetSafeHwnd())
	{
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
	}

	return hbr;
}


BOOL CConditionCheck::OnInitDialog()
{
	CFCDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	::SetWindowTheme(GetDlgItem(IDC_CONDITION_CHECK_FIRST)->GetSafeHwnd(), TEXT(""), TEXT(""));
	::SetWindowTheme(GetDlgItem(IDC_CONDITION_CHECK_SECOND)->GetSafeHwnd(), TEXT(""), TEXT(""));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
