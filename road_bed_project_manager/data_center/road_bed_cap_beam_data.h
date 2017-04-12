#pragma once

#include "x_framework/macro.h"
#include "x_framework/interface/data_center_interface.h"
#include "x_framework/interface/serialize_interface.h"

#include "road_bed_graph_data_base.h"

//��������
class ROAD_BED_PROJECT_MANAGER_API demo_cap_beam_common
{
public:
	demo_cap_beam_common();
	~demo_cap_beam_common();
public:
public:
	void serialize_members(member_rw_interface& mt);

public:
	double m_RdAndBKX_Angle;//��������·�߼н�
 	double m_PosH;			//����λ
	double m_PosContrlSec;	//���ƽ����·��
 	std::vector<double> m_TopSlope;//������������
	std::vector<double> m_BotSlope;//�����ײ�����
	double m_Length_H;		//�������򳤶�
	double m_CapSec_Hei;	//�����߶�
	double m_CapSec_Lever;	//�������߳�
	int m_Fnd_Type;			//��������---0:׮��ʽ  1:��̨׮ 2:�������
	std::vector<double>	m_JC_TopLever;	//���߳�
	std::vector<double>	m_JC_BotLever;	//�׸߳�
};
//��������
class ROAD_BED_PROJECT_MANAGER_API demo_cap_beam_general
{
public:
	demo_cap_beam_general();
	~demo_cap_beam_general();

public:
	void serialize_members(member_rw_interface& mt);

public:
	double m_RdAndBKX_Angle;//��������·�߼н�
	double m_PosZ;			//����λ
	double m_PosH;			//����λ
	double m_PosContrlSec;	//���ƽ����·��
	bool   m_bSetDF;		//���öն��Ϸ�
	double m_DF_Wide;		//�ն��Ϸ���
	std::vector<double> m_TopSlope;//������������
	std::vector<double> m_BotSlope;//�����ײ�����
};
//����
class ROAD_BED_PROJECT_MANAGER_API demo_cap_beam
{
public:
	demo_cap_beam();
	~demo_cap_beam();

public:
	void serialize_members(member_rw_interface& mt);

public:
	double m_Length_H;		//���򳤶�
	double m_length_Z;		//������
	double m_CapSide_AngleL;//�����������ˮƽ���߼н�
	double m_CapSide_AngleR;//�����ұ�����ˮƽ���߼н�
	double m_WideXL;		//��߶γ���L
	double m_WideXR;		//��߶γ���R
	double m_CapSide_HeiL;	//������˸߶�
	double m_CapSide_HeiR;	//�Ҳ����˸߶�
	double m_CapTop_XLen;	//�����нǿ��
	double m_CapSec_Hei;	//�����߶�
	double m_CapSec_Lever;	//�������߳�
	double m_PierToGLSide_LenL;//��߳���L
	double m_PierToGLSide_LenR;//��߳���R
};
//����
class ROAD_BED_PROJECT_MANAGER_API demo_cap_beam_Pier
{
public:
	demo_cap_beam_Pier();
	~demo_cap_beam_Pier();

public:
	void serialize_members(member_rw_interface& mt);

public:
	int m_PierSec_Type;//0:Բ�� 1:���� 2:�ߵ��Ǿ��� 3:Բ�����Ǿ���
	double m_Pier_D;
	bool m_bSetXL;
	double m_XL_Wide;
	double m_XL_Hei;
	double m_Pier_PosZ;
	std::vector<double> m_Pier_PosH;//����λ
	std::vector<double> m_XL_Pos;	//ϵ��λ��

