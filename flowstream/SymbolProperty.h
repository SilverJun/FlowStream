#pragma once

// CSymbolProperty 뷰입니다.
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
	CSymbolProperty();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CSymbolProperty();

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public :
	std::vector<PropertyEX*> propertys;

	// 심볼 속성창을 생성한다.
	VOID	PushProperty(INT dialogIndex, CSymbol* symbol);
	// 심볼 속성창을 바꾼다.
	VOID	PropertyChange(CSymbol* symbol);
	// 심볼 생성창을 업데이트한다.
	VOID	PropertyUpdate(CSymbol* symbol);
	// 심볼 생성창의 크기를 재조정한다.
	VOID	PropertyResize();
	// 심볼 생성창을 제거한다.
	VOID	PropertyDelete(CSymbol*	 symbol);


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


