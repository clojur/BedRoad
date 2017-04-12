#pragma once
#include "../resource.h"
#include <tuple>

#include "x_framework/macro.h"
#include "x_framework/interface/cmd_container_interface.h"
#include "x_framework/windows_helper/app_dialog_base.h"


// 新建项目对话框
class road_bed_create_project_dialog : public app_dialog_base
{
	DECLARE_DYNAMIC(road_bed_create_project_dialog)
	DECLARE_MESSAGE_MAP()

public:
	road_bed_create_project_dialog(CWnd* parent = nullptr);
	virtual ~road_bed_create_project_dialog();

public:
	enum { IDD = IDD_DIALOG_NEW_PROJECT };

public:
	// 窗口关闭后取到的数据（经过合并及处理后的数据，不是界面原样的数据）
	CString		m_full_path_name;
	CString		m_ui_project_name;
	CString		m_ui_project_path;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* dx);

protected:
	afx_msg void on_clicked_button_browser_path();
	afx_msg void on_clicked_button_ok();
};


class demo_project_commands : public cmd_container_interface
{
public:
	demo_project_commands();
	virtual ~demo_project_commands();

public:
	virtual bool fire(const CString& domain, const CString& cmd, const CString& param = _T(""), int drive_mode = 0);
	virtual void get_status(const CString& domain, const CString& cmd, bool& enable, bool& checked, bool& is_transparent);
	virtual void set_command_filter(std::vector<std::tuple<CString, CString, bool>>& cmds_can_do) const;

private:
	bool on_new(const CString& param, int drive_mode);
	bool on_open(const CString& param, int drive_mode);
	bool on_close_project(const CString& param, int drive_mode);
	bool on_quit(const CString& param, int drive_mode);
	bool on_save(const CString& param, int drive_mode);
	bool on_save_as(const CString& param, int drive_mode);
	bool on_test_3D(const CString& param,int drive_mode);

	void on_update_new(bool& enable, bool& checked);
	void on_update_open(bool& enable, bool& checked);
	void on_update_close_project(bool& enable, bool& checked);
	void on_update_quit(bool& enable, bool& checked);
	void on_update_save(bool& enable, bool& checked);
	void on_update_save_as(bool& enable, bool& checked);
	void on_update_test_3D(bool& enable, bool& checked);
};

