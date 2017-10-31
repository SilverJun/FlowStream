// ConditionCheck.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "ConditionCheck.h"
#include "afxdialogex.h"

// CConditionCheck ��ȭ �����Դϴ�.

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


// CConditionCheck �޽��� ó�����Դϴ�.
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
		// ���� ���� �����Ѵ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CConditionCheck::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);


	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CConditionCheck::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CConditionCheck::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CConditionCheck::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData();

	label = _T("");

	if (firstCheck)
	{
		label += firstVariable;
	}
	else
	{
		label += firstValue;

		// �Ҵ簪�� 8�ڸ�����
		if (firstValue.GetLength() >= 8)
		{
			AfxMessageBox(_T("�Ҵ�� ���� Ȯ�����ּ���. (�ִ� 8�ڸ�)"));

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

		// �Ҵ簪�� 8�ڸ�����
		if (secondValue.GetLength() >= 8)
		{
			AfxMessageBox(_T("�Ҵ�� ���� Ȯ�����ּ���. (�ִ� 8�ڸ�)"));

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateActivate();
}


void CConditionCheck::OnBnClickedConditionCheckSecond()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateActivate();
}


BOOL CConditionCheck::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CFCDialog::PreTranslateMessage(pMsg);
}


HBRUSH CConditionCheck::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFCDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.

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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	::SetWindowTheme(GetDlgItem(IDC_CONDITION_CHECK_FIRST)->GetSafeHwnd(), TEXT(""), TEXT(""));
	::SetWindowTheme(GetDlgItem(IDC_CONDITION_CHECK_SECOND)->GetSafeHwnd(), TEXT(""), TEXT(""));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
