#include "StdAfx.h"
#include "Widget.h"

Widget::Widget(void)
{
	m_visible= true;
}

Widget::~Widget(void)
{
}

//设置控件的可见性
void Widget::SetVisible( bool visible )
{
	m_visible= visible;
}
