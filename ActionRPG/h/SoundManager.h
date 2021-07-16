#ifndef SoundManager_h_
#define SoundManager_h_

#include<unordered_map>
#include<string>

class SoundMng
{
	//�}�W�b�N�i���o�폜�penum
	enum SoundState
	{
		State_Error = -1,		//���s
		State_None,				//�s�����Ȃ�
		State_Success,			//����
		State_Num				//�ő�l
	};
public:
	//�V���O���g��
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
	/*
		map���g���ăT�E���h���Ǘ����Ă���
		stging�^�̃L�[��int�ŋA���Ă���ϐ�
		unordered_map���g�����Ƃɂ���āAmap�̎��̂悤�Ȑ��񂪂Ȃ����ߏ����������Ȃ�
	*/
	std::unordered_map<std::string, int>m_SoundList;
	SoundMng() {}
	~SoundMng() { AllRelease(); }

};
#endif