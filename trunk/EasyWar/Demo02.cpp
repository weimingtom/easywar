#include "stdafx.h"
#include "Demo02.h"

int groupNum;

//初始化
void Demo02::Init( void* host )
{
	groupNum = DRAW.AddSpriteGroup( 1 );
	DRAW.AddSprite( groupNum, 0, "bg2.png" );

	int bgmID = SND.LoadBGM("close.wav");

	SND.PlayBGM( bgmID, 0 );
}

//每帧运行
void Demo02::Run( void* host, unsigned int time  )
{
	DRAW.Draw( groupNum, 0, 0, 0 );
}

//结束
void Demo02::End( void* host )
{
	;
}
