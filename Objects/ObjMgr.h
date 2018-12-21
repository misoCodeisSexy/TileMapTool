#pragma once

#include "Obj.h"

class CBackGround;
class CMisoToolView;
class CObjMgr
{

DECLARE_SINGLETON(CObjMgr)

public:
	void	AlpaRender(CObj* obj, CMisoToolView* pView);
	void	OnAdd(CObj* obj, const D3DXVECTOR3& vPos, CMisoToolView* pView, CBackGround* pBackGround);

private:
	void	Picking(CObj* obj, const D3DXVECTOR3& vPos, const int& iIndex, bool& isAdded, CMisoToolView* pView, CBackGround* pBackGround);

public:
	CObjMgr(void);
	~CObjMgr(void);
};
