
// testModelingView.h : interface of the CtestModelingView class
//

#pragma once

#include "Db3DModeling/Db3DModelingInc.h"
#include "Db3DModeling/OSGBaseView.h"
#include "Db3DModeling/ViewControlData.h"



class CtestModelingDoc;
class CTestModelingView : public CDbOSGBaseView
{
protected: // create from serialization only
	CTestModelingView();
	DECLARE_DYNCREATE(CTestModelingView)

// Attributes
public:
	CtestModelingDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTestModelingView();

	virtual void OnInitialUpdate();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in testModelingView.cpp
inline CtestModelingDoc* CTestModelingView::GetDocument() const
   { return reinterpret_cast<CtestModelingDoc*>(m_pDocument); }
#endif





 
class CTestControlData :public CViewControlData
{
public:
	CTestControlData();
  	void CreateSreen();
};