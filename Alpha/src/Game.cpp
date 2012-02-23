#include "Game.h"
#include "GameMessage.h"
#include "LevelManager.h"
#include "GameLog.h"

#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

//singletons
#include "ObjectFactory.h"
#include "GUIManager.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "MessageSystem.h"
#include "PhysicsWorld.h"
#include "Camera.h"

const int velocityIterations = 6;
const int positionIterations = 2;

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
	PhysicsWorld::GetSingleton()->Shutdown();

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
			//temp code to add and subtract lives
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::N))
			{
				static float timer = 0;
				if(timer >= 0){
					m_LevelManager->GetPlayer()->GetHealthComponent()->RemoveLife();
					timer = 100;
				}
				else
					timer -= m_App->GetFrameTime();
			}
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::M))
			{
				static float timer2 = 0;
				if(timer2 >= 0){
					m_LevelManager->GetPlayer()->GetHealthComponent()->AddLife();
					timer2 = 100;
				}
				else
					timer2 -= m_App->GetFrameTime();
			}
        }

		m_App->Clear();
		if(m_GameState == PLAYLEVEL){
			//update physics
			PhysicsWorld::GetSingleton()->GetPhysicsWorld()->Step(m_App->GetFrameTime(), velocityIterations, positionIterations);
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
		GUIManager::GetSingleton()->PushScreen(new Kaotic_Alpha::Screen_Loading("Loading", m_App));
			//force GUI update and render in order to display screen before level is loaded		
			m_App->Clear();
			GUIManager::GetSingleton()->UpdateScreens(m_App->GetFrameTime()); 
			m_App->Display();
		m_LevelManager->Startup();
		m_LevelManager->LoadLevel(2);
		std::cout << "Loaded" << std::endl;
		ChangeState(PLAYLEVEL);
		break;
	case PLAYLEVEL:
		GUIManager::GetSingleton()->PopScreen();
		GUIManager::GetSingleton()->PushScreen(new Kaotic_Alpha::Screen_HUD("HUD", m_App, m_LevelManager->GetPlayer()));
		m_App->Clear();
		break;
	case UNLOADLEVEL:
		GUIManager::GetSingleton()->PopScreen();
		m_LevelManager->ShutdownCurrentLevel();
		break;
	case QUITLEVEL:
		GUIManager::GetSingleton()->PopScreen();
		m_LevelManager->Shutdown();
		ChangeState(MAINMENU);
		break;
	case QUIT:
		m_App->Close();
		break;
	default:
		break;
	}
}