#pragma once
#include "afxwin.h"


// CObjectListDialog ��ȭ �����Դϴ�.

class CObjectListDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CObjectListDialog)

public:
	CObjectListDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CObjectListDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OBJECTCREATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString objectName;
	CEdit xSizeControl;
	CEdit ySizeControl;
	afx_msg void OnBnClickedOk();
	CString xSize;
	CString ySize;
};
