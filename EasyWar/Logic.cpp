#include "stdafx.h"
#include "Logic.h"

Logic::Logic()
{
	m_LogicState = eLogicInit;
}

Logic::~Logic()
{
}

//Logic运作
void Logic::Update( unsigned int time )
{
	switch( m_LogicState )
	{
	case eLogicInit:	//初始化一次
		Init( m_host );
		m_LogicState = eLogicRun;
		break;
	case eLogicRun:		//运行态
		Run( m_host, time );
		break;
	case eLogicEnd:		//结束一次
		End( m_host );
		m_LogicState = eLogicDead;
		break;
	case eLogicPause:	//暂停态
		Sleep( m_host );
		m_LogicState = eLogicSleep;
		break;
	case eLogicSleep:	//睡眠（暂停态执行一次后）
	case eLogicDead:	//死亡态
	default:
		break;
	}
}

//判断Logic是否死亡
bool Logic::Dead()
{
	if( m_LogicState == eLogicDead )
	{
		return true;
	}

	return false;
}

//暂停Logic
void Logic::Pause()
{
	if( m_LogicState == eLogicDead )	//若本Logic死亡就不必暂停了，以免妨碍宿主清除本Logic
	{
		return;
	}

	m_LastState = m_LogicState;
	m_LogicState = eLogicPause;
}

//恢复Logic的运行
void Logic::Resume()
{
	m_LogicState = m_LastState;
	Awake( m_host );
}

//退出Logic
void Logic::Exit()
{
	m_LogicState = eLogicEnd;
}

//设置Logic的宿主
void Logic::SetHost( void* host )
{
	m_host = host;
}

//发送消息，将消息存储到Logic消息队列中
void Logic::SendMessage( int ID, void* data )
{
	sLogicMsg message;
	
	message.ID = ID;
	message.data = data;

	m_msg.push( message );
}

//获取消息
bool Logic::GetMessage( sLogicMsg* msg )
{
	if( m_msg.empty() )
	{
		return false;
	}

	msg->ID = m_msg.back().ID;			//获取消息队列里最后一条消息
	msg->data = m_msg.back().data;
	m_msg.pop();

	return true;
}

//被暂停时被调用一次
void Logic::Sleep( void* host )
{
}

//醒来时被调用一次
void Logic::Awake( void* host )
{
}
