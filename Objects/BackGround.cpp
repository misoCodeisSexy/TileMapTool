#include "StdAfx.h"
#include "BackGround.h"
#include "MisoToolView.h"

#include "resource.h"
#include "MyForm.h"

CBackGround::CBackGround(void)
{
}

CBackGround::~CBackGround(void)
{
	Release();
}

HRESULT CBackGround::Initialize(void)
{
	m_vecTile.reserve(m_pMainView->m_tileX * m_pMainView->m_tileY);
	for(int i = 0; i < m_pMainView->m_tileY; ++i)
	{
		for(int j = 0; j < m_pMainView->m_tileX; ++j)
		{
			TILE*		pTile = new TILE;

			float fx = j * TILECX + ((i % 2) * (TILECX / 2.f));
			float fy = i * (TILECY / 2.f);

			pTile->vPos     = D3DXVECTOR3(fx, fy, 0.f);
			pTile->vSize    = D3DXVECTOR3((float)TILECX, (float)TILECY, 0.f);
			pTile->byOption = -1;
			pTile->listDrawID.push_back(1);
			pTile->floor	= 0;

			m_vecTile.push_back(pTile);
		}
	}

	return S_OK;
}

void CBackGround::Render(void)
{
	const TEXINFO*		pTexture = NULL;
	D3DXMATRIX			matTrans;
	TCHAR				szBuf[MIN_STR] = L"";

#pragma region 픽킹 타일 그리기
	for(int i = 0; i < m_pMainView->m_tileY; ++i)
	{
		for(int j = 0; j < m_pMainView->m_tileX; ++j)
		{
			int iIndex = i * m_pMainView->m_tileX + j;

			D3DXMatrixTranslation(&matTrans, 
				m_vecTile[iIndex]->vPos.x - m_pMainView->GetScrollPos(0), 
				m_vecTile[iIndex]->vPos.y - m_pMainView->GetScrollPos(1), 
				0.f);

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			list<BYTE>::iterator iter;
			if( m_vecTile[iIndex]->floor >= 1 )
			{
				float flrDist = (float)FLOOR_DIST;
				for(iter = m_vecTile[iIndex]->listDrawID.begin(); iter != m_vecTile[iIndex]->listDrawID.end(); ++iter )
				{
					if( iter == m_vecTile[iIndex]->listDrawID.end() )
					{
						// error...
						MSG_BOX(L"miso @ list Error!");
					}

					pTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", 
						L"Tile", *iter);

					if( pTexture->tImgInfo.Height == TILECY )
					{
						CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
							NULL, // 출력할 이미지의 크기를 결정, 렉트로 지정
							&D3DXVECTOR3(31.f, flrDist, 0.f), // 출력할 이미지의 센터 지점을 결정
							NULL, // 출력할 이미지의 위치를 지정
							D3DCOLOR_ARGB(255, 255, 255, 255));
					}
					else
					{
						CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
							NULL, // 출력할 이미지의 크기를 결정, 렉트로 지정
							&D3DXVECTOR3(31.f, 16+flrDist, 0.f), // 출력할 이미지의 센터 지점을 결정
							NULL, // 출력할 이미지의 위치를 지정
							D3DCOLOR_ARGB(255, 255, 255, 255));

						flrDist += (float)FLOOR_DIST;
					}
				}	
			}
			else
			{
				pTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", 
					L"Tile", m_vecTile[iIndex]->listDrawID.front());

				CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
					NULL, // 출력할 이미지의 크기를 결정, 렉트로 지정
					&D3DXVECTOR3(31.f, 16.f, 0.f), // 출력할 이미지의 센터 지점을 결정
					NULL, // 출력할 이미지의 위치를 지정
					D3DCOLOR_ARGB(255, 255, 255, 255));
			}

			if( m_pMainView->m_pMyForm->m_tabTile.m_CheckBtn.GetCheck() == 1 )
			{
				wsprintf(szBuf, L"%d", iIndex);	
				CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(), 
					szBuf, lstrlen(szBuf), 
					NULL, NULL, D3DCOLOR_ARGB(255, 0, 0, 0));
			}
		}
	}
