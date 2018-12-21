// TabObject.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MisoTool.h"
#include "TabObject.h"

#include "MainFrm.h"
#include "MisoToolView.h"

// CTabObject ��ȭ �����Դϴ�.

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


// CTabObject �޽��� ó�����Դϴ�.

BOOL CTabObject::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	SetObjectList();

	m_ctrlSlider.SetRange(0, 255);
	m_ctrlSlider.SetRangeMin(0);
	m_ctrlSlider.SetRangeMax(255);
	m_ctrlSlider.SetPos(255);
	m_ctrlSlider.SetLineSize(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString objName;
	m_list.GetText(m_list.GetCurSel(), objName);

	//	�ؽ�Ʈ �����ϰ� �ش� �̹����� ���
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pMyObject->Release();
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_objCount = 0;
}
