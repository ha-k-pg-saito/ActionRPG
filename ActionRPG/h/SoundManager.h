#ifndef SoundManager_h_
#define SoundManager_h_

#include<map>
#include<string>

enum SoundState
	{
		State_Error = -1,		//¸”s
		State_None,				//s“®‚µ‚È‚¢
		State_Success,			//¬Œ÷
		State_Num				//Å‘å’l
	};

class SoundMng
{
public:
	static SoundMng* Instance()
	{
		static SoundMng instance;
		return &instance;
	}

private:


public:
	bool Load(const char* filename, std::string keyword);
	void Play(std::string keyword, int playtype = 0, int toppositionflag = 0);
	void Stop(std::string keyword);
	void Release(std::string keyword);
	void AllRelease();

private:
	std::map<std::string, int>m_SoundList;
	SoundMng() {}
	~SoundMng() { AllRelease(); }

};


#endif