// CreateVariable.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "CreateVariable.h"
#include "afxdialogex.h"


// CCreateVariable 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCreateVariable, CFCDialog)

CCreateVariable::CCreateVariable(CWnd* pParent /*=NULL*/)
	: CFCDialog(IDD_DIALOG_CreateVariable, pParent)
	, type(_T(""))
	, name(_T(""))
{

}

CCreateVariable::~CCreateVariable()
{
}

void CCreateVariable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CREATE_COMBO_TYPE, variableType);
	DDX_CBString(pDX, IDC_CREATE_COMBO_TYPE, type);
	DDX_Control(pDX, IDC_CREATE_EDIT_NAME, variableName);
	DDX_Text(pDX, IDC_CREATE_EDIT_NAME, name);
}


BEGIN_MESSAGE_MAP(CCreateVariable, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON, &CCreateVariable::OnBnClickedButton)
END_MESSAGE_MAP()


// CCreateVariable 메시지 처리기입니다.

VOID CCreateVariable::UpdateProperty()
{
	UpdateData();

}

BOOL CCreateVariable::Initialize(CSymbol* symbol)
{
	variableType.AddString(_T("INT"));
	variableType.AddString(_T("FLOAT"));
	variableType.AddString(_T("STRING"));

	this->symbol = symbol;

	variable = new FCVariable;
	variable->bPushed = FALSE;

	return TRUE;
}

void CCreateVariable::OnBnClickedButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	UpdateData();

	switch (variableType.GetCurSel())
	{
	case 0:
		variable->type = eFCVariableType::eVariableType_INT;

		break;

	case 1:
		variable->type = eFCVariableType::eVariableType_FLOAT;

		break;

	case 2:
		variable->type = eFCVariableType::eVariableType_STRING;

		break;

	default:
		AfxMessageBox(_T("변수의 자료형이 선택되지 않았습니다."));

		return;
	}

	// 변수는 8글자로 제한.
	if (name.GetLength() == 0 || name.GetLength() > 8)
	{
		AfxMessageBox(_T("변수의 이름이 잘못됬습니다."));

		return;
	}

	variable->name = name;

	if (!variable->bPushed)
	{
		// 겹친 이름이 있을 경우 
		if (!mainFrame->objectFlow->selectedObjectFlow->PushVariable(variable))
		{
			AfxMessageBox(_T("이미 이 이름을 가진 변수가 있습니다."));

			return;
		}

		variable->bPushed = TRUE;
	}

	CString label;

	label += type;

	label += " ";

	label += name;

	symbol->label = label;

	symbol->bVariableFlag = TRUE;

	symbol->variable = variable;

	mainFrame->objectFlow->Invalidate();

	symbol->ResizeSymbol();
}


BOOL CCreateVariable::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CFCDialog::PreTranslateMessage(pMsg);
}
