#pragma once


// ͼֽ���Ʋ��Ի���
class ROAD_BED_UI_MANAGER_API road_bed_graph_drawing_strategy_base : public CObject
{
	DECLARE_SERIAL(road_bed_graph_drawing_strategy_base)

public:
	road_bed_graph_drawing_strategy_base();
	virtual ~road_bed_graph_drawing_strategy_base();

public:
	// ����ͼֽ����ͼֽ��p0�����е��ļ�����ֵ��ͨ��tag�õ������ļ���������׺
	// ��ͬ�Ĺ����ܳ���ͼֽ��Ŀ��һ��������ͼֽ����֯��ʽҲ��һ������˽�ͼֽ�����·�������ƽ��ɻ�ͼ�����ڽ���ʱ
	// ����ֵ�Ǻ����ҿ��е�
	virtual bool draw(const CString& file_path_name);

public:
	// ͼֽ���ݵ�tag�����ڴ�����������ȡͼֽ����
	CString m_graph_data_tag;
};
