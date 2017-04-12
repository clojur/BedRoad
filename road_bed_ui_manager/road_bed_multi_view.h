#pragma once
#include "x_framework/macro.h"
#include "x_framework/interface/window_interface.h"

#include "Db3DModeling/Db3DModelingInc.h"
#include "Db3DModeling/CompositeView.h"
#include "Db3DModeling/MultiViewPortOSG.h"
#include "Db3DModeling/ViewControlData.h"
#include "Db3DModeling/OSGObject.h"
#include "Db3DModeling/string_tools.h"

class CBedBoneControlData;
class CBedCrossControlData;
class CtestObj;
class road_bed_multi_view :public CDbCompositeView,public window_interface
{
	DECLARE_SERIAL(road_bed_multi_view)
	DECLARE_MESSAGE_MAP()
public:
	road_bed_multi_view();
	virtual ~road_bed_multi_view();
public:
	virtual	bool LoadData(const CString& data_path);
	virtual void OnSize(UINT nType, int cx, int cy);
	virtual CString GetTitle();
public:
	CBedBoneControlData* pPane1;
	CBedCrossControlData* pPane3;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	bool m_bInit;
};

class CBedBoneControlData :public CViewControlData
{
public:
	CBedBoneControlData(){}
	~CBedBoneControlData(){}
	virtual void CreateSreen();
};

class CBedCrossControlData :public CViewControlData
{
public:
	CBedCrossControlData(){}
	~CBedCrossControlData(){}
	virtual void CreateSreen();
};


class CBedObjInterface :public CDbObjInterface
{
public:
	CBedObjInterface(){}
	CBedObjInterface(CViewControlData* VCD) :CDbObjInterface(VCD), m_ccd(VCD){

	}
	~CBedObjInterface(){}
	virtual CDbObjInterface* Clone(){
		CBedObjInterface* pTest = new CBedObjInterface(GetViewControlData());

		pTest->m_ccd = m_ccd;

		return pTest;
	}
private:
	CViewControlData* m_ccd;

};

