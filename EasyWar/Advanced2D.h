#pragma once
#include "Graph.h"
#include "Animation.h"
#include "Logic.h"
#include <list>

using namespace std;

enum{ eLevelTop = 0, eLevelMid, eLevelBottom };

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
	list<Unit2D*> m_2dsTop;										//存储所有要渲染的2D对象（分层）
	list<Unit2D*> m_2dsMid;										//渲染的顺序不同
	list<Unit2D*> m_2dsBottom;									//Top最上，Bottom最下，Mid中间

};
