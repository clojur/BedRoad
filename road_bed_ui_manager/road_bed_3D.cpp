#include "stdafx.h"
#include "road_bed_3D.h"
/*********************road_bed_3D**************************/

IMPLEMENT_SERIAL(road_bed_3D, CDbOSGBaseView, 1)

BEGIN_MESSAGE_MAP(road_bed_3D, CDbOSGBaseView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &road_bed_3D::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// road_bed_3D construction/destruction

road_bed_3D::road_bed_3D()
{
	// TODO: add construction code here

}

road_bed_3D::~road_bed_3D()
{
}

BOOL road_bed_3D::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	return CWnd::PreCreateWindow(cs);
}

// road_bed_3D drawing



// road_bed_3D printing


void road_bed_3D::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL road_bed_3D::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void road_bed_3D::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void road_bed_3D::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void road_bed_3D::OnInitialUpdate()
{
	CDbOSGBaseView::OnInitialUpdate();
}

#ifdef _DEBUG
void road_bed_3D::AssertValid() const
{
	CView::AssertValid();
}

void road_bed_3D::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif


/*********************CtestControlData**************************/
CtestControlData::CtestControlData()
{

}

CtestControlData::~CtestControlData()
{

}

void CtestControlData::CreateSreen()
{
	CtestObj* pCreateObj = new CtestObj(this);
	CDb_MeshInfo *pOneMesh = new CDb_MeshInfo;
	pOneMesh->color = RGB(255,0,0,);
	pOneMesh->strName = _T("tri");
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
	PerspectiveView();
}

CtestObj::CtestObj()
{

}

CtestObj::CtestObj(CViewControlData* VCD) :
CDbObjInterface(VCD),
m_x(VCD)
{
}

CtestObj::~CtestObj()
{

}

CDbObjInterface* CtestObj::Clone()
{
	CtestObj* pTest = new CtestObj(GetViewControlData());

	pTest->m_x = m_x;

	return pTest;
}


BOOL road_bed_3D::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return true;
}


int road_bed_3D::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;

	CtestControlData* pControlData = new CtestControlData;
	InitOSG(pControlData);
	return 0;
}

CString road_bed_3D::get_title()
{
	return (_T("路基3D"));
}



void road_bed_3D::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
}
