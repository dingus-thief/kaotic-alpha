#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include "Vector2.h"
#include "GUIElement.h"
#include "MessageSystem.h"
#include "ImageManager.h"

namespace Kaotic_Alpha
{
	class GUIButton
		: public GUIElement
	{
	public:
		GUIButton(sf::RenderWindow* appRef, std::string filename, float offsetX, float offsetY, GameMessage* sentMessage)
			: GUIElement(appRef), m_SentMessage(sentMessage)
		{
			m_Pressed = false;
			m_Position = Vector2(offsetX,offsetY);
			m_BGImage = ImageManager::GetSingleton()->GetImage(filename);
			m_CurrentSprite = sf::Sprite();
			m_CurrentSprite.SetPosition(m_Position.X, m_Position.Y);
			m_CurrentSprite.SetImage(m_BGImage);
			m_Dimensions = Vector2(static_cast<float>(m_BGImage.GetWidth()), static_cast<float>(m_BGImage.GetHeight()));
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
				m_CurrentSprite.SetColor(sf::Color(255, 255, 255));
			}
		}

		bool IsPressed() const { return m_Pressed; }
		void Render() 
		{
			m_AppRef->Draw(m_CurrentSprite);
		}

	protected:
		void OnPress()
		{
			if(!m_Pressed){
				MessageSystem::GetSingleton()->QueueMessage(m_SentMessage);
			}
			m_Pressed = true;
		}

		void OnActive()
		{
			m_Active = true;
			m_CurrentSprite.SetColor(sf::Color(255, 195, 0));
			if(m_AppRef->GetInput().IsMouseButtonDown(sf::Mouse::Button::Left))
			{
				m_CurrentSprite.SetColor(sf::Color(75, 75, 75));
				OnPress();
			}
		}

		GameMessage*		m_SentMessage;
		sf::Image			m_BGImage;
		sf::Sprite			m_CurrentSprite;

		sf::FloatRect		m_ButtonBounds;
		Vector2				m_Dimensions;
		Vector2				m_Position;
		bool				m_Pressed;
		bool				m_Active;
	};
}

#endif