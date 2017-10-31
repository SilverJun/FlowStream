// SymbolProperty.cpp : ���� �����Դϴ�.
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


// CSymbolProperty �׸����Դϴ�.

void CSymbolProperty::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.

	CRect RectClient;
	GetClientRect(&RectClient);

	pDC->FillSolidRect(&RectClient, RGB(80, 80, 80));
}


// CSymbolProperty �����Դϴ�.

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


// CSymbolProperty �޽��� ó�����Դϴ�.


int CSymbolProperty::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();

	if (bStart)
	{
		mainFrame->symbolProperty->PropertyResize();
	}
}
