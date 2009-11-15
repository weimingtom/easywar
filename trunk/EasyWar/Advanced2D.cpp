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
}

//每帧运行（time为上帧到这帧的毫秒数）
void Advanced2D::Run( void* host, unsigned int time )
{
	list<Unit2D*>::iterator unitPt;

	//渲染底部层
	for( unitPt= m_2dsBottom.begin(); unitPt != m_2dsBottom.end(); unitPt++ )
	{
		(*unitPt)->Update( time );
	}

	//渲染中层
	for( unitPt= m_2dsMid.begin(); unitPt != m_2dsMid.end(); unitPt++ )
	{
		(*unitPt)->Update( time );
	}

	//渲染Top层
	for( unitPt= m_2dsTop.begin(); unitPt != m_2dsTop.end(); unitPt++ )
	{
		(*unitPt)->Update( time );
	}

}

//结束
void Advanced2D::End( void* host )
{
	m_2dsTop.clear();
	m_2dsMid.clear();
	m_2dsBottom.clear();
}

//添加一个渲染对象到指定层的渲染列表
void Advanced2D::AddUnit( Unit2D* obj, int level )
{
	switch( level )
	{
	case eLevelTop:
		m_2dsTop.push_back( obj );
		break;
	case eLevelMid:
		m_2dsMid.push_back( obj );
		break;
	case eLevelBottom:
		m_2dsBottom.push_back( obj );
		break;
	default:
		break;
	}

}
