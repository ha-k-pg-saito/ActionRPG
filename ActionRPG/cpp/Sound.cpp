#include"../h/Sound.h"

void Sound::Load()
{
	//サウンドファイルを読み込む
	SoundHandle = LoadSoundMem("音声ファイル");
}

void Sound::play()
{
	//サウンド再生
	PlaySoundFile("音声ファイル",DX_PLAYTYPE_LOOP);
}

void Sound::stop()
{
	//サウンドを止める
	StopSoundFile();
}