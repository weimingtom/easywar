#include "stdafx.h"
#include "Demo02.h"

//初始化
void Demo02::Init( void* host )
{
	GAME_FRAME( host )->AutoClear( true );

	int bgmID = SND.LoadBGM("close.wav");

	SND.PlayBGM( bgmID, 0 );
}

//每帧运行
void Demo02::Run( void* host, unsigned int time  )
{
	;
}

//结束
void Demo02::End( void* host )
{
	;
}
