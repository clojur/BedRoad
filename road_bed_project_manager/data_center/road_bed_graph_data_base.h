#pragma once

#include "x_framework/macro.h"
#include "x_framework/interface/data_center_interface.h"
#include "x_framework/interface/serialize_interface.h"
#include "road_bed_project_data.h"


// ͼֽ���ݵĻ���
class ROAD_BED_PROJECT_MANAGER_API road_bed_graph_data_base : public data_node_base
{
	DECLARE_SERIAL(road_bed_graph_data_base)

public:
	road_bed_graph_data_base(const CString& graph_name = _T("")); // �˴�Ϊͼֽ����������ƣ������ǻ��Ƴ���ͼֽ�ļ���
	virtual ~road_bed_graph_data_base();

public:
	virtual void serialize_members(member_rw_interface& mt);

public:
	// ���ص�ǰ�ڵ��Ӧ��ͼֽע����Ϣ
	bool get_graph_reg_info(road_bed_graph_register_info& info) const;

public:
	// ͼֽ�������ƣ���������ͼֽ����ע����Ϣ�������ʺ���ͼֽ������ֱ�Ӵ洢ע����Ϣ�����򿪷��������޸������ļ�
	// ʱ������Ŀ�е�ͼֽ��ͼ����������������ཫ�޷����������ñ仯�������л������ǲ�ǡ���ģ�����ɽ���ı�ȥ��
	// ���ݰ���һ�����ֻ�����������ʹ�õ�ʱ�Զ����ң�
	// ע�⣺�û�ָ����ͼֽ�ڵ����Ʒ��ڻ�����m_name��
	CString m_graph_type_name;

	CString m_graph_dxf_file_name; // ���ɵ�dxfͼֽ�ļ����·�������ƣ��к�׺���ұ����������Ŀ�ļ��еĸ�Ŀ¼��
	CString m_graph_dwg_file_name; // ���ɵ�dwgͼֽ�ļ����·�������ƣ��к�׺���ұ����������Ŀ�ļ��еĸ�Ŀ¼��
	CString m_graph_pdf_file_name; // ���ɵ�pdfͼֽ�ļ����·�������ƣ��к�׺���ұ����������Ŀ�ļ��еĸ�Ŀ¼��
};
