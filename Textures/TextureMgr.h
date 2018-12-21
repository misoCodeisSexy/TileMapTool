#pragma once

class CTexture;
class CTextureMgr
{

DECLARE_SINGLETON(CTextureMgr)

private:
	map<wstring, CTexture*>				m_MapTexture;
	typedef	map<wstring, CTexture*>		MAPTEXTURE;

public:
	HRESULT	InsertTexture(const wstring& wstrFilePath, 
								  const wstring& wstrObjKey, 
								  TEXTYPE eTextype,
								  const wstring& wstrStateKey = L"", 
								  const int& iCount = 0) ;

	const TEXINFO*	GetTexture( const wstring& wstrObjKey, 
								const wstring& wstrStateKey = L"", 
								const int& iCount = 0) ;

	void			Release(void);

private:
	CTextureMgr(void);
public:
	~CTextureMgr(void);
};
