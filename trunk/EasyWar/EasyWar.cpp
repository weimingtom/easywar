// EasyWar.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "AdvancedFrame.h"

#include "Demo01.h"
#include "Demo02.h"

AdvancedFrame g_game;

int _tmain(int argc, _TCHAR* argv[])
{
	//全屏
	bool fullScreen = argc > 1 ? true : false;

	g_game.Initial( 640, 480, "EasyWar", "Tank.bmp", fullScreen );
//	g_game.SetFPS( 60 );

	//////Demo
	g_game.AddLogic( "Demo01", CREATE_LOGIC( Demo01 ) );

	g_game.Running();
	g_game.Destroy();

	return 0;
}
