#pragma once
#include "afxwin.h"


// CTabMap ��ȭ �����Դϴ�.

class CTabMap : public CDialog
{
	DECLARE_DYNAMIC(CTabMap)

public:
	CTabMap(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabMap();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TABMAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	void		SetEditObjctCount(void);
	void		SetEditMonsterCount(void);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnSaveMapDatas();
	afx_msg void OnLoadMapData();

private:
	void		SetLastOpenText(CString lastText);
	void		SetLoadDataEditText(void);
};
