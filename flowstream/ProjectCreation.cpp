// ProjectCreation.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "FlowStream.h"
#include "ProjectCreation.h"
#include "afxdialogex.h"


// CProjectCreation 대화 상자입니다.

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


// CProjectCreation 메시지 처리기입니다.


BOOL CProjectCreation::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	projectFolderPath.EnableFolderBrowseButton();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
