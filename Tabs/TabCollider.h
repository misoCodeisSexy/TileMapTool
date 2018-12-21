#pragma once
#include "afxwin.h"


// CTabCollider 대화 상자입니다.

class CTabCollider : public CDialog
{
	DECLARE_DYNAMIC(CTabCollider)

public:
	CTabCollider(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTabCollider();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TABCOLLIDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
