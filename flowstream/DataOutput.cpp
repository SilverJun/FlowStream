// DataOutput.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "DataOutput.h"
#include "afxdialogex.h"


// CDataOutput 대화 상자입니다.

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


// CDataOutput 메시지 처리기입니다.


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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CFCDialog::PreTranslateMessage(pMsg);
}


void CDataOutput::OnBnClickedButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
