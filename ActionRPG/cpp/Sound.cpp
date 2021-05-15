#include"../h/Sound.h"

void Sound::Init(int sound)
{
	//サウンドファイルを読み込む
	m_SoundHandle[3] = sound;
}

void Sound::play()
{
	//サウンド再生(ループ)
	PlaySoundMem(m_SoundHandle[0], DX_PLAYTYPE_LOOP);
}

void Sound::stop()
{
	//サウンドを止める
	StopSoundMem(m_SoundHandle[0]);
}