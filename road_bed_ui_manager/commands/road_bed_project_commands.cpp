#include "stdafx.h"

#include "x_framework/macro.h"
#include "x_framework/tools/file_tools.h"
#include "x_framework/interface/data_center_interface.h"
#include "x_framework/interface/window_interface.h"

#include "road_bed_project_commands.h"
#include "E:\Code\Team\BimRoadBed\Main\src\Frame\main_application\start_page.h"
#include "../road_bed_3D.h"
#include "../road_bed_multi_view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace std;



IMPLEMENT_DYNAMIC(road_bed_create_project_dialog, app_dialog_base)
BEGIN_MESSAGE_MAP(road_bed_create_project_dialog, app_dialog_base)
	ON_BN_CLICKED(IDC_BUTTON_BROWSER_PATH, on_clicked_button_browser_path)
	ON_BN_CLICKED(IDOK, on_clicked_button_ok)
END_MESSAGE_MAP()


road_bed_create_project_dialog::road_bed_create_project_dialog(CWnd* parent /*= nullptr*/) : app_dialog_base(IDD, parent)
{
}

road_bed_create_project_dialog::~road_bed_create_project_dialog()
{
}

void road_bed_create_project_dialog::DoDataExchange(CDataExchange* dx)
{
	app_dialog_base::DoDataExchange(dx);

	DDX_Text(dx, IDC_PROJECT_NAME, m_ui_project_name);
	DDX_Text(dx, IDC_PROJECT_PATH, m_ui_project_path);
}

BOOL road_bed_create_project_dialog::OnInitDialog()
{
	app_dialog_base::OnInitDialog();

	CWinApp* win_app = AfxGetApp();
	if (!win_app) return FALSE;

	CString last_saved_string = win_app->GetProfileString(_T("create_project"), _T("project_path"), _T(""));
	if (last_saved_string.IsEmpty() || !PathIsDirectory(last_saved_string) || !PathFileExists(last_saved_string))
	{
		TCHAR desk_top_buffer[MAX_PATH + 1] = { 0 };
		SHGetSpecialFolderPath(GetSafeHwnd(), desk_top_buffer, CSIDL_DESKTOP, FALSE);
		last_saved_string = desk_top_buffer;
	}

	m_ui_project_name = _T("����Ŀ");
	m_ui_project_path = last_saved_string;

	UpdateData(FALSE);

	return TRUE;
}

void road_bed_create_project_dialog::on_clicked_button_browser_path()
{
	CFolderPickerDialog dlg;
	if (IDOK != dlg.DoModal()) return;

	CString path = dlg.GetPathName();
	CEdit* model_name = (CEdit*) GetDlgItem(IDC_PROJECT_PATH);
	if (model_name && model_name->GetSafeHwnd()) model_name->SetWindowText(path);
}

void road_bed_create_project_dialog::on_clicked_button_ok()
{
	UpdateData(TRUE);

	m_ui_project_name.Trim();
	m_ui_project_path.Trim();

	if (m_ui_project_name.IsEmpty())
	{
		AfxMessageBox(_T("��Ŀ���Ʋ���Ϊ��"), MB_OK | MB_ICONERROR);
		return;
	}

	if (m_ui_project_path.IsEmpty())
	{
		AfxMessageBox(_T("��Ŀ·������Ϊ��"), MB_OK | MB_ICONERROR);
		return;
	}

	CString ext = file_tools::get_ext_from_file_path_name(m_ui_project_name);
	if (ext.IsEmpty()) m_ui_project_name += _T(".") + data_center::get_data_file_suffix();

	CString end_char = m_ui_project_path.Right(1);
	bool is_path_with_xg = (end_char == _T("\\") || end_char == _T("/"));
	m_full_path_name = m_ui_project_path + (is_path_with_xg ? _T("") : _T("\\")) +  m_ui_project_name;

	// �����û�ѡ�����ĿĿ¼
	CWinApp* win_app = AfxGetApp();
	if (win_app) win_app->WriteProfileString(_T("create_project"), _T("project_path"), m_ui_project_path);

	CDialogEx::OnOK();
}


//////////////////////////////////////////////////////////////////////////


demo_project_commands::demo_project_commands() : cmd_container_interface(true)
{
}

demo_project_commands::~demo_project_commands()
{
}

bool demo_project_commands::fire(const CString& domain, const CString& cmd, const CString& param /*= _T("")*/, int drive_mode /*= 0*/)
{
	if (0 == domain.CompareNoCase(_T("sys")) && 0 == cmd.CompareNoCase(_T("new")))
		on_new(param, drive_mode);
	else if (0 == domain.CompareNoCase(_T("sys")) && 0 == cmd.CompareNoCase(_T("open")))
		on_open(param, drive_mode);
	else if (0 == domain.CompareNoCase(_T("sys")) && 0 == cmd.CompareNoCase(_T("close_project")))
		on_close_project(param, drive_mode);
	else if (0 == domain.CompareNoCase(_T("sys")) && 0 == cmd.CompareNoCase(_T("quit")))
		on_quit(param, drive_mode);
	else if (0 == domain.CompareNoCase(_T("sys")) && 0 == cmd.CompareNoCase(_T("save")))
		on_save(param, drive_mode);
	else if (0 == domain.CompareNoCase(_T("sys")) && 0 == cmd.CompareNoCase(_T("save_as")))
		on_save_as(param, drive_mode);
	else if (0 == domain.CompareNoCase(_T("app")) && 0 == cmd.CompareNoCase(_T("test3D")))
		on_test_3D(param, drive_mode);
	else
		; // nothing

	return false;
}

