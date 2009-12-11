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

	m_guiContainer.add( &m_imgButton );
	m_guiContainer.setPosition( 0, 0 );
	m_guiContainer.setSize( 640, 480 );
	m_guiContainer.setOpaque( false );

	//放置带图片的按钮
	m_butImg = new gcn::SDLImage( NULL, true );
	m_butImg->setImageLoader( &m_sdlImgLoader );
	gcn::Image* tmp;
	tmp = m_butImg->load("button.png");
	delete m_butImg;
	m_butImg = (gcn::SDLImage*)tmp;
	m_imgButton.setFrameSize( 0 );
	m_imgButton.setImage( m_butImg );
	m_imgButton.setSize( 59, 59 );
	m_imgButton.setPosition( 10, 10 );

	//按钮事件绑定，设置侦听器
	m_evtListener = new mouseEvt;
	((mouseEvt*)m_evtListener)->SetEntity( this );
	m_imgButton.setId( "bt1" );
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
	delete m_evtListener;

	m_bg.Leave();
	for( int i(0); i < 4; i++ )
	{
		m_tank[i].Leave();
	}

}
