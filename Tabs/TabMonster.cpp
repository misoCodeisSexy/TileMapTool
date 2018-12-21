// TabMonster.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MisoTool.h"
#include "TabMonster.h"

#include "MainFrm.h"
#include "MisoToolView.h"

// CTabMonster ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTabMonster, CDialog)

CTabMonster::CTabMonster(CWnd* pParent /*=NULL*/)
	: CDialog(CTabMonster::IDD, pParent)
{
	m_Image.Create(_T("view2"), WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
		CRect(0,0, 100, 100), this, IDC_STATIC3);
}

CTabMonster::~CTabMonster()
{
}

void CTabMonster::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_STATIC3, m_Image);
	DDX_Control(pDX, IDC_COMBO1, m_comboBox);
	DDX_Control(pDX, IDC_ATTRIBUTE, m_Attribute);
}


BEGIN_MESSAGE_MAP(CTabMonster, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST2, &CTabMonster::OnLbnSelchangeList2)
	ON_CBN_SELENDOK(IDC_COMBO1, &CTabMonster::OnCbnSelendokCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTabMonster::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTabMonster �޽��� ó�����Դϴ�.

BOOL CTabMonster::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_comboBox.InsertString(0, L"Fire");
	m_comboBox.InsertString(1, L"Water");
	m_comboBox.InsertString(2, L"Wind");
	m_comboBox.InsertString(3, L"Soil");
	m_comboBox.InsertString(4, L"Light");
	m_comboBox.InsertString(5, L"Darkness");

	m_comboBox.SetCurSel(0);
	OnCbnSelendokCombo1();

	SetMonsterList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CTabMonster::SetMonsterList()
{
	m_list.ResetContent();

	for(int i=0; i< MONSTER_NUMBER; ++i)
	{
		TCHAR lastStr[MAX_PATH] = L"";

		wstring str;
		GetMonsterName(i, str);

		wsprintf(lastStr, str.c_str(), i);
		m_list.InsertString(i, lastStr);
	}

	m_list.SetCurSel(0);
	OnLbnSelchangeList2();
}

void CTabMonster::GetMonsterName(int idx, wstring& name)
{
	switch(idx)
	{
	case ANGEL:
		{
			name = L"Angel";
		}
		break;
	case WITCH_BLACK:
		{
			name = L"Witch_Black";
		}
		break;
	case WITCH_WHITE:
		{
			name = L"Witch_White";
		}
		break;
	case NECRO:
		{
			name = L"NecroPancer";
		}
		break;
	}
}

void CTabMonster::OnLbnSelchangeList2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	TCHAR		 objName[MAX_PATH] = L"";
	wstring _name = L"monster_%02d";
	wsprintf(objName, _name.c_str(), m_list.GetCurSel());

	//	�ؽ�Ʈ �����ϰ� �ش� �̹����� ���
	wchar_t		path[MIN_STR]	= L"../Texture/Monster/";
	wchar_t*	finalPath;

	finalPath = wcscat( path, objName );
	finalPath = wcscat( finalPath, L".png" );

	CImage	image;
	image.Load(finalPath);

	CBitmap	bitmap;
	bitmap.Attach(image.Detach());

	HBITMAP	oldBitmap = m_Image.SetBitmap(bitmap);

	if(oldBitmap != NULL)	
		::DeleteObject(oldBitmap);

	bitmap.Detach(); 
}

const TEXINFO* CTabMonster::GetCurrentTexture()
{
	return CTextureMgr::GetInstance()->GetTexture(L"MONSTER", L"Monster", m_list.GetCurSel());
}
void CTabMonster::OnCbnSelendokCombo1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int test = m_comboBox.GetCurSel();
	TCHAR		 _name[MIDDLE_STR] = L"";
	_itot(test, _name, MIDDLE_STR);

	//	�ؽ�Ʈ �����ϰ� �ش� �̹����� ���
	wchar_t		path[MIN_STR]	= L"../Texture/Attribute/";
	wchar_t*	finalPath;

	finalPath = wcscat( path, _name );
	finalPath = wcscat( finalPath, L".png" );

	CImage	image;
	image.Load(finalPath);

	CBitmap	bitmap;
	bitmap.Attach(image.Detach());

	HBITMAP	oldBitmap = m_Attribute.SetBitmap(bitmap);

	if(oldBitmap != NULL)	
		::DeleteObject(oldBitmap);

	bitmap.Detach(); 
}

void CTabMonster::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pMonster->Release();
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_mstCount = 0;
}
