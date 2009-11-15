#pragma once

#include <list>
#include <map>
#include <vector>
#include "SpriteGroup.h"

using namespace std;


//图像类
class Graph
{
public:
	~Graph();
	void Destory();								//销毁（如果存在的话）
	bool IsWndExist();							//窗口已存在
	void CreateWnd( int wid, int hei, bool fullscreen= false );
												//按照指定宽高创建一个窗口
	static Graph* GetSingle();					//获取本类的单件
	int AddSpriteGroup( int size );				//添加一个SpriteGroup组（返回该组的索引）
	bool AddSprite( int group, int pos, const char* filename );
												//对指定SpriteGroup组添加Sprite
	Sprite& GetSprite( int group, int pos );	//得到指定Sprite的引用
	void ClearAllSpriteGroup();					//清除所有的SpriteGroup

	void Flush();								//每次图像函数完成需调用次
	void ClearWnd( int r, int g, int b );		//用指定颜色来清屏【很耗时间】
	void DrawRect( int x1, int y1, int x2, int y2, int r, int g, int b, int a );
												//画框（某些特定的地方可能会用到）
	void Draw( int group, int sprite, int x, int y );
												//绘制一个Sprite到窗口（普通）
	void Draw( int group, int sprite, int x, int y, double angle, double zoom );
												//绘制一个Sprite到窗口（旋转、缩放）
	void Draw( int group, int sprite, int x, int y, int alpha );
												//绘制一个Sprite到窗口（半透明混合）【暂有问题】

protected:
	Graph();

protected:
	static Graph* m_me;							//保存指向本类唯一对象的指针
	int m_wndWid;								//窗口的宽
	int m_wndHei;								//窗口的高
	bool m_beInit;								//已被初始化过（创建了窗口）

	SDL_Surface* m_mainWnd;						//主窗口
	vector<SpriteGroup*> m_spriteGroup;			//所有的SpriteGroup组

};

#define DRAW (*Graph::GetSingle())
