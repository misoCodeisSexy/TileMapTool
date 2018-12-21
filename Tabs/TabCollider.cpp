// TabCollider.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MisoTool.h"
#include "TabCollider.h"

#include "MainFrm.h"
#include "MisoToolView.h"

// CTabCollider ��ȭ �����Դϴ�.

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


// CTabCollider �޽��� ó�����Դϴ�.

BOOL CTabCollider::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	SetTileImage();

	m_checkBtn.SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

const TEXINFO* CTabCollider::SetTileImage(bool bObject /* = false */)
{
	wchar_t		path[MIDDLE_STR]	= L"../Texture/Tile/Collider/";
	wchar_t*	finalPath;
	CString		tileName;

	tileName.Format(L"collider_%02d", m_radio);		// %d ���̱�
	finalPath = wcscat(path, tileName);				// ��� + ���� ���̱�
	finalPath = wcscat(finalPath, L".png");			// Ȯ���� ���̱�

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_radio = 0;
	SetTileImage();
}

void CTabCollider::OnBnClickedRadio2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_radio = 1;
	SetTileImage();
}

void CTabCollider::OnBnClickedCheck1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
}

void CTabCollider::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackGround->TileChangeAll();
}
