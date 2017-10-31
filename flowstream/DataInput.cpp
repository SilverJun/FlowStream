// DataInput.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "DataInput.h"
#include "afxdialogex.h"


// CDataInput ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDataInput, CFCDialog)

CDataInput::CDataInput(CWnd* pParent /*=NULL*/)
	: CFCDialog(IDD_DIALOG_Input, pParent)
	, VariableName(_T(""))
{

}

CDataInput::~CDataInput()
{
}

void CDataInput::DoDataExchange(CDataExchange* pDX)
{
	CFCDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_VARIABLE, Variable);
	DDX_CBString(pDX, IDC_COMBO_VARIABLE, VariableName);
}


BEGIN_MESSAGE_MAP(CDataInput, CFCDialog)
	ON_BN_CLICKED(IDC_BUTTON, &CDataInput::OnBnClickedButton)
END_MESSAGE_MAP()


// CDataInput �޽��� ó�����Դϴ�.


BOOL CDataInput::Initialize(CSymbol * symbol)
{
	this->symbol = symbol;
	return TRUE;
}

VOID CDataInput::UpdateProperty()
{
	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	UpdateData();

	Variable.ResetContent();

	for each (FCVariable* var in mainFrame->objectFlow->selectedObjectFlow->variables)
	{
		Variable.AddString(var->name);
	}
}

BOOL CDataInput::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CFCDialog::PreTranslateMessage(pMsg);
}


void CDataInput::OnBnClickedButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	UpdateData();

	CString label;
	label = _T("input ");
	label += VariableName;

	symbol->label = label;

	mainFrame->objectFlow->Invalidate();

	symbol->ResizeSymbol();
}
