#pragma once
#include <vector>

using namespace std;

#define MAX_CHANNEL	4


//控制声音的部分
class Sound
{
public:
	~Sound();
	static Sound* GetSingle();							//获取单件
	bool InitDevice();									//初始化音频设备
	void Destroy();										//摧毁函数
	int LoadSE( const char* fileName );					//加载一个音效声音
	int LoadBGM( const char* fileName );				//加载一个背景音乐
	void PlaySE( int num, int loop = 0 );				//播放音效
	void PlayBGM( int num, int loop = -1 );				//播放背景音乐
	void StopBGM();										//暂停BGM的播放
	void StopSE();										//暂停SE的播放
	void FreeAllSE();									//释放所有的SE
	void FreeAllBGM();									//释放所有的BGM

protected:
	Sound();

protected:
	static Sound* m_me;									//保存指向本对象的唯一单件的指针

	vector<Mix_Chunk*> m_allSE;							//保存所有的音效声音SE
	vector<Mix_Music*> m_allBGM;						//保存所有的背景音乐BGM

	int m_curChannel;									//当前混音通道

};

#define SND	(*Sound::GetSingle())
