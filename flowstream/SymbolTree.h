#pragma once


// CSymbolTree ���Դϴ�.

//=========================================
// CSymbolTree : �ɺ��� ������ ����� TreeCtrl�� ������ Ŭ����
class CSymbolTree : public CTreeView
{
	DECLARE_DYNCREATE(CSymbolTree)

protected:
	CSymbolTree();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CSymbolTree();

public :
	// ����ڰ� �۾��� �ϱ� ���� ���� ������ �����ΰ�
	bool		bSelected;
	// ó�� ���� �� �ɺ� ���� ó���� ���ϱ� ����
	bool		bStartFlag;

	// �ɺ� Ʈ�� ������
	HTREEITEM hSymbols;
	// �ɺ��� if ������
	HTREEITEM	hIf;
	// �ɺ��� set ������
	HTREEITEM hSet;
	// �ɺ��� print ������
	HTREEITEM hPrint;
	// �ɺ��� create ������
	HTREEITEM hCreate;
	// �ɺ��� while ������
	HTREEITEM hWhile;
	// �ɺ��� input ������
	HTREEITEM hInput;
	// �ɺ��� output ������
	HTREEITEM hOutput;

	// ���� Ʈ�� ������
	HTREEITEM hLines;
	// ���� ���� Ʈ�� ������
	HTREEITEM hLine;
	// ���� ���� Ʈ�� ������
	HTREEITEM hTrueLine;
	// �� ���� Ʈ�� ������
	HTREEITEM hFalseLine;

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSingleExpand(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
//	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
//	virtual void OnDraw(CDC* /*pDC*/);
};


