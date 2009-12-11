#include "stdafx.h"
#include "Demo01.h"


#define ANI_SPEED	50


void Demo01::Init( void* host )
{
	m_host = host;

	//坦克的初始位置和方向
	m_x = 120;
	m_y = 0;
	m_dir = m_nextDir= eDirRight;

	//创建坦克各个方向的动画
	m_tank[eDirUp].CreateAniAuto( "TankUp.png", 7, 1, 7 );
	m_tank[eDirUp].SetFrameTime( ANI_SPEED );
	m_tank[eDirDown].CreateAniAuto( "TankDown.png", 7, 1, 7 );
	m_tank[eDirDown].SetFrameTime( ANI_SPEED );
	m_tank[eDirLeft].CreateAniAuto( "TankLeft.png", 1, 7, 7 );
	m_tank[eDirLeft].SetFrameTime( ANI_SPEED );
	m_tank[eDirRight].CreateAniAuto( "TankRight.png", 1, 7, 7 );
	m_tank[eDirRight].SetFrameTime( ANI_SPEED );

	m_bg.CreateAniAuto( "bg.png", 1, 1, 1 );

	//将动画添加到Advance2D
	ADVANCE_FRAME( host )->ADRAW()->AddUnit( &m_bg, eLevelBottom );
	ADVANCE_FRAME( host )->ADRAW()->AddUnit( &m_tank[eDirUp], eLevelMid );
	ADVANCE_FRAME( host )->ADRAW()->AddUnit( &m_tank[eDirDown], eLevelMid );
	ADVANCE_FRAME( host )->ADRAW()->AddUnit( &m_tank[eDirLeft], eLevelMid );
	ADVANCE_FRAME( host )->ADRAW()->AddUnit( &m_tank[eDirRight], eLevelMid );

	//转向声
	m_sndId = SND.LoadSE( "turn.wav" );

	m_bg.SetPos( 0, 0 );
	m_bg.Play( 0 );
	m_tank[m_dir].SetPos( m_x, m_y );
	m_tank[m_dir].Play( 0 );

	//GUI初始化
	m_guiGraph.setTarget( DRAW._GetSurface() );

	m_gui.setGraphics( &m_guiGraph );
	m_gui.setInput( &m_guiInput );
	m_gui.setTop( &m_guiContainer );

	m_guiContainer.add( &m_button );
	m_guiContainer.add( &m_wnd );
	m_guiContainer.add( &m_icon );
	m_guiContainer.setPosition( 0, 0 );
	m_guiContainer.setSize( 640, 480 );
	m_guiContainer.setOpaque( false );

	m_wnd.add( &m_imgButton );
	m_wnd.add( &m_check );

	//放置按钮
	gcn::Color theColor1( 200, 0, 0, 200 );
	gcn::Color theColor2( 0, 200, 0, 200 );
	gcn::Color theColor3( 0, 0, 200, 200 );
	m_button.setSize( 60, 20 );
	m_button.setPosition( 300, 20 );
	m_button.setFrameSize( 0 );
	m_button.setBaseColor( theColor1 );
	m_button.setBackgroundColor( theColor2 );
	m_button.setForegroundColor( theColor3 );
	m_button.setSelectionColor( theColor3 );
	//放置带图片的按钮
	m_butImg = new gcn::SDLImage( NULL, true );
	m_butImg->setImageLoader( &m_sdlImgLoader );
	gcn::Image* tmp;
	tmp = m_butImg->load("boost1.png");
	delete m_butImg;
	m_butImg = (gcn::SDLImage*)tmp;
	m_imgButton.setFrameSize( 0 );
	m_imgButton.setImage( m_butImg );
	m_imgButton.setSize( 32, 32 );
	m_imgButton.setPosition( 50, 30 );
	//放置图标
	m_iconImg = new gcn::SDLImage( NULL, true );
	m_iconImg->setImageLoader( &m_sdlImgLoader );
	tmp = m_iconImg->load("boost2.png");
	delete m_iconImg;
	m_iconImg = (gcn::SDLImage*)tmp;
	m_icon.setImage( m_iconImg );
	m_icon.setSize( 100, 100 );
	m_icon.setPosition( 0, 0 );
	m_iconVisable = true;
	//放置窗口
	m_wnd.setSize( 120, 90 );
	m_wnd.setPosition( 250, 70 );
	m_wnd.setBaseColor( theColor2 );
	//放置CheckBox
	m_check.setSize( 20, 20 );
	m_check.setPosition( 5, 5 );

	//按钮事件绑定，设置侦听器
	m_evtListener = new mouseEvt;
	((mouseEvt*)m_evtListener)->SetEntity( this );
	m_button.setId( "bt1" );
	m_button.addMouseListener( m_evtListener );
	m_imgButton.setId( "bt2" );
	m_imgButton.addMouseListener( m_evtListener );
	
}

void Demo01::Run( void* host, unsigned int time  )
{
	if( Input::KeyDown( UP ) )
	{
		m_y--;
		m_nextDir = eDirUp;
	}else if( Input::KeyDown( DOWN ) )
	{
		m_y++;
		m_nextDir = eDirDown;
	}else if( Input::KeyDown( LEFT ) )
	{
		m_x--;
		m_nextDir = eDirLeft;
	}else if( Input::KeyDown( RIGHT ) )
	{
		m_x++;
		m_nextDir = eDirRight;
	}

	//坦克方向改变，更换动画
	if( m_dir != m_nextDir )
	{
		m_dir = m_nextDir;
	//	SND.PlaySE( m_sndId );

		for( int i(0); i< 4; i++ )
		{
			if( i == m_dir )
			{
				m_tank[i].Play( 0 );
			}else
			{
				m_tank[i].Stop();
			}
		}
	}

	//动画位置改变
	m_tank[m_dir].SetPos( m_x, m_y );

	//GUI更新
	m_guiInput.pushInput( *Input::_GetEvtStruct() );
	m_gui.logic();
	m_gui.draw();

}

void Demo01::Sleep( void* host )
{
	m_bg.Stop();
	for( int i(0); i < 4; i++ )
	{
		m_tank[i].Stop();
	}
}

void Demo01::End( void* host )
{
	delete m_butImg;
	delete m_iconImg;
	delete m_evtListener;

	m_bg.Leave();
	for( int i(0); i < 4; i++ )
	{
		m_tank[i].Leave();
	}

}
