#pragma once
#include <cmath>

using namespace std;


//这里提供了一些基本的东西，点，颜色，矩形的结构极一些简单操作，宏等

#define CREATE_LOGIC( x )	new x


//颜色结构
struct Color
{
	int _r;
	int _g;
	int _b;
	int _a;

	Color():_r(0),_g(0),_b(0),_a(0){}
	Color( int r, int g, int b, int a ):_r(r),_g(g),_b(b),_a(a){}
};

//点结构（整数）
struct Point
{
	int _x;
	int _y;

	Point():_x(0),_y(0){}
	Point( int x, int y ):_x(x),_y(y){}
};

//点结构（实数）
struct Pointf
{
	float _x;
	float _y;

	Pointf():_x(0.0f),_y(0.0f){}
	Pointf( float x, float y ):_x(x),_y(y){}
};


//矩形结构
struct Rect
{
	int _left;
	int _top;
	int _right;
	int _bottom;

	Rect():_left(0),_top(0),_right(0),_bottom(0){}
	Rect( int _l, int _t, int _r, int _b ):_left(_l),_top(_t),_right(_r),_bottom(_b){}
};
