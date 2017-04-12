#include "stdafx.h"

#include "x_framework/macro.h"
#include "x_framework/tools/string_tools.h"
#include "x_framework/tools/tinyxml2.h"
#include "x_framework/tools/xml_tools.h"

#include "road_bed_cap_beam_data.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

demo_cap_beam_common::demo_cap_beam_common()
{
	m_RdAndBKX_Angle = 0.0;
 	m_PosH = 0.0;
	m_PosContrlSec = 0.0;
	m_Length_H = 0.0;
	m_CapSec_Hei = 0.0;
	m_CapSec_Lever = 0.0;
	m_Fnd_Type = 0;
}

demo_cap_beam_common::~demo_cap_beam_common()
{

}

void demo_cap_beam_common::serialize_members(member_rw_interface& mt)
{
	int version = 1;

	if (mt.is_storing())
	{
		mt & x_wrapper_macro(version);
		//总体
		mt & x_wrapper_macro(m_RdAndBKX_Angle);
		mt & x_wrapper_macro(m_PosH);
		mt & x_wrapper_macro(m_PosContrlSec);
		mt & x_wrapper_macro(m_TopSlope);
		mt & x_wrapper_macro(m_BotSlope);
		mt & x_wrapper_macro(m_Length_H);
		mt & x_wrapper_macro(m_CapSec_Hei);
		mt & x_wrapper_macro(m_CapSec_Lever);
		mt & x_wrapper_macro(m_Fnd_Type);
		mt & x_wrapper_macro(m_JC_TopLever);
		mt & x_wrapper_macro(m_JC_BotLever);
	}
	else
	{
		mt & x_wrapper_macro(version);
		if (1 == version)
		{
			//总体
			mt & x_wrapper_macro(m_RdAndBKX_Angle);
			mt & x_wrapper_macro(m_PosH);
			mt & x_wrapper_macro(m_PosContrlSec);
			mt & x_wrapper_macro(m_TopSlope);
			mt & x_wrapper_macro(m_BotSlope);
			mt & x_wrapper_macro(m_Length_H);
			mt & x_wrapper_macro(m_CapSec_Hei);
			mt & x_wrapper_macro(m_CapSec_Lever);
			mt & x_wrapper_macro(m_Fnd_Type);
			mt & x_wrapper_macro(m_JC_TopLever);
			mt & x_wrapper_macro(m_JC_BotLever);
		}
	}
}

///
demo_cap_beam_general::demo_cap_beam_general()
{
	m_RdAndBKX_Angle = 0.0;
	m_PosZ = 0.0;
	m_PosH = 0.0;
	m_PosContrlSec = 0.0;
	m_bSetDF = false;
	m_DF_Wide = 0.0;
}
demo_cap_beam_general::~demo_cap_beam_general()
{

}
void demo_cap_beam_general::serialize_members(member_rw_interface& mt)
{
	int version = 1;

	if (mt.is_storing())
	{
		mt & x_wrapper_macro(version);
		//总体
		mt & x_wrapper_macro(m_RdAndBKX_Angle);
		mt & x_wrapper_macro(m_PosZ);
		mt & x_wrapper_macro(m_PosH);
		mt & x_wrapper_macro(m_PosContrlSec);
		mt & x_wrapper_macro(m_bSetDF);
		mt & x_wrapper_macro(m_DF_Wide);
		mt & x_wrapper_macro(m_TopSlope);
		mt & x_wrapper_macro(m_BotSlope);
	}
	else
	{
		mt & x_wrapper_macro(version);
		if (1 == version)
		{
			//总体
			mt & x_wrapper_macro(m_RdAndBKX_Angle);
			mt & x_wrapper_macro(m_PosZ);
			mt & x_wrapper_macro(m_PosH);
			mt & x_wrapper_macro(m_PosContrlSec);
			mt & x_wrapper_macro(m_bSetDF);
			mt & x_wrapper_macro(m_DF_Wide);
			mt & x_wrapper_macro(m_TopSlope);
			mt & x_wrapper_macro(m_BotSlope);
		}
	}
}

