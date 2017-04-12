#pragma once

#include "x_framework/macro.h"
#include "x_framework/interface/data_center_interface.h"
#include "x_framework/interface/serialize_interface.h"


class ROAD_BED_PROJECT_MANAGER_API road_bed_graph_folder_node : public data_node_base
{
	DECLARE_SERIAL(road_bed_graph_folder_node)

public:
	road_bed_graph_folder_node(const CString& name = _T(""));
	virtual ~road_bed_graph_folder_node();

public:
	virtual void serialize_members(member_rw_interface& mt);
};
