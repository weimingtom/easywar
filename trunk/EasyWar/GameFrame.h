//游戏框架类
#pragma once

#include <map>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include "Graph.h"
#include "Input.h"
#include "Sound.h"

using namespace std;

//鼠标框位置等信息记录结构
struct mouserectinfo
{
	int _x1;
	int _y1;
	int _x2;
	int _y2;

	bool _show;

	mouserectinfo():_show( false ){}
};

class Logic;

class  GameFrame
{
public:
	GameFrame();
	~GameFrame();

	void Initial( int wid, int hei, char* wndName= "Demo", char* icon= NULL, bool fullscreen= false );
													//初始化
	void Running();									//运行中
	void Destroy();									//结束
	void Exit();									//使游戏退出

	bool AddLogic( string logicName, Logic* task );	//添加一个Logic
	Logic* GetLogic( string logicName );			//通过名字来获取某个Logic的指针
	void EnableMouseRect( int r, int g, int b, int a );
													//显示鼠标框
	void DisableMouseRect();						//关闭鼠标框的显示
	void SetFPS( float fps );						//设定帧数
	void AutoClear( bool flag );					//每帧是否自动清屏
	int Rand();										//返回一个随机数

protected:
	map<string,Logic*> m_allLogic;					//存储所有的Logic
	bool m_alive;									//游戏是否在进行

	Color m_rectColor;								//鼠标框的颜色
	bool m_mouseRect;								//是否需要画鼠标框
	mouserectinfo m_rectInfo;						//框的信息（包括画与否）

	unsigned int m_timePerFrame;					//每帧的耗时（毫秒）
	unsigned int m_time;							//游戏应该进行的时间（毫秒）
	bool m_autoClear;								//清屏标志

protected:
	void updateMouseRect();							//更新鼠标框

	//调试用代码
#ifdef _DEBUG

#define COUNT_TIME_INTERVAL		5000				//统计一次FPS的间隔时间
	int md_frames;
	unsigned int md_lastTime;

#endif

};


//指针转换的宏
#define GAME_FRAME( x )	((GameFrame*)x)
