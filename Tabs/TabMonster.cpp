// TabMonster.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MisoTool.h"
#include "TabMonster.h"

#include "MainFrm.h"
#include "MisoToolView.h"

// CTabMonster 대화 상자입니다.

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


// CTabMonster 메시지 처리기입니다.

BOOL CTabMonster::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

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
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	TCHAR		 objName[MAX_PATH] = L"";
	wstring _name = L"monster_%02d";
	wsprintf(objName, _name.c_str(), m_list.GetCurSel());

	//	텍스트 연결하고 해당 이미지를 출력
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int test = m_comboBox.GetCurSel();
	TCHAR		 _name[MIDDLE_STR] = L"";
	_itot(test, _name, MIDDLE_STR);

	//	텍스트 연결하고 해당 이미지를 출력
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pMonster->Release();
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_mstCount = 0;
}
