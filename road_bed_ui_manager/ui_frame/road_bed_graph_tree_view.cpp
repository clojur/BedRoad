#include "stdafx.h"
#include "../resource.h"

#include "road_bed_project_manager/macro.h"
#include "road_bed_project_manager/data_center/road_bed_graph_data_base.h"
#include "road_bed_project_manager/data_center/road_bed_graph_folder_node.h"

#include "road_bed_graph_grid_ui_observer_base.h"
#include "road_bed_dialog_create_graph_object.h"
#include "road_bed_graph_editor_wnd.h"
#include "road_bed_dialog_create_folder.h"
#include "road_bed_dialog_rename.h"
#include "road_bed_graph_drawing_strategy_base.h"

#include "road_bed_graph_tree_view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace std;



project_tree_node_data::project_tree_node_data()
{
	m_node_type = project_tree_node_type::unknown;
}

project_tree_node_data::~project_tree_node_data()
{
}

IMPLEMENT_SERIAL(road_bed_graph_tree_view, CXTPTreeView, 1)
BEGIN_MESSAGE_MAP(road_bed_graph_tree_view, CXTPTreeView)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND_RANGE(APP_POPUP_MENU_ID_START, APP_POPUP_MENU_ID_END, on_command_all_popup_menu)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, on_tree_node_expanded)
END_MESSAGE_MAP()

road_bed_graph_tree_view::road_bed_graph_tree_view()
{
	m_last_option_node_handle = nullptr;
	initialize_menus();
}

road_bed_graph_tree_view::~road_bed_graph_tree_view()
{
	// ��Դ��Ҫ��ɾ�����ѱ�image_list�ӹ�
	// safe_delete(m_bitmap);
	clear_tree_nodes();
}

bool road_bed_graph_tree_view::load_data_to_ui(const CString& data_tag)
{
	initialize_tree_nodes();
	return true;
}

bool road_bed_graph_tree_view::save_data_from_ui()
{
	return true;
}

void road_bed_graph_tree_view::on_project_data_notify(const CString& node_tag, notifer_action ac)
{
	if (notifer_action::pre_removed_node == ac)
	{
		return; // ɾ��ǰ����Ӧ��ɾ��������Ӧ�����¸�����
	}
	else if (notifer_action::post_project_saved_as == ac)
	{
		CTreeCtrl& tree = GetTreeCtrl();
		if (tree.GetSafeHwnd())
		{
			HTREEITEM root = tree.GetRootItem();
			if (root) tree.SetItemText(root, data_center::get_data_file_name());
		}
	}
	else if (notifer_action::pre_project_closed == ac)
	{
		clear_tree_nodes();
	}
	else
	{
		// �Ժ�Ҫ����tag�������ø��������Ĳ����Ա���߳���Ч�ʣ����ڿ�����ʱ�������´���
		initialize_tree_nodes();
	}
}

void road_bed_graph_tree_view::initialize_menus()
{
	popup_menu_item* project_menu = add_popup_menu(_T("project"));
	if (project_menu)
	{
		project_menu->add_sub_item(_T("���ͼֽ...\tAlt+&A"), [&](){ return on_menu_project_item_add_graph(); }, nullptr);
		project_menu->add_sub_item(_T("ȫ����ͼ\tAlt+&G"), [&](){ return on_menu_project_item_draw_all_graphs(); }, nullptr);
		project_menu->add_sub_item(_T("���\tAlt+&C"), [&](){ return on_menu_project_item_clear_all(); }, nullptr);
		project_menu->add_sub_item(_T("���Ŀ¼...\tAlt+&D"), [&](){ return on_menu_project_item_add_directory(); }, nullptr);
	}

	popup_menu_item* directory_menu = add_popup_menu(_T("directory"));
	if (directory_menu)
	{
		directory_menu->add_sub_item(_T("���ͼֽ...\tAlt+&A"), [&](){ return on_menu_directory_item_add_graph(); }, nullptr);
		directory_menu->add_sub_item(_T("ȫ����ͼ\tAlt+&G"), [&](){ return on_menu_directory_item_draw_all_graphs(); }, nullptr);
		directory_menu->add_sub_item(_T("���\tAlt+&C"), [&](){ return on_menu_directory_item_clear_all(); }, nullptr);
		directory_menu->add_sub_item(_T("���Ŀ¼...\tAlt+&D"), [&](){ return on_menu_directory_item_add_directory(); }, nullptr);
		directory_menu->add_sub_item(_T("ɾ��\tAlt+&E"), [&](){ return on_menu_directory_item_delete(); }, nullptr);
		directory_menu->add_sub_item(_T("������...\tAlt+&R"), [&](){ return on_menu_directory_item_rename(); }, nullptr);
	}

	popup_menu_item* graph_menu = add_popup_menu(_T("graph"));
	if (graph_menu)
	{
		graph_menu->add_sub_item(_T("��ͼ\tAlt+&G"), [&](){ return on_menu_graph_item_draw_one_graph(); }, nullptr);
		graph_menu->add_sub_item(_T("ɾ��\tAlt+&E"), [&](){ return on_menu_graph_item_delete_one_graph(); }, nullptr);
		graph_menu->add_sub_item(_T("������...\tAlt+&R"), [&](){ return on_menu_graph_item_rename(); }, nullptr);
		graph_menu->add_sub_item(_T("-"));
		graph_menu->add_sub_item(_T("����ģ��"), [&](){ return on_menu_graph_open_output_template(); },  nullptr);
		graph_menu->add_sub_item(_T("����ģ��"), [&](){return on_menu_graph_open_import_template(); }, nullptr);
		graph_menu->add_sub_item(_T("-"));
		graph_menu->add_sub_item(_T("��dxfͼֽ"), [&](){ return on_menu_graph_open_dxf_file(); }, nullptr);
		graph_menu->add_sub_item(_T("��dwgͼֽ"), [&](){return on_menu_graph_open_dwg_file(); }, nullptr);
		graph_menu->add_sub_item(_T("��pdfͼֽ"), [&](){return on_menu_graph_open_pdf_file(); }, nullptr);
	}
}

