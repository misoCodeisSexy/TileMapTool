#include "StdAfx.h"
#include "Monster.h"
#include "MisoToolView.h"

#include "resource.h"
#include "MyForm.h"

CMonster::CMonster(void)
{
}

/*virtual*/ CMonster::~CMonster(void)
{
	Release();
}

HRESULT	CMonster::Initialize(void)
{
	return S_OK;
}

void CMonster::Render(void)
{
	const TEXINFO*	pTexture = NULL;
	D3DXMATRIX		matTrans;
	const int drawAlpha = m_pMainView->m_pMyForm->m_tabObject.m_ctrlSlider.GetPos();

	list<UNITDATA*>::iterator iter = m_listUnit.begin();
	for( ; iter != m_listUnit.end(); iter++)
	{
		D3DXMatrixTranslation(&matTrans, 
			(*iter)->info.vPos.x - m_pMainView->GetScrollPos(0), 
			(*iter)->info.vPos.y - m_pMainView->GetScrollPos(1), 
			0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		pTexture = CTextureMgr::GetInstance()->GetTexture(L"MONSTER", L"Monster", (*iter)->info.drawID);
		D3DXVECTOR3 vec((float)pTexture->tImgInfo.Width/2, (float)pTexture->tImgInfo.Height/2, 0);

		CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
										NULL,	// 출력할 이미지의 크기를 결정, 렉트로 지정
										&vec,	// 출력할 이미지의 센터 지점을 결정
										NULL,	// 출력할 이미지의 위치를 지정
										D3DCOLOR_ARGB(drawAlpha, drawAlpha, drawAlpha, 255));
	}
}

