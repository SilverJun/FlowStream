// CreateVariable.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "CreateVariable.h"
#include "afxdialogex.h"


// CCreateVariable ��ȭ �����Դϴ�.

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


// CCreateVariable �޽��� ó�����Դϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
		AfxMessageBox(_T("������ �ڷ����� ���õ��� �ʾҽ��ϴ�."));

		return;
	}

	// ������ 8���ڷ� ����.
	if (name.GetLength() == 0 || name.GetLength() > 8)
	{
		AfxMessageBox(_T("������ �̸��� �߸�����ϴ�."));

		return;
	}

	variable->name = name;

	if (!variable->bPushed)
	{
		// ��ģ �̸��� ���� ��� 
		if (!mainFrame->objectFlow->selectedObjectFlow->PushVariable(variable))
		{
			AfxMessageBox(_T("�̹� �� �̸��� ���� ������ �ֽ��ϴ�."));

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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CFCDialog::PreTranslateMessage(pMsg);
}
