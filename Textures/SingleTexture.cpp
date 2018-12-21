#include "StdAfx.h"
#include "SingleTexture.h"

CSingleTexture::CSingleTexture(void)
: m_pTexInfo(NULL)
{
}

CSingleTexture::~CSingleTexture(void)
{
	 Release();
}

HRESULT CSingleTexture::InsertTexture(const wstring& wstrFilePath, const wstring& wstrStateKey /*= L""*/, const int& iCount /*= 0*/)
{
	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	m_pTexInfo->uniqueDrawID = iCount;

	// 지정한 이미지 파일에 대한 정보를 받아온다
	if(FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_pTexInfo->tImgInfo)))
	{
		MSG_BOX(wstrFilePath.c_str());
		return E_FAIL;
	}

	// 파일을 기본으로 해서 텍스쳐를 생성
	if(FAILED(D3DXCreateTextureFromFileEx(m_pDevice->GetDevice(), 
		wstrFilePath.c_str(), 
		m_pTexInfo->tImgInfo.Width, 
		m_pTexInfo->tImgInfo.Height, 
		m_pTexInfo->tImgInfo.MipLevels,
		0, 
		m_pTexInfo->tImgInfo.Format,
		D3DPOOL_MANAGED, 
		D3DX_DEFAULT,		// 테두리 표현을 어떻게 할 것인가
		D3DX_DEFAULT,		// 확대, 축소 했을 경우
		NULL,				// 제거할 이미지 색상 값
		&m_pTexInfo->tImgInfo,
		NULL,				// 팔레트(8비트 미만의 이미지) 처리
		&m_pTexInfo->pTexture)))
	{
		MSG_BOX(L"Single Texture Image Load Failed");
		return E_FAIL;
	}		


	return S_OK;
}

const TEXINFO* CSingleTexture::GetTexture(const wstring& wstrStateKey /*= L""*/, const int& iCount /*= 0*/)
{
	return m_pTexInfo;
}

void CSingleTexture::Release(void)
{
	m_pTexInfo->pTexture->Release();

	::Safe_Delete(m_pTexInfo);
}