void road_bed_graph_tree_view::app_theme_changed(theme_style_settings& settings)
{
	CTreeCtrl& tree = GetTreeCtrl();
	if (tree.GetSafeHwnd()) tree.SetBkColor(settings.m_window_back_color);
}

HTREEITEM insert_tree_data_node(CTreeCtrl& tree, HTREEITEM parent_item, data_node_base* cur_node_data)
{
	CString node_text = (cur_node_data ? cur_node_data->get_node_name() : _T(""));

	// ����ͼֽ�ڵ㲻��Ҫ��������
	road_bed_graph_data_base* gd = dynamic_cast<road_bed_graph_data_base*>(cur_node_data);
	if (gd)
	{
		HTREEITEM node_handle = tree.InsertItem(node_text, 0, 0, parent_item, nullptr);
		if (nullptr == node_handle) return nullptr;

		project_tree_node_data* tree_item_data = new project_tree_node_data();
		tree_item_data->m_data_node_tag = gd->get_node_tag();
		tree_item_data->m_graph_reg_type_name = gd->m_graph_type_name;
		tree_item_data->m_node_type = project_tree_node_type::graph;
		tree.SetItemData(node_handle, (DWORD_PTR)tree_item_data);

		return node_handle;
	}

	road_bed_graph_folder_node* fd = dynamic_cast<road_bed_graph_folder_node*>(cur_node_data);
	if (fd)
	{
		HTREEITEM node_handle = tree.InsertItem(node_text, 1, 1, parent_item, nullptr);
		if (nullptr == node_handle) return nullptr;

		project_tree_node_data* tree_item_data = new project_tree_node_data();
		tree_item_data->m_data_node_tag = fd->get_node_tag();
		// tree_item_data->m_grap_resister_info;
		tree_item_data->m_node_type = project_tree_node_type::folder;
		tree.SetItemData(node_handle, (DWORD_PTR) tree_item_data);

		return node_handle;
	}

	// ��Щ�ڵ����⣬��һ��Ҫ�нڵ����ݣ�����Ŀ���ڵ�
	HTREEITEM node_handle = tree.InsertItem(node_text, parent_item, nullptr);
	if (nullptr == node_handle) return nullptr;

	tree.SetItemData(node_handle, (DWORD_PTR)nullptr);
	return node_handle;
}

void implement_initialize_tree_nodes(CTreeCtrl& tree, HTREEITEM parent_item, data_node_base* cur_node_data)
{
	if (!cur_node_data) return;

	HTREEITEM cur_handle = insert_tree_data_node(tree, parent_item, cur_node_data);
	if (!cur_handle) return;

	for (int i = 0; i < (int) cur_node_data->get_children_count(); ++i)
		implement_initialize_tree_nodes(tree, cur_handle, cur_node_data->get_child(i));

	tree.Expand(cur_handle, TVE_EXPAND);
}

