#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_h

#include "Level.h"
#include "GameLog.h"
#include "Player.h"
#include "ObjectFactory.h"
#include "Camera.h"

namespace Kaotic_Alpha
{
	class LevelManager
	{
	public:
		LevelManager(sf::RenderWindow* appRef)
			: m_AppRef(appRef)
		{			
			m_CurrentLevel = NULL;
			m_CurrentLevelNum = NULL;
			m_Player = NULL;
			m_Camera = NULL;
		}

		void Startup()
		{
			m_Camera = new Camera();
			m_Camera->SetSize(static_cast<float>(m_AppRef->GetWidth()), static_cast<float>(m_AppRef->GetHeight()));

			//might want to parse an xml file to get this info
			m_NumLevels = 5;
			m_Player = ObjectFactory::GetSingleton()->CreateObject(m_AppRef, "Player");
			m_Player->Startup();
			m_Camera->FollowTarget(m_Player);
		}

		void LoadLevel(int levelNum)
		{
			if(m_CurrentLevel == NULL){
				if(levelNum <= m_NumLevels && levelNum > 0){
					m_CurrentLevelNum = levelNum;
					WriteLog << "Loading level " << levelNum << std::endl;
					m_CurrentLevel = new Level(levelNum, m_AppRef);
					m_CurrentLevel->Startup();
				}
				else{
					WriteLog << "ERROR: Level " << levelNum << " does not exist." << std::endl;
				}
			}
			else{
				WriteLog << "ERROR: already have an active level. Shut down current level before loading another." << std::endl;
			}
		}

		//not sure this will need to be implemented yet
		void LoadPreviousLevel()
		{
			LoadLevel(--m_CurrentLevelNum);
		}
		//not sure this will need to be implemented yet
		void LoadNextLevel()
		{
			LoadLevel(++m_CurrentLevelNum);
		}

		void ShutdownCurrentLevel()
		{
			if(m_CurrentLevel != NULL)
			{
				m_CurrentLevel->Shutdown();
				delete m_CurrentLevel;
				m_CurrentLevel = NULL;
			}
		}

		void Update(float deltaTime)
		{
			if(m_CurrentLevel != NULL){
				//update camera
				m_Camera->Update(deltaTime);
				//update level components
				m_CurrentLevel->Update(deltaTime, m_Camera, m_Player);
			}
		}

		void Shutdown()
		{
			ShutdownCurrentLevel();
			if(m_Player != NULL){
				m_Player->Shutdown();
				ObjectFactory::GetSingleton()->DestroyObject(m_Player);
				m_Player = NULL;
			}

			if(m_Camera != NULL){
				delete m_Camera;
				m_Camera = NULL;
			}
		}

		int GetCurrentLevelNum() const { return m_CurrentLevelNum; }

	private:
		sf::RenderWindow*	m_AppRef;
		GameObject*			m_Player;
		Level*				m_CurrentLevel;
		Camera*				m_Camera;
		int					m_CurrentLevelNum;
		int					m_NumLevels;

	};
}
#endif