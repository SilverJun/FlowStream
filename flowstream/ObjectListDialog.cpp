// ObjectListDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "ObjectListDialog.h"
#include "afxdialogex.h"


// CObjectListDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CObjectListDialog, CDialogEx)

CObjectListDialog::CObjectListDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_OBJECTCREATE, pParent)
	, objectName(_T(""))
	, xSize(_T(""))
	, ySize(_T(""))
{

}

CObjectListDialog::~CObjectListDialog()
{
}

void CObjectListDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OBJECTNAME, objectName);
	DDV_MaxChars(pDX, objectName, 8);
	DDX_Control(pDX, IDC_EDIT_XSIZE, xSizeControl);
	DDX_Control(pDX, IDC_EDIT_YSIZE, ySizeControl);
	DDX_Text(pDX, IDC_EDIT_XSIZE, xSize);
	DDX_Text(pDX, IDC_EDIT_YSIZE, ySize);
}


BEGIN_MESSAGE_MAP(CObjectListDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CObjectListDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CObjectListDialog 메시지 처리기입니다.



void CObjectListDialog::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CDialogEx::OnOK();
}
