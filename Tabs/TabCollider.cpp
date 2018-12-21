// TabCollider.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MisoTool.h"
#include "TabCollider.h"

#include "MainFrm.h"
#include "MisoToolView.h"

// CTabCollider 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTabCollider, CDialog)

CTabCollider::CTabCollider(CWnd* pParent /*=NULL*/)
	: CDialog(CTabCollider::IDD, pParent)
	, m_radio(0)
{

}

CTabCollider::~CTabCollider()
{
}

void CTabCollider::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Control(pDX, IDC_IMAGE2, m_Image);
	DDX_Control(pDX, IDC_CHECK1, m_checkBtn);
}


BEGIN_MESSAGE_MAP(CTabCollider, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &CTabCollider::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CTabCollider::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_CHECK1, &CTabCollider::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTabCollider::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTabCollider 메시지 처리기입니다.

BOOL CTabCollider::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	SetTileImage();

	m_checkBtn.SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

const TEXINFO* CTabCollider::SetTileImage(bool bObject /* = false */)
{
	wchar_t		path[MIDDLE_STR]	= L"../Texture/Tile/Collider/";
	wchar_t*	finalPath;
	CString		tileName;

	tileName.Format(L"collider_%02d", m_radio);		// %d 붙이기
	finalPath = wcscat(path, tileName);				// 경로 + 파일 붙이기
	finalPath = wcscat(finalPath, L".png");			// 확장자 붙이기

	CImage	image;
	image.Load(finalPath);

	CBitmap	bitmap;
	bitmap.Attach(image.Detach());

	HBITMAP	oldBitmap = m_Image.SetBitmap(bitmap);

	if(oldBitmap != NULL)	
		::DeleteObject(oldBitmap);

	bitmap.Detach();

	if(bObject == true)
		return CTextureMgr::GetInstance()->GetTexture(L"COLTILE", L"ColTile", 1);

	return CTextureMgr::GetInstance()->GetTexture(L"COLTILE", L"ColTile", m_radio);
}
void CTabCollider::OnBnClickedRadio1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_radio = 0;
	SetTileImage();
}

void CTabCollider::OnBnClickedRadio2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_radio = 1;
	SetTileImage();
}

void CTabCollider::OnBnClickedCheck1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
}

void CTabCollider::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackGround->TileChangeAll();
}
