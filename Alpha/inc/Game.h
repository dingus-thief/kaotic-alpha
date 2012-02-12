#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

namespace Kaotic_Alpha
{
	class Game
	{
	public:
		Game()
			: m_IsRunning(true)
		{}
		~Game(){}

		void Startup();
		void Shutdown();
		void Run();

	private:
		bool m_IsRunning;
		sf::RenderWindow* m_App;
	};
}

#endif