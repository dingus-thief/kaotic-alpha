#ifndef SCREEN_MAIN_MENU_H
#define SCREEN_MAIN_MENU_H

#include "GUIButton.h"
#include "GUIScreen.h"
#include "GUIImage.h"

namespace Kaotic_Alpha
{
	class Screen_MainMenu
		: public GUIScreen
	{
	public:
		void Startup()
		{
			m_GUIElements.push_back(new GUIImage(m_AppRef, "MainMenuBG.png"));
			m_GUIElements.push_back(new GUIButton(m_AppRef, "Play", 60, 550));
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