void road_bed_graph_tree_view::initialize_tree_nodes()
{
	CTreeCtrl& tree = GetTreeCtrl();
	if (!tree.GetSafeHwnd()) return;

	clear_tree_nodes();

	m_last_option_node_handle = nullptr;
	
	// ������ڵ��ʱ̫С�����÷ŵ�SetRedraw֮���ˣ��򻯴����߼�
	HTREEITEM root = tree.InsertItem(data_center::get_data_file_name(), 2, 2, nullptr, nullptr);
	if (data_center::is_closed()) return; // ���ڲ�����ڵ���棬������Ŀ���ƽڵ����ʾ����

	// �������ĵ����ݸ��Ͳ����ڽ����ϴ������ڵ���
	data_node_base* node_data = data_center::get_data_root();
	if (!node_data) return;

	tree.SetRedraw(FALSE); // ����clear_tree_nodes()֮����Ϊ���ڲ�Ҳ��SetRedraw����

	for (int i = 0; i < (int) node_data->get_children_count(); ++i)
		implement_initialize_tree_nodes(tree, root, node_data->get_child(i));

	tree.Expand(root, TVE_EXPAND);

	tree.SetRedraw(TRUE);
}

void implement_only_clear_tree_data(CTreeCtrl& tree, HTREEITEM cur_item)
{
	// ��ɾ�����ڵ�ĸ������ݣ����ڵ㱾��ɾ��
	project_tree_node_data* node_data = (project_tree_node_data*) tree.GetItemData(cur_item);
	safe_delete(node_data);
	tree.SetItemData(cur_item, (DWORD_PTR) nullptr);

	// ��ɾ���ӽڵ������
	cur_item = tree.GetChildItem(cur_item);
	while (cur_item)
	{
		implement_only_clear_tree_data(tree, cur_item);
		cur_item = tree.GetNextSiblingItem(cur_item);
	}
}

void road_bed_graph_tree_view::clear_tree_nodes()
{
	m_last_option_node_handle = nullptr;

	CTreeCtrl& tree = GetTreeCtrl();
	if (!tree.GetSafeHwnd()) return;

	HTREEITEM root = tree.GetRootItem();
	if (!root) return;
	
	tree.SetRedraw(FALSE);

	implement_only_clear_tree_data(tree, root);
	tree.DeleteAllItems();

	tree.SetRedraw(TRUE);
}

HTREEITEM road_bed_graph_tree_view::get_tree_node_under_cursor()
{
	CTreeCtrl& tree = GetTreeCtrl();
	if (!tree.GetSafeHwnd()) return nullptr;

	CPoint point_click;
	GetCursorPos(&point_click);
	tree.ScreenToClient(&point_click);
	
	// �����õ�����ϵ�뵯���˵�ʱ�õĲ���ͬһ����û�����κ�һ���ڵ����һ���ֱ�ӷ���
	return tree.HitTest(point_click);
}

data_node_base* road_bed_graph_tree_view::get_data_node_by_tree_item(HTREEITEM item)
{
	if (!item) return nullptr;

	CTreeCtrl& tree = GetTreeCtrl();
	if (!tree.GetSafeHwnd()) return nullptr;

	// ���ڵ�û�����ݣ������ڵ��������
	project_tree_node_data* tree_node = (project_tree_node_data*) tree.GetItemData(m_last_option_node_handle);
	if (!tree_node) return nullptr;

	return data_center::get_data_node(tree_node->m_data_node_tag);
}

