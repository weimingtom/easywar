#pragma once
#include "Graph.h"
#include "Input.h"
#include "Logic.h"
#include <vector>

using namespace std;


//简单的GUI系统类
class GUI : public Logic
{
public:
	GUI(void);
	~GUI(void);
	virtual void Init( void* host );							//初始化
	virtual void Run( void* host, unsigned int time );			//每帧运行（time为上帧到这帧的毫秒数）
	virtual void End( void* host );								//结束

protected:
	;

};
