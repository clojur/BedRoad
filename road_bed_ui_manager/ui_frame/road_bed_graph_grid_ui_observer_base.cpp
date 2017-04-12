#include "stdafx.h"

#include "road_bed_graph_grid_ui_observer_base.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace std;


IMPLEMENT_SERIAL(road_bed_graph_grid_ui_observer_base, CObject, 1)
road_bed_graph_grid_ui_observer_base::road_bed_graph_grid_ui_observer_base()
{
}

road_bed_graph_grid_ui_observer_base::~road_bed_graph_grid_ui_observer_base()
{

}

void road_bed_graph_grid_ui_observer_base::get_table_template_names(std::vector<std::pair<CString, std::vector<CString>>>& all_tables) const
{
	all_tables.clear();
}

void road_bed_graph_grid_ui_observer_base::save_data_from_ui(std::map<CString, CTHDataBase*>& all_dbs)
{

}

void road_bed_graph_grid_ui_observer_base::load_data_to_ui(std::map<CString, CTHDataBase*>& all_dbs)
{

}

void road_bed_graph_grid_ui_observer_base::cell_button_be_clicked(CTHDataBase* db, NM_THGRID* notify_struct)
{

}

void road_bed_graph_grid_ui_observer_base::cell_value_changed(CTHDataBase* db, NM_THGRID* notify_struct)
{

}
