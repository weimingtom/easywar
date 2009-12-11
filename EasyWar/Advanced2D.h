#pragma once
#include "Graph.h"
#include "Animation.h"
#include "Logic.h"

enum{  eLevelBottom = 0, eLevelMid,  eLevelTop, eMaxLevel };

//在原来的Graph类上进行一层封装，提供一些功能
class Advanced2D : public Logic
{
public:
	Advanced2D();
	~Advanced2D();
	virtual void Init( void* host );							//初始化
	virtual void Run( void* host, unsigned int time );			//每帧运行（time为上帧到这帧的毫秒数）
	virtual void End( void* host );								//结束
	void AddUnit( Unit2D* obj, int level = 0 );					//添加一个渲染对象

protected:
	Unit2D* m_2dsLevels[eMaxLevel];								//存储所有要渲染的2D对象（分层），渲染的顺序不同，Top最上，Bottom最下，Mid中间

	Unit2D* m_listTail[eMaxLevel];

};
