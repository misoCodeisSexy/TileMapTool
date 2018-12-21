#pragma once
#include "afxwin.h"


// CTabMap 대화 상자입니다.

class CTabMap : public CDialog
{
	DECLARE_DYNAMIC(CTabMap)

public:
	CTabMap(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTabMap();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TABMAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
