#pragma once

// CFCDialog 대화 상자입니다.

//==================================================
// CFCDialog : Dialog들의 공통점을 묶은 클래스
class CFCDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CFCDialog)

public:
	CFCDialog(UINT nIDTemplate, CWnd *pParent);   // 표준 생성자입니다.
	virtual ~CFCDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FCDIALOG };
#endif

public :
	virtual	VOID	UpdateProperty() = 0;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
