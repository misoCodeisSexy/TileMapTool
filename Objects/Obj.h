#pragma once

class CObj
{
public:
	virtual const TEXINFO*	GetCurTexture(void){ return NULL; }

	virtual RECT			GetCurrentObjectRect(const D3DXVECTOR3& center)
	{
		RECT rect;
		rect.left = rect.top = rect.right = rect.bottom = 0;
		return 	rect;
	}

	virtual void			AddList(const D3DXVECTOR3& vPos){ }

public:
	CObj(void);
	virtual ~CObj(void);
};