#pragma endregion

#pragma region 백그라운드 그리기
	for(int i = 0; i < m_pMainView->m_tileY; ++i)
	{
		for(int j = 0; j < m_pMainView->m_tileX; ++j)
		{
			int	iIndex = i * m_pMainView->m_tileX + j;

			if( m_pMainView->m_pMyForm->m_tabTile.m_radio == 0 )	// none
			{
				pTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", 
					L"Tile", DEFAULT_NONE);
			}
			else
			{
				pTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", 
					L"Tile", DEFAULT_LINE);
			}

			// mfc GetScrollPos( 0(x) or 1(y) )   => 스크롤 상자 내부 스크롤 바의 현재 위치를 검색합니다.
			// ID3DXSprite.SetTransform( matrix ) => 스프라이트에 대한 변환행렬을 지정합니다.

			D3DXMatrixTranslation(&matTrans, 
				m_vecTile[iIndex]->vPos.x - m_pMainView->GetScrollPos(0), 
				m_vecTile[iIndex]->vPos.y - m_pMainView->GetScrollPos(1), 
				0.f);

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
				NULL, // 출력할 이미지의 크기를 결정, 렉트로 지정
				&D3DXVECTOR3(31.f, 16.f, 0.f), // 출력할 이미지의 센터 지점을 결정
				NULL, // 출력할 이미지의 위치를 지정
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
#pragma endregion

#pragma region 콜라이더 그리기

	if( m_pMainView->m_pMyForm->m_tabCollider.m_checkBtn.GetCheck() == 1 )
	{
		for(int i = 0; i < m_pMainView->m_tileY; ++i)
		{
			for(int j = 0; j < m_pMainView->m_tileX; ++j)
			{
				int	iIndex = i * m_pMainView->m_tileX + j;

				if( m_vecTile[iIndex]->byOption > -1 )		// take option
				{
					pTexture = CTextureMgr::GetInstance()->GetTexture(L"COLTILE", 
						L"ColTile", m_vecTile[iIndex]->byOption );
				}
				else
				{
					pTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", 
						L"Tile", DEFAULT_NONE);
				}

				D3DXMatrixTranslation(&matTrans, 
					m_vecTile[iIndex]->vPos.x - m_pMainView->GetScrollPos(0), 
					m_vecTile[iIndex]->vPos.y - m_pMainView->GetScrollPos(1), 
					0.f);

				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
					NULL, // 출력할 이미지의 크기를 결정, 렉트로 지정
					&D3DXVECTOR3(31.f, 16.f, 0.f), // 출력할 이미지의 센터 지점을 결정
					NULL, // 출력할 이미지의 위치를 지정
					D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
	}
	
#pragma endregion
}

void CBackGround::MiniViewRender(void)
{
	const TEXINFO*		pTexture = NULL;
	D3DXMATRIX			matScale, matTrans, matWorld;

	float w = (float)WINCX / (float)(m_pMainView->m_tileX * TILECX);
	float h = ((float)WINCY / (float)(m_pMainView->m_tileY * TILECY)) * 2;

#pragma region Line
	for(int i = 0; i < m_pMainView->m_tileY; ++i)
	{
		for(int j = 0; j < m_pMainView->m_tileX; ++j)
		{
			int idx = i * m_pMainView->m_tileX + j;
			pTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile",
													DEFAULT_LINE);

			D3DXMatrixScaling(&matScale, w, h, 0.f);

			D3DXMatrixTranslation(&matTrans
								, m_vecTile[idx]->vPos.x * w
								, m_vecTile[idx]->vPos.y * h
								, 0.f);

			matWorld = matScale * matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture
						, NULL		// 출력할 이미지의 크기를 결정, 렉트로 지정
						, &D3DXVECTOR3(31.f, 16.f, 0.f)	// 출력할 이미지의 센터 지점 결정
						, NULL		// 출력할 이미지의 위치 지정
						, D3DCOLOR_ARGB(255,255,255,255));
		}
	}
#pragma endregion

