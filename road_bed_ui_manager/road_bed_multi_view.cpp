#include "stdafx.h"
#include "road_bed_multi_view.h"

/*************road_bed_multi_view***********************/
IMPLEMENT_SERIAL(road_bed_multi_view, CDbCompositeView, 1);
BEGIN_MESSAGE_MAP(road_bed_multi_view, CDbCompositeView)
	ON_WM_CREATE()
END_MESSAGE_MAP()
road_bed_multi_view::road_bed_multi_view():
m_bInit(false)
{
}


road_bed_multi_view::~road_bed_multi_view()
{
}

bool road_bed_multi_view::LoadData(const CString& data_path)
{
	if (!m_bInit)
	{
		mOSG = new CDbCompositeViewOSG(this);
		mOSG->m_backColor = osg::Vec4(0.7f,0.7f,0.7f,1.0f);
		mOSG->InitOSG();
		mOSG->SetSpace(1);
		if (mOSG)
		{
			pPane1 = new CBedBoneControlData;
			pPane1->bfactor = true;
			pPane1->mViewSet.x = 0;
			pPane1->mViewSet.y = 0.5;
			pPane1->mViewSet.width = 1;
			pPane1->mViewSet.height = 0.6;
			
			pPane1->mViewSet.strTitle = _T("BedBone");
			pPane1->mViewSet.titleSize = 30;
			pPane1->PerspectiveView();
			pPane1->mViewSet.bDefaultFocus = true;
			pPane1->TopView();
			mOSG->AddView(pPane1);

			pPane3 = new CBedCrossControlData;
			pPane3->bfactor = true;
			pPane3->mViewSet.x = 0;
			pPane3->mViewSet.y = 0;
			pPane3->mViewSet.width = 1;
			pPane3->mViewSet.height = 0.4;
			pPane3->mViewSet.strTitle = _T("BedCross");
			pPane3->mViewSet.titleSize = 30;
			pPane3->mViewSet.bDefaultFocus = false;
			//pPane3->TopView();
			mOSG->AddView(pPane3);
		}
		m_pThread = AfxBeginThread(AFX_THREADPROC(Render), (LPVOID)(mOSG));
		SetCurrentThreadStatus(0);
		m_bInit = true;
	}
	return true;
}


int road_bed_multi_view::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDbCompositeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	LoadData(_T(""));
	// TODO:  在此添加您专用的创建代码

	return 0;
}

void road_bed_multi_view::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
}

CString road_bed_multi_view::GetTitle()
{
	return (_T("MultiView"));
}

void CBedBoneControlData::CreateSreen()
{
	CBedObjInterface* pCreateObj = new CBedObjInterface(this);
	CDb_MeshInfo *pOneMesh = new CDb_MeshInfo;
	pOneMesh->color = RGB(255, 0, 0, );
	pOneMesh->strName = _T("tri1");
	CDb_Point3 point;
	point.x = -1.0f;
	point.y = 0.0f;
	point.z = -1.0f;
	pOneMesh->m_Ptsvec.push_back(point);
	point.x = 1.0f;
	point.y = 0.0f;
	point.z = -1.0f;
	pOneMesh->m_Ptsvec.push_back(point);
	point.x = 0.0f;
	point.y = 0.0f;
	point.z = 1.0f;
	pOneMesh->m_Ptsvec.push_back(point);

	pOneMesh->m_Indexsvec.push_back(0);
	pOneMesh->m_Indexsvec.push_back(1);
	pOneMesh->m_Indexsvec.push_back(2);

	pCreateObj->AddMeshInfo(pOneMesh);
	addData(pCreateObj);
}

void CBedCrossControlData::CreateSreen()
{
	CBedObjInterface* pCreateObj = new CBedObjInterface(this);
	CDb_MeshInfo *pOneMesh = new CDb_MeshInfo;
	pOneMesh->color = RGB(0, 255, 0, );
	pOneMesh->strName = _T("tri2");
	CDb_Point3 point;
	point.x = -1.0f;
	point.y = 0.0f;
	point.z = -1.0f;
	pOneMesh->m_Ptsvec.push_back(point);
	point.x = 1.0f;
	point.y = 0.0f;
	point.z = -1.0f;
	pOneMesh->m_Ptsvec.push_back(point);
	point.x = 0.0f;
	point.y = 0.0f;
	point.z = 1.0f;
	pOneMesh->m_Ptsvec.push_back(point);

	pOneMesh->m_Indexsvec.push_back(0);
	pOneMesh->m_Indexsvec.push_back(1);
	pOneMesh->m_Indexsvec.push_back(2);

	pCreateObj->AddMeshInfo(pOneMesh);
	addData(pCreateObj);
}
