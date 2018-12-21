#pragma once

class CMisoToolView;
class CMyObject : CObj
{
private:
	list<OBJECT*>		m_listObject;
	CMisoToolView*		m_pMainView;

public:
	HRESULT		Initialize(void);
	void		Release(void);

	void		Render(void);
	void		MiniViewRender(void);

	void		RemoveObject(const CPoint point);

	void		AddList(OBJECT* pObject);

public:		// get, set
	void				SetMainView(CMisoToolView*	pMainView) { m_pMainView = pMainView; }
	list<OBJECT*>		GetObjList() { return m_listObject; }

public:		// virtual
	virtual const TEXINFO*	GetCurTexture(void);
	virtual RECT			GetCurrentObjectRect(const D3DXVECTOR3& center);
	virtual void			AddList(const D3DXVECTOR3& vPos);

public:
	CMyObject(void);
	virtual ~CMyObject(void);
};
