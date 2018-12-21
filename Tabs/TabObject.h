#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CTabObject ��ȭ �����Դϴ�.

class CTabObject : public CDialog
{
	DECLARE_DYNAMIC(CTabObject)

public:
	CTabObject(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabObject();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TABOBJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
