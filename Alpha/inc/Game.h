#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "MessageListener.h"

namespace Kaotic_Alpha
{
	class GameMessage;
	class LevelManager;

	enum GAMESTATE
	{
		MAINMENU = 0,
		LOADLEVEL = 1,
		PLAYLEVEL = 2,
		UNLOADLEVEL = 3,
		QUITLEVEL = 4,
	};

	class Game
		: public MessageListener
	{
	public:
		Game()
			: m_IsRunning(true)
		{}
		~Game(){}

		void Startup();
		void Shutdown();
		void Run();
		void ChangeState(GAMESTATE newState);
		GameMessage* ProcessMessage(GameMessage* msg);

	private:
		bool m_IsRunning;
		sf::RenderWindow*	m_App;
		LevelManager*		m_LevelManager;
		GAMESTATE			m_GameState;
	};
}

#endif