#pragma once
#include "afxwin.h"


// CTabTile ��ȭ �����Դϴ�.

class CTabTile : public CDialog
{
	DECLARE_DYNAMIC(CTabTile)

public:
	CTabTile(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabTile();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TABTILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CComboBox m_comboBox;
	CListBox m_listBox;
	int m_radio;
	CButton m_CheckBtn;

	CStatic m_Image;
	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo2();

private:
	void SetTileList(int start, int end);

public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedCngall();
	afx_msg void OnStnClickedImage();
};
