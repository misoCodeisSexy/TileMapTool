
// MisoToolView.h : CMisoToolView Ŭ������ �������̽�
//


#pragma once

#include "BackGround.h"
#include "MyObject.h"
#include "Monster.h"

class CMyForm;
class CMisoToolDoc;
class CMisoToolView : public CScrollView 
{
protected: // serialization������ ��������ϴ�.
	CMisoToolView();
	DECLARE_DYNCREATE(CMisoToolView)

// Ư���Դϴ�.
public:
	CMisoToolDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMisoToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();

private:
	CDevice*				m_pDevice;
	bool					m_isClicked;
	
public:
	CBackGround*			m_pBackGround;
	CMyObject*				m_pMyObject;
	CMonster*				m_pMonster;

	CMyForm*				m_pMyForm;

	BYTE					m_drawID;

	CPoint					m_MousePoint;

public:

	int		m_tileX;
	int		m_tileY;

	UINT	m_objCount;
	UINT	m_mstCount;

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MisoToolView.cpp�� ����� ����
inline CMisoToolDoc* CMisoToolView::GetDocument() const
   { return reinterpret_cast<CMisoToolDoc*>(m_pDocument); }
#endif

