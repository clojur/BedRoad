
// testModelingView.cpp : implementation of the CtestModelingView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "testModeling.h"
#endif

#include "osg/Geode"
#include "osgText/Font"
#include "osg/Vec3"

#include "testModelingView.h"
#include "testModelingDoc.h"

#include "Db3DModeling/OSGInterface.h"
#include "Db3DModeling/OSGTools.h"
#include "Db3DModeling/OSGWraper.h"

#include "Db3DModeling/string_tools.h"
#include "Db3DModeling/OSGObject.h"

#include "ACADAdaptor\cadIOInc.h"
#include "THMath/TH_Math_API.h"
#include "THmath/Polygon2.h"
#include "THMathLib\THMathLibShare.h"
#include "THAlgor/THAlgorInc.h"
#include "THCurveLib\THCurveLibShare.h"
#include "THGOControl\THGOControlShare.h"
#include "THGraphOutputLib\THGraphOutputShare.h"
#include "THGraphOutputObjectBase\THGraphOutputObjectBaseShare.h"
#include "THGraphOutputObjectBase2\THGraphOutputObjectBase2Share.h"
#include "THGOCurveGraph\THGOCurveGraphShare.h"
#include "THGraphOutputObjects\THGraphOutputObjectsShare.h"
#include "Db3DModeling/OSGDimObj.h"
#include "osg/ComputeBoundsVisitor"
#include "osg/PositionAttitudeTransform"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestModelingView

IMPLEMENT_DYNCREATE(CTestModelingView, CDbOSGBaseView)

BEGIN_MESSAGE_MAP(CTestModelingView, CDbOSGBaseView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestModelingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CtestModelingView construction/destruction

CTestModelingView::CTestModelingView()
{
	// TODO: add construction code here

}

CTestModelingView::~CTestModelingView()
{
}

BOOL CTestModelingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CtestModelingView drawing

void CTestModelingView::OnDraw(CDC* /*pDC*/)
{
	CtestModelingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CtestModelingView printing


void CTestModelingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTestModelingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestModelingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestModelingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTestModelingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestModelingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CtestModelingView diagnostics

#ifdef _DEBUG
void CTestModelingView::AssertValid() const
{
	CView::AssertValid();
}

void CTestModelingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtestModelingDoc* CTestModelingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtestModelingDoc)));
	return (CtestModelingDoc*)m_pDocument;
}
#endif //_DEBUG


// CtestModelingView message handlers



using namespace osg;

#include <osgdb/ReadFile>
#include <osg/Node>
#include <osgViewer/Viewer>
 



///////////////////////////////
void ImportContinueLineFromCAD(const CString& strFile,osg::Group* pRoot )
{
	std::vector<CTHCurve> curves;
	CString strError;

	CGEBody cadImple;
	cadImple.SetFile(strFile);
	cadImple.Import();

	std::vector<CString> allLayers = cadImple.GetLayer();
	if (allLayers.size() == 0)
		return;

	osg::Vec3 offset;
	bool bOffset = false;

	CGEPart* part = cadImple.Get(allLayers[1]);
	if (part)
	{
		osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;

		for (CGEPolyLine3d*ptr : part->m_PolyLineVec)
		{
			if (!ptr) continue;	

			if (ptr->m_pointVec.size() > 1)
			{
				osg::Vec3Array *points = new osg::Vec3Array;


				for (size_t i = 0; i < ptr->m_pointVec.size(); ++i)
				{
					const CGEPoint3d &pt1 = ptr->m_pointVec[i];
					if (!bOffset)
					{
						bOffset = true;
						offset = osg::Vec3(pt1.m_x, pt1.m_y, pt1.m_z);
					}

					points->push_back(osg::Vec3(pt1.m_x, pt1.m_y, pt1.m_z) - offset);
				}

				osg::Geometry* pGeomotry = createLinesGeode(points, osg::Vec4(0.5, 0.5, 0.5, 1));
				pGeode->addDrawable(pGeomotry);
			}

		}

		for (CGELine3d* ptr : part->m_LineVec)
		{
			if (!ptr) continue;
			const CGEPoint3d &pt1 = ptr->m_start;
			const CGEPoint3d &pt2 = ptr->m_end;
		}
		for (CGECircArc3d* ptr : part->m_CircArcVec)
		{
			if (!ptr) continue;
			const CGEPoint3d &center = ptr->m_center;
		}

		if (bOffset)
		{
			osg::ref_ptr<osg::PositionAttitudeTransform> pTrans = new osg::PositionAttitudeTransform;
			pTrans->setName("offset");
	//		pTrans->setPosition(offset);
 			pTrans->addChild(pGeode.get());
			pRoot->addChild(pTrans.get() );
		}

	}
}


