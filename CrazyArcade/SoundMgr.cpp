#include "stdafx.h"

#include "SoundMgr.h"

#include <string>
#include "fmod_common.h"



IMPLEMENT_SINGLETON(CSoundMgr)


CSoundMgr::CSoundMgr()
	:m_pSystem(nullptr)
{
	Initialize();
}


CSoundMgr::~CSoundMgr()
{
	Release();
}

std::wstring ConvertUtf8ToWide(const std::string& str)
{
	int count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
	std::wstring wstr(count, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstr[0], count);
	return wstr;
}

void CSoundMgr::Initialize()
{
	FMOD_RESULT 	result;
	unsigned int	version = 0;

	result = FMOD_System_Create(&m_pSystem, FMOD_VERSION);
	result = FMOD_System_GetVersion(m_pSystem, &version);
	result = FMOD_System_Init(m_pSystem,512, FMOD_INIT_NORMAL, nullptr);


	__finddata64_t filefinder;

	int iResult = 0;
	
	char szDirPath[128] ="";
	char szFileName[128] = "";
	char szFullPath[128] = "";

	m_hFile = _findfirst64("../Sound/*.wav", &filefinder);
	if (-1 == m_hFile)
		return;


	strcpy_s(szFullPath, szDirPath);

	FMOD_RESULT eRes;
	
	while (iResult != -1)
	{	
		char szDirPath[128] = "../Sound/";

		TCHAR* FileName = new TCHAR[258];

		strcpy_s(szFileName, filefinder.name);
		strcat_s(szDirPath, szFileName);

		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, filefinder.name, strlen(filefinder.name)+1, FileName, strlen(filefinder.name)+1);
		
		char cTemp[256] = { 0, };
		
		WideCharToMultiByte(CP_ACP, 0, FileName, strlen(filefinder.name) + 1,cTemp, strlen(filefinder.name) + 1, NULL, NULL);

		if (0 == strcmp(filefinder.name, cTemp))
		{
			FMOD_SOUND* pSound = nullptr;
			eRes = FMOD_System_CreateSound(m_pSystem, szDirPath, FMOD_CREATESTREAM, 0, &pSound);
			if (eRes == FMOD_OK)
			{
				m_mapSound.emplace(FileName, pSound);
				
			}
		}

		{
			if (0 != _findnext64(m_hFile, &filefinder))
			{
				iResult = -1;
			}
			
		}
	}

	_findclose(m_hFile);
	//LoadSoundFile();
}

void CSoundMgr::Update()
{
}

void CSoundMgr::Release()
{
	for (auto& Mypair : m_mapSound)
	{
		delete[] Mypair.first;
		FMOD_Sound_Release(Mypair.second);
	}
	m_mapSound.clear();
	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}

void CSoundMgr::PlayBGM(TCHAR* pSoundKey, CHANNELID eID)
{
	// 음악 재생이 안되서 일단 주석
	m_pSoundKey = pSoundKey;

	if (m_mapSound.empty())
		return;

	map<TCHAR*, FMOD_SOUND*>::iterator iter = find_if(m_mapSound.begin(), m_mapSound.end(), CMyStrCmp(pSoundKey));

	if (iter == m_mapSound.end())
		return;

	FMOD_System_PlaySound(m_pSystem, iter->second, nullptr, false, &m_pChannel[eID]);
	FMOD_Channel_SetMode(m_pChannel[eID], FMOD_DEFAULT);
}

void CSoundMgr::StopSound(CHANNELID eID)
{
	FMOD_Channel_Stop(m_pChannel[eID]);
}

void CSoundMgr::StopAll()
{
	for (int i = 0; i < MAXCHANNEL; ++i)
	{
		FMOD_Channel_Stop(m_pChannel[i]);
	}
}

void CSoundMgr::LoadSoundFile()
{


	//FMOD_System_Update(m_pSystem);
}
