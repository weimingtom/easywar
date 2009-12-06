#pragma once
#include "GameFrame.h"
#include "Advanced2D.h"


//继承了原来的GameFrame并提供更多功能
class AdvancedFrame : public GameFrame
{
public:
	AdvancedFrame();
	~AdvancedFrame();
	void Initial( int wid, int hei, char* wndName = "Demo", char* icon = NULL, bool fullscreen = false );
													//初始化
	void Destroy();									//结束
	Advanced2D* ADRAW(){ return m_adv2d; }			//得到指向Advanced2D对象的指针（用于图形操作）

protected:
	Advanced2D* m_adv2d;							//Advanced2D对象的指针（只有一个）

};


#define ADVANCE_FRAME( x ) ((AdvancedFrame*)x)		//指针转换的宏
