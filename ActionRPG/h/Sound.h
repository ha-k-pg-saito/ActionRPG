#ifndef Sound_h_
#define Sound_h_

#include"DxLib.h"

class Sound
{
public:
	//シングルトン
	static Sound* Instance()
	{
		static Sound instance;
		return &instance;
	}

public:
	void Load();
	void play();
	void stop();

public:
	//サウンドのハンドルを保存する変数
	int SoundHandle[3];

private:
	Sound() {}
	~Sound() {}
};


#endif