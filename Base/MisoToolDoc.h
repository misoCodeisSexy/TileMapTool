
// MisoToolDoc.h : CMisoToolDoc Ŭ������ �������̽�
//


#pragma once


class CMisoToolDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMisoToolDoc();
	DECLARE_DYNCREATE(CMisoToolDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CMisoToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


