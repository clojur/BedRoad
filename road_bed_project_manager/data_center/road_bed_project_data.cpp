#include "stdafx.h"

#include "x_framework/macro.h"
#include "x_framework/tools/file_tools.h"
#include "x_framework/tools/string_tools.h"
#include "x_framework/tools/tinyxml2.h"
#include "x_framework/tools/xml_tools.h"

#include "road_bed_graph_data_base.h"

#include "road_bed_project_data.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


//////////////////////////////////////////////////////////////////////////

std::map<CString, road_bed_graph_register_info> road_bed_project_data::m_all_type_info;

//////////////////////////////////////////////////////////////////////////


IMPLEMENT_SERIAL(road_bed_graph_register_info, CObject, 1)
road_bed_graph_register_info::road_bed_graph_register_info()
{

}

road_bed_graph_register_info::road_bed_graph_register_info(const road_bed_graph_register_info& src)
{
	*this = src;
}

road_bed_graph_register_info::~road_bed_graph_register_info()
{

}

road_bed_graph_register_info& road_bed_graph_register_info::operator=(const road_bed_graph_register_info& src)
{
	if (this == &src) return *this;

	m_type_name = src.m_type_name;
	m_data_class_name = src.m_data_class_name;
	m_common_grid_class_name = src.m_common_grid_class_name;
	m_advance_grid_class_name = src.m_advance_grid_class_name;
	m_graphic_editor_class_name = src.m_graphic_editor_class_name;
	m_drawing_strategy_class_name = src.m_drawing_strategy_class_name;

	return *this;
}

void road_bed_graph_register_info::initiate_by_xml(tinyxml2::XMLElement* node)
{
	if (!node) return;

	m_type_name = get_xml_node_attribute_str(node, _T("type_name"));
	m_data_class_name = get_xml_node_attribute_str(node, _T("data_class_name"));
	m_common_grid_class_name = get_xml_node_attribute_str(node, _T("common_grid_class_name"));
	m_advance_grid_class_name = get_xml_node_attribute_str(node, _T("advance_grid_class_name"));
	m_graphic_editor_class_name = get_xml_node_attribute_str(node, _T("graphic_editor_class_name"));
	m_drawing_strategy_class_name = get_xml_node_attribute_str(node, _T("drawing_strategy_class_name"));
}

void road_bed_graph_register_info::serialize_members(member_rw_interface& mt)
{
	int version = 2;

	if (mt.is_storing())
	{
		mt.write(_T("version"), version);

		mt.write(_T("m_type_name"), m_type_name);
		mt.write(_T("m_data_class_name"), m_data_class_name);
		mt.write(_T("m_common_grid_class_name"), m_common_grid_class_name);
		mt.write(_T("m_advance_grid_class_name"), m_advance_grid_class_name);
		mt.write(_T("m_graphic_editor_class_name"), m_graphic_editor_class_name);
		mt.write(_T("m_drawing_strategy_class_name"), m_drawing_strategy_class_name);
	}
	else
	{
		mt.read(_T("version"), version);

		if (1 == version)
		{
			mt.read(_T("m_type_name"), m_type_name);
			mt.read(_T("m_data_class_name"), m_data_class_name);
			mt.read(_T("m_common_grid_class_name"), m_common_grid_class_name);
			mt.read(_T("m_advance_grid_class_name"), m_advance_grid_class_name);
			mt.read(_T("m_graphic_editor_class_name"), m_graphic_editor_class_name);
		}
		else if (2 == version)
		{
			mt.read(_T("m_type_name"), m_type_name);
			mt.read(_T("m_data_class_name"), m_data_class_name);
			mt.read(_T("m_common_grid_class_name"), m_common_grid_class_name);
			mt.read(_T("m_advance_grid_class_name"), m_advance_grid_class_name);
			mt.read(_T("m_graphic_editor_class_name"), m_graphic_editor_class_name);
			mt.read(_T("m_drawing_strategy_class_name"), m_drawing_strategy_class_name);
		}
		else
		{
			// nothing;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
demo_graph_data_manager::demo_graph_data_manager()
{

}
demo_graph_data_manager::~demo_graph_data_manager()
{

}
//////////////////////////////////////////////////////////////////////////


road_bed_project_data::road_bed_project_data()
{
	add_child_node(new demo_graph_data_manager());
}

road_bed_project_data::~road_bed_project_data()
{
}

void road_bed_project_data::serialize_members(member_rw_interface& mt)
{
	int version = 1;

	if (mt.is_storing())
	{
		mt.write(_T("version"), version);
	}
	else
	{
		mt.read(_T("version"), version);

		if (1 == version)
		{
			// nothing;
		}
	}

	data_node_base::serialize_members(mt);
}

void road_bed_project_data::set_default_value()
{
	clear_node();
}

CString road_bed_project_data::get_project_temp_path(bool end_with_backslashed /*= true*/)
{
	CString working_path = data_center::get_project_working_folder_path(true);
	if (working_path.IsEmpty()) return _T("");

	working_path.Append(_T("temps"));
	if (end_with_backslashed) working_path.Append(_T("\\"));

	return working_path;
}

CString road_bed_project_data::get_project_graph_path(bool end_with_backslashed /*= true*/)
{
	CString working_path = data_center::get_project_working_folder_path(true);
	if (working_path.IsEmpty()) return _T("");

	working_path.Append(_T("graphs"));
	if (end_with_backslashed) working_path.Append(_T("\\"));

	return working_path;
}

void road_bed_project_data::initiate_graph_register_info_by_xml()
{
	m_all_type_info.clear();

	// ��ʼ��ȡxml����
	CString xml_file_full_path = file_tools::get_app_path_with_xg() + _T("gui_xml\\app_graph_register_info.xml");
	tinyxml2::XMLDocument doc;
	if (tinyxml2::XML_SUCCESS != doc.LoadFile(string_tools::CString_to_string(xml_file_full_path).c_str())) return;

	tinyxml2::XMLElement* node = doc.FirstChildElement("app_graph_register_info_type");
	if (!node || node->NoChildren()) return;

	node = node->FirstChildElement("graph_register_info_item");
	if (!node) return;

	do
	{
		road_bed_graph_register_info info;
		info.initiate_by_xml(node);
		
		if (!info.m_type_name.IsEmpty() && !info.m_data_class_name.IsEmpty())
			m_all_type_info[info.m_type_name] = info;

		node = node->NextSiblingElement("graph_register_info_item");
	} while (node);
}

bool road_bed_project_data::get_graph_register_info(const CString& type_name, road_bed_graph_register_info& info)
{
	if (type_name.IsEmpty()) return false;

	auto it = m_all_type_info.find(type_name);
	if (it != m_all_type_info.end())
	{
		info = it->second;
		return true;
	}

	return false;
}

void road_bed_project_data::add_graph_register_info(const road_bed_graph_register_info& info)
{
	if (info.m_type_name.IsEmpty()) return;

	m_all_type_info[info.m_type_name] = info;
}

void road_bed_project_data::get_graph_register_info_list(std::vector<road_bed_graph_register_info*>& all_items)
{
	all_items.clear();

	for (auto& x : m_all_type_info)
		all_items.push_back(&x.second);
}

demo_graph_data_manager& road_bed_project_data::get_graph_data_manager()
{
	std::vector<data_node_base*> children = get_children();
	return *dynamic_cast<demo_graph_data_manager*>(children[0]);
}

road_bed_project_data& get_project_data()
{
	return *dynamic_cast<road_bed_project_data*>(data_center::get_data_root());
}


