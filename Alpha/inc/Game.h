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
		MAINMENU,
		LOADLEVEL,
		PLAYLEVEL,
		UNLOADLEVEL,
		QUITLEVEL,
		QUIT
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