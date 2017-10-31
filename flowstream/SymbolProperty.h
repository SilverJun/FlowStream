#pragma once

// CSymbolProperty ���Դϴ�.
#define EDIT_ID	40100

#include "FCDialog.h"

#include "ConditionCheck.h"
#include "CreateVariable.h"
#include "Allocation.h"
#include "DataInput.h"
#include "DataOutput.h"
 
class CSymbol;

typedef struct PropertyUI
{
	CSymbol*		symbol;
	CFCDialog*	dialog;
} PropertyEX;

class CSymbolProperty : public CView
{
	DECLARE_DYNCREATE(CSymbolProperty)

protected:
	CSymbolProperty();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CSymbolProperty();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public :
	std::vector<PropertyEX*> propertys;

	// �ɺ� �Ӽ�â�� �����Ѵ�.
	VOID	PushProperty(INT dialogIndex, CSymbol* symbol);
	// �ɺ� �Ӽ�â�� �ٲ۴�.
	VOID	PropertyChange(CSymbol* symbol);
	// �ɺ� ����â�� ������Ʈ�Ѵ�.
	VOID	PropertyUpdate(CSymbol* symbol);
	// �ɺ� ����â�� ũ�⸦ �������Ѵ�.
	VOID	PropertyResize();
	// �ɺ� ����â�� �����Ѵ�.
	VOID	PropertyDelete(CSymbol*	 symbol);


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


