#pragma once
#include "BasicUtility.h"

class SpriteGroup;

//Sprite类，用于表示2D图块
class Sprite
{
	friend class SpriteGroup;

public:
	Sprite();
	Sprite( const char* filename );
	~Sprite();
	void Load( const char* filename );		//加载图片
	void Kill();							//删除Sprite
	void SetAlpha( int alpha );				//设置半透明
	void SetAngleZoom( double angle, double zoom );
											//旋转缩放
	void Clip( int x, int y, int wid, int hei );
											//剪切（以得到原图的局部）
	void Clip( Rect& region );				//剪切
	void Clip( float u1, float v1, float u2, float v2 );
											//剪切（按照UV坐标来）

protected:
	SDL_Surface* m_spr;						//存储本图块的surface

};
