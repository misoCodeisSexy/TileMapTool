#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CTabObject 대화 상자입니다.

class CTabObject : public CDialog
{
	DECLARE_DYNAMIC(CTabObject)

public:
	CTabObject(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTabObject();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TABOBJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	CListBox m_list;
	CStatic m_Image;
	CSliderCtrl m_ctrlSlider;

private:
	void			SetObjectList();

public:
	const TEXINFO*	GetCurrentTexture();

public:
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButton2();
};