void road_bed_graph_tree_view::active_graph_editor(const CString& editor_title, const project_tree_node_data& tree_node_data)
{
	CString class_name;
	CObject* tmp_obj = nullptr;

	road_bed_graph_register_info info;
	if (false == road_bed_project_data::get_graph_register_info(tree_node_data.m_graph_reg_type_name, info)) return;

	class_name = info.m_common_grid_class_name;
	tmp_obj = CRuntimeClass::CreateObject(class_name);
	if (!tmp_obj)
	{
		CString err_info = _T("�� [ ") + class_name + _T(" ] �޷�ʵ������ͼֽ�༭������ʧ��");
		AfxMessageBox(err_info, MB_OK | MB_ICONERROR);
		return;
	}

	std::unique_ptr<road_bed_graph_grid_ui_observer_base> grid_ui(dynamic_cast<road_bed_graph_grid_ui_observer_base*>(tmp_obj));
	if (!grid_ui)
	{
		safe_delete(tmp_obj);
		CString err_info = _T("�� [ ") + class_name + _T(" ] �޷�ʵ������ͼֽ�༭������ʧ��");
		AfxMessageBox(err_info, MB_OK | MB_ICONERROR);
		return;
	}

	//////////////////////////////////////////////////////////////////////////

	class_name = info.m_advance_grid_class_name;
	tmp_obj = CRuntimeClass::CreateObject(class_name);
	if (!tmp_obj)
	{
		CString err_info = _T("�� [ ") + class_name + _T(" ] �޷�ʵ������ͼֽ�༭������ʧ��");
		AfxMessageBox(err_info, MB_OK | MB_ICONERROR);
		return;
	}

	std::unique_ptr<road_bed_graph_grid_ui_observer_base> adv_grid_ui(dynamic_cast<road_bed_graph_grid_ui_observer_base*>(tmp_obj));
	if (!adv_grid_ui)
	{
		safe_delete(tmp_obj);
		CString err_info = _T("�� [ ") + class_name + _T(" ] �޷�ʵ������ͼֽ�༭������ʧ��");
		AfxMessageBox(err_info, MB_OK | MB_ICONERROR);
		return;
	}

	//////////////////////////////////////////////////////////////////////////

	class_name = info.m_graphic_editor_class_name;
	tmp_obj = CRuntimeClass::CreateObject(class_name);
	if (!tmp_obj)
	{
		CString err_info = _T("�� [ ") + class_name + _T(" ] �޷�ʵ������ͼֽ�༭������ʧ��");
		AfxMessageBox(err_info, MB_OK | MB_ICONERROR);
		return;
	}

	std::unique_ptr<road_bed_graph_graphic_ui_observer_base> graphic_ui(dynamic_cast<road_bed_graph_graphic_ui_observer_base*>(tmp_obj));
	if (!graphic_ui)
	{
		safe_delete(tmp_obj);
		CString err_info = _T("�� [ ") + class_name + _T(" ] �޷�ʵ������ͼֽ�༭������ʧ��");
		AfxMessageBox(err_info, MB_OK | MB_ICONERROR);
		return;
	}

	//////////////////////////////////////////////////////////////////////////

	road_bed_graph_editor_wnd* editor_wnd = new road_bed_graph_editor_wnd();

	// �������ⲿ�����ȷ��ڱ༭�ڲ������ã�һ�ǿ��Աܿ����ݴ���ʧ��ʱ���µı༭����ʵ�������������Ǹ�����չʾ����
	// �����ݰ����ԭ�������Ժ���һ������Ч�������ǿ����ⲿʹ�û������������Ч�ʲ�Ϊ�༭��ֱ���ṩ���ݶ�����
	// ����һ�Ժ�������ҵ��仯�������̱临�ӻ�����Ժ��ʺ�ʹ����������ģʽ�������̽�����֯
	editor_wnd->set_common_grid_ui_observer(grid_ui);
	editor_wnd->set_common_graphic_ui_observer(graphic_ui);
	editor_wnd->set_advance_grid_ui_observer(adv_grid_ui);

	// �ڲ��Զ������������id
	static unsigned int editor_wnd_start_id = 1001;

	// ���������ٴ��������ڱ���ָ�������ڣ����򴴽�ʧ�ܣ��˴�����ָ��һ������ӵ���������ܻ��Զ�����Ϊ��ȷ�ĸ�����
	BOOL flag = editor_wnd->Create(nullptr, nullptr, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
		CRect(), this, ++editor_wnd_start_id);

	if (TRUE != flag)
	{
		safe_delete(editor_wnd);
		AfxMessageBox(_T("ͼֽ�༭������ʧ��"), MB_OK | MB_ICONERROR);
		return;
	}

	app_ui_interface* app = get_app_ui_interface();
	if (app) app->add_working_space_view(editor_wnd, tree_node_data.m_data_node_tag);
}

road_bed_graph_data_base* road_bed_graph_tree_view::create_graph_data_base(const CString& class_name)
{
	CObject* obj = (CRuntimeClass::CreateObject(class_name));
	if (!obj)
	{
		CString err_info = _T("�� [ ") + class_name + _T(" ] �޷�ʵ������ͼֽ����ʧ��");
		AfxMessageBox(err_info, MB_OK | MB_ICONERROR);
		return nullptr;
	}

	road_bed_graph_data_base* new_node = dynamic_cast<road_bed_graph_data_base*>(obj);
	if (!new_node)
	{
		CString err_info = _T("�� [ ") + class_name + _T(" ] �޷�ʵ������ͼֽ����ʧ��");
		AfxMessageBox(err_info, MB_OK | MB_ICONERROR);
		safe_delete(obj); // ���ɾ���������ڴ�й©
		return nullptr;
	}

	// ���ý������ݸ��£�ֱ�����Բ��ᴥ��֪ͨ����Ϊ��û�йҽӵ���������
	return new_node;
}

