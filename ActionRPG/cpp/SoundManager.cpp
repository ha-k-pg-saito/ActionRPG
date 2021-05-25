#include "../h/SoundManager.h"
#include"DxLib.h"

bool SoundMng::Load(const char* filename, std::string keyword)
{
	//リスト内を調べてリスト内にファイルになければ読み込む
	if (m_SoundList.find(keyword) != m_SoundList.end()) return true;

	int handle = LoadSoundMem(filename);

	if (SoundState::State_Error == handle) return false;

	// 読み込みが成功したら 引数のキーワードでハンドルを保存する
	m_SoundList[keyword] = handle;

	return true;
}

void SoundMng::Play(std::string keyword, int playtype, int toppositionflag)
{
	if (m_SoundList.find(keyword) == m_SoundList.end()) return;
	int handle = m_SoundList[keyword];
	
	if (CheckSoundMem(handle) == SoundState::State_None)
	{
		PlaySoundMem(handle, playtype, toppositionflag);
	}
}

void SoundMng::Stop(std::string keyword)
{
	if (m_SoundList.find(keyword) == m_SoundList.end()) return;

	int handle = m_SoundList[keyword];
	if (CheckSoundMem(handle) == SoundState::State_Success)
	{
		StopSoundMem(handle);
	}
}

void SoundMng::Release(std::string keyword)
{
	// 空なら早期リターン
	if (m_SoundList.empty()) return;

	// テクスチャハンドルが保存されている場所を指しているイテレーターを取得
	auto itr = m_SoundList.find(keyword);

	if (itr != m_SoundList.end())
	{
		DeleteSoundMem(m_SoundList[keyword]);
		m_SoundList.erase(itr);
	}
}

void SoundMng::AllRelease()
{
	// 空なら早期リターン
	if (m_SoundList.empty()) return;
	//読み込んだサウンドデータをメモリから解放
	InitSoundMem();
	m_SoundList.clear();
}
