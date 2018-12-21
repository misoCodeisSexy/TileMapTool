#pragma once
#include "texture.h"

class CMultiTexture :
	public CTexture
{
private:
	typedef	vector<TEXINFO*>					VECTEXINFO;
	typedef map<wstring, VECTEXINFO>			MAPTEXINFO;

	MAPTEXINFO									m_MapMultiTexture;
	
public:
	CMultiTexture(void);
	~CMultiTexture(void);

public:
	virtual HRESULT InsertTexture(const wstring& wstrFilePath, 
									const wstring& wstrStateKey = L"", 
									const int& iCount = 0);
	
	virtual const TEXINFO* GetTexture(const wstring& wstrStateKey = L"", 
										const int& iCount = 0);
	
	virtual void Release(void);

};
