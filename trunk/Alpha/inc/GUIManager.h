#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <vector>
#include "GUIScreen.h"

/*
	GUIManager contains a vector of gui screens which acts as a stack of screens
	A new screen can be pushed to the top of the stack or the top screen can be popped from the stack.
	If stack needs to be cleared, just call ClearScreens() method
*/

namespace Kaotic_Alpha
{
	class GUIManager
	{
	public:
		void PushScreen(Kaotic_Alpha::GUIScreen* newScreen);
		void PopScreen();
		void ClearScreens();
		void UpdateScreens(float deltaTime);

		static Kaotic_Alpha::GUIManager* GetSingleton();
		void Shutdown();

	private:
		GUIManager(){}
		std::vector<Kaotic_Alpha::GUIScreen*> m_Screens;
		static Kaotic_Alpha::GUIManager* pInstance;
	};
}

#endif