class CTestObj : public CDbObjInterface
{
public:
	double m_x;
	CString m_testValue;

public:
	CTestObj(CViewControlData* pControlData) :CDbObjInterface(pControlData)
	{
		m_type = "CTestObj";
		SetID(CDbOSGDataCenter::GetID());
		SetName(m_type + cdb_string_tools::num_to_string(m_id));

		m_testValue = "test";
	}
	BOOL OnUpdateByDim(const CString& strDimFlag, const CString& strDimName, const CString& strDimValue)
	{
		m_testValue = strDimValue;

		m_pOSG->doOperation("–ﬁ∏ƒ Ù–‘", this);

		return TRUE;
	}

	std::vector<CDbObjInterface*> CreateDimObjects()
	{
		std::vector<CDbObjInterface*> dimObjests;

		CDbDimObj* pSpanDim = new CDbDimObj(m_pOSG, this, "name", "test", "name", TEXT_DIM);
		if (pSpanDim)
		{
			pSpanDim->m_insertPoint = osg::Vec3(0, 0, 0);
			pSpanDim->m_dimValue = m_testValue;

			pSpanDim->m_bEnChart = FALSE;
			pSpanDim->m_dimTextSize = 30;

			pSpanDim->m_dAngle = M_PI_2;

			pSpanDim->m_color = osg::Vec4(0, 1, 0, 1);

			pSpanDim->m_bAutoScale = false;

			pSpanDim->m_bReadOnly = false;

			dimObjests.push_back(pSpanDim);
		}
		return dimObjests;
	  
	}
	virtual CDbObjInterface* Clone()
	{
		CTestObj* pTest = new CTestObj(GetViewControlData());
  
		pTest->m_x = m_x;

		return pTest;
	}
};


CTestControlData::CTestControlData()
{
}

void CTestControlData::CreateSreen()
{
	ImportContinueLineFromCAD("G:\\Drawing-Terrain.dxf", pTerrain);
	osg::ComputeBoundsVisitor cbbv;
	GraphicsGroup->accept(cbbv);

	if (pTerrain)
	{
		pTerrain->accept(cbbv);
	}

	osg::BoundingBox bb = cbbv.getBoundingBox();

	if (bb.valid())
	{
		CTestObj* pCreateObj = new CTestObj(this);

		osg::Vec3 center = bb.center();

		for (int i = 0; i < 6; i++)
		{
			CDb_MeshInfo* pOneMesh = new CDb_MeshInfo;

			pOneMesh->strName = cdb_string_tools::num_to_string(i + 1);
			pOneMesh->color = RGB(255, 0, 0);
			{
				CDb_Point3 onePoint;
				onePoint.x = i * 10 + center[0];
				onePoint.y = -10    + center[1];
				onePoint.z = 0      + center[2];
				pOneMesh->m_Ptsvec.push_back(onePoint);

				onePoint.x = i * 10 + center[0];
				onePoint.y = 10 + center[1];
				onePoint.z = 0 + center[2];
				pOneMesh->m_Ptsvec.push_back(onePoint);

				onePoint.x = i * 10 + center[0];
				onePoint.y = 10 + center[1];
				onePoint.z = 20 + center[2];
				pOneMesh->m_Ptsvec.push_back(onePoint);

				onePoint.x = i * 10 + center[0];
				onePoint.y = -10 + center[1];
				onePoint.z = 20 + center[2];
				pOneMesh->m_Ptsvec.push_back(onePoint);
			}

		{
			pOneMesh->m_Indexsvec.push_back(0);
			pOneMesh->m_Indexsvec.push_back(1);
			pOneMesh->m_Indexsvec.push_back(2);
			pOneMesh->m_Indexsvec.push_back(-1);
			pOneMesh->m_Indexsvec.push_back(2);
			pOneMesh->m_Indexsvec.push_back(3);
			pOneMesh->m_Indexsvec.push_back(0);
			pOneMesh->m_Indexsvec.push_back(-1);
		}

		pCreateObj->AddMeshInfo(pOneMesh);
		}

		addData(pCreateObj);
	}
	 



	PerspectiveView();
 }
 
void CTestModelingView::OnInitialUpdate()
{
	CDbOSGBaseView::OnInitialUpdate();

	CTestControlData* pControlData = new CTestControlData;
	InitOSG(pControlData);
}