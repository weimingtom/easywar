#include "stdafx.h"
#include "Unit2D.h"

Unit2D::Unit2D()
{
	m_head = false;
	m_prior = NULL;
	m_next = NULL;
}

Unit2D::~Unit2D()
{
}

//更新函数
void Unit2D::Update( unsigned int time )
{
}

//脱离，自动从Advance2D的渲染列表中被剔除
void Unit2D::Leave()
{
	if( m_prior )
	{
		m_prior->m_next = m_next;
	}
	if( m_next )
	{
		m_next->m_prior = m_prior;
	}
}

//设置位置
void Unit2D::SetPos( int x, int y )
{
	m_pos._x = x;
	m_pos._y = y;
}

//设置为头单元（无效）
void Unit2D::SetHead()
{
	m_head = true;
	m_prior = NULL;
	m_next = NULL;
}

//设置前一个节点
void Unit2D::SetPrior( Unit2D* prior )
{
	m_prior = prior;
}

//设置后一个节点
void Unit2D::SetNext( Unit2D* next )
{
	m_next = next;
}
