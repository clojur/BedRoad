#pragma once
#include <vector>
#include <map>
#include <memory>

#include "x_framework/macro.h"
#include "x_framework/windows_helper/multi_grid_view.h"
#include "x_framework/interface/window_interface.h"
#include "x_framework/interface/console_interface.h"
#include "x_framework/interface/cmd_container_interface.h"

#include "road_bed_graph_grid_ui_observer_base.h"
#include "road_bed_graph_graphic_ui_observer_base.h"


class road_bed_graph_graphic_ui_observer_base;
class multi_grid_view;
class component_grid_base;
class CTHDataBase;
class road_bed_graph_editor_wnd;


class tab_addvance_navigate_button : public CXTPTabManagerNavigateButton
{
public:
	tab_addvance_navigate_button(CXTPTabManager* manager, road_bed_graph_editor_wnd* editor);
	~tab_addvance_navigate_button();

public:
	virtual void DrawEntry(CDC* pDC, CRect rc, COLORREF clr, BOOL bEnabled);
	virtual void PerformClick(HWND hWnd, CPoint pt);

private:
	road_bed_graph_editor_wnd* m_editor = nullptr; // 暂存对象，不管理内存
};


class tab_common_navigate_button : public CXTPTabManagerNavigateButton
{
public:
	tab_common_navigate_button(CXTPTabManager* manager, road_bed_graph_editor_wnd* editor);
	~tab_common_navigate_button();

public:
	virtual void DrawEntry(CDC* pDC, CRect rc, COLORREF clr, BOOL bEnabled);
	virtual void PerformClick(HWND hWnd, CPoint pt);

private:
	road_bed_graph_editor_wnd* m_editor = nullptr; // 暂存对象，不管理内存
};


// 图纸图形化编辑窗口
class graph_graphic_view : public CWnd, public window_interface, public data_node_notify_interface,
	public console_session_interface, public cmd_container_interface
{
	DECLARE_MESSAGE_MAP()

public:
	graph_graphic_view(road_bed_graph_editor_wnd* editor);
	virtual ~graph_graphic_view();

public:
	// 数据对象内存由外部编辑器统一管理，内部仅暂存指针
	bool load_data_to_ui(road_bed_graph_graphic_ui_observer_base* data);
	bool save_data_from_ui(road_bed_graph_graphic_ui_observer_base* data);
	void set_window_backcolor(COLORREF bk_color);
	
	// 重新加载并刷新一下图纸窗口，并加载关联的图纸数据
	void refresh_graph_window();

private:
	virtual void on_project_data_deleted(const CString& node_tag);
	virtual void on_project_data_new(const CString& node_tag);
	virtual void on_project_data_changed(const CString& node_tag);
	virtual void on_project_data_notify(const CString& node_tag, notifer_action ac);
	virtual void app_theme_changed(theme_style_settings& settings);

	virtual void session_be_finished();
	virtual void on_console_action(int action_type);
	virtual bool is_doing_command();

	virtual bool fire(const CString& domain, const CString& cmd, const CString& param = _T(""), int drive_mode = 0);
	virtual void get_status(const CString& domain, const CString& cmd, bool& enable, bool& checked, bool& is_transparent);
	virtual void set_command_filter(std::vector<std::tuple<CString, CString, bool>>& cmds_can_do) const;


private:
	road_bed_graph_graphic_ui_observer_base*		m_graphic_ui_data; // 暂存对象，不管理内存
	COLORREF							m_back_color;
	road_bed_graph_editor_wnd*					m_editor; // 暂存对象，不管理内存
	bool								m_is_doing_cmd;

private:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* dc);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


// 带标签的多表视窗口
class tab_multi_grid_data_wnd : public CWnd
{
	DECLARE_MESSAGE_MAP()

public:
	tab_multi_grid_data_wnd(road_bed_graph_editor_wnd* editor);
	virtual ~tab_multi_grid_data_wnd();

public:
	// 数据对象内存由外部编辑器统一管理，内部仅暂存指针
	bool load_data_to_ui(road_bed_graph_grid_ui_observer_base* data);
	bool save_data_from_ui(road_bed_graph_grid_ui_observer_base* data);
	void set_window_backcolor(COLORREF bk_color);
	void add_mode_navigate_button(CXTPTabManagerNavigateButton* button);
	multi_grid_tab_control* get_grid_tab_control();

private:
	virtual void on_project_data_deleted(const CString& node_tag);
	virtual void on_project_data_new(const CString& node_tag);
	virtual void on_project_data_changed(const CString& node_tag);

private:
	void clear_ui_data();
	void make_all_children_window_back_color_same_as_this();

private:
	multi_grid_tab_control				m_grid_tabs;
	road_bed_graph_grid_ui_observer_base*		m_grid_ui_data;
	COLORREF							m_bk_color;

