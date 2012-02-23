#ifndef GUISCREEN_H
#define GUISCREEN_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Vector2.h"

#include "GUIElement.h"

namespace Kaotic_Alpha
{
	class GUIScreen
	{
	public:	
		GUIScreen(std::string name, sf::RenderWindow* appRef)
			: m_AppRef(appRef)
		{
			m_Name = name;
		}
		virtual ~GUIScreen(){}

		virtual void Startup(){}
		virtual void Update(float deltaTime){}
		virtual void Render(){}
		virtual void Shutdown(){}

		std::string GetName() const { return m_Name; }

	protected:	
		std::string					m_Name;
		sf::RenderWindow*			m_AppRef;
		Vector2						m_Size;
		Vector2						m_Position;
		sf::Sprite*					m_BackgroundImage;
		std::vector<GUIElement*>	m_GUIElements;

	};
}

#endif