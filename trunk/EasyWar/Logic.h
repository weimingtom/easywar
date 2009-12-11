//一个Logic是一个任务单位
//继承Logic并重载相关函数来制造自己的任务
#pragma once
#include <queue>
#include "GameFrame.h"

using namespace std;

//Logic状态枚举
enum{ eLogicInit, eLogicRun, eLogicEnd, eLogicDead, eLogicPause, eLogicSleep };

//Logic消息结构
struct sLogicMsg
{
	int ID;
	void* data;
};

//Logic类
class Logic
{
friend class GameFrame;

public:
	Logic();
	~Logic();

	bool Dead();								//本Logic是否已死亡（GameFrame负责清除死亡的Logic）
	void Exit();								//结束本Logic的运行
	void Pause();								//暂停本Logic的运行
	void Resume();								//恢复本Logic的运行
	void SendMessage( int ID, void* data );		//发送消息（用于Logic通信，或一个Logic控制另一个）

	//[这三个函数必须被重载]
	virtual void Init( void* host ) = 0;		//初始化
	virtual void Run( void* host, unsigned int time ) = 0;	
												//每帧运行（time为上帧到这帧的毫秒数）
	virtual void Sleep( void* host );			//被暂停时被调用一次
	virtual void Awake( void* host );			//醒来时被调用一次
	virtual void End( void* host ) = 0;			//结束

private:
	int m_LogicState;							//当前Logic的状态
	int m_LastState;							//挂起时Logic的状态
	void* m_host;								//指向本Logic宿主的指针
	queue<sLogicMsg> m_msg;						//本Logic的消息队列

private:
	void Update( unsigned int time );			//更新
	void SetHost( void* host );					//设置宿主
	bool GetMessage( sLogicMsg* msg );			//获取消息（被获取的消息从消息队列里自动删除）

};
