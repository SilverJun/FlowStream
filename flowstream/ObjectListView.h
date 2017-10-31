#pragma once

// CObjectListView 뷰입니다.

#define IMAGE_XDISTANCE	100
#define IMAGE_YDISTANCE	100

class CListObject;
class CObjectListDialog;

//===============================================
// CObjectListView : 오브젝트를 관리하는 리스트
class CObjectListView : public CListView
{
	DECLARE_DYNCREATE(CObjectListView)

protected:
	CObjectListView();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	// 오브젝트를 삭제한다.
	VOID	DeleteObject(CString name);
	// 이미지 위치 보정
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


