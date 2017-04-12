#pragma once
#include "../resource.h"

#include "road_bed_project_manager/macro.h"
#include "road_bed_project_manager/data_center/road_bed_project_data.h"

#include "x_framework/macro.h"
#include "x_framework/windows_helper/app_dialog_base.h"


class road_bed_dialog_rename : public app_dialog_base
{
	DECLARE_DYNAMIC(road_bed_dialog_rename)
	DECLARE_MESSAGE_MAP()

public:
	road_bed_dialog_rename(CWnd* pParent = NULL);
	virtual ~road_bed_dialog_rename();

public:
	enum { IDD = IDD_DIALOG_RENAME };

public:
	CString						m_result_name;
	std::vector<CString>		m_exist_names;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* dx);
	virtual void OnOK();

private:
	CEdit		m_edit_graph_name;
};
