// FlowStreamDoc.h : CFlowStreamDoc Ŭ������ �������̽�
//
#pragma once

#include <rapidjson\rapidjson.h>
#include <rapidjson\document.h>

#include <rapidjson\filereadstream.h>
#include <rapidjson\encodedstream.h>    // EncodedInputStream

#include <rapidjson\filewritestream.h>
#include <rapidjson\encodedstream.h>    // EncodedOutputStream

#include <rapidjson\stringbuffer.h>
#include <rapidjson\prettywriter.h>

#include <rapidjson\encodings.h>

#include <rapidjson\error\en.h>

enum eLineType
{
	eNo,
	eYes,
	eTrueLine,
	eFalseLine
};

class CFlowStreamDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CFlowStreamDoc();
	DECLARE_DYNCREATE(CFlowStreamDoc)

// Ư���Դϴ�.
public:
	rapidjson::GenericDocument<rapidjson::UTF16LE<wchar_t> > projectDoc;
	CString projectName;
	CString filePath;

// �۾��Դϴ�.
public:
	BOOL NewProjectFile(LPCTSTR path);
	BOOL SaveProjectFile(LPCTSTR path);
	BOOL LoadProjectFile(LPCTSTR path);
private:
	VOID CreateSymbols();

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CFlowStreamDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
};
