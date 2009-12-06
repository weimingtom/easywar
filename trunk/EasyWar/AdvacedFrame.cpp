#include "stdafx.h"
#include "AdvancedFrame.h"

AdvancedFrame::AdvancedFrame()
{
	m_adv2d = NULL;
}

AdvancedFrame::~AdvancedFrame()
{
}

//初始化
void AdvancedFrame::Initial( int wid, int hei, char* wndName, char* icon, bool fullscreen )
{
	GameFrame::Initial( wid, hei, wndName, icon, fullscreen );

	//添加高级2D渲染模块的Logic
	m_adv2d = CREATE_LOGIC( Advanced2D );
	AddLogic( "AdvancedGraph", m_adv2d );

}

//结束
void AdvancedFrame::Destroy()
{
	GameFrame::Destroy();

	m_adv2d = NULL;
}
