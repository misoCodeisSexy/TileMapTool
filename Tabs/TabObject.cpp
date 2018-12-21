// TabObject.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MisoTool.h"
#include "TabObject.h"

#include "MainFrm.h"
#include "MisoToolView.h"

// CTabObject 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTabObject, CDialog)

CTabObject::CTabObject(CWnd* pParent /*=NULL*/)
	: CDialog(CTabObject::IDD, pParent)
{
	m_Image.Create(_T("view"), WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
		CRect(0,0, 200, 200), this, IDC_STATIC2);
}

CTabObject::~CTabObject()
{
}

void CTabObject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_STATIC2, m_Image);
	DDX_Control(pDX, IDC_SLIDER2, m_ctrlSlider);
}


BEGIN_MESSAGE_MAP(CTabObject, CDialog)
	
	ON_LBN_SELCHANGE(IDC_LIST1, &CTabObject::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTabObject::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTabObject 메시지 처리기입니다.

BOOL CTabObject::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	SetObjectList();

	m_ctrlSlider.SetRange(0, 255);
	m_ctrlSlider.SetRangeMin(0);
	m_ctrlSlider.SetRangeMax(255);
	m_ctrlSlider.SetPos(255);
	m_ctrlSlider.SetLineSize(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CTabObject::SetObjectList()
{
	m_list.ResetContent();

	for(int i=0; i<OBJECT_NUMBER; ++i)
	{
		TCHAR lastStr[MAX_PATH] = L"";
		wstring str = L"object_%02d";

		wsprintf(lastStr, str.c_str(), i);
		m_list.InsertString(i, lastStr);
	}

	m_list.SetCurSel(0);
	OnLbnSelchangeList1();
}
void CTabObject::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString objName;
	m_list.GetText(m_list.GetCurSel(), objName);

	//	텍스트 연결하고 해당 이미지를 출력
	wchar_t		path[MIN_STR]	= L"../Texture/Object/";
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

const TEXINFO* CTabObject::GetCurrentTexture()
{
	return CTextureMgr::GetInstance()->GetTexture(L"OBJECT", L"Object",m_list.GetCurSel());
}

void CTabObject::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pMyObject->Release();
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_objCount = 0;
}