BOOL road_bed_graph_tree_view::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASBUTTONS | TVS_HASLINES | TVS_SHOWSELALWAYS/* | TVS_TRACKSELECT*/ | TVS_DISABLEDRAGDROP;
	//lpCreateStruct->style &= ~TVS_LINESATROOT;
	lpCreateStruct->dwExStyle |= TVS_EX_DOUBLEBUFFER | TVS_EX_AUTOHSCROLL | TVS_EX_FADEINOUTEXPANDOS;

	if (-1 == CXTPTreeView::OnCreate(lpCreateStruct)) return FALSE;

	// XTP 17.2.0��bug������ǰԤ��ķ����Ч���ᱻ����Ϊ�գ�������ɺ��ٱ���һ�Σ�֮ǰ�汾û��������⣩
	GetTreeCtrl().ModifyStyle(NULL, TVS_HASBUTTONS | TVS_HASLINES | TVS_SHOWSELALWAYS /* | TVS_TRACKSELECT*/ | TVS_DISABLEDRAGDROP);
	//GetTreeCtrl().ModifyStyleEx(NULL,/* TVS_EX_DOUBLEBUFFER | */TVS_EX_AUTOHSCROLL | TVS_EX_FADEINOUTEXPANDOS);

	// �������ڵ�ͼ��
	m_bitmap.LoadBitmap(IDB_GRAPH_TREE_ICONS);
	
	m_normal_image_list.Create(16, 16, ILC_COLOR24 | ILC_MASK, 16, 1);
	m_normal_image_list.Add(&m_bitmap, RGB(255, 255, 255));
	
	m_bitmap.DeleteObject();

	GetTreeCtrl().SetImageList(&m_normal_image_list, TVSIL_NORMAL);

	// ���ڴ���ʱ�ֹ�������ʼ״̬������
	app_ui_interface* app = get_app_ui_interface();
	if (app)
	{
		theme_style_settings app_theme = app->get_style_and_settings();
		app_theme_changed(app_theme);
	}
	
	m_last_option_node_handle = nullptr;

	return TRUE;
}

void road_bed_graph_tree_view::OnClose()
{
	clear_tree_nodes();
}

BOOL road_bed_graph_tree_view::OnEraseBkgnd(CDC* dc)
{
	return CXTPTreeView::OnEraseBkgnd(dc);
}

void road_bed_graph_tree_view::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	m_last_option_node_handle = nullptr;

	CXTPTreeView::OnLButtonDblClk(nFlags, point);

	CTreeCtrl& tree = GetTreeCtrl();
	if (!tree.GetSafeHwnd()) return;

	HTREEITEM clicked_item_handle = get_tree_node_under_cursor();
	if (!clicked_item_handle) return; // û�����κ�һ���ڵ����һ���ֱ�ӷ���

	// �ѽ����ԭ���ĵط��Ƶ���ǰ���������Ӧ����Ŀ��
	tree.Select(clicked_item_handle, TVGN_CARET);
	m_last_option_node_handle = clicked_item_handle;

	project_tree_node_data* tree_node_data = (project_tree_node_data*) tree.GetItemData(clicked_item_handle);
	if (!tree_node_data) return;
	if (project_tree_node_type::graph != tree_node_data->m_node_type) return; // ֻ��ͼֽ˫������Ч

	// �������������������༭ʱ�Լ����������������ҽڵ�������Ϊ�Ժ���ܱ����ı���������ʾ���ı�����������Ҫ�����ݽڵ�����һ��
	data_node_base* node_data = data_center::get_data_node(tree_node_data->m_data_node_tag);
	active_graph_editor(node_data ? node_data->get_node_name() : _T(""), *tree_node_data);
}

void road_bed_graph_tree_view::OnLButtonDown(UINT nFlags, CPoint point)
{
	CXTPTreeView::OnLButtonDown(nFlags, point);
}

void road_bed_graph_tree_view::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_last_option_node_handle = nullptr;

	// mfc��CTreeCtrl�Ҽ���Ӧ��bug��˫���Ҽ�������Ӧ���Ҽ��˵������ڴ˴���Ӧ���ķ���OnRButtonDown����Ӧ
	// [WYZ]ע�����������Ƶ�Notify��Ϣ����ȷ��Ӧ���Ҽ���Ϣ��������Ϣ�����˫����Ҳ�������ַ�ʽ��ʾ�����£�
	// ON_NOTIFY(NM_RCLICK, TREE_CTRL_ID, on_tree_node_right_click)
	CXTPTreeView::OnRButtonDown(nFlags, point);

	CTreeCtrl& tree = GetTreeCtrl();
	if (!tree.GetSafeHwnd()) return;

	HTREEITEM root_item_handle = tree.GetRootItem(); // ����Ϊ��
	HTREEITEM clicked_item_handle = get_tree_node_under_cursor();
	if (!clicked_item_handle) return; // û�����κ�һ���ڵ����һ���ֱ�ӷ���
	
	// �ѽ����ԭ���ĵط��Ƶ���ǰ���������Ӧ����Ŀ��
	tree.Select(clicked_item_handle, TVGN_CARET);
	m_last_option_node_handle = clicked_item_handle;

	if (root_item_handle == clicked_item_handle)
	{
		popup_menu(_T("project"));
		return;
	}

	data_node_base* node_base = get_data_node_by_tree_item(clicked_item_handle);
	road_bed_graph_folder_node* fd = dynamic_cast<road_bed_graph_folder_node*>(node_base);
	if (fd)
	{
		popup_menu(_T("directory"));
		return;
	}

	road_bed_graph_data_base* gd = dynamic_cast<road_bed_graph_data_base*>(node_base);
	if (gd)
	{
		popup_menu(_T("graph"));
		return;
	}
}

