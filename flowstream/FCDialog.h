#pragma once

// CFCDialog ��ȭ �����Դϴ�.

//==================================================
// CFCDialog : Dialog���� �������� ���� Ŭ����
class CFCDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CFCDialog)

public:
	CFCDialog(UINT nIDTemplate, CWnd *pParent);   // ǥ�� �������Դϴ�.
	virtual ~CFCDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FCDIALOG };
#endif

public :
	virtual	VOID	UpdateProperty() = 0;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
