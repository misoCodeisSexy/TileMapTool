#include "StdAfx.h"
#include "MultiTexture.h"

CMultiTexture::CMultiTexture(void)
{
}

CMultiTexture::~CMultiTexture(void)
{
	Release();
}

HRESULT CMultiTexture::InsertTexture(const wstring& wstrFilePath, const wstring& wstrStateKey /*= L""*/, const int& iCount /*= 0*/)
{
	TCHAR		szPath[MAX_PATH] = L"";

	vector<TEXINFO*>		vecTexture;

	for(int i = 0; i < iCount; ++i)
	{
		wsprintf(szPath, wstrFilePath.c_str(), i);

		TEXINFO*		pTexInfo = new TEXINFO;
		ZeroMemory(pTexInfo, sizeof(TEXINFO));

		pTexInfo->uniqueDrawID = i;

		if(FAILED(D3DXGetImageInfoFromFile(szPath, &pTexInfo->tImgInfo)))
		{
			MSG_BOX(szPath);
			return E_FAIL;
		}

		if(FAILED(D3DXCreateTextureFromFileEx(m_pDevice->GetDevice(), 
			szPath, 
			pTexInfo->tImgInfo.Width, 
			pTexInfo->tImgInfo.Height, 
			pTexInfo->tImgInfo.MipLevels,
			0, 
			pTexInfo->tImgInfo.Format,
			D3DPOOL_MANAGED, 
			D3DX_DEFAULT,		// 테두리 표현을 어떻게 할 것인가
			D3DX_DEFAULT,		// 확대, 축소 했을 경우
			NULL,				// 제거할 이미지 색상 값
			&pTexInfo->tImgInfo,
			NULL,				// 팔레트(8비트 미만의 이미지) 처리
			&pTexInfo->pTexture)))
		{
			MSG_BOX(L"Multi Texture Image Load Failed");
			return E_FAIL;
		}

		vecTexture.push_back(pTexInfo);
	}

	m_MapMultiTexture.insert(MAPTEXINFO::value_type(wstrStateKey, vecTexture));
	
	
	return S_OK;
}

const TEXINFO* CMultiTexture::GetTexture(const wstring& wstrStateKey /*= L""*/, 
										 const int& iCount /*= 0*/)
{
	MAPTEXINFO::iterator	iter = m_MapMultiTexture.find(wstrStateKey);	// key로 값 찾아줌

	if(iter == m_MapMultiTexture.end())
		return NULL;

	return iter->second[iCount];
}

void CMultiTexture::Release(void)
{
	MAPTEXINFO::iterator iter		= m_MapMultiTexture.begin();
	MAPTEXINFO::iterator iter_end	= m_MapMultiTexture.end();

	for(	;iter != iter_end; ++iter)
	{
		for(size_t i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->pTexture->Release();
			Safe_Delete(iter->second[i]);			// delete 하고 !!
		}
		iter->second.clear();		// vector의 모든 원소 제거
	}
	m_MapMultiTexture.clear();		// map 내부의 모든 데이터 제거
}
