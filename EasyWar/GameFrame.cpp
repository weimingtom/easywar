#include "stdafx.h"
#include "GameFrame.h"
#include "Logic.h"

GameFrame::GameFrame()
{
	m_alive = true;
	m_mouseRect= false;
	m_timePerFrame= 0;
	m_autoClear= false;
}

GameFrame::~GameFrame()
{
}

//初始化
void GameFrame::Initial( int wid, int hei, char* wndName, char* icon, bool fullscreen )
{
	//初始化SDL库
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER );
	//设置窗口图标
	SDL_WM_SetIcon(SDL_LoadBMP( icon ), NULL);
	//创建窗口
	DRAW.CreateWnd( wid, hei, fullscreen );
	//设置窗口Caption
	SDL_WM_SetCaption( wndName, NULL );
	//时间初始化
	m_time= SDL_GetTicks();
	//声音系统初始化
	SND.InitDevice();
	//随机数生成器初始化
	srand( (unsigned int)time(0) );

#ifdef _DEBUG
	md_frames= 0;
	md_lastTime= 0;
#endif

}

//主要的调度部分
void GameFrame::Running()
{
	while( m_alive )
	{
		//控制帧数用
		unsigned int nowTime= SDL_GetTicks();			//得到程序运行到当前所经历的毫秒数
		unsigned int ticks= nowTime - m_time;			//

		if( ticks < m_timePerFrame )
		{
			SDL_Delay( 0 );
			continue;
		}
		m_time+= m_timePerFrame;

		//控制信息需要每帧更新
		Input::Update();

		//程序退出
		if( Input::Quit() || Input::KeyDown(ESC) )		//游戏退出（窗口被关闭）
		{
			break;
		}

		map<string,Logic*>::iterator logic;
		vector<map<string,Logic*>::iterator> corpse;	//用于存储死亡的Logic的迭代器

		if( m_autoClear )
		{
			DRAW.ClearWnd( 0, 0, 0 );
		}

		//遍历并运作Logic
		for( logic = m_allLogic.begin() ; logic != m_allLogic.end() ; logic++ )
		{
			logic->second->Update( ticks );
			if( logic->second->Dead() )					//如果该Logic死亡，则删除该Logic
			{
				delete logic->second;
				corpse.push_back( logic );
			}
		}

		//清除已死亡的Logic的尸体
		for( unsigned int i(0); i< corpse.size(); i++ )
		{
			m_allLogic.erase( corpse[i] );
		}

		corpse.clear();

		updateMouseRect();								//鼠标框更新

		DRAW.Flush();									//屏幕缓冲的交换由这里统一进行

#ifdef _DEBUG	//【计算帧数并输出到console】
		md_frames++;
		unsigned int countTime= nowTime - md_lastTime;
		if( countTime > COUNT_TIME_INTERVAL )
		{
			md_lastTime= nowTime;
			printf( "FPS: %.2f\n", (float)md_frames / ((float)countTime * 0.001f ) );
			md_frames= 0;
		}
#endif

	}

}

//游戏结束
void GameFrame::Destroy()
{
	//清除所有Logic
	map<string,Logic*>::iterator logic;
	for( logic = m_allLogic.begin() ; logic != m_allLogic.end() ; logic++ )
	{
		delete logic->second;
	}
	m_allLogic.clear();
	//销毁graph
	DRAW.Destory();
	//销毁sound
	SND.Destroy();
	//SDL中止
	SDL_Quit();
}

//添加一个Logic
bool GameFrame::AddLogic( string logicName, Logic* task )
{
	if( task )								//避免空指针的传入
	{
		map<string,Logic*>::iterator logic;

		logic = m_allLogic.find( logicName );

		if( logic == m_allLogic.end() )		//避免Logic名字重复
		{
			task->SetHost( (void*)this );
			m_allLogic[logicName] = task;
			return true;
		}

	}

	return false;
}

//通过名字来获取某个Logic的指针
Logic* GameFrame::GetLogic( string logicName )
{
	map<string,Logic*>::iterator logic;

	logic = m_allLogic.find( logicName );

	if( logic != m_allLogic.end() )
	{
		return m_allLogic[logicName];
	}

	return NULL;

}

//退出游戏
void GameFrame::Exit()
{
	m_alive = false;
}

//显示鼠标框
void GameFrame::EnableMouseRect( int r, int g, int b, int a)
{
	m_rectColor._r= r;
	m_rectColor._g= g;
	m_rectColor._b= b;
	m_rectColor._a= a;

	m_mouseRect= true;

}

//关闭鼠标框的显示
void GameFrame::DisableMouseRect()
{
	m_mouseRect= false;
}

//更新鼠标框
void GameFrame::updateMouseRect()
{
	if( !m_mouseRect )				//鼠标框没有启用
	{
		return;
	}

	if( m_rectInfo._show )
	{
		m_rectInfo._x2= Input::Xpos();
		m_rectInfo._y2= Input::Ypos();
		
		DRAW.DrawRect( m_rectInfo._x1, m_rectInfo._y1, m_rectInfo._x2, m_rectInfo._y2,
						  m_rectColor._r, m_rectColor._g, m_rectColor._b, m_rectColor._a );
	}

	if( Input::LButtonEvent() == eMouseDown )
	{
		m_rectInfo._show= true;
		m_rectInfo._x1= m_rectInfo._x2= Input::Xpos();
		m_rectInfo._y1= m_rectInfo._y2= Input::Ypos();
	}else if( Input::LButtonEvent() == eMouseUp )
	{
		m_rectInfo._show= false;
	}

}

//设定帧数
void GameFrame::SetFPS( float fps )
{
	m_timePerFrame= int( ( 1.0f / fps ) * 1000.0f );
}

//每帧是否自动清屏
void GameFrame::AutoClear( bool flag )
{
	m_autoClear= flag;
}

//返回一个随机数
int GameFrame::Rand()
{
	return rand();
}
