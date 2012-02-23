#ifndef SCREEN_LOADING_H
#define SCREEN_LOADING_H

#include "GUIScreen.h"
#include "GUIImage.h"

namespace Kaotic_Alpha
{
	class Screen_Loading
		: public GUIScreen
	{
	public:
		void Startup()
		{
			m_GUIElements.push_back(new GUIImage(m_AppRef, "loading.png"));
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

		Screen_Loading(std::string name, sf::RenderWindow* appRef)
			: GUIScreen(name, appRef)
		{}
		virtual ~Screen_Loading(){}

	private:
	};
}

#endif