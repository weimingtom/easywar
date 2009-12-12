// EasyWar.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#ifndef _DEBUG
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif
#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						
#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif
#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#endif

#include "AdvancedFrame.h"

#include "Demo01.h"
#include "Demo02.h"

AdvancedFrame g_game;

#ifdef _DEBUG
int _tmain(int argc, _TCHAR* argv[])
#else
int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
#endif
{

	g_game.Initial( 640, 480, "EasyWar", "Tank.bmp", false );
//	g_game.SetFPS( 60 );

	//////Demo
	g_game.AddLogic( "Demo01", CREATE_LOGIC( Demo01 ) );

	g_game.Running();
	g_game.Destroy();

	return 0;
}
