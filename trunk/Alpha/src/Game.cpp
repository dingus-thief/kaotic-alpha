#include "Game.h"
#include "GameLog.h"
#include "Player.h"

#include <SFML/System.hpp>

//singletons
#include "ObjectFactory.h"
#include "GUIManager.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "Timer.h"

const int FPS = 30;

void Kaotic_Alpha::Game::Startup()
{
	m_App = new sf::RenderWindow(sf::VideoMode(1280, 720, 32), "SFML Test");
}

void Kaotic_Alpha::Game::Shutdown()
{
	delete m_App;
	
	//shut down singletons to avoid memory leaks
	Kaotic_Alpha::ObjectFactory::GetSingleton()->Shutdown();
	Kaotic_Alpha::GUIManager::GetSingleton()->Shutdown();
	Kaotic_Alpha::SoundManager::GetSingleton()->Shutdown();
	Kaotic_Alpha::ImageManager::GetSingleton()->Shutdown();
}

void Kaotic_Alpha::Game::Run()
{
	Kaotic_Alpha::Timer timer;
	timer.Start();

	//set window BG
	sf::Sprite Sprite;
	Sprite.SetColor(sf::Color(255, 255, 255, 255));
	Sprite.SetImage(ImageManager::GetSingleton()->GetImage("bg-panorama.jpg"));

	Kaotic_Alpha::Player* player = new Kaotic_Alpha::Player(m_App);
	player->Startup();

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
		//1. Gather Input
		//2. Update Components
		player->Update();
		//3. Render Scene
		m_App->Display();
	}

	player->Shutdown();
}