#pragma once
#include "afxwin.h"


// CObjectListDialog 대화 상자입니다.

class CObjectListDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CObjectListDialog)

public:
	CObjectListDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CObjectListDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OBJECTCREATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString objectName;
	CEdit xSizeControl;
	CEdit ySizeControl;
	afx_msg void OnBnClickedOk();
	CString xSize;
	CString ySize;
};
