#include "../h/SoundManager.h"
#include"DxLib.h"

bool SoundMng::Load(const char* filename, std::string keyword)
{
	//���X�g���𒲂ׂă��X�g���Ƀt�@�C���ɂȂ���Γǂݍ���
	if (m_SoundList.find(keyword) != m_SoundList.end()) return true;

	int handle = LoadSoundMem(filename);

	if (SoundState::State_Error == handle) return false;

	// �ǂݍ��݂����������� �����̃L�[���[�h�Ńn���h����ۑ�����
	m_SoundList[keyword] = handle;

	return true;
}

void SoundMng::Play(std::string keyword, int playtype, int toppositionflag)
{
	//���X�g���T���āA��ԉ��܂ōs���Δ�����
	if (m_SoundList.find(keyword) == m_SoundList.end()) return;
	int handle = m_SoundList[keyword];
	//�Đ������ǂ������ׂ遁���Đ�����Ă��Ȃ������Đ�����	
	if (CheckSoundMem(handle) == SoundState::State_None)
	{
		PlaySoundMem(handle, playtype, toppositionflag);
		ChangeVolumeSoundMem(180, handle);
	}
}

void SoundMng::Stop(std::string keyword)
{
	if (m_SoundList.find(keyword) == m_SoundList.end()) return;

	int handle = m_SoundList[keyword];
	//�Đ������ǂ������ׂ遁���Đ��������w�肵���T�E���h���~�߂�
	if (CheckSoundMem(handle) == SoundState::State_Success)
	{
		StopSoundMem(handle);
	}
}

void SoundMng::Release(std::string keyword)
{
	// ��Ȃ瑁�����^�[��
	if (m_SoundList.empty()) return;

	// �e�N�X�`���n���h�����ۑ�����Ă���ꏊ���w���Ă���C�e���[�^�[���擾
	auto itr = m_SoundList.find(keyword);

	if (itr != m_SoundList.end())
	{
		DeleteSoundMem(m_SoundList[keyword]);
		m_SoundList.erase(itr);
	}
}

void SoundMng::AllRelease()
{
	// ��Ȃ瑁�����^�[��
	if (m_SoundList.empty()) return;
	//�ǂݍ��񂾃T�E���h�f�[�^��������������
	InitSoundMem();
	m_SoundList.clear();
}