demo_cap_beam::demo_cap_beam()
{
	m_Length_H = 0.0;
	m_length_Z = 0.0;
	m_CapSide_AngleL = 90.0;
	m_CapSide_AngleR = 90.0;
	m_WideXL = 0.0;
	m_WideXR = 0.0;
	m_CapSide_HeiL = 0.0;
	m_CapSide_HeiR = 0.0;
	m_CapTop_XLen = 0.0;
	m_CapSec_Hei = 0.0;
	m_CapSec_Lever = 0.0;
	m_PierToGLSide_LenL = 0.0;
	m_PierToGLSide_LenR = 0.0;
}
demo_cap_beam::~demo_cap_beam()
{

}
void demo_cap_beam::serialize_members(member_rw_interface& mt)
{
	int version = 1;

	if (mt.is_storing())
	{
		mt & x_wrapper_macro(version);
		//盖梁
		mt & x_wrapper_macro(m_Length_H);
		mt & x_wrapper_macro(m_length_Z);
		mt & x_wrapper_macro(m_CapSide_AngleL);
		mt & x_wrapper_macro(m_CapSide_AngleR);
		mt & x_wrapper_macro(m_WideXL);
		mt & x_wrapper_macro(m_WideXR);
		mt & x_wrapper_macro(m_CapSide_HeiL);
		mt & x_wrapper_macro(m_CapSide_HeiR);
		mt & x_wrapper_macro(m_CapTop_XLen);
		mt & x_wrapper_macro(m_CapSec_Hei);
		mt & x_wrapper_macro(m_CapSec_Lever);
		mt & x_wrapper_macro(m_PierToGLSide_LenL);
		mt & x_wrapper_macro(m_PierToGLSide_LenR);
	}
	else
	{
		mt & x_wrapper_macro(version);
		if (1 == version)
		{
			//盖梁
			mt & x_wrapper_macro(m_Length_H);
			mt & x_wrapper_macro(m_length_Z);
			mt & x_wrapper_macro(m_CapSide_AngleL);
			mt & x_wrapper_macro(m_CapSide_AngleR);
			mt & x_wrapper_macro(m_WideXL);
			mt & x_wrapper_macro(m_WideXR);
			mt & x_wrapper_macro(m_CapSide_HeiL);
			mt & x_wrapper_macro(m_CapSide_HeiR);
			mt & x_wrapper_macro(m_CapTop_XLen);
			mt & x_wrapper_macro(m_CapSec_Hei);
			mt & x_wrapper_macro(m_CapSec_Lever);
			mt & x_wrapper_macro(m_PierToGLSide_LenL);
			mt & x_wrapper_macro(m_PierToGLSide_LenR);
		}
	}
}

