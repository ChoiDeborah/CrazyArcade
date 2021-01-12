#include "stdafx.h"
#include "SceneMgr.h"
#include "Logo.h"
#include "MyMenu.h"
#include "Stage.h"
#include "Stage2.h"
#include "Stage3.h"
#include "MapEditor.h"
#include "LastScene.h"
#include "GameMgr.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	:m_pScene(nullptr)
	, m_eCurScene(SceneID::SCENE_END)
	, m_eNextScene(SceneID::SCENE_END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::SceneChange(SceneID::ID eScene)
{

	if (CGameMgr::Get_Instance()->m_bReload)
	{
		m_eNextScene = eScene;
		if (m_pScene)
		{
			delete m_pScene;
			m_pScene = nullptr;
		}


		switch (m_eNextScene)
		{
		case SceneID::SCENE_LOGO:
			m_pScene = new CLogo;
			break;
		case SceneID::SCENE_MENU:
			m_pScene = new CMyMenu;
			break;
		case SceneID::SCENE_EDIT:
			m_pScene = new CMapEditor;
			break;
		case SceneID::SCENE_STAGE:
			m_pScene = new CStage;
			break;
		case SceneID::SCENE_STAGE2:
			m_pScene = new CStage2;
			break;
		case SceneID::SCENE_STAGE3:
			m_pScene = new CStage3;
			break;
		case SceneID::SCENE_END:
			m_pScene = new CLastScene;
			break;
		default:
			break;
		}

		m_pScene->Initialize();

		m_eCurScene = m_eNextScene;
		return;
	}
	m_eNextScene = eScene;
	if (m_eCurScene != m_eNextScene )
	{
		if (m_pScene)
		{
			delete m_pScene;
			m_pScene = nullptr;
		}
		switch (m_eNextScene)
		{
		case SceneID::SCENE_LOGO:
			m_pScene = new CLogo;
			break;
		case SceneID::SCENE_MENU:
			m_pScene = new CMyMenu;
			break;
		case SceneID::SCENE_EDIT:
			m_pScene = new CMapEditor;
			break;
		case SceneID::SCENE_STAGE:
			m_pScene = new CStage;
			break;
		case SceneID::SCENE_STAGE2:
			m_pScene = new CStage2;
			break;
		case SceneID::SCENE_STAGE3:
			m_pScene = new CStage3;
			break;
		case SceneID::SCENE_END:
			m_pScene = new CLastScene;
			break;
		default:
			break;
		}

		m_pScene->Initialize();

		m_eCurScene = m_eNextScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	if (m_pScene)
	{
		delete m_pScene;
		m_pScene = nullptr;
	}
}
