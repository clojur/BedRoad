#pragma once

#ifdef ROAD_BED_PROJECT_MANAGER_DLL
#	define ROAD_BED_PROJECT_MANAGER_API __declspec(dllexport)
#else
#	define ROAD_BED_PROJECT_MANAGER_API __declspec(dllimport)
#	ifdef _DEBUG
#		pragma comment(lib,"road_bed_project_manager_d.lib")
#		pragma message("auto linking to road_bed_project_manager_d.lib")
#	else
#		pragma comment(lib,"road_bed_project_manager.lib")
#		pragma message("auto linking to road_bed_project_manager.lib")
#	endif
#endif
