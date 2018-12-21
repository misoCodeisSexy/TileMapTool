#pragma once
#include "afxwin.h"


// CTabMonster ��ȭ �����Դϴ�.

class CTabMonster : public CDialog
{
	DECLARE_DYNAMIC(CTabMonster)

public:
	CTabMonster(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabMonster();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TABMONSTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList2();
	
public:
	virtual BOOL OnInitDialog();

private:
	void		SetMonsterList();

public:
	void		GetMonsterName(int idx, wstring& name);
	//void		GetMonsterName(int idx, wstring& name,  wstring& desc);

public:
	const TEXINFO*	GetCurrentTexture();

public:	
	CStatic m_Image;
	CListBox m_list;
	CComboBox m_comboBox;
	afx_msg void OnCbnSelendokCombo1();
	CStatic m_Attribute;
	afx_msg void OnBnClickedButton1();
};