void CMonster::MiniViewRender(void)
{
	const TEXINFO*	pTexture = NULL;
	D3DXMATRIX			matScale, matTrans, matWorld;

	float w = (float)WINCX / (float)(m_pMainView->m_tileX * TILECX);
	float h = ((float)WINCY / (float)(m_pMainView->m_tileY * TILECY)) * 2;


	list<UNITDATA*>::iterator iter = m_listUnit.begin();
	for( ; iter != m_listUnit.end(); iter++)
	{
		D3DXMatrixScaling(&matScale, w, h, 0.f);

		D3DXMatrixTranslation(&matTrans, 
			(*iter)->info.vPos.x * w, 
			(*iter)->info.vPos.y * h, 
			0.f);

		matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		pTexture = CTextureMgr::GetInstance()->GetTexture(L"MONSTER", L"Monster", (*iter)->info.drawID);
		D3DXVECTOR3 vec((float)pTexture->tImgInfo.Width/2, (float)pTexture->tImgInfo.Height/2, 0);

		CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
			NULL,	// 출력할 이미지의 크기를 결정, 렉트로 지정
			&vec,	// 출력할 이미지의 센터 지점을 결정
			NULL,	// 출력할 이미지의 위치를 지정
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

/* virtual */ const TEXINFO* CMonster::GetCurTexture(void)
{
	return m_pMainView->m_pMyForm->m_tabMonster.GetCurrentTexture();
}

/* virtual */ RECT	CMonster::GetCurrentObjectRect(const D3DXVECTOR3& center)
{
	RECT rect;
	rect.left = rect.top = rect.right = rect.bottom = 0;

	int listIdx = m_pMainView->m_pMyForm->m_tabMonster.m_list.GetCurSel();

	switch(listIdx)
	{
	case 0:
		{
			rect.left		= (m_pMainView->m_MousePoint.x - (LONG)center.x) + 20;
			rect.top		= (m_pMainView->m_MousePoint.y + (LONG)center.y) - 13;
			rect.right		= rect.left + 20;
			rect.bottom		= rect.top + 13;
		}
		return rect;
	}

	return rect;
}

/* virtual */ void CMonster::AddList(const D3DXVECTOR3& vPos)
{
	UNITDATA*		pUnit = new UNITDATA;

	// unit data save...
	SetUnitData(pUnit);

	pUnit->info.vPos = D3DXVECTOR3((float)vPos.x, (float)vPos.y, 0.f);
	pUnit->info.vSize = D3DXVECTOR3(1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&pUnit->info.matWorld,
							vPos.x - m_pMainView->GetScrollPos(0),
							vPos.y - m_pMainView->GetScrollPos(1),
							0.f);
		
	pUnit->info.vLook	= D3DXVECTOR3(1.f, 0.f, 0.f);
	pUnit->info.vDir	= D3DXVECTOR3(0.f, 0.f, 0.f);

	pUnit->info.drawID	 = m_pMainView->m_pMyForm->m_tabMonster.m_list.GetCurSel();
	m_listUnit.push_back(pUnit);

	m_pMainView->m_mstCount += 1;
	m_pMainView->m_pMyForm->m_tabMap.SetEditMonsterCount();
}

void CMonster::AddList(UNITDATA* pMonster)
{
	m_listUnit.push_back(pMonster);
}

void CMonster::SetUnitData(UNITDATA* data)
{
	CString str;

	m_pMainView->m_pMyForm->m_tabMonster.GetDlgItemText(IDC_EDIT_HP, str);
	data->iHP = _ttoi(str);

	m_pMainView->m_pMyForm->m_tabMonster.GetDlgItemText(IDC_EDIT_MP, str);
	data->iMP = _ttoi(str);

	m_pMainView->m_pMyForm->m_tabMonster.GetDlgItemText(IDC_EDIT_STR, str);
	data->iSTR = _ttoi(str);

	m_pMainView->m_pMyForm->m_tabMonster.GetDlgItemText(IDC_EDIT_DEF, str);
	data->iDEF = _ttoi(str);

	m_pMainView->m_pMyForm->m_tabMonster.GetDlgItemText(IDC_EDIT_INT, str);
	data->iINT = _ttoi(str);

	m_pMainView->m_pMyForm->m_tabMonster.GetDlgItemText(IDC_EDIT_REP, str);
	data->iREP = _ttoi(str);

	m_pMainView->m_pMyForm->m_tabMonster.GetDlgItemText(IDC_EDIT_DEX, str);
	data->iDEX = _ttoi(str);

	m_pMainView->m_pMyForm->m_tabMonster.GetDlgItemText(IDC_EDIT_EXP, str);
	data->iEXP = _ttoi(str);

	data->byState = 0; // normal
	data->byAttribute = m_pMainView->m_pMyForm->m_tabMonster.m_comboBox.GetCurSel();
}

void CMonster::Release()
{
	for_each(m_listUnit.begin(), m_listUnit.end(), DeleteObj());
	m_listUnit.clear();
	list<UNITDATA*>().swap(m_listUnit);

	m_pMainView->m_mstCount = 0;
}

void CMonster::RemoveObject(const CPoint point)
{
	const TEXINFO*		pTexture = NULL;

	list<UNITDATA*>::iterator iter = m_listUnit.begin();
	for( ; iter != m_listUnit.end(); )
	{
		pTexture = CTextureMgr::GetInstance()->GetTexture(L"MONSTER", L"Monster", (*iter)->info.drawID);
		D3DXVECTOR3 vec((float)pTexture->tImgInfo.Width/2, (float)pTexture->tImgInfo.Height/2, 0);

		RECT rect_;
		SetRect(&rect_, 0, 0, 0, 0);
		rect_.left		= (LONG)((*iter)->info.vPos.x - vec.x);
		rect_.top		= (LONG)((*iter)->info.vPos.y - vec.y);
		rect_.right		= rect_.left + pTexture->tImgInfo.Width;
		rect_.bottom	= rect_.top + pTexture->tImgInfo.Height;

		if( ( rect_.left <= point.x && point.x <= rect_.right ) &&
			( rect_.top <= point.y && point.y <= rect_.bottom ) )
		{
			UNITDATA*	pObj = *iter;
			iter =  m_listUnit.erase(iter);
			delete	pObj;

			m_pMainView->m_mstCount -= 1;

			return;
		}

		iter++;
	}
}