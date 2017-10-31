// FCDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "FCDialog.h"
#include "afxdialogex.h"


// CFCDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFCDialog, CDialogEx)

CFCDialog::CFCDialog(UINT nIDTemplate, CWnd *pParent )
	: CDialogEx(nIDTemplate, pParent)
{
	this->SetBackgroundColor(RGB(80, 80, 80));
}

CFCDialog::~CFCDialog()
{
}

void CFCDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFCDialog, CDialogEx)
END_MESSAGE_MAP()


// CFCDialog 메시지 처리기입니다.