void road_bed_graph_tree_view::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_last_option_node_handle = nullptr;

	// mfc��CTreeCtrl�Ҽ���Ӧ��bug��˫���Ҽ�������ӦOnRButtonUp������������ӦOnRButtonDown��������
	// �Ҽ��ſ�����ӦOnRButtonDown������Ҽ��˵��ķ���OnRButtonDown����Ӧ
	// [WYZ]ע�����������Ƶ�Notify��Ϣ����ȷ��Ӧ���Ҽ���Ϣ��������Ϣ�����˫����Ҳ�������ַ�ʽ��ʾ�����£�
	// ON_NOTIFY(NM_RCLICK, TREE_CTRL_ID, on_tree_node_right_click)
	CXTPTreeView::OnLButtonUp(nFlags, point);
}

void road_bed_graph_tree_view::on_tree_node_expanded(NMHDR* nm, LRESULT* lparam)
{
}

void road_bed_graph_tree_view::on_command_all_popup_menu(UINT id)
{
	on_transform_popup_menu_command(id);
}

void road_bed_graph_tree_view::on_menu_project_item_add_graph()
{
	road_bed_dialog_create_graph_object dlg;

	// ���е�ͼֽ����ֻ��ֱ���ӽڵ㣬��Ϊ��ͬ��Ŀ¼���ǿ�����ͬ����ͼֽ
	data_node_base* rt = data_center::get_data_root();
	if (rt)
	{
		for (size_t i = 0; i < rt->get_children_count(); ++i)
		{
			data_node_base* cur_dn = rt->get_child(i);
			if (cur_dn) dlg.m_exist_graph_names.push_back(cur_dn->get_node_name());
		}
	}
	
	if (IDOK != dlg.DoModal()) return;
	
	// ���ý������ݸ��£�ֱ���޸����Բ��ᴥ��֪ͨ����Ϊ��û�йҽӵ�����������
	road_bed_graph_register_info info;
	if (false == road_bed_project_data::get_graph_register_info(dlg.m_result_type_name, info)) return;

	road_bed_graph_data_base* new_node = create_graph_data_base(info.m_data_class_name);
	if (!new_node) return;

	new_node->set_node_name(dlg.m_result_graph_name);
	new_node->m_graph_type_name = dlg.m_result_type_name;	
	rt->add_child_node(new_node);
}

void road_bed_graph_tree_view::on_menu_project_item_add_directory()
{
	data_node_base* rt = data_center::get_data_root();
	if (!rt) return;

	road_bed_dialog_create_folder dlg;

	// ���е�Ŀ¼����ֻ��ֱ���ӽڵ㣬��Ϊ��ͬ��Ŀ¼���ǿ�����ͬ����Ŀ¼
	for (size_t i = 0; i < rt->get_children_count(); ++i)
	{
		data_node_base* cur_dn = rt->get_child(i);
		if (cur_dn) dlg.m_exist_names.push_back(cur_dn->get_node_name());
	}
	
	if (IDOK != dlg.DoModal()) return;

	road_bed_graph_folder_node* fn = new road_bed_graph_folder_node(dlg.m_result_name);
	rt->add_child_node(fn);
}

void road_bed_graph_tree_view::on_menu_project_item_draw_all_graphs()
{
	AfxMessageBox(_T("��δʵ��"), MB_OK | MB_ICONINFORMATION);


	//data_node_base* rt = data_center::get_data_root();
	//if (!rt) return; // ���ڵ㲻��ͼֽĿ¼������ɾ��

	//data_node_base* rt_2 = rt->get_child(0);
	//if (rt_2)
	//{
	//	graph_data_base* gb = new graph_data_base();
	//	//rt_2->add_child_node(gb);
	//}
}

void road_bed_graph_tree_view::on_menu_project_item_clear_all()
{
	data_node_base* rt = data_center::get_data_root();
	if (!rt)  return;
	if (IDYES == AfxMessageBox(_T("ȷ�������Ŀ��"), MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2))
		rt->delete_all_children();
}

