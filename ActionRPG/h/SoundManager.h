#ifndef SoundManager_h_
#define SoundManager_h_

#include<map>
#include<string>

//マジックナンバ削除用enum
enum SoundState
	{
		State_Error = -1,		//失敗
		State_None,				//行動しない
		State_Success,			//成功
		State_Num				//最大値
	};

class SoundMng
{
public:
	//シングルトン
	static SoundMng* Instance()
	{
		static SoundMng instance;
		return &instance;
	}

public:
	bool Load(const char* filename, std::string keyword);
	void Play(std::string keyword, int playtype = 0, int toppositionflag = 0);
	void Stop(std::string keyword);
	void Release(std::string keyword);
	void AllRelease();

private:
	//mapを使ってサウンドを管理している
	//stging型のキーがintで帰ってくる変数
	std::map<std::string, int>m_SoundList;
	SoundMng() {}
	~SoundMng() { AllRelease(); }

};


#endif