#pragma region 타일

	for(int i = 0; i < m_pMainView->m_tileY; ++i)
	{
		for(int j = 0; j < m_pMainView->m_tileX; ++j)
		{
			int idx = i * m_pMainView->m_tileX + j;
			if( m_vecTile[idx]->floor >= 1 )
			{
				list<BYTE>::iterator iter;
				float dist = (float)FLOOR_DIST;
				for(iter = m_vecTile[idx]->listDrawID.begin(); iter != m_vecTile[idx]->listDrawID.end(); ++iter)
				{
					pTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile", *iter);
					
					D3DXMatrixScaling(&matScale, w, h, 0.f);
					
					D3DXMatrixTranslation(&matTrans
						, m_vecTile[idx]->vPos.x * w
						, m_vecTile[idx]->vPos.y * h
						, 0.f);

					matWorld = matScale * matTrans;

					CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);


					if( pTexture->tImgInfo.Height == TILECY )
					{
						CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
							NULL, // 출력할 이미지의 크기를 결정, 렉트로 지정
							&D3DXVECTOR3(31.f, dist, 0.f), // 출력할 이미지의 센터 지점을 결정
							NULL, // 출력할 이미지의 위치를 지정
							D3DCOLOR_ARGB(255, 255, 255, 255));
					}
					else
					{
						CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
							NULL, // 출력할 이미지의 크기를 결정, 렉트로 지정
							&D3DXVECTOR3(31.f, 16+dist, 0.f), // 출력할 이미지의 센터 지점을 결정
							NULL, // 출력할 이미지의 위치를 지정
							D3DCOLOR_ARGB(255, 255, 255, 255));

						dist += (float)FLOOR_DIST;
					}
				}		
			}
			else
			{
				pTexture = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile",
					m_vecTile[idx]->listDrawID.front());

				D3DXMatrixScaling(&matScale, w, h, 0.f);

				D3DXMatrixTranslation(&matTrans
					, m_vecTile[idx]->vPos.x * w
					, m_vecTile[idx]->vPos.y * h
					, 0.f);

				matWorld = matScale * matTrans;

				CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

				CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture
					, NULL		// 출력할 이미지의 크기를 결정, 렉트로 지정
					, &D3DXVECTOR3(31.f, 16.f, 0.f)	// 출력할 이미지의 센터 지점 결정
					, NULL		// 출력할 이미지의 위치 지정
					, D3DCOLOR_ARGB(255,255,255,255));
			}
		}
	}
#pragma endregion

}

void CBackGround::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), DeleteObj());
	m_vecTile.clear();
	vector<TILE*>().swap(m_vecTile);
}

int CBackGround::GetTileIndex(const D3DXVECTOR3& vPos)
{
	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if(Picking(vPos, i))
		{
			return i;
		}
	}

	return -1;
}

void CBackGround::TileChange(const D3DXVECTOR3& vPos, const BYTE& byDrawID)
{
	int	iIndex = GetTileIndex(vPos);

	if(-1 == iIndex ) return;

	// 콜라이더 타일 모드일 경우
	if( m_pMainView->m_pMyForm->m_sTabCurState == IDD_TABCOLLIDER )
	{
		SetTileCollider(iIndex);
		return;
	}

	const TEXINFO* texInfo = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile", byDrawID);

	if( texInfo->tImgInfo.Height > TILECY )
	{
		if(m_vecTile[iIndex]->floor == 0)
			m_vecTile[iIndex]->listDrawID.pop_back();

		m_vecTile[iIndex]->floor += 1; 
		m_vecTile[iIndex]->listDrawID.push_back(byDrawID);
	}
	else if ( m_vecTile[iIndex]->floor >= 1 && texInfo->tImgInfo.Height == TILECY )
	{
		texInfo = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile", m_vecTile[iIndex]->listDrawID.back());
		if(texInfo->tImgInfo.Height == TILECY)
		{
			m_vecTile[iIndex]->listDrawID.pop_back();
		}
		
		m_vecTile[iIndex]->listDrawID.push_back(byDrawID);
	}
	else
	{
		m_vecTile[iIndex]->listDrawID.front() = byDrawID;
	}	
}

