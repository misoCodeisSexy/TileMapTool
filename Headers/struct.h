#pragma once

typedef	struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;
	D3DXIMAGE_INFO			tImgInfo;
	BYTE					uniqueDrawID;	// ������ ID��, ��ĥ �� X
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
	char			byOption;		// �̵� ���� ����
	unsigned int	floor;			// Ÿ�� ����
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
	
	int						iSTR;	// ���ݷ�
	int						iDEF;	// ����
	int						iINT;	// ����
	int						iREP;	// ���׷�
	int						iDEX;	// ��ø��
	
	BYTE					byState;		// ����
	BYTE					byAttribute;	// �Ӽ�

	int						iEXP;			// �ִ� ����ġ

	INFO					info;
}UNITDATA;
