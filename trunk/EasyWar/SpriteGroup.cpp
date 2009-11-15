#include "stdafx.h"
#include "SpriteGroup.h"

SpriteGroup::SpriteGroup()
{
}

SpriteGroup::SpriteGroup( int groupsize )
{
	m_allSpr.resize( groupsize );
}

SpriteGroup::~SpriteGroup()
{
	ClearAll();
}

//设置可以容纳多少个Sprite
void SpriteGroup::SetSize( int groupsize )
{
	m_allSpr.resize( groupsize );
}

//添加一个Sprite
bool SpriteGroup::AddSprite( int index, const char* fileName )
{
	FILE* pic;
	pic= fopen( fileName, "rb");

	if( pic == NULL )								//文件不存在，则添加失败
	{
		return false;
	}
	fclose( pic );

	if( index < 0 || index >= (int)m_allSpr.size() )//位置越界，则添加失败
	{
		return false;
	}

	m_allSpr[index].Load( fileName );

	return true;
}

//消除本组所有Sprite
void SpriteGroup::ClearAll()
{
	m_allSpr.clear();
}

//得到某个Sprite的Surface的指针
SDL_Surface* SpriteGroup::operator[]( int index )
{
	return m_allSpr[index].m_spr;
}

//得到本组的一个的一个引用
Sprite& SpriteGroup::GetSprite( int index )
{
	return m_allSpr[index];
}
