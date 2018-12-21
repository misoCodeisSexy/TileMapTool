// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MisoTool.h"
#include "MyForm.h"
#include "MisoToolView.h"

#include "MainFrm.h"

// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(CMyForm::IDD)
	, m_pTabWndShow(NULL)
	, m_sTabCurState(IDD_TABMAP)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMyForm::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CMyForm 진단입니다.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm 메시지 처리기입니다.

void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	SetScrollSizes(MM_TEXT, CSize(0,0));

	CString		strOne = _T("Map");
	CString		strTwo = _T("Tile");
	CString		strThree = _T("Collider");
	CString		strFour = _T("Object");
	CString		strFive = _T("Monster");

	m_Tab.InsertItem(1, strOne);
	m_Tab.InsertItem(2, strTwo);
	m_Tab.InsertItem(3, strThree);
	m_Tab.InsertItem(4, strFour);
	m_Tab.InsertItem(5, strFive);

	CRect Rect;
	m_Tab.GetClientRect(&Rect);

	m_tabMap.Create(IDD_TABMAP, &m_Tab);
	m_tabMap.SetWindowPos(NULL, 3, 25,
		Rect.Width()-12, Rect.Height()-30,
		SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pTabWndShow = &m_tabMap;

	m_tabTile.Create(IDD_TABTILE, &m_Tab);
	m_tabTile.SetWindowPos(NULL, 3, 25,
		Rect.Width()-12, Rect.Height()-30,
		SWP_NOZORDER);

	m_tabCollider.Create(IDD_TABCOLLIDER, &m_Tab);
	m_tabCollider.SetWindowPos(NULL, 3, 25,
		Rect.Width()-12, Rect.Height()-30,
		SWP_NOZORDER);

	m_tabObject.Create(IDD_TABOBJECT, &m_Tab);
	m_tabObject.SetWindowPos(NULL, 3, 25,
		Rect.Width()-12, Rect.Height()-30,
		SWP_NOZORDER);

	m_tabMonster.Create(IDD_TABMONSTER, &m_Tab);
	m_tabMonster.SetWindowPos(NULL, 3, 25,
		Rect.Width()-12, Rect.Height()-30,
		SWP_NOZORDER);

}

void CMyForm::MousePositionUpdate(CPoint point)
{
	CClientDC dc(this);

	CString strX, strY;
	strX.Format(_T("%03d"), point.x);
	strY.Format(_T("%03d"), point.y);
	dc.TextOut(125, 8, strX);
	dc.TextOut(200, 8, strY);

	UpdateData(FALSE);
}
void CMyForm::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if(m_pTabWndShow != NULL)
	{
		m_pTabWndShow->ShowWindow(SW_HIDE);
		m_pTabWndShow = NULL;
	}

	int nIndex = m_Tab.GetCurSel();
	switch(nIndex)
	{
	case 0:
		{
			m_tabMap.SetEditObjctCount();
			m_tabMap.SetEditMonsterCount();

			m_tabMap.ShowWindow(SW_SHOW);
			m_pTabWndShow = &m_tabMap;
			m_sTabCurState = IDD_TABMAP;
		}
		break;
	case 1:
		{
			m_tabTile.ShowWindow(SW_SHOW);
			m_pTabWndShow = &m_tabTile;
			m_sTabCurState = IDD_TABTILE;
		}
		break;
	case 2:
		{
			m_tabCollider.ShowWindow(SW_SHOW);
			m_pTabWndShow = &m_tabCollider;
			m_sTabCurState = IDD_TABCOLLIDER;
		}
		break;
	case 3:
		{
			m_tabObject.ShowWindow(SW_SHOW);
			m_pTabWndShow = &m_tabObject;
			m_sTabCurState = IDD_TABOBJECT;
			((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
		}
		break;
	case 4:
		{
			m_tabMonster.ShowWindow(SW_SHOW);
			m_pTabWndShow = &m_tabMonster;
			m_sTabCurState = IDD_TABMONSTER;
			((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
		}
		break;
	}

	*pResult = 0;
}
