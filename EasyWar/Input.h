#pragma once

#define MOUSEDOWN	1
#define MOUSEUP		2

//部分按键定义
#define ESC			SDLK_ESCAPE
#define ENTER		SDLK_RETURN
#define UP			SDLK_UP
#define DOWN		SDLK_DOWN
#define RIGHT		SDLK_RIGHT
#define LEFT		SDLK_LEFT
#define SPACE		SDLK_SPACE


//鼠标按键用到的一些枚举
enum{ eLButton= 0, eRButton };
enum{ eMouseNon= 0, eMouseDown, eMouseUp };

//获取输入的类（提供静态方法）
class Input
{
public:
	static void Update();				//更新事件状态
	static bool Quit();					//是否有退出事件产生？
	static int LButtonEvent()			//返回左键事件
	{
		return m_mouseEvent[eLButton];
	}
	static int RButtonEvent()			//返回右键事件
	{
		return m_mouseEvent[eRButton];
	}
	static bool LButtonDown()			//左键是否按下
	{
		return m_mouseKeyState[eLButton];
	}
	static bool RButtonDown()			//右键是否按下
	{
		return m_mouseKeyState[eRButton];
	}
	static int Xpos()					//返回鼠标的X坐标
	{
		return m_mouseX;
	}
	static int Ypos()					//返回鼠标的Y坐标
	{
		return m_mouseY;
	}
	static int KeyDown( int key )		//判断某键是否按下		//** 这里没有数组越界的检查
	{
		return m_KeyState[key];
	}
	static SDL_Event* _GetEvtStruct()	//底层接口，不推荐使用
	{
		return &m_evt;
	}

protected:
	static bool m_mouseKeyState[2];		//鼠标按键状态
	static int m_mouseEvent[2];			//鼠标事件
	static int m_mouseX;				//鼠标位置X
	static int m_mouseY;				//鼠标位置Y
	static Uint8 *m_KeyState;			//按键状态

	static SDL_Event m_evt;				//事件结构

};


/*
RButton的点击和抬起事件有点问题，会产生多次，不知道是我编码的问题还是SDL的问题
按键的按下事件没做，只做了可以判断该键是按下还是抬起的
*/