void demo_project_commands::get_status(const CString& domain, const CString& cmd,
	bool& enable, bool& checked, bool& is_transparent)
{
	enable = false;
	checked = false;
	is_transparent = false;

	if (0 == domain.CompareNoCase(_T("sys")) && 0 == cmd.CompareNoCase(_T("new")))
		on_update_new(enable, checked);
	else if (0 == domain.CompareNoCase(_T("sys")) && 0 == cmd.CompareNoCase(_T("open")))
		on_update_open(enable, checked);
	else if (0 == domain.CompareNoCase(_T("sys")) && 0 == cmd.CompareNoCase(_T("close_project")))
		on_update_close_project(enable, checked);
	else if (0 == domain.CompareNoCase(_T("sys")) && 0 == cmd.CompareNoCase(_T("quit")))
		on_update_quit(enable, checked);
	else if (0 == domain.CompareNoCase(_T("sys")) && 0 == cmd.CompareNoCase(_T("save")))
		on_update_save(enable, checked);
	else if (0 == domain.CompareNoCase(_T("sys")) && 0 == cmd.CompareNoCase(_T("save_as")))
		on_update_save_as(enable, checked);
	else if (0 == domain.CompareNoCase(_T("app")) && 0 == cmd.CompareNoCase(_T("test3D")))
		on_update_test_3D(enable,checked);
	else
		; // nothing
}

void demo_project_commands::set_command_filter(std::vector<std::tuple<CString, CString, bool>>& cmds_can_do) const
{
	cmds_can_do.push_back(make_tuple(_T("sys"), _T("new"), false));
	cmds_can_do.push_back(make_tuple(_T("sys"), _T("open"), false));
	cmds_can_do.push_back(make_tuple(_T("sys"), _T("close_project"), false));
	cmds_can_do.push_back(make_tuple(_T("sys"), _T("quit"), false));
	cmds_can_do.push_back(make_tuple(_T("sys"), _T("save"), false));
	cmds_can_do.push_back(make_tuple(_T("sys"), _T("save_as"), false));
	cmds_can_do.push_back(make_tuple(_T("app"), _T("test3D"), false));
}

bool demo_project_commands::on_new(const CString& param, int drive_mode)
{
	if (!data_center::get_data_root()) return false;

	road_bed_create_project_dialog dlg;
	if (IDOK != dlg.DoModal()) return false;

	if (data_center::is_open()) data_center::close_file();

	// �Ƚ�������֪ͨ����Ϊ���ʱ����滹û���أ��ղ�����ע�����Ų���ʡ�ԣ�����tmp������������ڲ���ȷ
	{
		data_node_notify_guard tmp(false);

		// ����ģ������
		data_center::new_file(dlg.m_full_path_name);
		if (!data_center::is_open()) return false; // ����ģ��ʧ��ֱ�ӷ���

		// ��������Ԫ��
		app_ui_interface* app = get_app_ui_interface();
		if (app)
		{
			app->set_title(file_tools::get_full_name_from_file_path_name(dlg.m_full_path_name));
			app->post_close_all_workspace_window(); // ����ʹ��post��ʽ��������ʼҳ�д��������
			app->create_all_docking_panes();
		}
	}

	// �ֹ�����һ�ν���֪ͨ��������post���ƣ��Ա�ȷ������������������յ�����
	data_node_base* nd = data_center::get_data_root();
	if (nd) nd->post_notify_if_enable(notifer_action::post_project_loaded);

	return false;
}

bool demo_project_commands::on_open(const CString& param, int drive_mode)
{
	CWaitCursor cur_tmp;

	CString path_name = param; // ֧���޽���ʱʹ�ò���ֱ�Ӵ�ָ���ļ�
	path_name.Trim();
	if (path_name.IsEmpty())
	{
		CFileDialog dlg(TRUE, _T("*.") + data_center::get_data_file_suffix(), _T(""),
			OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, data_center::get_data_file_filter());
		if (IDOK != dlg.DoModal()) return false;

		path_name = dlg.GetPathName();
	}

	// �Ƚ�������֪ͨ����Ϊ���ʱ����滹û���أ��ղ�����ע�����Ų���ʡ�ԣ�����tmp������������ڲ���ȷ
	{
		data_node_notify_guard tmp(false);
		if (false == data_center::open_file(path_name)) return false;
	}

	// �ֹ�����һ�ν���֪ͨ��������post���ƣ��Ա�ȷ������������������յ�����
	data_node_base* nd = data_center::get_data_root();
	if (nd) nd->post_notify_if_enable(notifer_action::post_project_loaded);

	app_ui_interface* app = get_app_ui_interface();
	if (app)
	{
		app->set_title(file_tools::get_full_name_from_file_path_name(path_name));
		app->post_close_all_workspace_window(); // ����ʹ��post��ʽ��������ʼҳ�д��������
		app->create_all_docking_panes();
	}

	return false;
}

