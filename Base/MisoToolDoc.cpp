
// MisoToolDoc.cpp : CMisoToolDoc Ŭ������ ����
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


// CMisoToolDoc ����/�Ҹ�

CMisoToolDoc::CMisoToolDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CMisoToolDoc::~CMisoToolDoc()
{
}

BOOL CMisoToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CMisoToolDoc serialization

void CMisoToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CMisoToolDoc ����

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


// CMisoToolDoc ���
