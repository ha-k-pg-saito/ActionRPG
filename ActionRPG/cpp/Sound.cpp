#include"../h/Sound.h"

void Sound::Init(int soundhandle)
{
	//サウンドファイルを読み込む
	m_SoundHandle = soundhandle;
}

void Sound::play()
{
	//サウンド再生(ループ)
	PlaySoundMem(m_SoundHandle, DX_PLAYTYPE_BACK,FALSE);
}

void Sound::stop()
{
	//サウンドを止める
	StopSoundMem(m_SoundHandle);
}