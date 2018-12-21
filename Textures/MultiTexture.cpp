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
			D3DX_DEFAULT,		// �׵θ� ǥ���� ��� �� ���ΰ�
			D3DX_DEFAULT,		// Ȯ��, ��� ���� ���
			NULL,				// ������ �̹��� ���� ��
			&pTexInfo->tImgInfo,
			NULL,				// �ȷ�Ʈ(8��Ʈ �̸��� �̹���) ó��
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
	MAPTEXINFO::iterator	iter = m_MapMultiTexture.find(wstrStateKey);	// key�� �� ã����

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
			Safe_Delete(iter->second[i]);			// delete �ϰ� !!
		}
		iter->second.clear();		// vector�� ��� ���� ����
	}
	m_MapMultiTexture.clear();		// map ������ ��� ������ ����
}
