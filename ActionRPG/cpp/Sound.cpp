#include"../h/Sound.h"

void Sound::Load()
{
	//サウンドファイルを読み込む
	SoundHandle[0] = LoadSoundMem("音声ファイル");
	SoundHandle[1] = LoadSoundMem("音声ファイル");
	SoundHandle[2] = LoadSoundMem("音声ファイル");
}

void Sound::play()
{
	//サウンド再生(ループ)
	PlaySoundMem(SoundHandle[0],DX_PLAYTYPE_LOOP);
	PlaySoundMem(SoundHandle[1],DX_PLAYTYPE_LOOP);
	PlaySoundMem(SoundHandle[2],DX_PLAYTYPE_LOOP);
}

void Sound::stop()
{
	//サウンドを止める
	StopSoundMem(SoundHandle[0]);
	StopSoundMem(SoundHandle[1]);
	StopSoundMem(SoundHandle[2]);
}