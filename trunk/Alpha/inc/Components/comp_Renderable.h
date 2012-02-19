#ifndef COMP_RENDERABLE
#define COMP_RENDERABLE

#include <SFML/Graphics.hpp>
#include <vector>
 
#include "GameLog.h"
#include "Vector2.h"
#include "Components/Component.h"
#include "Camera.h"

namespace Kaotic_Alpha
{
	class Comp_Renderable
		: public Component
	{
	public:
		Comp_Renderable(sf::RenderWindow* app)
			: m_AppRef(app)
		{}

		void Update(float deltaTime)
		{
		}
		void AddSprite(sf::Sprite sprite)
		{
			m_Sprites.push_back(sprite);
		}
		void Render(Camera* camera)
		{
			for(std::vector<sf::Sprite>::iterator it = m_Sprites.begin(); it != m_Sprites.end(); ++it){
				sf::Sprite sprite = (*it);
				//translate sprites position from world space to local space
				Kaotic_Alpha::Vector2 pos(sprite.GetPosition().x, sprite.GetPosition().y);
				pos = camera->TranslateWorldCoordsToLocal(pos);
				sprite.SetPosition(pos.X, pos.Y);
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