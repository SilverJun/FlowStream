#pragma once
#include "afxwin.h"

enum eFCVariableType
{
	eVariableType_INT,
	eVariableType_FLOAT,
	eVariableType_STRING
};

// 보여주기용 변수, 실제 변수가 아님
typedef struct _FCVariable
{
	CString					name;
	CString					value;
	eFCVariableType			type;
	BOOL					bPushed;
	INT*					intValue = nullptr;
	FLOAT*					floatValue = nullptr;
	std::string*			stringValue = nullptr;
} FCVariable;

// CCreateVariable 대화 상자입니다.

class CCreateVariable : public CFCDialog
{
	DECLARE_DYNAMIC(CCreateVariable)

public:
	CCreateVariable(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCreateVariable();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CreateVariable };
#endif

public :
	// 대화상자 초기화
	BOOL		Initialize(CSymbol* symbol);


	// 대화상자와 연결된 심볼
	CSymbol*		symbol;
	// 대화상자와 연결된 변수
	FCVariable*	variable;

public :
	// FCDialog의 순수 가상 함수
	VOID	UpdateProperty();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox	variableType;
	CString			type;
	CEdit				variableName;
	CString			name;
	afx_msg void OnBnClickedButton();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
