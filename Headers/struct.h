#pragma once

typedef	struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;
	D3DXIMAGE_INFO			tImgInfo;
	BYTE					uniqueDrawID;	// 고유한 ID값, 겹칠 수 X
}TEXINFO;

typedef struct tagObject
{
	D3DXVECTOR3		vPos;
	BYTE			drawID;
}OBJECT;

typedef	struct tagTile
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vSize;
	char			byOption;		// 이동 가능 여부
	unsigned int	floor;			// 타일 높이
	std::list<BYTE>		listDrawID;
}TILE;

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vSize;
	D3DXMATRIX		matWorld;

	BYTE			drawID;
}INFO;

typedef struct tagUnitData
{
	std::wstring			wstrName;

	int						iHP;
	int						iMP;
	
	int						iSTR;	// 공격력
	int						iDEF;	// 방어력
	int						iINT;	// 지력
	int						iREP;	// 마항력
	int						iDEX;	// 민첩성
	
	BYTE					byState;		// 상태
	BYTE					byAttribute;	// 속성

	int						iEXP;			// 주는 경험치

	INFO					info;
}UNITDATA;
