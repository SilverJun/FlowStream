#pragma once

// CObjectListView ���Դϴ�.

#define IMAGE_XDISTANCE	100
#define IMAGE_YDISTANCE	100

class CListObject;
class CObjectListDialog;

//===============================================
// CObjectListView : ������Ʈ�� �����ϴ� ����Ʈ
class CObjectListView : public CListView
{
	DECLARE_DYNCREATE(CObjectListView)

protected:
	CObjectListView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CObjectListView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public :
	std::vector<CListObject*> objects;

public :
	INT DeleteAllFiles(LPCWSTR szDir, int recur);
	// ������Ʈ�� �����Ѵ�.
	VOID	DeleteObject(CString name);
	// �̹��� ��ġ ����
	VOID	ImagePositionRevision();

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnNcPaint();
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


