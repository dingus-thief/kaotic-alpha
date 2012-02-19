#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include "Vector2.h"
#include "GUIElement.h"
#include "MessageSystem.h"
#include "Game.h"

namespace Kaotic_Alpha
{
	class GUIButton
		: public GUIElement
	{
	public:
		GUIButton(sf::RenderWindow* appRef, std::string text, float offsetX, float offsetY)
			: GUIElement(appRef)
		{
			m_Pressed = false;
			m_Position = Vector2(offsetX,offsetY);
			m_Text.SetText(text);
			m_Text.Move(m_Position.X, m_Position.Y);
			m_Text.SetColor(sf::Color(255, 255, 255));
			m_Dimensions = Vector2(m_Text.GetRect().GetWidth(), m_Text.GetRect().GetHeight());
		}
		virtual ~GUIButton()
		{
		}
		void Update(float deltaTime)
		{
			int mouseX = m_AppRef->GetInput().GetMouseX();
			int mouseY = m_AppRef->GetInput().GetMouseY();
			m_ButtonBounds = sf::FloatRect(m_Position.X, m_Position.Y, (m_Position.X + m_Dimensions.X), (m_Position.Y + m_Dimensions.Y));
			if(m_ButtonBounds.Contains(static_cast<float>(mouseX), static_cast<float>(mouseY))){
				OnActive();
			}
			else{
				m_Text.SetColor(sf::Color(255, 255, 255));
			}
		}

		bool IsPressed() const { return m_Pressed; }
		void Render() 
		{
			m_AppRef->Draw(m_Text);
		}

	protected:
		void OnPress()
		{
			if(!m_Pressed){
				GameMessage* msg = new GameMessage(GameMessage::STATECHANGE);
				msg->TargetState = GAMESTATE::LOADLEVEL;
				MessageSystem::GetSingleton()->QueueMessage(msg);
			}
			m_Pressed = true;
		}

		void OnActive()
		{
			m_Text.SetColor(sf::Color(125, 125, 125));
			m_Active = true;
			if(m_AppRef->GetInput().IsMouseButtonDown(sf::Mouse::Button::Left))
			{
				m_Text.SetColor(sf::Color(75, 75, 75));
				OnPress();
			}
		}

		sf::String			m_Text;

		sf::FloatRect		m_ButtonBounds;
		Vector2				m_Dimensions;
		Vector2				m_Position;
		bool				m_Pressed;
		bool				m_Active;
	};
}

#endif