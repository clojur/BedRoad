#pragma once
#include <utility>
#include <map>
#include <vector>

struct NM_THGRID;
class CTHDataBase;

// �������������ݹ۲�����
class ROAD_BED_UI_MANAGER_API road_bed_graph_grid_ui_observer_base : public CObject
{
	DECLARE_SERIAL(road_bed_graph_grid_ui_observer_base)

public:
	road_bed_graph_grid_ui_observer_base();
	virtual ~road_bed_graph_grid_ui_observer_base();

public:
	// ����Ҫ��ʾ�ı��ģ������
	// ע�⣬���������ɿ���Զ����صģ�����ʹ�����ṩ���Զ���������Ҫ����ģ�������ע������������ȷʶ��
	// �Ƽ��Զ�����ͳһ��װ�ɽӿڣ���������DllMain()���Ƶ�λ�õ���һ�£�ȷ��ֻ����һ�μ���
	virtual void get_table_template_names(std::vector<std::pair<CString, std::vector<CString>>>& all_tables) const;
	virtual void save_data_from_ui(std::map<CString, CTHDataBase*>& all_dbs);
	virtual void load_data_to_ui(std::map<CString, CTHDataBase*>& all_dbs);
	virtual void cell_button_be_clicked(CTHDataBase* db, NM_THGRID* notify_struct);
	virtual void cell_value_changed(CTHDataBase* db, NM_THGRID* notify_struct);

public:
	// ͼֽ���ݵ�tag�����ڴ�����������ȡͼֽ����
	CString m_graph_data_tag;
};
