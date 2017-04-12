#include "stdafx.h"
#include "road_bed_graph_drawing_strategy_base.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_SERIAL(road_bed_graph_drawing_strategy_base, CObject, 1)
road_bed_graph_drawing_strategy_base::road_bed_graph_drawing_strategy_base()
{
}

road_bed_graph_drawing_strategy_base::~road_bed_graph_drawing_strategy_base()
{

}

bool road_bed_graph_drawing_strategy_base::draw(const CString& file_path_name)
{
	return false;
}
