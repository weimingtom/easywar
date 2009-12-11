#pragma once
#include "Logic.h"
#include "AdvancedFrame.h"

class Demo02 : public Logic
{
public:

	virtual void Init( void* host );					//初始化
	virtual void Run( void* host, unsigned int time  );	//每帧运行
	virtual void End( void* host );						//结束

private:


};