demo_cap_beam_Pier::demo_cap_beam_Pier()
{
	m_PierSec_Type = 0;
	m_Pier_D = 1600.0;
	m_bSetXL = false;
	m_XL_Wide = 0.0;
	m_XL_Hei = 0.0;
	m_Pier_PosZ = 0.0;

	dWide_H = 0.0;
	dWide_Z = 0.0;
	dWide_LnDJ_H = 0.0;
	dWide_LnDJ_Z = 0.0;
	dWide_ArcDJ_R = 0.0;
}
demo_cap_beam_Pier::~demo_cap_beam_Pier()
{
}
void demo_cap_beam_Pier::serialize_members(member_rw_interface& mt)
{
	int version = 1;

	if (mt.is_storing())
	{
		mt & x_wrapper_macro(version);
		//墩柱
		mt & x_wrapper_macro(m_PierSec_Type);
		mt & x_wrapper_macro(m_Pier_D);
		mt & x_wrapper_macro(m_bSetXL);
		mt & x_wrapper_macro(m_XL_Wide);
		mt & x_wrapper_macro(m_XL_Hei);
		mt & x_wrapper_macro(m_Pier_PosZ);
		mt & x_wrapper_macro(m_Pier_PosH);
		mt & x_wrapper_macro(m_XL_Pos);

		mt & x_wrapper_macro(dWide_H);
		mt & x_wrapper_macro(dWide_Z);
		mt & x_wrapper_macro(dWide_LnDJ_H);
		mt & x_wrapper_macro(dWide_LnDJ_Z);
		mt & x_wrapper_macro(dWide_ArcDJ_R);
	}
	else
	{
		mt & x_wrapper_macro(version);
		if (1 == version)
		{
			mt & x_wrapper_macro(m_PierSec_Type);
			mt & x_wrapper_macro(m_Pier_D);
			mt & x_wrapper_macro(m_bSetXL);
			mt & x_wrapper_macro(m_XL_Wide);
			mt & x_wrapper_macro(m_XL_Hei);
			mt & x_wrapper_macro(m_Pier_PosZ);
			mt & x_wrapper_macro(m_Pier_PosH);
			mt & x_wrapper_macro(m_XL_Pos);

			mt & x_wrapper_macro(dWide_H);
			mt & x_wrapper_macro(dWide_Z);
			mt & x_wrapper_macro(dWide_LnDJ_H);
			mt & x_wrapper_macro(dWide_LnDJ_Z);
			mt & x_wrapper_macro(dWide_ArcDJ_R);
		}
	}
}

