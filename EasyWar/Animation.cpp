#include "stdafx.h"
#include "Animation.h"
#include "Graph.h"


Animation::Animation()
{
	m_frameCount= 0;
	m_currFrame= 0;
	m_groupNum= -1;
	m_loop= 0;
	m_frameInterval= 0;
	m_timer= 0;
	m_state= eAniStop;
}

Animation::~Animation()
{
}

//更新函数
void Animation::Update( unsigned int time )
{
	if( m_state == eAniPlaying )
	{
		DRAW.Draw( m_groupNum, m_currFrame, m_pos._x, m_pos._y );

		//时间到达该换帧的时间
		if( m_timer >= m_frameInterval )
		{
			m_timer= 0;
			m_currFrame++;
			if( m_currFrame >= m_frameCount )			//一次动画播放完
			{
				m_currFrame= 0;
				m_loop--;
				if( m_loop == 0 )						//动画完毕（播放次数结束）
				{
					m_state= eAniStop;
				}else if( m_loop < 0 )					//无限循环播放的动画
				{
					m_loop= 0;
				}
			}
		}
		m_timer+= time;
	}else if( m_state == eAniPause )
	{
		DRAW.Draw( m_groupNum, m_currFrame, m_pos._x, m_pos._y );
	}

}

//设置动画总帧数
void Animation::SetFrameCount( int count )
{
	//创建图像组，返回组号
	m_groupNum=	DRAW.AddSpriteGroup( count );
	//总帧数
	m_frameCount= count;

}

//设置某一帧的图像
void Animation::SetFrame( int index, char* fileName, Rect& clip )
{
	if( index < 0 || index >= m_frameCount || m_groupNum < 0 )
	{
		return;
	}

	DRAW.AddSprite( m_groupNum, index, fileName );
	DRAW.GetSprite( m_groupNum, index ).Clip( clip );

}

//播放（0为无限循环播放）
void Animation::Play( int loop )
{
	m_currFrame= 0;
	m_loop= loop;
	m_state= eAniPlaying;
	m_timer= 0;
}

//停止播放
void Animation::Stop()
{
	m_state= eAniStop;
}

//设置每帧的间隔时间
void Animation::SetFrameTime( unsigned int interval )
{
	m_frameInterval= interval;
}

//根据特定图片及格式自动创建一个动画序列，最后个参数为实际帧数，而不是网格数量作为帧数
void Animation::CreateAniAuto( char* fileName, int wid, int hei, int count )
{
	SetFrameCount( count );

	int cnts= 0;
	float u1, v1, u2, v2;
	float uW= 1.0f / (float)wid;
	float vH= 1.0f / (float)hei;

	for( int i(0); i< hei; i++ )
	{
		for( int j(0); j< wid; j++ )
		{
			DRAW.AddSprite( m_groupNum, cnts, fileName );
			u1= j * uW;
			v1= i * vH;
			u2= u1 + uW;
			v2= v1 + vH;
			DRAW.GetSprite( m_groupNum, cnts ).Clip( u1, v1, u2, v2 );

			cnts++;
			if( cnts >= count )
			{
				return;
			}
		}
	}

}

//产生目标的副本
void Animation::Duplicate( Animation& orgAni )
{
	m_groupNum= orgAni.m_groupNum;
	m_frameCount= orgAni.m_frameCount;
	m_frameInterval= orgAni.m_frameInterval;

}

//暂停播放（有显示）
void Animation::Pause( int frame )
{
	m_state= eAniPause;
	m_currFrame= frame;

}
