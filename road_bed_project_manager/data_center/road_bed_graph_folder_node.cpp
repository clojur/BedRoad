#include "stdafx.h"

#include "x_framework/macro.h"
#include "x_framework/tools/string_tools.h"
#include "x_framework/tools/tinyxml2.h"
#include "x_framework/tools/xml_tools.h"

#include "road_bed_graph_folder_node.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


IMPLEMENT_SERIAL(road_bed_graph_folder_node, data_node_base, 1)
road_bed_graph_folder_node::road_bed_graph_folder_node(const CString& name/* = _T("")*/) : data_node_base(name)
{

}

road_bed_graph_folder_node::~road_bed_graph_folder_node()
{

}

void road_bed_graph_folder_node::serialize_members(member_rw_interface& mt)
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
		}
	}

	data_node_base::serialize_members(mt);
}
