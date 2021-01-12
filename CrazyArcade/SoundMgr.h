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
	void PlaySound(TCHAR* pSoundKey, CHANNELID eID);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(CHANNELID eID);
	void StopAll();
private:
	void LoadSoundFile();
private:
	// 사운드 리소스 정보 갖고 있는 객체 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannel[MAXCHANNEL];
	//사운드 채널 객체및 장치를 관리할 객체 
	FMOD_SYSTEM* m_pSystem;
};

