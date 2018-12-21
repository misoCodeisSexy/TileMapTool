// MiniView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MisoTool.h"
#include "MiniView.h"

#include "BackGround.h"
#include "MainFrm.h"
#include "MisoToolView.h"

// CMiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView()
{

}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniView �׸����Դϴ�.

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.

	CBackGround*	pBackGround = ((CMainFrame*)AfxGetApp()->GetMainWnd())->m_pMainView->m_pBackGround;
	CMyObject*		pMyObject	= ((CMainFrame*)AfxGetApp()->GetMainWnd())->m_pMainView->m_pMyObject;
	CMonster*		pMonster	= ((CMainFrame*)AfxGetApp()->GetMainWnd())->m_pMainView->m_pMonster;

	CDevice::GetInstance()->Render_Begin();

	pBackGround->MiniViewRender();
	pMyObject->MiniViewRender();
	pMonster->MiniViewRender();

	CDevice::GetInstance()->Render_End();
	CDevice::GetInstance()->GetDevice()->Present(NULL, NULL, m_hWnd, NULL);
}


// CMiniView �����Դϴ�.

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniView �޽��� ó�����Դϴ�.
