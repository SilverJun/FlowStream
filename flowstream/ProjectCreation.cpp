// ProjectCreation.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "ProjectCreation.h"
#include "afxdialogex.h"


// CProjectCreation ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CProjectCreation, CDialogEx)

CProjectCreation::CProjectCreation(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PROJ_NEW, pParent)
{
	
}

CProjectCreation::~CProjectCreation()
{
}

void CProjectCreation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PROJ_NAME, projectName);
	DDX_Control(pDX, IDC_PROJ_FOLDER_EDIT, projectFolderPath);
	DDX_Text(pDX, IDC_EDIT_PROJ_NAME, projectNameString);
	DDX_Text(pDX, IDC_PROJ_FOLDER_EDIT, projectFolderPathString);
}


BEGIN_MESSAGE_MAP(CProjectCreation, CDialogEx)
END_MESSAGE_MAP()


// CProjectCreation �޽��� ó�����Դϴ�.


BOOL CProjectCreation::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	projectFolderPath.EnableFolderBrowseButton();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