demo_cap_beam_foundation::demo_cap_beam_foundation()
{
	m_Fnd_Type = 0;
	m_Found_Type = 0;
	m_JC_PosZ = 0.0;
	m_Found_D = 0.0;
	m_bFound_JiaCu = false;
	m_JiaCu_D = 0.0;
	m_JiaCu_Hei = 0.0;
	m_JiaCuGD_Hei = 0.0;
	m_bFound_SetXL = 0.0;
	m_FoundXL_Wide = 0.0;
	m_FoundXL_Hei = 0.0;
	m_FoundXL_bSetBotDC = false;
	m_FoundXLDC_Hei = 0.0;
	m_FoundXLDC_Wide = 0.0;
	m_bSetXL = false;
	m_XL_Wide = 0.0;
	m_XL_Hei = 0.0;

	m_CTHor_Width = 0.0;
	m_CTVer_Width = 0.0;
	m_CT_Hei = 0.0;
	m_CTFound_DisCT = 0.0;
	m_Layout_Type = 0;
	//扩大基础
	m_KuoDa_TopHei = 0.0;
	m_KuoDa_TopWZ = 0.0;
	m_KuoDa_TopWH = 0.0;
}
demo_cap_beam_foundation::~demo_cap_beam_foundation()
{

}
void demo_cap_beam_foundation::serialize_members(member_rw_interface& mt)
{
	int version = 1;

	if (mt.is_storing())
	{
		mt & x_wrapper_macro(version);
		mt & x_wrapper_macro(m_Fnd_Type);
		mt & x_wrapper_macro(m_Found_Type);
		mt & x_wrapper_macro(m_JC_PosZ);
		mt & x_wrapper_macro(m_Found_D);
		mt & x_wrapper_macro(m_bFound_JiaCu);
		mt & x_wrapper_macro(m_JiaCu_D);
		mt & x_wrapper_macro(m_JiaCu_Hei);
		mt & x_wrapper_macro(m_JiaCuGD_Hei);
		mt & x_wrapper_macro(m_bFound_SetXL);
		mt & x_wrapper_macro(m_FoundXL_Wide);
		mt & x_wrapper_macro(m_FoundXL_Hei);
		mt & x_wrapper_macro(m_FoundXL_bSetBotDC);
		mt & x_wrapper_macro(m_FoundXLDC_Hei);
		mt & x_wrapper_macro(m_FoundXLDC_Wide);
		mt & x_wrapper_macro(m_bSetXL);
		mt & x_wrapper_macro(m_XL_Wide);
		mt & x_wrapper_macro(m_XL_Hei);
		mt & x_wrapper_macro(m_CTHor_Width);
		mt & x_wrapper_macro(m_CTVer_Width);
		mt & x_wrapper_macro(m_CT_Hei);
		mt & x_wrapper_macro(m_CTFound_DisCT);
		mt & x_wrapper_macro(m_Layout_Type);
		mt & x_wrapper_macro(m_KuoDa_TopHei);
		mt & x_wrapper_macro(m_KuoDa_TopWZ);
		mt & x_wrapper_macro(m_KuoDa_TopWH);
		mt & x_wrapper_macro(m_FoundXL_Pos);
		mt & x_wrapper_macro(m_JC_PosH);
		mt & x_wrapper_macro(m_JC_TopLever);
		mt & x_wrapper_macro(m_JC_BotLever);

	}
	else
	{
		mt & x_wrapper_macro(version);

		if (1 == version)
		{
			mt & x_wrapper_macro(m_Fnd_Type);
			mt & x_wrapper_macro(m_Found_Type);
			mt & x_wrapper_macro(m_JC_PosZ);
			mt & x_wrapper_macro(m_Found_D);
			mt & x_wrapper_macro(m_bFound_JiaCu);
			mt & x_wrapper_macro(m_JiaCu_D);
			mt & x_wrapper_macro(m_JiaCu_Hei);
			mt & x_wrapper_macro(m_JiaCuGD_Hei);
			mt & x_wrapper_macro(m_bFound_SetXL);
			mt & x_wrapper_macro(m_FoundXL_Wide);
			mt & x_wrapper_macro(m_FoundXL_Hei);
			mt & x_wrapper_macro(m_FoundXL_bSetBotDC);
			mt & x_wrapper_macro(m_FoundXLDC_Hei);
			mt & x_wrapper_macro(m_FoundXLDC_Wide);
			mt & x_wrapper_macro(m_bSetXL);
			mt & x_wrapper_macro(m_XL_Wide);
			mt & x_wrapper_macro(m_XL_Hei);
			mt & x_wrapper_macro(m_CTHor_Width);
			mt & x_wrapper_macro(m_CTVer_Width);
			mt & x_wrapper_macro(m_CT_Hei);
			mt & x_wrapper_macro(m_CTFound_DisCT);
			mt & x_wrapper_macro(m_Layout_Type);
			mt & x_wrapper_macro(m_KuoDa_TopHei);
			mt & x_wrapper_macro(m_KuoDa_TopWZ);
			mt & x_wrapper_macro(m_KuoDa_TopWH);
			mt & x_wrapper_macro(m_FoundXL_Pos);
			mt & x_wrapper_macro(m_JC_PosH);
			mt & x_wrapper_macro(m_JC_TopLever);
			mt & x_wrapper_macro(m_JC_BotLever);
		}
	}
}

