// DataOutput.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "DataOutput.h"
#include "afxdialogex.h"


// CDataOutput ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDataOutput, CFCDialog)

CDataOutput::CDataOutput(CWnd* pParent /*=NULL*/)
	: CFCDialog(IDD_DIALOG_OUTPUT, pParent)
	, ExpressionText(_T(""))
{

}

CDataOutput::~CDataOutput()
{
}

void CDataOutput::DoDataExchange(CDataExchange* pDX)
{
	CFCDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, Expression);
	DDX_Text(pDX, IDC_EDIT_OUTPUT, ExpressionText);
}


BEGIN_MESSAGE_MAP(CDataOutput, CFCDialog)
	ON_BN_CLICKED(IDC_BUTTON, &CDataOutput::OnBnClickedButton)
END_MESSAGE_MAP()


// CDataOutput �޽��� ó�����Դϴ�.


BOOL CDataOutput::Initialize(CSymbol * symbol)
{
	this->symbol = symbol;
	return TRUE;
}

VOID CDataOutput::UpdateProperty()
{
	UpdateData();
}

BOOL CDataOutput::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CFCDialog::PreTranslateMessage(pMsg);
}


void CDataOutput::OnBnClickedButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	UpdateData();

	CString label;

	label = _T("output (");
	label += ExpressionText;
	label += _T(")");

	symbol->label = label;

	mainFrame->objectFlow->Invalidate();

	symbol->ResizeSymbol();
}
