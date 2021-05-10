#include"../h/Sound.h"

void Sound::Load()
{
	//サウンドファイルを読み込む
	m_SoundHandle[0] = LoadSoundMem("音声ファイル");
	m_SoundHandle[1] = LoadSoundMem("音声ファイル");
	m_SoundHandle[2] = LoadSoundMem("音声ファイル");
}

void Sound::Init()
{
	Load();
}

void Sound::play()
{
	//サウンド再生(ループ)
	PlaySoundMem(m_SoundHandle[0],DX_PLAYTYPE_LOOP);
	PlaySoundMem(m_SoundHandle[1],DX_PLAYTYPE_LOOP);
	PlaySoundMem(m_SoundHandle[2],DX_PLAYTYPE_LOOP);
}

void Sound::stop()
{
	//サウンドを止める
	StopSoundMem(m_SoundHandle[0]);
	StopSoundMem(m_SoundHandle[1]);
	StopSoundMem(m_SoundHandle[2]);
}