demo_cap_beam_drawsetting::demo_cap_beam_drawsetting()
{
	m_Scale = 0.0;
	m_CtrBreakHei = 8000.0;
	m_DrawDK = false;
	m_DrawDS = false;
	m_DrawDMX = false;
	m_DrawGCSLB = false;
	m_DrawCTPM = false;
	m_BZDSType = false;
	m_BZDSLever_LM = false;
	m_BZDSHei_LM = false;
	m_bBZDSPosInPM = false;
	m_BZSlopeInside = false;
	m_BZGLLeverAtDKInside = false;
	m_bBZGLDJSizeInPM = false;
	m_bBZDunPMPos = false;
	m_bBZCMBKXdisDunCen = false;
}
demo_cap_beam_drawsetting::~demo_cap_beam_drawsetting()
{

}
void demo_cap_beam_drawsetting::serialize_members(member_rw_interface& mt)
{
	int version = 1;

	if (mt.is_storing())
	{
		mt & x_wrapper_macro(version);
		mt & x_wrapper_macro(m_Scale);
		mt & x_wrapper_macro(m_FZs);
		mt & x_wrapper_macro(m_CtrBreakHei);
		mt & x_wrapper_macro(m_DrawDK);
		mt & x_wrapper_macro(m_DrawDS);
		mt & x_wrapper_macro(m_DrawDMX);
		mt & x_wrapper_macro(m_DrawGCSLB);
		mt & x_wrapper_macro(m_DrawCTPM);
		mt & x_wrapper_macro(m_BZDSType);
		mt & x_wrapper_macro(m_BZDSLever_LM);
		mt & x_wrapper_macro(m_BZDSHei_LM);
		mt & x_wrapper_macro(m_bBZDSPosInPM);
		mt & x_wrapper_macro(m_BZSlopeInside);
		mt & x_wrapper_macro(m_BZGLLeverAtDKInside);
		mt & x_wrapper_macro(m_bBZGLDJSizeInPM);
		mt & x_wrapper_macro(m_bBZDunPMPos);
		mt & x_wrapper_macro(m_bBZCMBKXdisDunCen);
	}
	else
	{
		mt & x_wrapper_macro(version);

		if (1 == version)
		{
			mt & x_wrapper_macro(m_Scale);
			mt & x_wrapper_macro(m_FZs);
			mt & x_wrapper_macro(m_CtrBreakHei);
			mt & x_wrapper_macro(m_DrawDK);
			mt & x_wrapper_macro(m_DrawDS);
			mt & x_wrapper_macro(m_DrawDMX);
			mt & x_wrapper_macro(m_DrawGCSLB);
			mt & x_wrapper_macro(m_DrawCTPM);
			mt & x_wrapper_macro(m_BZDSType);
			mt & x_wrapper_macro(m_BZDSLever_LM);
			mt & x_wrapper_macro(m_BZDSHei_LM);
			mt & x_wrapper_macro(m_bBZDSPosInPM);
			mt & x_wrapper_macro(m_BZSlopeInside);
			mt & x_wrapper_macro(m_BZGLLeverAtDKInside);
			mt & x_wrapper_macro(m_bBZGLDJSizeInPM);
			mt & x_wrapper_macro(m_bBZDunPMPos);
			mt & x_wrapper_macro(m_bBZCMBKXdisDunCen);
		}
	}
}

