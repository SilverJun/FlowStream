// FCDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "FCDialog.h"
#include "afxdialogex.h"


// CFCDialog ��ȭ �����Դϴ�.

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


// CFCDialog �޽��� ó�����Դϴ�.
