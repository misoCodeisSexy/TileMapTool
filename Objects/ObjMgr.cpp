#include "StdAfx.h"
#include "ObjMgr.h"

#include "MisoToolView.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr(void)
{
}

CObjMgr::~CObjMgr(void)
{
	
}

void CObjMgr::AlpaRender(CObj* obj, CMisoToolView* pView)
{
	D3DXMATRIX			matTrans;
	const TEXINFO* curTex = obj->GetCurTexture();
	if( curTex == NULL ) return;

	D3DXVECTOR3 vec((float)curTex->tImgInfo.Width/2, (float)curTex->tImgInfo.Height/2, 0.f);

	D3DXMatrixTranslation(&matTrans, 
							(float)pView->m_MousePoint.x,
							(float)pView->m_MousePoint.y,
							0.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

	CDevice::GetInstance()->GetSprite()->Draw(curTex->pTexture
											, NULL
											, &vec
											, NULL
											, D3DCOLOR_ARGB(127,127,127,225));
}	

void CObjMgr::OnAdd(CObj* obj, const D3DXVECTOR3& vPos, CMisoToolView* pView, CBackGround* pBackGround)
{
	const size_t tileSize = pBackGround->GetTileSize();

	bool isAdded_ = false;
	for(size_t i = 0; i < tileSize; ++i)
	{
		Picking(obj, vPos, i, isAdded_, pView, pBackGround);
	}
}

void CObjMgr::Picking(CObj* obj, const D3DXVECTOR3& vPos, const int& iIndex, bool& isAdded, CMisoToolView* pView, CBackGround* pBackGround)
{
	D3DXVECTOR3 vecPos = pBackGround->GetIdxTilePosition(iIndex);

	vecPos.x = vecPos.x - pView->GetScrollPos(0);
	vecPos.y = vecPos.y - pView->GetScrollPos(1);

	// 마름모 꼭지점 만들기
	D3DXVECTOR3		vPoint[4] =
	{
		D3DXVECTOR3(vecPos.x, vecPos.y - (pView->m_tileX / 2.f), 0.f),
		D3DXVECTOR3(vecPos.x + (pView->m_tileX / 2.f), vecPos.y, 0.f),
		D3DXVECTOR3(vecPos.x, vecPos.y + (pView->m_tileY / 2.f), 0.f),
		D3DXVECTOR3(vecPos.x - (pView->m_tileX / 2.f), vecPos.y, 0.f)
	};

	const TEXINFO* curTex = obj->GetCurTexture();
	D3DXVECTOR3 vec((float)curTex->tImgInfo.Width/2, (float)curTex->tImgInfo.Height/2, 0);
	RECT rect = obj->GetCurrentObjectRect(vec);

	if( vPoint[3].x <= rect.right &&
		vPoint[1].x >= rect.left)
	{
		if( vPoint[0].y <= rect.bottom &&
			vPoint[2].y >= rect.top )
		{
			pBackGround->SetTileCollider(iIndex, true);

			if( isAdded == false )
			{
				obj->AddList(vPos);
				isAdded = true;
			}

			return;
		}
	}
}
