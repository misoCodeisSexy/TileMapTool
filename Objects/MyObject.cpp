#include "StdAfx.h"
#include "MyObject.h"
#include "MisoToolView.h"

#include "resource.h"
#include "MyForm.h"

#include "BackGround.h"

CMyObject::CMyObject(void)
{
}

/*virtual*/ CMyObject::~CMyObject(void)
{
	Release();
}

HRESULT CMyObject::Initialize(void)
{
	return S_OK;
}

void CMyObject::Render(void)
{
	const TEXINFO*	pTexture = NULL;
	D3DXMATRIX		matTrans;
	const int drawAlpha = m_pMainView->m_pMyForm->m_tabObject.m_ctrlSlider.GetPos();

	list<OBJECT*>::iterator iter = m_listObject.begin();
	for( ; iter != m_listObject.end(); iter++)
	{
		D3DXMatrixTranslation(&matTrans, 
			(*iter)->vPos.x - m_pMainView->GetScrollPos(0), 
			(*iter)->vPos.y - m_pMainView->GetScrollPos(1), 
			0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		pTexture = CTextureMgr::GetInstance()->GetTexture(L"OBJECT", L"Object", (*iter)->drawID);
		D3DXVECTOR3 vec((float)pTexture->tImgInfo.Width/2, (float)pTexture->tImgInfo.Height/2, 0);

		CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
			NULL,	// 출력할 이미지의 크기를 결정, 렉트로 지정
			&vec,	// 출력할 이미지의 센터 지점을 결정
			NULL,	// 출력할 이미지의 위치를 지정
			D3DCOLOR_ARGB(drawAlpha, drawAlpha, drawAlpha, 255));

		/*
		
			디버깅..
		
		RECT rect_;
		SetRect(&rect_, 0, 0, 0, 0);
		rect_.left		= (LONG)(*iter)->vPos.x - vec.x;
		rect_.top		= (LONG)(*iter)->vPos.y - vec.y;
		rect_.right		= rect_.left + pTexture->tImgInfo.Width;
		rect_.bottom	= rect_.top + pTexture->tImgInfo.Height;

		CClientDC dc(m_pMainView);
		dc.Rectangle(&rect_);*/
	}
}

/* virtual */ const TEXINFO* CMyObject::GetCurTexture()
{
	return m_pMainView->m_pMyForm->m_tabObject.GetCurrentTexture();
}

void CMyObject::MiniViewRender(void)
{
	const TEXINFO*	pTexture = NULL;
	D3DXMATRIX			matScale, matTrans, matWorld;

	float w = (float)WINCX / (float)(m_pMainView->m_tileX * TILECX);
	float h = ((float)WINCY / (float)(m_pMainView->m_tileY * TILECY)) * 2;


	list<OBJECT*>::iterator iter = m_listObject.begin();
	for( ; iter != m_listObject.end(); iter++)
	{
		D3DXMatrixScaling(&matScale, w, h, 0.f);

		D3DXMatrixTranslation(&matTrans, 
			(*iter)->vPos.x * w, 
			(*iter)->vPos.y * h, 
			0.f);

		matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		pTexture = CTextureMgr::GetInstance()->GetTexture(L"OBJECT", L"Object", (*iter)->drawID);
		D3DXVECTOR3 vec((float)pTexture->tImgInfo.Width/2, (float)pTexture->tImgInfo.Height/2, 0);

		CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture,
			NULL,	// 출력할 이미지의 크기를 결정, 렉트로 지정
			&vec,	// 출력할 이미지의 센터 지점을 결정
			NULL,	// 출력할 이미지의 위치를 지정
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CMyObject::Release(void)
{
	for_each(m_listObject.begin(), m_listObject.end(), DeleteObj());
	m_listObject.clear();
	list<OBJECT*>().swap(m_listObject);
}


/* virtual */ RECT CMyObject::GetCurrentObjectRect(const D3DXVECTOR3& center)
{
	RECT rect;
	rect.left = rect.top = rect.right = rect.bottom = 0;

	int listIdx = m_pMainView->m_pMyForm->m_tabObject.m_list.GetCurSel();

	switch(listIdx)
	{
	case 0:
		{
			rect.left		= (m_pMainView->m_MousePoint.x - (LONG)center.x) + 17;
			rect.top		= (m_pMainView->m_MousePoint.y + (LONG)center.y) - 13;
			rect.right		= rect.left + 30;
			rect.bottom		= rect.top + 13;
		}
		return rect;
	case 2:
		{
			rect.left		= (m_pMainView->m_MousePoint.x - (LONG)center.x) + 10;
			rect.top		= (m_pMainView->m_MousePoint.y + (LONG)center.y) - 30;
			rect.right		= rect.left + 85;
			rect.bottom		= rect.top + 30;
		}
		return rect;
	case 6:
		{
			rect.left		= (m_pMainView->m_MousePoint.x - (LONG)center.x) + 10;
			rect.top		= (m_pMainView->m_MousePoint.y + (LONG)center.y) - 13;
			rect.right		= rect.left + 20;
			rect.bottom		= rect.top + 10;
		}
		return rect;
	case 9:
		{
			rect.left		= (m_pMainView->m_MousePoint.x - (LONG)center.x) + 15;
			rect.top		= (m_pMainView->m_MousePoint.y + (LONG)center.y) - 22;
			rect.right		= rect.left + 30;
			rect.bottom		= rect.top + 13;
		}
		return rect;
	}

	return rect;
}

/*virtual*/ void CMyObject::AddList(const D3DXVECTOR3& vPos)
{
	OBJECT*			pObject = new OBJECT;
	pObject->vPos	= D3DXVECTOR3((float)vPos.x, (float)vPos.y, 0.f);
	pObject->drawID = m_pMainView->m_pMyForm->m_tabObject.m_list.GetCurSel();
	m_listObject.push_back(pObject);

	m_pMainView->m_objCount += 1;
	m_pMainView->m_pMyForm->m_tabMap.SetEditObjctCount();
}

void CMyObject::AddList(OBJECT* pObject)
{
	m_listObject.push_back(pObject);
}

void CMyObject::RemoveObject(const CPoint point)
{
	const TEXINFO*		pTexture = NULL;

	list<OBJECT*>::iterator iter = m_listObject.begin();
	for( ; iter != m_listObject.end(); )
	{
		pTexture = CTextureMgr::GetInstance()->GetTexture(L"OBJECT", L"Object", (*iter)->drawID);
		D3DXVECTOR3 vec((float)pTexture->tImgInfo.Width/2, (float)pTexture->tImgInfo.Height/2, 0);

		RECT rect_;
		SetRect(&rect_, 0, 0, 0, 0);
		rect_.left		= (LONG)((*iter)->vPos.x - vec.x);
		rect_.top		= (LONG)((*iter)->vPos.y - vec.y);
		rect_.right		= rect_.left + pTexture->tImgInfo.Width;
		rect_.bottom	= rect_.top + pTexture->tImgInfo.Height;

		if( ( rect_.left <= point.x && point.x <= rect_.right ) &&
			( rect_.top <= point.y && point.y <= rect_.bottom ) )
		{
			OBJECT*	pObj = *iter;
			iter =  m_listObject.erase(iter);
			delete	pObj;

			m_pMainView->m_objCount -= 1;

			return;
		}

		iter++;
	}
}