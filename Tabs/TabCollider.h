#pragma once
#include "afxwin.h"


// CTabCollider ��ȭ �����Դϴ�.

class CTabCollider : public CDialog
{
	DECLARE_DYNAMIC(CTabCollider)

public:
	CTabCollider(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabCollider();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TABCOLLIDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_radio;
	CStatic m_Image;
	CButton m_checkBtn;

public:
	virtual BOOL OnInitDialog();

public:
	const TEXINFO* SetTileImage(bool bObject = false);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedCheck1();
	
	afx_msg void OnBnClickedButton1();
};
