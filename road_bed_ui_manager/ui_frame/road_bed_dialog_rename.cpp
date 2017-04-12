#include "stdafx.h"
#include "road_bed_dialog_rename.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace std;


IMPLEMENT_DYNAMIC(road_bed_dialog_rename, app_dialog_base)
BEGIN_MESSAGE_MAP(road_bed_dialog_rename, app_dialog_base)
END_MESSAGE_MAP()

road_bed_dialog_rename::road_bed_dialog_rename(CWnd* pParent /*=NULL*/)
	: app_dialog_base(road_bed_dialog_rename::IDD, pParent)
{
}

road_bed_dialog_rename::~road_bed_dialog_rename()
{
}

BOOL road_bed_dialog_rename::OnInitDialog()
{
	app_dialog_base::OnInitDialog();

	m_edit_graph_name.SetWindowText(m_result_name);

	return TRUE;
}

void road_bed_dialog_rename::DoDataExchange(CDataExchange* dx)
{
	app_dialog_base::DoDataExchange(dx);

	DDX_Control(dx, IDC_EDIT_NAME, m_edit_graph_name);
}

void road_bed_dialog_rename::OnOK()
{
	m_edit_graph_name.GetWindowText(m_result_name);
	m_result_name.Trim();
	if (m_result_name.IsEmpty())
	{
		AfxMessageBox(_T("名称不能为空"), MB_ICONWARNING | MB_OK);
		return;
	}

	auto it = std::find_if(m_exist_names.begin(), m_exist_names.end(), [&](const CString& cur_name)
	{
		return (0 == cur_name.CompareNoCase(m_result_name));
	});

	if (it != m_exist_names.end())
	{
		AfxMessageBox(_T("名称已存在"), MB_ICONWARNING | MB_OK);
		return;
	}

	app_dialog_base::OnOK();
}

