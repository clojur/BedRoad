#pragma once

#ifdef ROAD_BED_UI_MANAGER_DLL
#	define ROAD_BED_UI_MANAGER_API __declspec(dllexport)
#else
#	define ROAD_BED_UI_MANAGER_API __declspec(dllimport)
#	ifdef _DEBUG
#		pragma comment(lib,"road_bed_ui_manager_d.lib")
#		pragma message("auto linking to road_bed_ui_manager_d.lib")
#	else
#		pragma comment(lib,"road_bed_ui_manager.lib")
#		pragma message("auto linking to road_bed_ui_manager.lib")
#	endif
#endif
