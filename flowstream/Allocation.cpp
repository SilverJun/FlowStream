// Allocation.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "Allocation.h"
#include "afxdialogex.h"


// CAllocation ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAllocation, CDialogEx)

CAllocation::CAllocation(CWnd* pParent /*=NULL*/)
	: CFCDialog(IDD_DIALOG_Allocation, pParent)
	, variableName(_T(""))
	, allocationValue(_T(""))
	, allocationOperator(_T(""))
{

}

CAllocation::~CAllocation()
{
}

void CAllocation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALLOCATION_COMBO_VARIABLE, variable);
	DDX_CBString(pDX, IDC_ALLOCATION_COMBO_VARIABLE, variableName);
	DDX_Control(pDX, IDC_ALLOCATION_EDIT, allocationEdit);
	DDX_Text(pDX, IDC_ALLOCATION_EDIT, allocationValue);
	DDX_Control(pDX, IDC_ALLOCATION_COMBO_OPERATOR, allocationOperatorEdit);
	DDX_CBString(pDX, IDC_ALLOCATION_COMBO_OPERATOR, allocationOperator);
}


BEGIN_MESSAGE_MAP(CAllocation, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON, &CAllocation::OnBnClickedButton)
END_MESSAGE_MAP()


// CAllocation �޽��� ó�����Դϴ�.

VOID CAllocation::UpdateProperty()
{
	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();
	
	UpdateData();

	variable.ResetContent();

	for each (FCVariable* var in mainFrame->objectFlow->selectedObjectFlow->variables)
	{
		variable.AddString(var->name);
	}
}

BOOL CAllocation::Initialize(CSymbol* symbol)
{
	allocationOperatorEdit.AddString(_T("="));
	allocationOperatorEdit.AddString(_T("+="));
	allocationOperatorEdit.AddString(_T("-="));
	allocationOperatorEdit.AddString(_T("*="));
	allocationOperatorEdit.AddString(_T("/="));

	this->symbol = symbol;

	return TRUE;
}

void CAllocation::OnBnClickedButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString label;

	UpdateData();

	label += variableName;
	
	label += " ";
	
	label += allocationOperator;

	label += " ";

	label += allocationValue;

	// �Ҵ簪�� 8�ڸ�����
	if (allocationValue.GetLength() >= 8)
	{
		AfxMessageBox(_T("�Ҵ�� ���� Ȯ�����ּ���. (�ִ� 8�ڸ�)"));

		return;
	}

	symbol->label = label;

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	mainFrame->objectFlow->Invalidate();

	symbol->ResizeSymbol();
}


BOOL CAllocation::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) 
		return TRUE;

	return CFCDialog::PreTranslateMessage(pMsg);
}
