#pragma once

class CMisoToolView;
class CMonster : CObj
{
private:
	list<UNITDATA*>			m_listUnit;
	CMisoToolView*			m_pMainView;

public:
	HRESULT		Initialize(void);
	void		Release(void);

	void		Render(void);
	void		MiniViewRender(void);

	void		RemoveObject(const CPoint point);
	void		AddList(UNITDATA* pMonster);

public:
	void			SetMainView(CMisoToolView*	pMainView) { m_pMainView = pMainView; }
	list<UNITDATA*>	GetMonsterList() { return m_listUnit; }

public:
	virtual const TEXINFO*	GetCurTexture(void);
	virtual RECT			GetCurrentObjectRect(const D3DXVECTOR3& center);
	virtual void			AddList(const D3DXVECTOR3& vPos);

public:
	CMonster(void);
	virtual ~CMonster(void);

private:
	void SetUnitData(UNITDATA* data);
};
