#ifndef GUITEXT_H
#define GUITEXT_H

#include "GUIElement.h"
#include "Vector2.h"

namespace Kaotic_Alpha
{
	class GUIText
		: public GUIElement
	{
	public:
		GUIText(sf::RenderWindow* appRef, std::string text, sf::Color color, float offsetX=0, float offsetY=0)
			: GUIElement(appRef)
		{
			m_Position = Vector2(offsetX,offsetY);
			m_Text.SetText(text);
			m_Text.SetPosition(offsetX, offsetY);
			m_Text.SetColor(color);

			if (m_Font.LoadFromFile("../../media/fonts/Avanti.ttf", 30)){
				m_Text.SetFont(m_Font);
			}
		}
		virtual ~GUIText()
		{}
		void Update(float deltaTime)
		{}		
		void Render() 
		{
			m_AppRef->Draw(m_Text);
		}
		void SetText(std::string text)
		{
			m_Text.SetText(text);
		}

	private:
		Vector2				m_Position;
		sf::String			m_Text;
		sf::Font			m_Font;
	};
}

#endif