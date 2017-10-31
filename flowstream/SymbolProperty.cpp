// SymbolProperty.cpp : 구현 파일입니다.
//

#include "stdAFX.h"
#include "FlowStream.h"
#include "SymbolProperty.h"
#include "Symbol.h"

extern BOOL	bStart;

// CSymbolProperty

IMPLEMENT_DYNCREATE(CSymbolProperty, CView)

CSymbolProperty::CSymbolProperty()
{

}

CSymbolProperty::~CSymbolProperty()
{
}

BEGIN_MESSAGE_MAP(CSymbolProperty, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CSymbolProperty 그리기입니다.

void CSymbolProperty::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.

	CRect RectClient;
	GetClientRect(&RectClient);

	pDC->FillSolidRect(&RectClient, RGB(80, 80, 80));
}


// CSymbolProperty 진단입니다.

#ifdef _DEBUG
void CSymbolProperty::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CSymbolProperty::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSymbolProperty 메시지 처리기입니다.


int CSymbolProperty::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	
	//conditionCheck = new CConditionCheck();

	//conditionCheck->Create(IDD_DIALOG_ConditionCheck, this);
	//conditionCheck->ShowWindow(SW_SHOW);

	//conditionCheck->ShowWindow(SW_HIDE);

	return 0;
}

VOID CSymbolProperty::PushProperty(INT dialogIndex, CSymbol* symbol)
{
	PropertyEX* pEX = new PropertyEX;

	CConditionCheck* conditionCheck = new CConditionCheck();
	CCreateVariable* createVariable = new CCreateVariable();
	CAllocation* allocation = new CAllocation();
	CDataInput* dataInput = new CDataInput();
	CDataOutput* dataOutput = new CDataOutput();

	CRect rt;
	GetClientRect(&rt);

	switch (dialogIndex)
	{
	case 0 :
		conditionCheck->Create(IDD_DIALOG_ConditionCheck, this);
		conditionCheck->Initialize(symbol);
		conditionCheck->SetWindowPos(NULL, rt.left, rt.top, rt.right, rt.bottom, SWP_NOZORDER);

		pEX->dialog = dynamic_cast<CFCDialog*>(conditionCheck);

		break;

	case 1:
		createVariable->Create(IDD_DIALOG_CreateVariable, this);
		createVariable->Initialize(symbol);
		createVariable->SetWindowPos(NULL, rt.left, rt.top, rt.right, rt.bottom, SWP_NOZORDER);

		pEX->dialog = dynamic_cast<CFCDialog*>(createVariable);

		break;

	case 2:
		allocation->Create(IDD_DIALOG_Allocation, this);
		allocation->Initialize(symbol);
		allocation->SetWindowPos(NULL, rt.left, rt.top, rt.right, rt.bottom, SWP_NOZORDER);

		pEX->dialog = dynamic_cast<CFCDialog*>(allocation);

		break;
	case 3:
		dataInput->Create(IDD_DIALOG_Input, this);
		dataInput->Initialize(symbol);
		dataInput->SetWindowPos(NULL, rt.left, rt.top, rt.right, rt.bottom, SWP_NOZORDER);

		pEX->dialog = dynamic_cast<CFCDialog*>(dataInput);

		break;
	case 4:
		dataOutput->Create(IDD_DIALOG_OUTPUT, this);
		dataOutput->Initialize(symbol);
		dataOutput->SetWindowPos(NULL, rt.left, rt.top, rt.right, rt.bottom, SWP_NOZORDER);

		pEX->dialog = dynamic_cast<CFCDialog*>(dataOutput);

		break;
	}

	symbol->dialog = pEX->dialog;
	pEX->symbol = symbol;

	propertys.push_back(pEX);
}

VOID CSymbolProperty::PropertyChange(CSymbol* symbol)
{
	for each (PropertyEX* pEX in propertys)
	{
		if (pEX->symbol == symbol)
		{
			pEX->dialog->ShowWindow(SW_SHOW);
		}
		else
		{
			pEX->dialog->ShowWindow(SW_HIDE);
		}
	}
}

VOID CSymbolProperty::PropertyUpdate(CSymbol* symbol)
{
	for each (PropertyEX* pEX in propertys)
	{
		if (pEX->symbol == symbol)
		{
			pEX->dialog->UpdateProperty();
		}
	}
}

VOID CSymbolProperty::PropertyResize()
{
	if (bStart)
	{
		CRect rt;
		GetClientRect(&rt);

		for each (PropertyEX* pEX in propertys)
		{
			pEX->dialog->SetWindowPos(NULL, rt.left, rt.top, rt.right, rt.bottom, SWP_NOZORDER);
		}
	}
}

VOID CSymbolProperty::PropertyDelete(CSymbol* symbol)
{
	for each (PropertyEX* pEX in propertys)
	{
		if (pEX->symbol == symbol)
		{
			std::vector<PropertyEX*>::iterator iter = std::find(propertys.begin(), propertys.end(), pEX);

			propertys.erase(iter);

			return;
		}
	}
}

void CSymbolProperty::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	if (bStart)
	{
		mainFrame->symbolProperty->PropertyResize();
	}
}
