#include "stdafx.h"
#include "Sound.h"

Sound* Sound::m_me= NULL;


Sound::Sound()
{
}

Sound::~Sound()
{
}

//获取本类的单件
Sound* Sound::GetSingle()
{
	if( m_me == NULL )
	{
		m_me= new Sound();
	}

	return m_me;
}

//摧毁函数
void Sound::Destroy()
{
	if( m_me )
	{
		Mix_CloseAudio();

		FreeAllSE();
		FreeAllBGM();

		delete m_me;
		m_me= NULL;
	}

}

//初始化音频设备
bool Sound::InitDevice()
{
	int TMP_FREQ= MIX_DEFAULT_FREQUENCY;
	Uint16 TMP_FORMAT= MIX_DEFAULT_FORMAT;
	int TMP_CHUNK_SIZE= 512;

	//4通道混音
	int result=	Mix_OpenAudio(TMP_FREQ,TMP_FORMAT,MAX_CHANNEL,TMP_CHUNK_SIZE);

	m_curChannel= 0;

	return result == 1 ? true : false;
}

//释放所有的SE
void Sound::FreeAllSE()
{
	size_t len= m_allSE.size();

	for( size_t i(0); i< len; i++ )
	{
		Mix_FreeChunk( m_allSE[i] );
	}

	m_allSE.clear();
}

//释放所有的BGM
void Sound::FreeAllBGM()
{
	size_t len= m_allBGM.size();

	for( size_t i(0); i< len; i++ )
	{
		Mix_FreeMusic( m_allBGM[i] );
	}

	m_allBGM.clear();
}

//播放音效
void Sound::PlaySE( int num, int loop )
{
	Mix_PlayChannel( m_curChannel++, m_allSE[num], loop );

	if( m_curChannel >= MAX_CHANNEL )
	{
		m_curChannel= 0;
	}
}

//播放背景音乐
void Sound::PlayBGM( int num, int loop )
{
	Mix_PlayMusic( m_allBGM[num], loop );
}

//加载一个音效声音
int Sound::LoadSE( const char* fileName )
{
	Mix_Chunk* music;

	music= Mix_LoadWAV( fileName );

	//加载失败
	if( music == NULL )
	{
		return -1;
	}

	m_allSE.push_back( music );

	return (int)m_allSE.size() - 1;
}

//加载一个背景音乐
int Sound::LoadBGM( const char* fileName )
{
	Mix_Music* music;

	music= Mix_LoadMUS( fileName );

	//加载失败
	if( music == NULL )
	{
		return -1;
	}

	m_allBGM.push_back( music );

	return (int)m_allBGM.size() - 1;
}

//暂停BGM的播放
void Sound::StopBGM()
{
	Mix_FadeOutMusic( 1000 );
}

//暂停SE的播放
void Sound::StopSE()
{
	Mix_FadeOutChannel( 0, 0 );
	Mix_FadeOutChannel( 1, 0 );
	Mix_FadeOutChannel( 2, 0 );
	Mix_FadeOutChannel( 3, 0 );
}
