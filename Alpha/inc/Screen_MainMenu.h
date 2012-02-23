#ifndef SCREEN_MAIN_MENU_H
#define SCREEN_MAIN_MENU_H

#include "GUIScreen.h"
#include "GUIButton.h"
#include "GUIImage.h"
#include "GameMessage.h"
#include "SoundManager.h"
#include "Game.h"

namespace Kaotic_Alpha
{
	class Screen_MainMenu
		: public GUIScreen
	{
	public:
		void Startup()
		{
			SoundManager::GetSingleton()->PlayMusic("Maenam.ogg");

			GameMessage* msgPlay = new GameMessage(GameMessage::STATECHANGE);
			msgPlay->TargetState = LOADLEVEL;
			GameMessage* msgQuit = new GameMessage(GameMessage::STATECHANGE);
			msgQuit->TargetState = QUIT;

			m_GUIElements.push_back(new GUIImage(m_AppRef, "MainMenuBG.png"));
			m_GUIElements.push_back(new GUIButton(m_AppRef, "btn_Play.png", 230, 360, msgPlay));
			m_GUIElements.push_back(new GUIButton(m_AppRef, "btn_Options.png", 230, 410, NULL));
			m_GUIElements.push_back(new GUIButton(m_AppRef, "btn_Quit.png", 230, 460, msgQuit));
		}
		void Update(float deltaTime)
		{
			for(std::vector<GUIElement*>::iterator it = m_GUIElements.begin(); it != m_GUIElements.end(); ++it){
				(*it)->Update(deltaTime);
			}
		}
		void Shutdown()
		{
			for(std::vector<GUIElement*>::iterator it = m_GUIElements.begin(); it != m_GUIElements.end(); ++it){
				delete *it;
			}
			m_GUIElements.clear();
		}
		void Render()
		{
			for(std::vector<GUIElement*>::iterator it = m_GUIElements.begin(); it != m_GUIElements.end(); ++it){
				(*it)->Render();
			}
		}

		Screen_MainMenu(std::string name, sf::RenderWindow* appRef)
			: GUIScreen(name, appRef)
		{}
		virtual ~Screen_MainMenu(){}

	private:
	};
}
#endif