demo_cap_beam_parameters::demo_cap_beam_parameters()
{
	m_bOnlyOneLB = false;
	m_iCSHLBBGType = 0;
	m_iDunNumType = 0;
	m_bAllLeverUseOneName = false;
	m_bDSLeverLB = false;
	m_bDSHeiLB = false;

	m_strCSHLBName = _T("参数化列表");
	m_Angle = _T("A");
	m_GL_Len = _T("L");
	m_BS = _T("S");
	m_left_Slope = _T("i");
	m_right_Slope = _T("i");
	m_left_DJ = _T("L1");
	m_right_DJ = _T("L2");
	m_left_JB = _T("K1");
	m_right_JB = _T("K2");
	m_Dun_Dis = _T("Bs");
	m_GL_LeftTopLever = _T("H1");

	m_GL_rightTopLever = _T("H2");
	m_Dun_TopLever = _T("H3");
	m_DunXL_Lever = _T("H4");
	m_JC_TopLever = _T("H5");
	m_JC_BotLever = _T("H6");
	m_Dun_Hei = _T("h");

	m_Found_Len = _T("l");
	m_DS_Lever = _T("dsH");
	m_DS_Hei = _T("dsh");
	m_DisBKXtoRd = _T("e");
}
demo_cap_beam_parameters::~demo_cap_beam_parameters()
{

}
void demo_cap_beam_parameters::serialize_members(member_rw_interface& mt)
{
	int version = 1;

	if (mt.is_storing())
	{
		mt & x_wrapper_macro(version);
		mt & x_wrapper_macro(m_CSHLB_Comment);
		mt & x_wrapper_macro(m_strCSHLBName);
		mt & x_wrapper_macro(m_bOnlyOneLB);
		mt & x_wrapper_macro(m_iCSHLBBGType);
		mt & x_wrapper_macro(m_iDunNumType);
		mt & x_wrapper_macro(m_bAllLeverUseOneName);
		mt & x_wrapper_macro(m_bDSLeverLB);
		mt & x_wrapper_macro(m_bDSHeiLB);

		mt & x_wrapper_macro(m_Angle);
		mt & x_wrapper_macro(m_GL_Len);
		mt & x_wrapper_macro(m_BS);
		mt & x_wrapper_macro(m_left_Slope);
		mt & x_wrapper_macro(m_right_Slope);
		mt & x_wrapper_macro(m_left_DJ);
		mt & x_wrapper_macro(m_right_DJ);
		mt & x_wrapper_macro(m_left_JB);
		mt & x_wrapper_macro(m_right_JB);
		mt & x_wrapper_macro(m_Dun_Dis);
		mt & x_wrapper_macro(m_GL_LeftTopLever);
		mt & x_wrapper_macro(m_GL_rightTopLever);
		mt & x_wrapper_macro(m_Dun_TopLever);
		mt & x_wrapper_macro(m_DunXL_Lever);
		mt & x_wrapper_macro(m_JC_TopLever);
		mt & x_wrapper_macro(m_JC_BotLever);
		mt & x_wrapper_macro(m_Dun_Hei);
		mt & x_wrapper_macro(m_Found_Len);
		mt & x_wrapper_macro(m_DS_Lever);
		mt & x_wrapper_macro(m_DS_Hei);
		mt & x_wrapper_macro(m_DisBKXtoRd);
	}
	else
	{
		mt & x_wrapper_macro(version);

		if (1 == version)
		{
			mt & x_wrapper_macro(m_CSHLB_Comment);
			mt & x_wrapper_macro(m_strCSHLBName);
			mt & x_wrapper_macro(m_bOnlyOneLB);
			mt & x_wrapper_macro(m_iCSHLBBGType);
			mt & x_wrapper_macro(m_iDunNumType);
			mt & x_wrapper_macro(m_bAllLeverUseOneName);
			mt & x_wrapper_macro(m_bDSLeverLB);
			mt & x_wrapper_macro(m_bDSHeiLB);

			mt & x_wrapper_macro(m_Angle);
			mt & x_wrapper_macro(m_GL_Len);
			mt & x_wrapper_macro(m_BS);
			mt & x_wrapper_macro(m_left_Slope);
			mt & x_wrapper_macro(m_right_Slope);
			mt & x_wrapper_macro(m_left_DJ);
			mt & x_wrapper_macro(m_right_DJ);
			mt & x_wrapper_macro(m_left_JB);
			mt & x_wrapper_macro(m_right_JB);
			mt & x_wrapper_macro(m_Dun_Dis);
			mt & x_wrapper_macro(m_GL_LeftTopLever);
			mt & x_wrapper_macro(m_GL_rightTopLever);
			mt & x_wrapper_macro(m_Dun_TopLever);
			mt & x_wrapper_macro(m_DunXL_Lever);
			mt & x_wrapper_macro(m_JC_TopLever);
			mt & x_wrapper_macro(m_JC_BotLever);
			mt & x_wrapper_macro(m_Dun_Hei);
			mt & x_wrapper_macro(m_Found_Len);
			mt & x_wrapper_macro(m_DS_Lever);
			mt & x_wrapper_macro(m_DS_Hei);
			mt & x_wrapper_macro(m_DisBKXtoRd);
		}
	}
}

