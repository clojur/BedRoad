#pragma once

#include <vector>
#include <map>
#include "x_framework/macro.h"
#include "x_framework/interface/serialize_interface.h"
#include "x_framework/interface/data_center_interface.h"


namespace tinyxml2 { class XMLElement; }


// ͼֽ����ע����Ϣ
class ROAD_BED_PROJECT_MANAGER_API road_bed_graph_register_info : public CObject, public serialize_interface
{
	DECLARE_SERIAL(road_bed_graph_register_info)

public:
	road_bed_graph_register_info();
	road_bed_graph_register_info(const road_bed_graph_register_info& src);
	road_bed_graph_register_info& operator=(const road_bed_graph_register_info& src);
	virtual ~road_bed_graph_register_info();

public:
	virtual void serialize_members(member_rw_interface& mt);

public:
	void initiate_by_xml(tinyxml2::XMLElement* node);

public:
	CString		m_type_name;						// ͼֽ�������ƣ��硰���θ�����ʽ��һ�㹹��ͼ��
	CString		m_data_class_name;					// ���������������
	CString		m_common_grid_class_name;			// �������ñ���������������
	CString		m_advance_grid_class_name;			// �����߼�����������������
	CString		m_graphic_editor_class_name;		// ͼ�λ������༭�����������
	CString		m_drawing_strategy_class_name;		// ͼֽ���Ʋ����������
};

//ͼֽ������Ϣ
class demo_graph_data_manager : public data_node_base
{
public:
	demo_graph_data_manager();
	virtual ~demo_graph_data_manager();
};

// ��Ŀ����(ֱ��ע�ᵽ�������ģ���˲���д���л��꼴����������)
class ROAD_BED_PROJECT_MANAGER_API road_bed_project_data : public data_node_base
{
public:
	road_bed_project_data();
	virtual ~road_bed_project_data();

public:
	virtual void serialize_members(member_rw_interface& mt);
	virtual void set_default_value();

public:
	// ������Ŀ�ļ����׵���ʱ�ļ��и�·��
	CString get_project_temp_path(bool end_with_backslashed = true);

	// ������Ŀ�ļ����׵�ͼֽ�ļ��и�·��
	CString get_project_graph_path(bool end_with_backslashed = true);

	demo_graph_data_manager& get_graph_data_manager();

public:
	// ��xml�����ļ��м��ع���������Ϣ
	static void initiate_graph_register_info_by_xml();
	static bool get_graph_register_info(const CString& type_name, road_bed_graph_register_info& info);
	static void add_graph_register_info(const road_bed_graph_register_info& info);
	static void get_graph_register_info_list(std::vector<road_bed_graph_register_info*>& all_items);

private:
	// ͼֽ����ע����Ϣ�����ݻ��ڳ�������ʱ������ɣ��˴���������Ŀ�й���ѯʹ�ã������л�����Ŀ������
	static std::map<CString, road_bed_graph_register_info> m_all_type_info;
};

road_bed_project_data& get_project_data();
