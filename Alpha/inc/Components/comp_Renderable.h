#ifndef COMP_RENDERABLE
#define COMP_RENDERABLE

#include "Components/Component.h"
#include "GameLog.h"
#include "Vector2.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace Kaotic_Alpha
{
	class Comp_Renderable
		: public Component
	{
	public:
		Comp_Renderable(sf::RenderWindow* app)
			: m_AppRef(app)
		{}

		void Update()
		{
		}
		void AddSprite(sf::Sprite sprite)
		{
			m_Sprites.push_back(sprite);
		}
		void Render()
		{
			for(std::vector<sf::Sprite>::iterator it = m_Sprites.begin(); it != m_Sprites.end(); ++it){
				sf::Sprite sprite = (*it);
				m_AppRef->Draw(sprite);
			}
			m_Sprites.clear();
		}

	private:
		sf::RenderWindow*		m_AppRef;
		std::vector<sf::Sprite>	m_Sprites;
	};
}

#endif