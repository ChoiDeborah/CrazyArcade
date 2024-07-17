#pragma once
class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr)

public:
	enum CHANNELID { BGM, PLAYER, MONSTER, EFFECT, BOMB, UI, MAXCHANNEL };
public:
	void Initialize();
	void Update();
	void Release();

public:
	void PlayBGM(TCHAR* pSoundKey, CHANNELID eID = BGM);
	void StopSound(CHANNELID eID);
	void StopAll();
private:
	void LoadSoundFile();
private:
	// ���� ���ҽ� ���� ���� �ִ� ��ü 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannel[MAXCHANNEL];
	//���� ä�� ��ü�� ��ġ�� ������ ��ü 
	FMOD_SYSTEM* m_pSystem;

	TCHAR* m_pSoundKey = nullptr;
	intptr_t m_hFile;
};

