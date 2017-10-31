#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


// CProjectCreation ��ȭ �����Դϴ�.

class CProjectCreation : public CDialogEx
{
	DECLARE_DYNAMIC(CProjectCreation)

public:
	CProjectCreation(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CProjectCreation();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROJ_NEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit projectName;
	CString projectNameString;
	CMFCEditBrowseCtrl projectFolderPath;
	CString projectFolderPathString;
	virtual BOOL OnInitDialog();
};