void CBackGround::SetTileCollider(int iIndex, bool bObject /* = false */)
{
	const TEXINFO* texInfo = m_pMainView->m_pMyForm->m_tabCollider.SetTileImage(bObject);
	m_vecTile[iIndex]->byOption = texInfo->uniqueDrawID;
}

void CBackGround::TileChangeAll(void)
{
	const TEXINFO* texInfo = NULL;

	// 콜라이더 타일 모드일 경우
	if( m_pMainView->m_pMyForm->m_sTabCurState == IDD_TABCOLLIDER )
	{
		texInfo = m_pMainView->m_pMyForm->m_tabCollider.SetTileImage();

		vector<TILE*>::iterator iter;
		for(iter = m_vecTile.begin(); iter != m_vecTile.end(); ++iter)
		{
			(*iter)->byOption = texInfo->uniqueDrawID;
		}
	}
	else
	{
		texInfo = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile", m_pMainView->m_drawID);

		int floor_ = 0;
		if( texInfo->tImgInfo.Height > TILECY ) floor_ = 1;

		vector<TILE*>::iterator iter;
		for(iter = m_vecTile.begin(); iter != m_vecTile.end(); ++iter)
		{
			(*iter)->listDrawID.clear();	// 한 타일 내에 있는 층타일 전부 삭제
			(*iter)->listDrawID.push_back(m_pMainView->m_drawID);	// 기본 타일로 적용
			(*iter)->floor = floor_;
		}
	}

	m_pMainView->Invalidate(FALSE);
}

// 타일 오른쪽 클릭 시, 층타일 제거하는거
void CBackGround::TileRemove(const D3DXVECTOR3& vPos)
{
	int	iIndex = GetTileIndex(vPos);

	if( -1 == iIndex || m_vecTile[iIndex]->listDrawID.back() == 1 )
		return;

	const TEXINFO* texInfo = NULL;
	texInfo = CTextureMgr::GetInstance()->GetTexture(L"TILE", L"Tile",m_vecTile[iIndex]->listDrawID.back());

	m_vecTile[iIndex]->listDrawID.pop_back();  

	if( texInfo->tImgInfo.Height > TILECY )
	{
		// 층 타일 1개 있을 때	 삭제 후 
		if( m_vecTile[iIndex]->floor == 1 )
		{
			m_vecTile[iIndex]->listDrawID.push_back(1);		// 바닥재 추가
		}

		m_vecTile[iIndex]->floor -= 1;
	}
	// 바닥재만 있는 경우
	else if( m_vecTile[iIndex]->floor == 0 )
	{
		m_vecTile[iIndex]->listDrawID.push_back(1);
	}
}

void CBackGround::TileReset(void)
{
	Release();
	Initialize();
}

void CBackGround::SetIdxTileData(const int& iIdx, TILE* pTile)
{
	m_vecTile[iIdx]->vPos = pTile->vPos;
	m_vecTile[iIdx]->vSize = pTile->vSize;
	m_vecTile[iIdx]->byOption = pTile->byOption;
	m_vecTile[iIdx]->floor = pTile->floor;
}

void CBackGround::SetIdxTileData(const int& iIdx, unsigned int size, BYTE value[])
{
	m_vecTile[iIdx]->listDrawID.clear();

	for(unsigned int i=0; i < size; ++i)
	{
		m_vecTile[iIdx]->listDrawID.push_back(value[i]);
	}
}

bool CBackGround::Picking(const D3DXVECTOR3& vPos, const int& iIndex)
{
	D3DXVECTOR3			vPoint[4] = 
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - (TILECX / 2.f), m_vecTile[iIndex]->vPos.y , 0.f)
	};

	D3DXVECTOR3		vDirection[4] = 
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	for(int i = 0; i < 4; ++i)
	{
		D3DXVECTOR3	vDestDir = vPos - vPoint[i];
		const bool isCcw = IsCw( vDestDir, vDirection[i]);
		if( isCw == false )
			return false;
	}
	
	return true;
}

