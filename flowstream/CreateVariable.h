#pragma once
#include "afxwin.h"

enum eFCVariableType
{
	eVariableType_INT,
	eVariableType_FLOAT,
	eVariableType_STRING
};

// �����ֱ�� ����, ���� ������ �ƴ�
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

// CCreateVariable ��ȭ �����Դϴ�.

class CCreateVariable : public CFCDialog
{
	DECLARE_DYNAMIC(CCreateVariable)

public:
	CCreateVariable(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCreateVariable();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CreateVariable };
#endif

public :
	// ��ȭ���� �ʱ�ȭ
	BOOL		Initialize(CSymbol* symbol);


	// ��ȭ���ڿ� ����� �ɺ�
	CSymbol*		symbol;
	// ��ȭ���ڿ� ����� ����
	FCVariable*	variable;

public :
	// FCDialog�� ���� ���� �Լ�
	VOID	UpdateProperty();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox	variableType;
	CString			type;
	CEdit				variableName;
	CString			name;
	afx_msg void OnBnClickedButton();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
