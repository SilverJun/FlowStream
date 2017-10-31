// FlowStreamDoc.h : CFlowStreamDoc 클래스의 인터페이스
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
protected: // serialization에서만 만들어집니다.
	CFlowStreamDoc();
	DECLARE_DYNCREATE(CFlowStreamDoc)

// 특성입니다.
public:
	rapidjson::GenericDocument<rapidjson::UTF16LE<wchar_t> > projectDoc;
	CString projectName;
	CString filePath;

// 작업입니다.
public:
	BOOL NewProjectFile(LPCTSTR path);
	BOOL SaveProjectFile(LPCTSTR path);
	BOOL LoadProjectFile(LPCTSTR path);
private:
	VOID CreateSymbols();

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CFlowStreamDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
};
