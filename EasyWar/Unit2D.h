#pragma once
#include "BasicUtility.h"

class Advanced2D;

//一个2D渲染单元
class Unit2D
{
	friend class Advanced2D;

public:
	Unit2D();
	~Unit2D();
	virtual void Update( unsigned int time );					//更新函数
	void Leave();												//脱离，自动从Advance2D的渲染列表中被剔除
	void SetPos( int x, int y );								//设置位置
	void SetHead();												//设置为头单元（无效）
	void SetPrior( Unit2D* prior );
	void SetNext( Unit2D* next );

protected:
	Point m_pos;												//本渲染单元的位置
	bool m_head;

	Unit2D* m_prior;
	Unit2D* m_next;

};
