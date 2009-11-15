#pragma once


//所有GUI控件类的基类
class Widget
{
public:
	Widget(void);
	~Widget(void);
	virtual void Update()= 0;
	void SetVisible( bool visible );								//设置控件的可见性

protected:
	bool m_visible;

};
