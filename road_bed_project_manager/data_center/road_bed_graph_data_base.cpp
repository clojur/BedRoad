#include "stdafx.h"

#include "x_framework/macro.h"
#include "x_framework/tools/string_tools.h"

#include "road_bed_project_data.h"

#include "road_bed_graph_data_base.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


IMPLEMENT_SERIAL(road_bed_graph_data_base, data_node_base, 1)
road_bed_graph_data_base::road_bed_graph_data_base(const CString& graph_name/* = _T("")*/)
: data_node_base(graph_name)
{
}

road_bed_graph_data_base::~road_bed_graph_data_base()
{

}

void road_bed_graph_data_base::serialize_members(member_rw_interface& mt)
{
	int version = 2;

	if (mt.is_storing())
	{
		mt.write(_T("version"), version);

		mt.write(_T("m_graph_type_name"), m_graph_type_name);
		mt.write(_T("m_graph_dxf_file_name"), m_graph_dxf_file_name);
		mt.write(_T("m_graph_dwg_file_name"), m_graph_dwg_file_name);
		mt.write(_T("m_graph_pdf_file_name"), m_graph_pdf_file_name);
	}
	else
	{
		mt.read(_T("version"), version);

		if (1 == version)
		{
			mt.read(_T("m_graph_type_name"), m_graph_type_name);
			mt.read(_T("m_graph_dxf_file_name"), m_graph_dxf_file_name);
			mt.read(_T("m_graph_dwg_file_name"), m_graph_dwg_file_name);
			mt.read(_T("m_graph_pdf_file_name"), m_graph_pdf_file_name);
		}
		else
		{
			// nothing;
		}
	}

	data_node_base::serialize_members(mt);
}

bool road_bed_graph_data_base::get_graph_reg_info(road_bed_graph_register_info& info) const
{
	road_bed_project_data* proj = dynamic_cast<road_bed_project_data*>(data_center::get_data_root());
	if (!proj) return false;

	return proj->get_graph_register_info(m_graph_type_name, info);
}
