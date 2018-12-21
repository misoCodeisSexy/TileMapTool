#include "StdAfx.h"
#include "TextureMgr.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr(void)
{
}

CTextureMgr::~CTextureMgr(void)
{
	Release();
}

HRESULT CTextureMgr::InsertTexture(const wstring& wstrFilePath, 
								   const wstring& wstrObjKey, 
								   TEXTYPE eTextype, 
								   const wstring& wstrStateKey /*= L""*/, 
								   const int& iCount /*= 0*/)
{
	MAPTEXTURE::iterator	iter  = m_MapTexture.find(wstrObjKey);

	if(iter == m_MapTexture.end())
	{
		CTexture*		pTexture = NULL;

		switch(eTextype)
		{
		case TEX_SINGLE:
			pTexture = new CSingleTexture;
			break;

		case TEX_MULTI:
			pTexture = new CMultiTexture;
			break;
		}

		if(FAILED(pTexture->InsertTexture(wstrFilePath, wstrStateKey, iCount)))
		{
			MSG_BOX(wstrObjKey.c_str());
			return E_FAIL;
		}

		m_MapTexture.insert(MAPTEXTURE::value_type(wstrObjKey, pTexture));
	}

	return	S_OK;
}

const TEXINFO* CTextureMgr::GetTexture(const wstring& wstrObjKey, 
									   const wstring& wstrStateKey /*= L""*/, 
									   const int& iCount /*= 0*/)
{
	MAPTEXTURE::iterator	iter  = m_MapTexture.find(wstrObjKey);

	if(iter == m_MapTexture.end())
		return NULL;

	return iter->second->GetTexture(wstrStateKey, iCount);
}

void CTextureMgr::Release(void)
{
	for_each(m_MapTexture.begin(), m_MapTexture.end(), DeleteMap());
	m_MapTexture.clear();
}
