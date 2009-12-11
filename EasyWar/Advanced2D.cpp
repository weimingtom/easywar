#include "stdafx.h"
#include "Advanced2D.h"

Advanced2D::Advanced2D()
{
}

Advanced2D::~Advanced2D()
{
}

//初始化
void Advanced2D::Init( void* host )
{
	for( int i = eLevelBottom; i < eMaxLevel; i++ )
	{
		m_2dsLevels[i] = new Unit2D();
		m_2dsLevels[i]->SetHead();
		m_listTail[i] = m_2dsLevels[i];
	}
}

//每帧运行（time为上帧到这帧的毫秒数）
void Advanced2D::Run( void* host, unsigned int time )
{
	Unit2D* point;

	for( int i = eLevelBottom; i < eMaxLevel; i++ )
	{
		point = m_2dsLevels[i]->m_next;
		while( point )
		{
			point->Update( time );
			point = point->m_next;
		}
	}
}

//结束
void Advanced2D::End( void* host )
{
	for( int i = eLevelBottom; i < eMaxLevel; i++ )
	{
		delete m_2dsLevels[i];
	}
}

//添加一个渲染对象到指定层的渲染列表
void Advanced2D::AddUnit( Unit2D* obj, int level )
{
	m_listTail[level]->SetNext( obj );
	obj->SetPrior( m_listTail[level] );
	m_listTail[level] = obj;
	m_listTail[level]->SetNext( NULL );

}