	// 缓存创建的对象便于索引
	std::vector<CWnd*>					m_all_tab_page;
	std::map<CString, CTHDataBase*>		m_all_db_grids;

	// 记录创建过的多表窗口，实际上是可以不用记的，用以下代码可以取到tab中对应的多表窗口
	// CXTPTabManagerItem* cur_tab_item = m_grid_tabs.GetSelectedItem();
	// CWnd* cur_wnd = (cur_tab_item ? CWnd::FromHandle(cur_tab_item->GetHandle()) : nullptr);
	// multi_grid_view* cur_view = (cur_wnd ? dynamic_cast<multi_grid_view*>(cur_wnd) : nullptr);
	// 但为了效率还是要缓存一下比较好
	std::vector<multi_grid_view*>		m_created_multi_grid;

	road_bed_graph_editor_wnd*					m_editor; // 暂存对象，不管理内存

private:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT type, int cx, int cy);
	afx_msg BOOL on_cell_value_changed(UINT id, NMHDR * notify_struct, LRESULT * result);
	afx_msg BOOL on_cell_button_clicked(UINT id, NMHDR * notify_struct, LRESULT * result);
};


// 图纸常规窗口
class graph_common_window : public CWnd
{
	DECLARE_MESSAGE_MAP()

public:
	graph_common_window(road_bed_graph_editor_wnd* editor);
	virtual ~graph_common_window();

public:
	std::unique_ptr<road_bed_graph_graphic_ui_observer_base>	m_graphic_observer;		// 图形化编辑界面数据对象
	std::unique_ptr<road_bed_graph_grid_ui_observer_base>	m_grid_observer;		// 常规表格参数界面数据对象

public:
	bool load_data_to_ui(const CString& data_tag);
	bool save_data_from_ui();
	void set_window_backcolor(COLORREF bk_color);

private:
	graph_graphic_view		m_graphic_wnd;
	tab_multi_grid_data_wnd	m_grid_wnd;
	CXTPSplitterWnd			m_split_wnd;
	road_bed_graph_editor_wnd*		m_editor; // 暂存对象，不管理内存

private:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT type, int cx, int cy);
};


// 图纸高级窗口
class graph_advance_window : public CWnd
{
	DECLARE_MESSAGE_MAP()

public:
	graph_advance_window(road_bed_graph_editor_wnd* editor);
	virtual ~graph_advance_window();

public:
	CString											m_data_tag;				// 要展示的数据中心的数据tag
	std::unique_ptr<road_bed_graph_grid_ui_observer_base>	m_grid_observer;		// 常规表格参数界面数据对象

public:
	bool load_data_to_ui(const CString& data_tag);
	bool save_data_from_ui();
	void set_window_backcolor(COLORREF bk_color);

private:
	tab_multi_grid_data_wnd	m_grid_wnd;
	road_bed_graph_editor_wnd*		m_editor; // 暂存对象，不管理内存

private:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT type, int cx, int cy);
};


// 图纸编辑器窗口
class road_bed_graph_editor_wnd : public CWnd, public window_interface
{
	DECLARE_MESSAGE_MAP()

public:
	road_bed_graph_editor_wnd();
	virtual ~road_bed_graph_editor_wnd();

public:
	virtual bool load_data_to_ui(const CString& data_tag);
	virtual bool save_data_from_ui();
	virtual CString get_title();
	virtual void app_theme_changed(theme_style_settings& settings);

public:
	void change_to_advance_window();
	void change_to_normal_window();
	void set_common_grid_ui_observer(std::unique_ptr<road_bed_graph_grid_ui_observer_base>& observer);
	void set_common_graphic_ui_observer(std::unique_ptr<road_bed_graph_graphic_ui_observer_base>& observer);
	void set_advance_grid_ui_observer(std::unique_ptr<road_bed_graph_grid_ui_observer_base>& observer);

private:
	CString						m_data_tag;
	graph_common_window			m_graph_common_wnd;
	graph_advance_window		m_graph_advance_wnd;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT type, int cx, int cy);
};

