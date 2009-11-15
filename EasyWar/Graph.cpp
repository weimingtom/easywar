#include "stdafx.h"
#include "Graph.h"

//存储本类的单件
Graph* Graph::m_me= NULL;

Graph::Graph()
{
	m_mainWnd= NULL;
	m_beInit= false;
}

//在析构函数中释放本窗口
Graph::~Graph()
{
}

//获取本类的单件
Graph* Graph::GetSingle()
{
	if( m_me == NULL )
	{
		m_me= new Graph();
	}

	return m_me;
}

//销毁（如果存在的话）
void Graph::Destory()
{
	if( m_me )
	{
		m_me->ClearAllSpriteGroup();

		if( m_me->m_mainWnd )
		{
			SDL_FreeSurface( m_me->m_mainWnd );
			m_mainWnd= NULL;
			m_beInit= false;
		}

 		delete m_me;
		m_me= NULL;
	}
}

//按照指定宽高创建一个窗口
void Graph::CreateWnd( int wid, int hei, bool fullscreen )
{
	if( m_mainWnd )		//窗口已存在就不能再创建了
	{
		return;
	}

	if( fullscreen )
	{
		m_mainWnd= SDL_SetVideoMode( wid, hei, 24, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN );
	}else
	{
		m_mainWnd= SDL_SetVideoMode( wid, hei, 24, SDL_HWSURFACE | SDL_DOUBLEBUF );
	}

	m_wndWid= wid;
	m_wndHei= hei;

	m_beInit= true;

}

//使用指定颜色来清屏
void Graph::ClearWnd( int r, int g, int b )
{
	Uint32 color;
	
	color= SDL_MapRGBA( m_mainWnd->format, r, g, b, 0);

	SDL_FillRect( m_mainWnd, NULL, color );

}

//添加一个SpriteGroup组
int Graph::AddSpriteGroup( int size )
{
	SpriteGroup* newGroup= new SpriteGroup( size );

	m_spriteGroup.push_back( newGroup );

	return (int)m_spriteGroup.size() - 1;
}

//对指定SpriteGroup组添加Sprite
bool Graph::AddSprite( int group, int pos, const char* filename )
{
	if( group < 0 || group >= (int)m_spriteGroup.size() )	//组号越界，添加失败
	{
		return false;
	}

	return m_spriteGroup[group]->AddSprite( pos, filename );

}

//清除所有的SpriteGroup
void Graph::ClearAllSpriteGroup()
{
	size_t len= m_spriteGroup.size();

	for( size_t i(0); i< len; i++ )
	{
		delete m_spriteGroup[i];
	}

	m_spriteGroup.clear();
}

//每次图像函数完成需调用次
void Graph::Flush()
{
	SDL_Flip( m_mainWnd );
}

//画框（某些特定的地方可能会用到）
void Graph::DrawRect( int x1, int y1, int x2, int y2, int r, int g, int b, int a )
{
	rectangleRGBA( m_mainWnd, x1, y1, x2, y2, r, g, b, a );
}												

//绘制一个Sprite到窗口（普通）
void Graph::Draw( int group, int sprite, int x, int y )
{
	SDL_Surface* obj= (*m_spriteGroup[group])[sprite];
	SDL_Rect pos;
	pos.x= x;
	pos.y= y;
	pos.h= obj->h;
	pos.w= obj->w;

	SDL_BlitSurface( obj, NULL, m_mainWnd, &pos );

}

//绘制一个Sprite到窗口（旋转、缩放）
void Graph::Draw( int group, int sprite, int x, int y, double angle, double zoom )
{
	SDL_Surface* obj= (*m_spriteGroup[group])[sprite];

	obj= rotozoomSurface( obj, angle, zoom, 1 );
	SDL_Rect pos;
	pos.h= obj->h;
	pos.w= obj->w;
	pos.x= x - pos.w/2;
	pos.y= y - pos.h/2;

	SDL_BlitSurface( obj, NULL, m_mainWnd, &pos );

	SDL_FreeSurface( obj );

}

//绘制一个Sprite到窗口（半透明混合）
void Graph::Draw( int group, int sprite, int x, int y, int alpha )
{
	SDL_Surface* obj= (*m_spriteGroup[group])[sprite];

	SDL_Rect pos;
	pos.x= x;
	pos.y= y;
	pos.w= obj->w;
	pos.h= obj->h;

	SDL_gfxBlitRGBA( obj, NULL, m_mainWnd, &pos );

}

//得到指定Sprite的引用
Sprite& Graph::GetSprite( int group, int pos )
{
	return m_spriteGroup[group]->GetSprite( pos );
}

//窗口已存在
bool Graph::IsWndExist()
{
	return m_beInit;
}
