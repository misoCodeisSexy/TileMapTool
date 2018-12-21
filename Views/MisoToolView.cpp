
// MisoToolView.cpp : CMisoToolView 클래스의 구현
//

#include "stdafx.h"
#include "MisoTool.h"

#include "MisoToolDoc.h"
#include "MisoToolView.h"
#include "MainFrm.h"
#include "MiniView.h"

#include "MyForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMisoToolView

IMPLEMENT_DYNCREATE(CMisoToolView, CScrollView)

BEGIN_MESSAGE_MAP(CMisoToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMisoToolView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMisoToolView 생성/소멸

HWND	g_hWnd;

CMisoToolView::CMisoToolView()
: m_pDevice(CDevice::GetInstance())
, m_tileX(20)
, m_tileY(20)
, m_pBackGround(NULL)
, m_pMyForm(NULL)
, m_pMonster(NULL)
, m_pMyObject(NULL)
, m_drawID(2)
, m_isClicked(false)
, m_MousePoint(CPoint(0, 0))
, m_objCount(0)
, m_mstCount(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMisoToolView::~CMisoToolView()
{
	::Safe_Delete(m_pBackGround);
	::Safe_Delete(m_pMyObject);
	::Safe_Delete(m_pMonster);
	m_pMyForm = NULL;
}

BOOL CMisoToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMisoToolView 그리기

void CMisoToolView::OnDraw(CDC* /*pDC*/)
{
	CMisoToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	m_pDevice->Render_Begin();

	m_pBackGround->Render();
	m_pMyObject->Render();
	m_pMonster->Render();

	if( m_pMyForm->m_sTabCurState == IDD_TABOBJECT )
	{
		CObjMgr::GetInstance()->AlpaRender((CObj*)m_pMyObject, this);
		Invalidate(FALSE);
	}
	else if( m_pMyForm->m_sTabCurState == IDD_TABMONSTER )
	{
		CObjMgr::GetInstance()->AlpaRender((CObj*)m_pMonster, this);
		Invalidate(FALSE);
	}
	
	m_pDevice->Render_End();
	m_pDevice->GetDevice()->Present(NULL, NULL, NULL, NULL);
}


// CMisoToolView 인쇄


void CMisoToolView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CMisoToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMisoToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMisoToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMisoToolView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMisoToolView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMisoToolView 진단

#ifdef _DEBUG
void CMisoToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMisoToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMisoToolDoc* CMisoToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMisoToolDoc)));
	return (CMisoToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMisoToolView 메시지 처리기

void CMisoToolView::OnDestroy()
{
	CScrollView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CTextureMgr::GetInstance()->DestroyInstance();	
	m_pDevice->DestroyInstance();
}

void CMisoToolView::OnInitialUpdate()
{
	SetScrollSizes(MM_TEXT, CSize(TILECX * m_tileX, (TILECY / 2) * m_tileY));

	CMainFrame*		pMainFrm = ((CMainFrame*)AfxGetMainWnd()); 
	// 프레임 정보를 얻어와주는 함수

	RECT	rcWindow = { };
	pMainFrm->GetWindowRect(&rcWindow);	// 현재 윈도우 창의 프레임 사이즈를 얻어오는 함수

	SetRect(&rcWindow, 0, 0, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top);

	RECT	rcMainView = {};
	GetClientRect(&rcMainView);		// 순수 뷰 창의 크기를 얻어오는 함수

	float	fRowFrm = float(rcWindow.right - rcMainView.right);
	float	fColFrm = float(rcWindow.bottom - rcMainView.bottom);

	pMainFrm->SetWindowPos(NULL, 
		0, 0, 
		int(WINCX + fRowFrm), 
		int(WINCY + fColFrm), 
		SWP_NOZORDER);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	g_hWnd = m_hWnd;

	if(FAILED(m_pDevice->InitDevice()))
	{
		AfxMessageBox(L"뷰에서 디바이스 초기화 실패");
		return;
	}

	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Tile/tile_%03d.png", 
		L"TILE", TEX_MULTI, L"Tile", TILE_END)))
	{
		AfxMessageBox(L"시작 타일 텍스쳐 생성 실패");
		return;
	}

	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Tile/Collider/collider_%02d.png", 
		L"COLTILE", TEX_MULTI, L"ColTile", 2)))
	{	
		AfxMessageBox(L"옵션 타일 텍스쳐 생성 실패");
		return;
	}

	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Object/object_%02d.png", 
		L"OBJECT", TEX_MULTI, L"Object", OBJECT_NUMBER)))
	{	
		AfxMessageBox(L"오브젝트 텍스쳐 생성 실패");
		return;
	}

	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Monster/monster_%02d.png", 
		L"MONSTER", TEX_MULTI, L"Monster", MONSTER_NUMBER)))
	{	
		AfxMessageBox(L"몬스터 텍스쳐 생성 실패");
		return;
	}

	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Attribute/%d.png", 
		L"ATTRIBUTE", TEX_MULTI, L"Attribute", 6)))
	{	
		AfxMessageBox(L"속성 텍스쳐 생성 실패");
		return;
	}

 

	m_pBackGround = new CBackGround;
	m_pBackGround->SetMainView(this);

	if(FAILED(m_pBackGround->Initialize()))
	{
		AfxMessageBox(L"타일 생성 실패");
		return;
	}

	m_pMyForm = ((CMainFrame*)AfxGetApp()->GetMainWnd())->m_pMyForm;
	
	m_pMyObject = new CMyObject;
	if(FAILED(m_pMyObject->Initialize()))
	{
		AfxMessageBox(L"오브젝트 생성 실패");
		return;
	}
	m_pMyObject->SetMainView(this);

	m_pMonster = new CMonster;
	if(FAILED(m_pMonster->Initialize()))
	{
		AfxMessageBox(L"몬스터 생성 실패");
		return;
	}
	m_pMonster->SetMainView(this);

	CScrollView::OnInitialUpdate();
}

void CMisoToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnLButtonDown(nFlags, point);

	if(m_isClicked == true) return;

	if( m_pMyForm->m_sTabCurState == IDD_TABOBJECT )
	{
		CObjMgr::GetInstance()->OnAdd((CObj*)m_pMyObject,
								D3DXVECTOR3(		
								(float)point.x + GetScrollPos(0), 
								(float)point.y + GetScrollPos(1), 0.f)
								, this
								, m_pBackGround);
		m_isClicked = true;
	}
	else if( m_pMyForm->m_sTabCurState == IDD_TABMONSTER )
	{
		CObjMgr::GetInstance()->OnAdd((CObj*)m_pMonster,
								D3DXVECTOR3(		
								(float)point.x + GetScrollPos(0), 
								(float)point.y + GetScrollPos(1), 0.f)
								, this
								, m_pBackGround);
		m_isClicked = true;
	}
	else
	{
		m_pBackGround->TileChange(D3DXVECTOR3(
			(float)point.x + GetScrollPos(0), 
			(float)point.y + GetScrollPos(1), 0.f), m_drawID);
	}

	Invalidate(FALSE);
	((CMainFrame*)AfxGetMainWnd())->m_pMiniView->Invalidate(FALSE);
}

void CMisoToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnMouseMove(nFlags, point);

	m_pMyForm->MousePositionUpdate(point);
	m_MousePoint = point;

	if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		OnLButtonDown(nFlags, point);

	if(GetAsyncKeyState(VK_RBUTTON) & 0)
		OnRButtonDown(nFlags, point);
}

void CMisoToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnRButtonDown(nFlags, point);

	if( m_pMyForm->m_sTabCurState == IDD_TABOBJECT )
	{
		m_pMyObject->RemoveObject(point);
	}
	else if ( m_pMyForm->m_sTabCurState == IDD_TABMONSTER )
	{
		m_pMonster->RemoveObject(point);
	}
	else
	{
		m_pBackGround->TileRemove(D3DXVECTOR3(
			(float)point.x + GetScrollPos(0),
			(float)point.y + GetScrollPos(1),
			0.1f));
	}

	Invalidate(FALSE);
	((CMainFrame*)AfxGetMainWnd())->m_pMiniView->Invalidate(FALSE);
}
void CMisoToolView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnLButtonUp(nFlags, point);

	m_isClicked = false;
}
