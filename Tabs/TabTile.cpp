// TabTile.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MisoTool.h"
#include "TabTile.h"

#include "MainFrm.h"
#include "MisoToolView.h"
#include "MiniView.h"

// CTabTile ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTabTile, CDialog)

CTabTile::CTabTile(CWnd* pParent /*=NULL*/)
: CDialog(CTabTile::IDD, pParent)
, m_radio(1)
{

}

CTabTile::~CTabTile()
{
}

void CTabTile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_comboBox);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Control(pDX, IDC_CHECK1, m_CheckBtn);
	DDX_Control(pDX, IDC_IMAGE, m_Image);
}


BEGIN_MESSAGE_MAP(CTabTile, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CTabTile::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_RADIO1, &CTabTile::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CTabTile::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_CHECK1, &CTabTile::OnBnClickedCheck1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CTabTile::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_CNGALL, &CTabTile::OnBnClickedCngall)
END_MESSAGE_MAP()


// CTabTile �޽��� ó�����Դϴ�.

BOOL CTabTile::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_comboBox.InsertString(0, L"Base");
	m_comboBox.InsertString(1, L"Base2");
	m_comboBox.InsertString(2, L"EventStage");
	m_comboBox.InsertString(3, L"Boss");

	m_comboBox.SetCurSel(0);
	OnCbnSelchangeCombo2();			// list box �ʱ�ȭ

	CButton* pCheck = (CButton*)GetDlgItem(IDC_RADIO1);
	pCheck->SetCheck(0);
	pCheck = (CButton*)GetDlgItem(IDC_RADIO2);
	pCheck->SetCheck(1);

	m_CheckBtn.SetCheck(1);	// check box �ʱ�ȭ

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CTabTile::OnCbnSelchangeCombo2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int comboIdx = m_comboBox.GetCurSel();

	switch(comboIdx)
	{
	case 0:		// ����
		{
			SetTileList(TILE_BASE, TILE_BASE_TWO);
		}
		break;
	case 1:		// Ʃ�丮��
		{		
			SetTileList(TILE_BASE_TWO, TILE_EVENT_STAGE);
		}
		break;
	case 2:		// ����
		{
			SetTileList(TILE_EVENT_STAGE, TILE_BOSS);
		}	
		break;
	case 3:		// ����
		{
			SetTileList(TILE_BOSS, TILE_END);
		}
		break;
	}
}

void CTabTile::SetTileList(const int start, const int end)
{
	m_listBox.ResetContent();

	int idx = 0;
	for(int i = start; i < end; ++i, idx++)
	{
		TCHAR lastStr[MAX_PATH] = L"";
		wstring str = L"tile_%03d";

		wsprintf(lastStr, str.c_str(), i);
		m_listBox.InsertString(idx, lastStr);
	}

	// Ŀ�� �����ϰ� �ش� �̹��� ���
	m_listBox.SetCurSel(0);
	OnLbnSelchangeList1();
}

void CTabTile::OnBnClickedRadio1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_radio = 0;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
}

void CTabTile::OnBnClickedRadio2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_radio = 1;
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
}

void CTabTile::OnBnClickedCheck1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
}

void CTabTile::OnLbnSelchangeList1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString tileName;
	m_listBox.GetText(m_listBox.GetCurSel(), tileName);

	//	�ؽ�Ʈ �����ϰ� �ش� �̹����� ���
	wchar_t		path[MIN_STR]	= L"../Texture/Tile/";
	wchar_t*	finalPath;

	finalPath = wcscat( path, tileName );
	finalPath = wcscat( finalPath, L".png" );

	CImage	image;
	image.Load(finalPath);

	CBitmap	bitmap;
	bitmap.Attach(image.Detach());

	HBITMAP	oldBitmap = m_Image.SetBitmap(bitmap);

	if(oldBitmap != NULL)	
		::DeleteObject(oldBitmap);

	bitmap.Detach();

	////

	int value_ = 0;
	int comboIdx = m_comboBox.GetCurSel();

	switch(comboIdx)
	{
	case 0:		// start
		{
			value_ = m_listBox.GetCurSel() + TILE_BASE;
		}
		break;
	case 1:		// base
		{		
			value_ = m_listBox.GetCurSel() + TILE_BASE_TWO;
		}
		break;
	case 2:		// battle
		{
			value_ = m_listBox.GetCurSel() + TILE_EVENT_STAGE;
		}	
		break;
	case 3:		// boss
		{
			value_ = m_listBox.GetCurSel() + TILE_BOSS;
		}
		break;
	}

	const TEXINFO* texInfo = NULL;
	texInfo = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile", value_ );

	if( texInfo != NULL )
	{
		((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_drawID =
			texInfo->uniqueDrawID;
	}
}

void CTabTile::OnBnClickedCngall()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackGround->TileChangeAll();
	((CMainFrame*)AfxGetMainWnd())->m_pMiniView->Invalidate(FALSE);
}