	double dWide_H;			//���κ������
	double dWide_Z;			//�����������
	double dWide_LnDJ_H;	//�ߵ��Ǿ��κ�������
	double dWide_LnDJ_Z;	//�ߵ��Ǿ�����������
	double dWide_ArcDJ_R;	//Բ�����Ǿ���Բ���뾶
};
//����
class ROAD_BED_PROJECT_MANAGER_API demo_cap_beam_foundation
{
public:
	demo_cap_beam_foundation();
	~demo_cap_beam_foundation();

public:
	void serialize_members(member_rw_interface& mt);

public:
	int m_Fnd_Type;			//��������---0:׮��ʽ  1:��̨׮ 2:�������
	int m_Found_Type;		//׮������---0:��׹�ע׮ 2:Ԥ�Ʒ�׮
	double m_JC_PosZ;		//����λ
	double m_Found_D;		//ֱ����߳�
	bool m_bFound_JiaCu;	//׮���Ӵ�
	double m_JiaCu_D;		//�Ӵֶ�ֱ��
	double m_JiaCu_Hei;		//�Ӵֶθ߶�
	double m_JiaCuGD_Hei;	//���ɶθ߶�
	bool m_bFound_SetXL;	//����ϵ��
	double m_FoundXL_Wide;	//ϵ��������
	double m_FoundXL_Hei;	//ϵ������߶�
	bool m_FoundXL_bSetBotDC;//ϵ�������õ��
	double m_FoundXLDC_Hei;	//�����
	double m_FoundXLDC_Wide;//����������
	bool m_bSetXL;			//����ϵ��
	double m_XL_Wide;		//ϵ��������
	double m_XL_Hei;		//ϵ������߶�

	double m_CTHor_Width;	//��̨�����
	double m_CTVer_Width;	//��̨�����
	double m_CT_Hei;		//��̨���
	double m_CTFound_DisCT;	//׮�����̨���
	int m_Layout_Type;		//��׮��ʽ
	//�������
	double m_KuoDa_TopHei;	//����߶�
	double m_KuoDa_TopWZ;	//����������
	double m_KuoDa_TopWH;	//���������

	std::vector<double>	m_FoundXL_Pos;	//ϵ��λ��
	std::vector<double>	m_JC_PosH;		//����λ
	std::vector<double>	m_JC_TopLever;	//���߳�
	std::vector<double>	m_JC_BotLever;	//�׸߳�
};
//��ͼ����
class ROAD_BED_PROJECT_MANAGER_API demo_cap_beam_drawsetting
{
public:
	demo_cap_beam_drawsetting();
	~demo_cap_beam_drawsetting();

public:
	void serialize_members(member_rw_interface& mt);

public:
	double m_Scale;			//���Ʊ���
	CString m_FZs;			//�Զ��帽ע
	double m_CtrBreakHei;	//�ո��۶Ͽ��Ƹ߶�
	bool m_DrawDK;			//���Ƶ���
	bool m_DrawDS;			//���Ƶ�ʯ
	bool m_DrawDMX;			//���Ƶ�����
	bool m_DrawGCSLB;		//���ƹ���������
	bool m_DrawCTPM;		//�������Ƴ�̨׮����ƽ��ͼ
	bool m_BZDSType;		//��ע��ʯ����
	bool m_BZDSLever_LM;	//��ע��ʯ�߳�
	bool m_BZDSHei_LM;		//��ע��ʯ�߶�
	bool m_bBZDSPosInPM;	//��ע��ʯƽ�沼��
	bool m_BZSlopeInside;	//��ע�����¶����ڲ�
	bool m_BZGLLeverAtDKInside;	//��ע�����߳��ڵ����ڲ�
	bool m_bBZGLDJSizeInPM;		//��ע��������ƽ��ߴ�
	bool m_bBZDunPMPos;			//��ע����ƽ�沼��
	bool m_bBZCMBKXdisDunCen;	//��ע���沼���߾�������߾���
};
//�������б�
class ROAD_BED_PROJECT_MANAGER_API demo_cap_beam_parameters
{
public:
	demo_cap_beam_parameters();
	~demo_cap_beam_parameters();

public:
	void serialize_members(member_rw_interface& mt);

public:
	CString m_CSHLB_Comment;	//�б�Χ·��
	CString m_strCSHLBName;		//�������б����
	bool m_bOnlyOneLB;			//���������������б�
	int m_iCSHLBBGType;			//�������б���ʽ---0:����Ϊ�в���Ϊ�� 1:����Ϊ�ж���Ϊ�� 
	int m_iDunNumType;			//�������ԭ��---0:������ 1:���ڵ���
	bool m_bAllLeverUseOneName;	//�б�߳̾�ʹ��ͬһ������
	bool m_bDSLeverLB;			//��ʯ�̵߳����б�
	bool m_bDSHeiLB;			//��ʯ�߶ȵ����б�

