#pragma once
#include "BasicUtility.h"


//一个2D渲染单元
class Unit2D
{
public:
	Unit2D();
	~Unit2D();
	virtual void Update( unsigned int time )= 0;				//更新函数
	void Leave();												//脱离，自动从Advance2D的渲染列表中被剔除
	void SetPos( int x, int y );								//设置位置

protected:
	Point m_pos;												//本渲染单元的位置
	bool m_exist;

};
