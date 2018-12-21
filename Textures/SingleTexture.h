#pragma once

#include "texture.h"

class CSingleTexture : public CTexture
{
public:
	CSingleTexture(void);
	virtual ~CSingleTexture(void);

public:
	virtual HRESULT InsertTexture(const wstring& wstrFilePath, 
								const wstring& wstrStateKey = L"", 
								const int& iCount = 0);
	
	virtual const TEXINFO* GetTexture(const wstring& wstrStateKey = L"", 
									  const int& iCount = 0);
	virtual void Release(void);

private:
	TEXINFO*				m_pTexInfo;

};