	//�滻�Ĳ�������
	CString m_Angle;		//·���벼���߼н�
	CString m_GL_Len;		//��������
	CString m_BS;			//��������߾�·�߾���
	CString m_left_Slope;	//����������
	CString m_right_Slope;	//�����Ҳ����
	CString m_left_DJ;		//�������󵹽ǳ�
	CString m_right_DJ;		//�������ҵ��ǳ�
	CString m_left_JB;		//�������߳�
	CString m_right_JB;		//�����ҽ�߳�
	CString m_Dun_Dis;		//�ռ����ľ�
	CString m_GL_LeftTopLever;	//����������
	CString m_GL_rightTopLever;	//�������ұ��
	CString m_Dun_TopLever;	//�ն����
	CString m_DunXL_Lever;	//�ռ�ϵ�����
	CString m_JC_TopLever;	//���������
	CString m_JC_BotLever;	//�����ױ��
	CString m_Dun_Hei;		//�ո�
	CString m_Found_Len;	//׮��
	CString m_DS_Lever;		//��ʯ�߳�
	CString m_DS_Hei;		//��ʯ�߶�
	CString m_DisBKXtoRd;	//������������ľ���
};
//��������
class ROAD_BED_PROJECT_MANAGER_API demo_cap_beam_material
{
public:
	demo_cap_beam_material();
	~demo_cap_beam_material();

public:
	void serialize_members(member_rw_interface& mt);

public:
	CString m_GL_Mat;		//������������
	CString m_DS_Mat;		//��ʯ��������
	CString m_Dun_Mat;		//������������
	CString m_DunXL_Mat;	//����ϵ����������
	CString m_CTKD_Mat;		//��̨/���������������
	CString m_CTDC_Mat;		//��̨����������
	CString m_JCXL_Mat;		//����ϵ����������
	CString m_Fnd_Mat;		//׮����������

	CString m_GL_Type;		//�����ṹ����
	CString m_DS_Type;		//��ʯ�ṹ����
	CString m_Dun_Type;		//�����ṹ����
	CString m_DunXL_Type;	//����ϵ���ṹ����
	CString m_CTKD_Type;	//��̨/��������ṹ����
	CString m_CTDC_Type;	//��̨���ṹ����
	CString m_JCXL_Type;	//����ϵ���ṹ����
	CString m_Fnd_Type;		//׮���ṹ����
};


class ROAD_BED_PROJECT_MANAGER_API road_bed_cap_beam_data : public road_bed_graph_data_base
{
	DECLARE_SERIAL(road_bed_cap_beam_data)

public:
	road_bed_cap_beam_data();
	~road_bed_cap_beam_data();

private:
	virtual void serialize_members(member_rw_interface& mt);
public:
	//common
	demo_cap_beam_common		m_Common;		//��������
	
	//advance
	demo_cap_beam_general		m_Gen;			//��������
	demo_cap_beam				m_GL;			//��������
	demo_cap_beam_Pier			m_Pier;			//׮������
	demo_cap_beam_foundation	m_JC;			//��������
	demo_cap_beam_drawsetting	m_DrawSet;		//��ͼ����
	demo_cap_beam_parameters	m_CSHLB;		//�������б�
	demo_cap_beam_material		m_Materials;	//����ͳ��
};