bool demo_project_commands::on_close_project(const CString& param, int drive_mode)
{
	app_ui_interface* app = get_app_ui_interface();
	if (app)
	{
		int wnd_count = app->get_working_space_view_count(); // ��Ҫ�ŵ�ѭ����ȡ��ѭ��ǰȡһ��
		for (int i = wnd_count - 1; i >= 0; --i)
		{
			// ��ȡָ�������Ĵ�����Ϣ0������������ 1���������·����2������ָ�룬�ɹ�����true�����򷵻�false
			tuple<CString, CString, window_interface*> wnd_info;
			if (!app->get_tab_window_and_info(wnd_info, i)) continue;
			
			// �������ʼҳ�򲻹رգ���������ٴ򿪻�����˸
			if (_T("start_page") == std::get<0>(wnd_info) && param == _T("open_start_page")) continue;

			// app->close_working_space_view_using_postmessage_by_index(i, true); // ����ʹ��post��ʽ
			app->close_working_space_view_by_index(i);
		}

		app->destroy_all_docking_panes();
		app->set_title(_T(""));
		
		if (param == _T("open_start_page"))
			app->add_working_space_view(_T("start_page"), _T("")); // ���û����ʼҳ����ӣ��������
	}

	if (data_center::is_open()) data_center::close_file();

	return false;
}

bool demo_project_commands::on_quit(const CString& param, int drive_mode)
{
	if (data_center::is_open()) data_center::close_file();

	app_ui_interface* app = get_app_ui_interface();
	if (app)
	{
		app->close_all_workspace_window(true);
		app->destroy_all_docking_panes();
	}
	
	// ������Լ������������ٷ�
	// AfxPostQuitMessage(0);
	return false;
}

bool demo_project_commands::on_save(const CString& param, int drive_mode)
{
	CWaitCursor tmp;

	set<window_interface*> all_wnds = window_interface::get_all_window_instances();
	for (window_interface* x : all_wnds)
		if (x) x->save_data_from_ui();

	if (data_center::is_open()) data_center::save_file();
	return false;
}

bool demo_project_commands::on_save_as(const CString& param, int drive_mode)
{
	CWaitCursor tmp;

	if (data_center::is_closed()) return false;

	CString path_name = param; // ֧���޽���ʱʹ�ò���ֱ�ӱ��浽ָ���ļ�
	path_name.Trim();
	if (path_name.IsEmpty())
	{
		CFileDialog dlg(FALSE, _T("*.") + data_center::get_data_file_suffix(),
			data_center::get_data_file_full_path_name(),
			OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
			data_center::get_data_file_filter());

		if (IDOK != dlg.DoModal()) return false;

		path_name = dlg.GetPathName();
	}

	// �Ƚ��������ݱ��浽��������
	set<window_interface*> all_wnds = window_interface::get_all_window_instances();
	for (window_interface* x : all_wnds)
		if (x) x->save_data_from_ui();

	data_center::save_as_file(path_name);
	data_center::notify_if_enable(_T(""), notifer_action::post_project_saved_as);

	app_ui_interface* app = get_app_ui_interface();
	if (app) app->set_title(file_tools::get_full_name_from_file_path_name(path_name));

	return false;
}


bool demo_project_commands::on_test_3D(const CString& param, int drive_mode)
{
	//MessageBox(NULL, _T("����"), _T("js"), MB_OK);
	app_ui_interface* app = get_app_ui_interface();
	if (app)
	{
		app->set_title(file_tools::get_full_name_from_file_path_name(_T("jiangsi")));
		app->create_all_docking_panes();
		app->add_working_space_view(_T("road_bed_multi_view"),_T(""));
	}
	return false;
}

void demo_project_commands::on_update_new(bool& enable, bool& checked)
{
	enable = true;
	checked = false;
}

void demo_project_commands::on_update_open(bool& enable, bool& checked)
{
	enable = true;
	checked = false;
}

void demo_project_commands::on_update_close_project(bool& enable, bool& checked)
{
	enable = true;
	checked = false;
}

void demo_project_commands::on_update_quit(bool& enable, bool& checked)
{
	enable = true;
	checked = false;
}

void demo_project_commands::on_update_save(bool& enable, bool& checked)
{
	enable = true;
	checked = false;
}

void demo_project_commands::on_update_save_as(bool& enable, bool& checked)
{
	enable = true;
	checked = false;
}

void demo_project_commands::on_update_test_3D(bool& enable, bool& checked)
{
	enable = true;
	checked = false;
}
