// TabMap.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MisoTool.h"
#include "TabMap.h"

#include "MainFrm.h"
#include "MisoToolView.h"
#include "MiniView.h"

// CTabMap ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTabMap, CDialog)

CTabMap::CTabMap(CWnd* pParent /*=NULL*/)
	: CDialog(CTabMap::IDD, pParent)
{
	
}

CTabMap::~CTabMap()
{
}

void CTabMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabMap, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CTabMap::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTabMap::OnSaveMapDatas)
	ON_BN_CLICKED(IDC_BUTTON3, &CTabMap::OnLoadMapData)
END_MESSAGE_MAP()


// CTabMap �޽��� ó�����Դϴ�.

BOOL CTabMap::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	SetLoadDataEditText();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CTabMap::SetEditObjctCount(void)
{
	CString count;
	count.Format(_T("%d"), ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_objCount);
	GetDlgItem(IDC_OBJ_COUNT)->SetWindowText(count);
}

void CTabMap::SetEditMonsterCount(void)
{
	CString count;
	count.Format(_T("%d"), ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_mstCount);
	GetDlgItem(IDC_MST_COUNT)->SetWindowText(count);
}

void CTabMap::OnBnClickedButton1()		// apply
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString strValueX, strValueY;
	
	GetDlgItemText(IDC_TILE_X, strValueX);
	GetDlgItemText(IDC_TILE_Y, strValueY);

	if(strValueX == "0" || strValueY == "0") return;

	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_tileX = _ttoi(strValueX);
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_tileY = _ttoi(strValueY);
		
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackGround->TileReset();
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->SetScrollSizes(
		MM_TEXT, 
		CSize(TILECX * ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_tileX,
		(TILECY / 2) * ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_tileY)
		);

	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pMyObject->Release();
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pMonster->Release();

	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
	((CMainFrame*)AfxGetMainWnd())->m_pMiniView->Invalidate(FALSE);
}

void CTabMap::OnSaveMapDatas()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CFileDialog	Dlg(FALSE,  // false�� ��� save ���, true�� ��� load ���
					L"map",	// �����ϴ� ������ Ȯ���� ��
					L"*.map", // ���ʿ� ����� �̸�
					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
					L"*.map", // ���� �� �ؿ� ����� ���� ����
					this);

	if(Dlg.DoModal() == IDCANCEL)
		return;

	Dlg.m_ofn.lpstrInitialDir	= L"..\\Data";

	HANDLE	hFile = CreateFile(Dlg.GetPathName(), GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte = 0;
	WORD wc = 0xFEFF;


#pragma region Ÿ�� ����
	//	1. Ÿ�� ���� ���� �� Ÿ�� ���� ���� x,y

	CBackGround* pBG = ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackGround;	

	wc = ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_tileX;
	WriteFile(hFile, &wc, sizeof(int), &dwByte, NULL);	

	wc = ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_tileY;
	WriteFile(hFile, &wc, sizeof(int), &dwByte, NULL);	

	for( size_t i=0; i < pBG->GetTileSize(); ++i )
	{
		WriteFile(hFile, pBG->GetIdxTileData(i), sizeof(TILE), &dwByte, NULL);	

		list<BYTE>::iterator iter = pBG->GetIdxTileData(i)->listDrawID.begin();
		for( ; iter != pBG->GetIdxTileData(i)->listDrawID.end(); ++iter)
		{
			WriteFile(hFile, &(*iter), sizeof(BYTE), &dwByte, NULL);
		}
	}
#pragma endregion 

	//////////////////////////////////////////////////////////////////////////

	//	2. ������Ʈ ���� �� �ش� �����͵� ����

	wc = ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_objCount;
	WriteFile(hFile, &wc, sizeof(UINT), &dwByte, NULL);	

	list<OBJECT*> objTemp = ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pMyObject->GetObjList();
	list<OBJECT*>::iterator iter = objTemp.begin();
	for( ; iter != objTemp.end(); ++iter)
	{
		WriteFile(hFile, (*iter), sizeof(OBJECT), &dwByte, NULL);
	}

	//////////////////////////////////////////////////////////////////////////

	//	3. ���� ���� �� �ش� �����͵� ����

	wc = ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_mstCount;
	WriteFile(hFile, &wc, sizeof(UINT), &dwByte, NULL);	

	list<UNITDATA*> mstTemp = ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pMonster->GetMonsterList();
	list<UNITDATA*>::iterator iter2 = mstTemp.begin();
	for( ; iter2 != mstTemp.end(); ++iter2)
	{
		WriteFile(hFile, (*iter2), sizeof(UNITDATA), &dwByte, NULL);
	}


	CloseHandle(hFile);	
}

