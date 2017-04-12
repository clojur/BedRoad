// dllmain.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxwin.h>
#include <afxdllx.h>
#include "commands/road_bed_project_commands.h"
#include "x_framework/macro.h"
#include "x_framework/interface/cmd_container_interface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE demo_ui_manager_dll = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("demo_ui_manager_dll.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(demo_ui_manager_dll, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(demo_ui_manager_dll);

		register_cmd_container_by_class_name(demo_project_commands);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("demo_ui_manager_dll.DLL Terminating!\n");

		cmd_trigger_manager::remove_all_command();

		// Terminate the library before destructors are called
		AfxTermExtensionModule(demo_ui_manager_dll);
	}
	return 1;   // ok
}
