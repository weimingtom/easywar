#pragma once
#include "Unit2D.h"

//动画的状态枚举
enum{ eAniPlaying, eAniPause, eAniStop };

//2D动画类
class Animation : public Unit2D
{
public:
	Animation();
	~Animation();
	virtual void Update( unsigned int time );				//更新函数
	void SetFrameCount( int count );						//设置动画总帧数-（1）
	void SetFrame( int index, char* fileName, Rect& clip );	//设置某一帧的图像-（2）
	void CreateAniAuto( char* fileName, int wid, int hei, int count );
															//根据一张图片及格式自动创建一个动画序列
	void Play( int loop );									//播放（0为无限循环播放）
	void Stop();											//停止播放（无显示）
	void Pause( int frame = 0 );							//暂停播放（有显示）
	void SetFrameTime( unsigned int interval );				//设置每帧的间隔时间
	void Duplicate( Animation& orgAni );					//产生目标的副本

protected:
	int m_state;											//动画状态
	int m_currFrame;										//当前帧数
	int m_groupNum;											//图像组组号
	int m_frameCount;										//帧数
	int m_loop;												//循环次数
	unsigned int m_frameInterval;							//每帧间隔时间
	unsigned int m_timer;									//用来记录时间，控制动画帧速

};