void road_bed_graph_tree_view::on_menu_directory_item_add_graph()
{
	road_bed_dialog_create_graph_object dlg;

	// ���е�ͼֽ����ֻ��ֱ���ӽڵ㣬��Ϊ��ͬ��Ŀ¼���ǿ�����ͬ����ͼֽ
	data_node_base* rt = get_data_node_by_tree_item(m_last_option_node_handle);
	if (rt)
	{
		for (size_t i = 0; i < rt->get_children_count(); ++i)
		{
			data_node_base* cur_dn = rt->get_child(i);
			if (cur_dn) dlg.m_exist_graph_names.push_back(cur_dn->get_node_name());
		}
	}

	if (IDOK != dlg.DoModal()) return;

	// ���ý������ݸ��£�ֱ�����Բ��ᴥ��֪ͨ����Ϊ��û�йҽӵ���������
	road_bed_graph_register_info info;
	if (false == road_bed_project_data::get_graph_register_info(dlg.m_result_type_name, info)) return;

	road_bed_graph_data_base* new_node = create_graph_data_base(info.m_data_class_name);
	if (!new_node) return;

	new_node->set_node_name(dlg.m_result_graph_name);
	new_node->m_graph_type_name = dlg.m_result_type_name;
	rt->add_child_node(new_node);
}

void road_bed_graph_tree_view::on_menu_directory_item_draw_all_graphs()
{
	AfxMessageBox(_T("��δʵ��"), MB_OK | MB_ICONINFORMATION);
}

void road_bed_graph_tree_view::on_menu_directory_item_clear_all()
{
	data_node_base* dt = get_data_node_by_tree_item(m_last_option_node_handle);
	if (!dt) return;

	if (IDYES == AfxMessageBox(_T("ȷ������ļ��У�"), MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2))
		dt->delete_all_children();
}

void road_bed_graph_tree_view::on_menu_directory_item_add_directory()
{
	road_bed_dialog_create_folder dlg;

	// ���е�Ŀ¼����ֻ��ֱ���ӽڵ㣬��Ϊ��ͬ��Ŀ¼���ǿ�����ͬ����Ŀ¼��
	data_node_base* data_node = get_data_node_by_tree_item(m_last_option_node_handle);
	if (!data_node) return;

	for (size_t i = 0; i < data_node->get_children_count(); ++i)
	{
		data_node_base* cur_dn = data_node->get_child(i);
		if (cur_dn) dlg.m_exist_names.push_back(cur_dn->get_node_name());
	}

	if (IDOK != dlg.DoModal()) return;

	road_bed_graph_folder_node* fn = new road_bed_graph_folder_node(dlg.m_result_name);
	data_node->add_child_node(fn);
}

void road_bed_graph_tree_view::on_menu_directory_item_delete()
{
	data_node_base* dt = get_data_node_by_tree_item(m_last_option_node_handle);
	if (!dt || dt == data_center::get_data_root()) return; // ���ڵ㣬����ɾ��

	if (IDYES == AfxMessageBox(_T("ȷ��ɾ���ļ��У�"), MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2))
		dt->delete_only_self_data_node();
}

void road_bed_graph_tree_view::on_menu_directory_item_rename()
{
	// ���е�Ŀ¼����ֻ��ֱ���ӽڵ㣬��Ϊ��ͬ��Ŀ¼���ǿ�����ͬ����Ŀ¼��
	data_node_base* data_node = get_data_node_by_tree_item(m_last_option_node_handle);
	if (!data_node) return;

	road_bed_dialog_rename dlg;
	dlg.m_result_name = data_node->get_node_name();

	data_node_base* parent_node = data_node->get_parent();
	if (parent_node)
	{
		for (size_t i = 0; i < parent_node->get_children_count(); ++i)
		{
			data_node_base* cur_dn = parent_node->get_child(i);
			if (cur_dn) dlg.m_exist_names.push_back(cur_dn->get_node_name());
		}
	}

	if (IDOK != dlg.DoModal()) return;

	data_node->set_node_name(dlg.m_result_name);
}

