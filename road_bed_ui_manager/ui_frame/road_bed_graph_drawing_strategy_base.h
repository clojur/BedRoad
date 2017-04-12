#pragma once


// 图纸绘制策略基类
class ROAD_BED_UI_MANAGER_API road_bed_graph_drawing_strategy_base : public CObject
{
	DECLARE_SERIAL(road_bed_graph_drawing_strategy_base)

public:
	road_bed_graph_drawing_strategy_base();
	virtual ~road_bed_graph_drawing_strategy_base();

public:
	// 绘制图纸并对图纸这p0数据中的文件名赋值（通过tag得到），文件名不含后缀
	// 不同的构件能出的图纸数目不一样，对于图纸的组织方式也不一样，因此将图纸的相对路径和名称交由绘图函数在结束时
	// 负责赋值是合理且可行的
	virtual bool draw(const CString& file_path_name);

public:
	// 图纸数据的tag，用于从数据中心索取图纸数据
	CString m_graph_data_tag;
};
