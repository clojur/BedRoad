#pragma once


// ͼֽͼ�λ��༭���ڹ۲��߻���
class ROAD_BED_UI_MANAGER_API road_bed_graph_graphic_ui_observer_base : public CObject
{
	DECLARE_SERIAL(road_bed_graph_graphic_ui_observer_base)

public:
	road_bed_graph_graphic_ui_observer_base();
	virtual ~road_bed_graph_graphic_ui_observer_base();

public:
	virtual void save_data_from_ui();
	virtual void load_data_to_ui();

public:
	// ͼֽ���ݵ�tag�����ڴ�����������ȡͼֽ����
	CString m_graph_data_tag;
};