void road_bed_graph_tree_view::on_menu_graph_item_draw_one_graph()
{
	road_bed_graph_data_base* data_node = dynamic_cast<road_bed_graph_data_base*>(get_data_node_by_tree_item(m_last_option_node_handle));
	if (!data_node)
	{
		CString err_info = _T("ͼֽ�����޷���������ͼʧ��");
		AfxMessageBox(err_info, MB_OK | MB_ICONERROR);
		return;
	}

	road_bed_graph_register_info info;
	if (false == data_node->get_graph_reg_info(info))
	{
		CString err_info = _T("ͼֽ����ע����Ϣ������Ч����ͼʧ��");
		AfxMessageBox(err_info, MB_OK | MB_ICONERROR);
		return;
	}

	CString strategy_class_name = info.m_drawing_strategy_class_name;
	strategy_class_name.Trim();
	if (strategy_class_name.IsEmpty())
	{
		CString err_info = _T("ͼֽ���Ʋ����� [ ") + strategy_class_name + (" ] ��Ч����ͼʧ��");
		AfxMessageBox(err_info, MB_OK | MB_ICONERROR);
		return;
	}

	CObject* tmp_obj = CRuntimeClass::CreateObject(strategy_class_name);
	if (!tmp_obj)
	{
		CString err_info = _T("ͼֽ���Ʋ����� [ ") + strategy_class_name + _T(" ] �޷�ʵ��������ͼʧ��");
		AfxMessageBox(err_info, MB_OK | MB_ICONERROR);
		return;
	}

	std::unique_ptr<road_bed_graph_drawing_strategy_base> drawing_tool(dynamic_cast<road_bed_graph_drawing_strategy_base*>(tmp_obj));
	if (!drawing_tool)
	{
		safe_delete(tmp_obj);
		CString err_info = _T("ͼֽ���Ʋ����� [ ") + strategy_class_name + _T(" ] �޷�ʵ��������ͼʧ��");
		AfxMessageBox(err_info, MB_OK | MB_ICONERROR);
		return;
	}

	drawing_tool->m_graph_data_tag = data_node->get_node_tag();

	CString graph_name = data_node->m_graph_type_name + _T("-") + data_node->get_node_name();
	bool flag = drawing_tool->draw(graph_name);
	if (!flag)
	{
		CString err_info = _T("ͼֽ [ ") + graph_name + _T(" ] ����ʧ��");
		AfxMessageBox(err_info, MB_OK | MB_ICONERROR);
		// return; ��Ҫ���أ�ʧ��Ҳ���£���Ӧ��ͼֽ����Ҫ��Ϊûͼֽ����Ȼ��ʾ��ǰͼֽ���൱��Ҫ��ˢһ��
	}

	data_node->notify_if_enable(notifer_action::post_updated_node); // ͼֽ���Ʊ��ˣ�ͼֽҲ����
}

void road_bed_graph_tree_view::on_menu_graph_item_delete_one_graph()
{
	data_node_base* dt = get_data_node_by_tree_item(m_last_option_node_handle);
	if (!dt || dt == data_center::get_data_root()) return; // ���ڵ㣬����ɾ��

	if (IDYES == AfxMessageBox(_T("ȷ��ɾ��ͼֽ��"), MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2))
		dt->delete_only_self_data_node();
}

void road_bed_graph_tree_view::on_menu_graph_item_rename()
{
	// ���е�Ŀ¼����ֻ��ֱ���ӽڵ㣬��Ϊ��ͬ��Ŀ¼���ǿ�����ͬ����Ŀ¼��
	data_node_base* data_node = get_data_node_by_tree_item(m_last_option_node_handle);
	if (!data_node) return;

	road_bed_dialog_rename dlg;
	dlg.m_result_name = data_node->get_node_name();

	data_node_base* parent_node = data_node->get_parent();
	if (parent_node)
	{
		for (size_t i = 0; i < parent_node->get_children_count(); ++i)
		{
			data_node_base* cur_dn = parent_node->get_child(i);
			if (cur_dn) dlg.m_exist_names.push_back(cur_dn->get_node_name());
		}
	}

	if (IDOK != dlg.DoModal()) return;

	data_node->set_node_name(dlg.m_result_name);
}

void road_bed_graph_tree_view::on_menu_graph_open_output_template()
{
	AfxMessageBox(_T("��δʵ��"), MB_OK | MB_ICONINFORMATION);
}

void road_bed_graph_tree_view::on_menu_graph_open_import_template()
{
	AfxMessageBox(_T("��δʵ��"), MB_OK | MB_ICONINFORMATION);
}

void road_bed_graph_tree_view::on_menu_graph_open_dxf_file()
{
	::ShellExecute(nullptr, _T("open"), _T("E:\\��һ��.pdf"), nullptr, nullptr, SW_SHOW);
}

void road_bed_graph_tree_view::on_menu_graph_open_dwg_file()
{
	::ShellExecute(nullptr, _T("open"), _T("E:\\��һ��.pdf"), nullptr, nullptr, SW_SHOW);
}

void road_bed_graph_tree_view::on_menu_graph_open_pdf_file()
{
	::ShellExecute(nullptr, _T("open"), _T("E:\\��һ��.pdf"), nullptr, nullptr, SW_SHOW);
}

