#include "Game.h"
#include "GameMessage.h"
#include "LevelManager.h"
#include "GameLog.h"
#include <SFML/System.hpp>

//singletons
#include "ObjectFactory.h"
#include "GUIManager.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "CollisionManager.h"
#include "MessageSystem.h"
#include "Camera.h"

void Kaotic_Alpha::Game::Startup()
{
	int height = 720;
	int width = 1280;
	m_App = new sf::RenderWindow(sf::VideoMode(width, height, 32), "2D Platformer");
	MessageSystem::GetSingleton()->AddListener(this);
	m_GameState = MAINMENU;
}

void Kaotic_Alpha::Game::Shutdown()
{
	//shut down singletons to avoid memory leaks
	ObjectFactory::GetSingleton()->Shutdown();
	GUIManager::GetSingleton()->Shutdown();
	SoundManager::GetSingleton()->Shutdown();
	ImageManager::GetSingleton()->Shutdown();
	MessageSystem::GetSingleton()->Shutdown();
	CollisionManager::GetSingleton()->Shutdown();

	delete m_App;
}

void Kaotic_Alpha::Game::Run()
{
	m_LevelManager = new LevelManager(m_App);
	ChangeState(m_GameState);
	
	while(m_IsRunning && m_App->IsOpened())
	{	
		// Process events
        sf::Event Event;
        while (m_App->GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                m_App->Close();       
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
			{
				if(m_GameState == MAINMENU)
					m_App->Close();
				if(m_GameState == PLAYLEVEL)
					ChangeState(QUITLEVEL);
			}
        }

		m_App->Clear();
		if(m_GameState == PLAYLEVEL){
			m_LevelManager->Update(m_App->GetFrameTime());
		}
		MessageSystem::GetSingleton()->Update(m_App->GetFrameTime());
		GUIManager::GetSingleton()->UpdateScreens(m_App->GetFrameTime());
		m_App->Display();

		float fps = 1.f / m_App->GetFrameTime();
	}
	
	m_LevelManager->Shutdown();
}

Kaotic_Alpha::GameMessage* 	Kaotic_Alpha::Game::ProcessMessage(GameMessage* msg)
{
	if(msg->MsgType == GameMessage::STATECHANGE){
		ChangeState(msg->TargetState);
	}
	return NULL;
}

void Kaotic_Alpha::Game::ChangeState(GAMESTATE newState)
{
	m_GameState = newState;

	switch(newState)
	{
	case MAINMENU:
			GUIManager::GetSingleton()->PushScreen(new Kaotic_Alpha::Screen_MainMenu("Main Menu", m_App));
		break;
	case LOADLEVEL:
			GUIManager::GetSingleton()->PopScreen();
			m_LevelManager->Startup();
			m_LevelManager->LoadLevel(2);
			ChangeState(PLAYLEVEL);
		break;
	case PLAYLEVEL:
		break;
	case UNLOADLEVEL:
		m_LevelManager->ShutdownCurrentLevel();
		break;
	case QUITLEVEL:
		m_LevelManager->Shutdown();
		ChangeState(MAINMENU);
		break;
	default:
		break;
	}
}