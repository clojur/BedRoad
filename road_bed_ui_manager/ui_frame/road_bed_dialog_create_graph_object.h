#pragma once
#include "../resource.h"

#include "road_bed_project_manager/macro.h"
#include "road_bed_project_manager/data_center/road_bed_project_data.h"

#include "x_framework/macro.h"
#include "x_framework/windows_helper/app_dialog_base.h"


class road_bed_dialog_create_graph_object : public app_dialog_base
{
	DECLARE_DYNAMIC(road_bed_dialog_create_graph_object)
	DECLARE_MESSAGE_MAP()

public:
	road_bed_dialog_create_graph_object(CWnd* pParent = NULL);
	virtual ~road_bed_dialog_create_graph_object();

public:
	enum { IDD = IDD_DIALOG_CREATE_GRAPH_OBJECT };

public:
	CString								m_result_graph_name;
	CString								m_result_type_name;
	std::vector<CString>				m_exist_graph_names;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* dx);
	virtual void OnOK();

private:
	CEdit		m_edit_graph_name;
	CComboBox	m_combo_graph_type;
};
