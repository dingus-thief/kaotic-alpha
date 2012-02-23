#ifndef SCREEN_HUD_H
#define SCREEN_HUD_H

#include "GUIScreen.h"
#include "GUIImage.h"
#include "GUIText.h"
#include "GameObject.h"

const int MAX_LIVES_DISPLAYED = 5;

namespace Kaotic_Alpha
{
	class Screen_HUD
		: public GUIScreen
	{
	public:		
		void Startup()
		{
			m_NumLivesDisplayed = 0;
			m_LivesString = "";
		}
		
		void Update(float deltaTime)
		{
			unsigned int lives = m_PlayerRef->GetHealthComponent()->GetCurrentLives();

			//only display up to maximum number of lives as icons, otherwise use numbers
			if(lives < MAX_LIVES_DISPLAYED){
		
				//currently text on the screen, but we want to use icons, clear text from screen
				if(m_LivesString != ""){
					ClearGUIElements();
				}

				//need to add life icons
				if(m_NumLivesDisplayed < lives){
					for(unsigned int i = m_NumLivesDisplayed; i < lives; ++i){
						m_GUIElements.push_back(new GUIImage(m_AppRef, "life.png", (50.0f+35.0f*i), 50.0f));
						++m_NumLivesDisplayed;
					}
				}
				//need to remove life icons
				else if(m_NumLivesDisplayed > lives){
					delete m_GUIElements.at(m_GUIElements.size()-1);
					m_GUIElements.pop_back();
					--m_NumLivesDisplayed;
				}
			}
			//more than 5 lives, so display 1 icon + text
			else{
				//multiple lives displaying, removing from HUD
				if(m_NumLivesDisplayed > 1){
					ClearGUIElements();
					m_GUIElements.push_back(new GUIImage(m_AppRef, "life.png", 50, 50));
					m_LivesString = "x ";
					char buffer[33];
					_itoa_s(lives, buffer, 10);
					m_LivesString += buffer;
					m_GUIElements.push_back(new GUIText(m_AppRef, m_LivesString, sf::Color(255, 255, 255), 90, 60));
					m_NumLivesDisplayed = 1;
				}
				//only 1 life displaying, check if the text is correct
				else{
					std::string text = "x ";
					char buffer[33];
					_itoa_s(lives, buffer, 10);
					text += buffer;	

					if(m_LivesString == ""){
						m_LivesString = text;
						m_GUIElements.push_back(new GUIImage(m_AppRef, "life.png", 50, 50));
						m_GUIElements.push_back(new GUIText(m_AppRef, m_LivesString, sf::Color(255, 255, 255), 90, 60));
						m_NumLivesDisplayed = 1;
					}
					else if(m_LivesString != text){
						m_LivesString = text;
						m_GUIElements.pop_back();
						m_GUIElements.push_back(new GUIText(m_AppRef, m_LivesString, sf::Color(255, 255, 255), 90, 60));
					}
				}
			}

			for(std::vector<GUIElement*>::iterator it = m_GUIElements.begin(); it != m_GUIElements.end(); ++it){
				(*it)->Update(deltaTime);
			}
		}				
		
		void Render()
		{
			for(std::vector<GUIElement*>::iterator it = m_GUIElements.begin(); it != m_GUIElements.end(); ++it){
				(*it)->Render();
			}
		}
		
		void Shutdown()
		{
			for(std::vector<GUIElement*>::iterator it = m_GUIElements.begin(); it != m_GUIElements.end(); ++it){
				delete *it;
			}
			m_GUIElements.clear();
		}	

		Screen_HUD(std::string name, sf::RenderWindow* appRef, GameObject* player)
			: GUIScreen(name, appRef), m_PlayerRef(player)
		{}

	private:
		void ClearGUIElements()
		{
			m_LivesString = "";
			m_NumLivesDisplayed = 0;

			for(std::vector<GUIElement*>::iterator it = m_GUIElements.begin(); it != m_GUIElements.begin(); ++it){
				delete *it;
			}
			m_GUIElements.clear();
		}

		std::string		m_LivesString;
		unsigned int	m_NumLivesDisplayed;
		GameObject*		m_PlayerRef;
	};
}

#endif