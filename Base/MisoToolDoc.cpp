
// MisoToolDoc.cpp : CMisoToolDoc 클래스의 구현
//

#include "stdafx.h"
#include "MisoTool.h"

#include "MisoToolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMisoToolDoc

IMPLEMENT_DYNCREATE(CMisoToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CMisoToolDoc, CDocument)
END_MESSAGE_MAP()


// CMisoToolDoc 생성/소멸

CMisoToolDoc::CMisoToolDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMisoToolDoc::~CMisoToolDoc()
{
}

BOOL CMisoToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMisoToolDoc serialization

void CMisoToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CMisoToolDoc 진단

#ifdef _DEBUG
void CMisoToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMisoToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMisoToolDoc 명령
