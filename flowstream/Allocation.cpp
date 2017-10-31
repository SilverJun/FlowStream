// Allocation.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "Allocation.h"
#include "afxdialogex.h"


// CAllocation 대화 상자입니다.

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


// CAllocation 메시지 처리기입니다.

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString label;

	UpdateData();

	label += variableName;
	
	label += " ";
	
	label += allocationOperator;

	label += " ";

	label += allocationValue;

	// 할당값은 8자리까지
	if (allocationValue.GetLength() >= 8)
	{
		AfxMessageBox(_T("할당될 값을 확인해주세요. (최대 8자리)"));

		return;
	}

	symbol->label = label;

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	mainFrame->objectFlow->Invalidate();

	symbol->ResizeSymbol();
}


BOOL CAllocation::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) 
		return TRUE;

	return CFCDialog::PreTranslateMessage(pMsg);
}
