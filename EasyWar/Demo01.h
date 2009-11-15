#pragma once
#include "Logic.h"
#include "AdvancedFrame.h"

//方向
enum{ eDirUp= 0, eDirDown, eDirLeft, eDirRight };

//[Demo01]键盘上下左右控制一个坦克走来走去
class Demo01 : public Logic
{
public:

	virtual void Init( void* host );					//初始化
	virtual void Run( void* host, unsigned int time  );	//每帧运行
	virtual void End( void* host );						//结束

private:
	Animation m_tank[4];								//坦克动画们

	int m_x;											//位置
	int m_y;
	int m_dir;											//方向
	int m_nextDir;										//下次一要转的方向
	int m_sndId;										//声音的ID

};
