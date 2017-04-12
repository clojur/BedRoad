#pragma once

#include "x_framework/macro.h"
#include "x_framework/interface/window_interface.h"
#include "Db3DModeling/Db3DModelingInc.h"
#include "Db3DModeling/OSGBaseView.h"
#include "Db3DModeling/ViewControlData.h"
#include "Db3DModeling/OSGObject.h"
#include "Db3DModeling/string_tools.h"

class road_bed_3D :public CDbOSGBaseView, public window_interface
{
	DECLARE_SERIAL(road_bed_3D)
	DECLARE_MESSAGE_MAP()
protected: // create from serialization only
	road_bed_3D();
//	DECLARE_DYNCREATE(road_bed_3D)
	// Attributes

public:

	// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	/*实现一些window_interface接口*/
private:
	virtual CString get_title();
	//virtual void app_theme_changed(theme_style_settings& settings);

	// Implementation
public:
	virtual ~road_bed_3D();

	virtual void OnInitialUpdate();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

class CtestControlData :public CViewControlData
{
public:
	CtestControlData();
	~CtestControlData();
	virtual void CreateSreen();
};

class CtestObj :public CDbObjInterface
{
public:
	CtestObj();
	CtestObj(CViewControlData* VCD);
	~CtestObj();
	virtual CDbObjInterface* Clone();
private:
	CViewControlData* m_x;

};