demo_cap_beam_material::demo_cap_beam_material()
{

}
demo_cap_beam_material::~demo_cap_beam_material()
{

}
void demo_cap_beam_material::serialize_members(member_rw_interface& mt)
{
	int version = 1;

	if (mt.is_storing())
	{
		mt & x_wrapper_macro(version);
		mt & x_wrapper_macro(m_GL_Mat);
		mt & x_wrapper_macro(m_DS_Mat);
		mt & x_wrapper_macro(m_Dun_Mat);
		mt & x_wrapper_macro(m_DunXL_Mat);
		mt & x_wrapper_macro(m_CTKD_Mat);
		mt & x_wrapper_macro(m_CTDC_Mat);
		mt & x_wrapper_macro(m_JCXL_Mat);
		mt & x_wrapper_macro(m_Fnd_Mat);
		mt & x_wrapper_macro(m_GL_Type);
		mt & x_wrapper_macro(m_DS_Type);
		mt & x_wrapper_macro(m_Dun_Type);
		mt & x_wrapper_macro(m_DunXL_Type);
		mt & x_wrapper_macro(m_CTKD_Type);
		mt & x_wrapper_macro(m_CTDC_Type);
		mt & x_wrapper_macro(m_JCXL_Type);
		mt & x_wrapper_macro(m_Fnd_Type);
	}
	else
	{
		mt & x_wrapper_macro(version);

		if (1 == version)
		{
			mt & x_wrapper_macro(m_GL_Mat);
			mt & x_wrapper_macro(m_DS_Mat);
			mt & x_wrapper_macro(m_Dun_Mat);
			mt & x_wrapper_macro(m_DunXL_Mat);
			mt & x_wrapper_macro(m_CTKD_Mat);
			mt & x_wrapper_macro(m_CTDC_Mat);
			mt & x_wrapper_macro(m_JCXL_Mat);
			mt & x_wrapper_macro(m_Fnd_Mat);
			mt & x_wrapper_macro(m_GL_Type);
			mt & x_wrapper_macro(m_DS_Type);
			mt & x_wrapper_macro(m_Dun_Type);
			mt & x_wrapper_macro(m_DunXL_Type);
			mt & x_wrapper_macro(m_CTKD_Type);
			mt & x_wrapper_macro(m_CTDC_Type);
			mt & x_wrapper_macro(m_JCXL_Type);
			mt & x_wrapper_macro(m_Fnd_Type);
		}
	}
}




//////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(road_bed_cap_beam_data, road_bed_graph_data_base, 1)

road_bed_cap_beam_data::road_bed_cap_beam_data()
{

}
road_bed_cap_beam_data::~road_bed_cap_beam_data()
{

}

void road_bed_cap_beam_data::serialize_members(member_rw_interface& mt)
{
	int version = 1;

	if (mt.is_storing())
	{
		mt & x_wrapper_macro(version);
		mt & x_wrapper_macro(m_Common);
		mt & x_wrapper_macro(m_Gen);
		mt & x_wrapper_macro(m_GL);
		mt & x_wrapper_macro(m_Pier);
		mt & x_wrapper_macro(m_JC);
		mt & x_wrapper_macro(m_DrawSet);
		mt & x_wrapper_macro(m_CSHLB);
		mt & x_wrapper_macro(m_Materials);
	}
	else
	{
		mt & x_wrapper_macro(version);

		if (1 == version)
		{
			mt & x_wrapper_macro(m_Common);
			mt & x_wrapper_macro(m_Gen);
			mt & x_wrapper_macro(m_GL);
			mt & x_wrapper_macro(m_Pier);
			mt & x_wrapper_macro(m_JC);
			mt & x_wrapper_macro(m_DrawSet);
			mt & x_wrapper_macro(m_CSHLB);
			mt & x_wrapper_macro(m_Materials);
		}
	}

	road_bed_graph_data_base::serialize_members(mt);
}





