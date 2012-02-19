#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include <SFML/Graphics.hpp>

namespace Kaotic_Alpha
{
	class GameMessage;

	class Player
		: public Kaotic_Alpha::GameObject
	{
	public:
		Player(sf::RenderWindow* app, int uid);
		void Startup();
		void Update(float deltaTime);
		void Shutdown();
		GameMessage* ProcessMessage(GameMessage* msg);

	private:
		bool m_Jumping;
	};
}

#endif