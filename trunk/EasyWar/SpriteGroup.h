#pragma once
#include "Sprite.h"
#include <vector>

using namespace std;

//用于存储管理一组Sprite
class SpriteGroup
{
public:
	SpriteGroup();
	SpriteGroup( int groupsize );
	~SpriteGroup();
	void SetSize( int groupsize );							//设置可以容纳多少个Sprite
	bool AddSprite( int index, const char* fileName );		//添加一个Sprite
	void ClearAll();										//消除本组所有Sprite
	Sprite& GetSprite( int index );							//得到本组的一个的一个引用
	SDL_Surface* operator[]( int index );					//得到某个Sprite的Surface的指针

protected:
	vector<Sprite> m_allSpr;								//本Sprite组的所有Sprite

};
