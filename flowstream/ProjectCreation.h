#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


// CProjectCreation 대화 상자입니다.

class CProjectCreation : public CDialogEx
{
	DECLARE_DYNAMIC(CProjectCreation)

public:
	CProjectCreation(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CProjectCreation();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROJ_NEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit projectName;
	CString projectNameString;
	CMFCEditBrowseCtrl projectFolderPath;
	CString projectFolderPathString;
	virtual BOOL OnInitDialog();
};
