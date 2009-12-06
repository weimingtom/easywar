#include "stdafx.h"
#include "Input.h"


//声明静态变量
bool Input::m_mouseKeyState[2] = {false, false };
int Input::m_mouseEvent[2] = {eMouseNon, eMouseNon };
int Input::m_mouseX;
int Input::m_mouseY;
Uint8* Input::m_KeyState = NULL;
SDL_Event Input::m_evt;


//更新事件
void Input::Update()
{
	memset( &m_evt, 0, sizeof(m_evt) );
	SDL_PollEvent( &m_evt );

	//下面处理键盘输入
	m_KeyState = SDL_GetKeyState( NULL );

	//下面处理鼠标输入
	Uint8 mouseKey;
	mouseKey = SDL_GetMouseState( &m_mouseX, &m_mouseY );

	if( mouseKey & SDL_BUTTON(1) )	//左键按下状态
	{
		if( m_mouseKeyState[eLButton] )
		{
			m_mouseEvent[eLButton] = eMouseNon;	//这次按下，上次也按下，则取消鼠标点击事件
		}else
		{
			m_mouseEvent[eLButton] = eMouseDown;	//这次按下，上次没按下，则产生了鼠标点击事件
			m_mouseKeyState[eLButton] = true;
		}
	}else							//左键没按下状态
	{
		if( m_mouseKeyState[eLButton] )
		{
			m_mouseEvent[eLButton] = eMouseUp;	//这次没按下，上次按下，则产生鼠标抬起事件
			m_mouseKeyState[eLButton] = false;
		}else
		{
			m_mouseEvent[eLButton] = eMouseNon;	//这次没按下，上次也没按下，则取消鼠标抬起事件
		}
	}

	if( mouseKey & SDL_BUTTON(3) )	//右键按下状态
	{
		if( m_mouseKeyState[eRButton] )
		{
			m_mouseEvent[eRButton] = eMouseNon;	//这次按下，上次也按下，则取消鼠标按下事件
		}else
		{
			m_mouseEvent[eRButton] = eMouseDown;	//这次按下，上次没按下，则产生了鼠标按下事件
			m_mouseKeyState[eRButton] = true;
		}
	}else
	{
		if( m_mouseKeyState[eRButton] )
		{
			m_mouseEvent[eRButton] = eMouseUp;	//这次没按下，上次按下，则产生鼠标抬起事件
			m_mouseKeyState[eRButton] = false;
		}else
		{
			m_mouseEvent[eRButton] = eMouseNon;	//这次没按下，上次也没按下，则取消鼠标抬起事件
		}
	}
}

//判断程序是否退出
bool Input::Quit()
{

	if( m_evt.quit.type == SDL_QUIT )
	{
		return true;
	}

	return false;
}
