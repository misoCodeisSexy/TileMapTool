// MiniView.cpp : 구현 파일입니다.
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


// CMiniView 그리기입니다.

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.

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


// CMiniView 진단입니다.

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


// CMiniView 메시지 처리기입니다.
