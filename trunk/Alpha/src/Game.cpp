#include "Game.h"
#include "GameLog.h"
#include "Player.h"
#include "LevelFloor.h"

#include <SFML/System.hpp>

//singletons
#include "ObjectFactory.h"
#include "GUIManager.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "CollisionManager.h"
#include "MessageSystem.h"

#include "GameMessage.h"

const int FPS = 30;

void Kaotic_Alpha::Game::Startup()
{
	m_App = new sf::RenderWindow(sf::VideoMode(1280, 720, 32), "SFML Test");
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
	//set window BG
	sf::Sprite Sprite;
	Sprite.SetColor(sf::Color(255, 255, 255, 255));
	Sprite.SetImage(ImageManager::GetSingleton()->GetImage("bg-panorama.jpg"));

	Player* player = new Kaotic_Alpha::Player(m_App, 1);
	player->Startup();
	player->GetMovableComponent()->SetPositionY(0);
	LevelFloor* floor = new LevelFloor(m_App, 3);
	floor->Startup();

	SoundManager::GetSingleton()->PlayMusic("../../media/music/TellItByHeart.ogg");

	while(m_IsRunning && m_App->IsOpened())
	{	
		// Process events
        sf::Event Event;
        while (m_App->GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                m_App->Close();       
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				m_App->Close();
        }

		m_App->Clear();
		m_App->Draw(Sprite);
		//execute game loop
		//1. Process messages
		MessageSystem::GetSingleton()->Update(m_App->GetFrameTime());
		//2. Update Components
		player->Update(m_App->GetFrameTime());
		player->UpdateMovement(m_App->GetFrameTime());
		player->Render(m_App->GetFrameTime());
		//3. Render Scene
		m_App->Display();

		float fps = 1.f / m_App->GetFrameTime();
		std::cout << fps << std::endl;
	}

	player->Shutdown();
	floor->Shutdown();
}