//////////////////////////////////////////////////////////////////////////

void CTabMap::OnLoadMapData()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CFileDialog	Dlg(TRUE,  // false�� ��� save ���, true�� ��� load ���
					L"map",	// �����ϴ� ������ Ȯ���� ��
					L"*.map", // ���ʿ� ����� �̸�
					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
					L"*.map", // ���� �� �ؿ� ����� ���� ����
					this);
	
	if(Dlg.DoModal() == IDCANCEL)
		return;

	Dlg.m_ofn.lpstrInitialDir	= L"..\\Data";

	HANDLE	hFile = CreateFile(Dlg.GetPathName(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte = 0;
	WORD wc = 0xFEFF;

#pragma region Ÿ�� �б�

	ReadFile(hFile, &wc, sizeof(int), &dwByte, NULL);
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_tileX = wc;

	ReadFile(hFile, &wc, sizeof(int), &dwByte, NULL);
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_tileY = wc;

	// Ÿ�� ����
	CBackGround* pBG = ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackGround;
	
	pBG->TileReset();

	for( size_t i=0; i < pBG->GetTileSize(); ++i)
	{
		TILE*		pTileData = new TILE;
		ReadFile(hFile, pTileData, sizeof(TILE), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pTileData);
			break;
		}

		pBG->SetIdxTileData(i, pTileData);		// ������ ����

		BYTE* pTemp = new BYTE[pTileData->listDrawID.size()];
		BYTE temp;
		for(UINT j=0; j < pTileData->listDrawID.size() ; ++j)
		{
			ReadFile(hFile, &temp, sizeof(BYTE), &dwByte, NULL);
			pTemp[j] = temp;
		}
		
		pBG->SetIdxTileData(i, pTileData->listDrawID.size(), pTemp);
		delete[] pTemp;
	}

#pragma endregion


	// 2. ������Ʈ �б�

	// ������Ʈ ����
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pMyObject->Release();

	ReadFile(hFile, &wc, sizeof(UINT), &dwByte, NULL);
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_objCount = wc;

	for(UINT i =0; i< wc; ++i)
	{
		OBJECT* pObjTemp = new OBJECT;
		ReadFile(hFile, pObjTemp, sizeof(OBJECT), &dwByte, NULL);
		
		if(dwByte == 0)
		{
			::Safe_Delete(pObjTemp);
			break;
		}

		((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pMyObject->AddList(pObjTemp);
	}

	// 3. ����
	
	// ���� ����
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pMonster->Release();
		
	ReadFile(hFile, &wc, sizeof(UINT), &dwByte, NULL);
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_mstCount = wc;

	for(UINT i =0; i< wc; ++i)
	{
		UNITDATA* pMstTemp = new UNITDATA;
		ReadFile(hFile, pMstTemp, sizeof(UNITDATA), &dwByte, NULL);
	
		if(dwByte == 0)
		{
			::Safe_Delete(pMstTemp);
			break;
		}

		((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pMonster->AddList(pMstTemp);
	}

	CloseHandle(hFile);	

	((CMainFrame*)AfxGetMainWnd())->m_pMainView->SetScrollSizes(
		MM_TEXT, 
		CSize(TILECX * ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_tileX,
		(TILECY / 2) * ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_tileY)
		);

	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
	((CMainFrame*)AfxGetMainWnd())->m_pMiniView->Invalidate(FALSE);

	SetLastOpenText(Dlg.GetFileName());
	SetLoadDataEditText();
}

void CTabMap::SetLastOpenText(CString lastText)
{
	CString str;

	GetDlgItemText(IDC_OPEN2, str);
	SetDlgItemText(IDC_OPEN3, str);

	GetDlgItemText(IDC_OPEN1, str);
	SetDlgItemText(IDC_OPEN2, str);

	SetDlgItemText(IDC_OPEN1, lastText);
}	

void CTabMap::SetLoadDataEditText(void)
{
	CString tileX, tileY, count;	

	tileX.Format(_T("%d"), ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_tileX);
	GetDlgItem(IDC_TILE_X)->SetWindowText(tileX);

	tileY.Format(_T("%d"), ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_tileY);
	GetDlgItem(IDC_TILE_Y)->SetWindowText(tileY);

	//////////////////////////////////////////////////////////////////////////

	SetEditObjctCount();
	SetEditMonsterCount();
}