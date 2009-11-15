#include "stdafx.h"
#include "Unit2D.h"

Unit2D::Unit2D()
{
	m_exist= true;
}

Unit2D::~Unit2D()
{
}

//脱离，自动从Advance2D的渲染列表中被剔除
void Unit2D::Leave()
{
	m_exist= false;
}

//设置位置
void Unit2D::SetPos( int x, int y )
{
	m_pos._x= x;
	m_pos._y= y;
}
