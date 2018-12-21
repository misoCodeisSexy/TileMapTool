#pragma once

#include "Include.h"

class CMisoToolView;
class CBackGround
{

	enum DEFAULT_TILEID
	{
		DEFAULT_LINE = 0,
		DEFAULT_NONE
	};

private:
	vector<TILE*>				m_vecTile;
	CMisoToolView*				m_pMainView;

public:			// datas
	HRESULT		Initialize(void);
	void		Render(void);
	void		MiniViewRender(void);
	void		Release(void);
	void		TileChange(const D3DXVECTOR3& vPos, const BYTE& byDrawID);
	void		TileChangeAll(void);
	void		TileRemove(const D3DXVECTOR3& vPos);
	void		TileReset(void);

public:		// get, set
	void			SetMainView(CMisoToolView*	pMainView) { m_pMainView = pMainView; }
	void			SetTileCollider(int iIndex, bool bObject = false);
	void			SetIdxTileData(const int& iIdx, TILE* pTile);
	void			SetIdxTileData(const int& iIdx, unsigned int size, BYTE value[]);

	const size_t	GetTileSize(void) { return m_vecTile.size(); }
	D3DXVECTOR3		GetIdxTilePosition(const int& iIdx) { return m_vecTile[iIdx]->vPos; }
	TILE*			GetIdxTileData(const int& iIdx) { return m_vecTile[iIdx]; }

private:
	int			GetTileIndex(const D3DXVECTOR3& vPos);
	bool		Picking(const D3DXVECTOR3& vPos, const int& iIndex);

public:
	CBackGround(void);
	~CBackGround(void);
};
