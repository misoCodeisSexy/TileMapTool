#pragma once
#include "afxcmn.h"



// CMyForm 폼 뷰입니다.

#include "TabMap.h"
#include "TabTile.h"
#include "TabCollider.h"
#include "TabObject.h"
#include "TabMonster.h"

class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMyForm();

public:
	enum { IDD = IDD_MYFORM };

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

public:
	void MousePositionUpdate(CPoint point);

public:
	CTabCtrl			m_Tab;
	CTabMap				m_tabMap;
	CTabTile			m_tabTile;
	CTabCollider		m_tabCollider;
	CTabObject			m_tabObject;
	CTabMonster			m_tabMonster;
	CWnd*				m_pTabWndShow;

	unsigned short		m_sTabCurState;

public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};


