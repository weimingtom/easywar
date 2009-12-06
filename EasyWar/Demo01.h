#pragma once
#include "Logic.h"
#include "AdvancedFrame.h"

//方向
enum{ eDirUp= 0, eDirDown, eDirLeft, eDirRight };


//[Demo01]键盘上下左右控制一个坦克走来走去，附带一些UI的例子
class Demo01 : public Logic
{
	friend class mouseEvt;
public:

	virtual void Init( void* host );					//初始化
	virtual void Run( void* host, unsigned int time  );	//每帧运行
	virtual void End( void* host );						//结束

private:
	Animation m_tank[4];								//坦克动画们
	Animation m_bg;										//背景

	int m_x;											//位置
	int m_y;
	int m_dir;											//方向
	int m_nextDir;										//下次一要转的方向
	int m_sndId;										//声音的ID

	gcn::Gui m_gui;
	gcn::SDLGraphics m_guiGraph;
	gcn::SDLInput m_guiInput;
	gcn::Container m_guiContainer;
	gcn::Button m_button;
	gcn::ImageButton m_imgButton;
	gcn::Icon m_icon;
	gcn::SDLImage* m_butImg;
	gcn::SDLImage* m_iconImg;
	gcn::SDLImageLoader m_sdlImgLoader;
	gcn::Window m_wnd;
	gcn::CheckBox m_check;

	bool m_iconVisable;

	gcn::MouseListener* m_evtListener;

};


//事件侦听器
class mouseEvt: public gcn::MouseListener
{
public:
	virtual void mousePressed( gcn::MouseEvent& mouseEvent )
	{
		string widgetID = mouseEvent.getSource()->getId();

		//判断是哪个按键按下的
		if( widgetID == "bt1" )
		{
			if(	m_entity->m_iconVisable )
			{
				m_entity->m_iconVisable = false;
			}else
			{
				m_entity->m_iconVisable = true;
			}

			m_entity->m_wnd.setVisible( m_entity->m_iconVisable );

		}else if( widgetID == "bt2" )
		{
			m_entity->m_check.setSelected( true );
		}
	}
	
	void SetEntity( Demo01* entity )
	{
		m_entity = entity;
	}

protected:
	Demo01* m_entity;

};
