// DataInput.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "DataInput.h"
#include "afxdialogex.h"


// CDataInput 대화 상자입니다.

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


// CDataInput 메시지 처리기입니다.


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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CFCDialog::PreTranslateMessage(pMsg);
}


void CDataInput::OnBnClickedButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	UpdateData();

	CString label;
	label = _T("input ");
	label += VariableName;

	symbol->label = label;

	mainFrame->objectFlow->Invalidate();

	symbol->ResizeSymbol();
}
