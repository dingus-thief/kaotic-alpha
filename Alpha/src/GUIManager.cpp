#include "GUIManager.h"
#include "GameLog.h"

Kaotic_Alpha::GUIManager* Kaotic_Alpha::GUIManager::pInstance = NULL;

void Kaotic_Alpha::GUIManager::Shutdown()
{
	ClearScreens();
	delete pInstance;
	pInstance = NULL;
}

Kaotic_Alpha::GUIManager* Kaotic_Alpha::GUIManager::GetSingleton()
{
  if(pInstance == NULL){
    pInstance = new GUIManager();
  }
  return pInstance;
}

void Kaotic_Alpha::GUIManager::ClearScreens()
{
	for(std::vector<Kaotic_Alpha::GUIScreen*>::iterator it = m_Screens.begin(); it != m_Screens.end(); ++it){
		(*it)->Shutdown();
		delete *it;
	}
	m_Screens.clear();
}

void Kaotic_Alpha::GUIManager::PushScreen(GUIScreen* newScreen)
{
	newScreen->Startup();
	m_Screens.push_back(newScreen);
}

void Kaotic_Alpha::GUIManager::PopScreen()
{
	if(m_Screens.size() > 0){
		m_Screens.at(m_Screens.size()-1)->Shutdown();
		WriteLog << "Deleting " << m_Screens.at(m_Screens.size()-1)->GetName() << std::endl;
		delete m_Screens.at(m_Screens.size()-1);
		m_Screens.pop_back();
	}
}

void Kaotic_Alpha::GUIManager::UpdateScreens(float deltaTime)
{
	for(std::vector<Kaotic_Alpha::GUIScreen*>::iterator it = m_Screens.begin(); it != m_Screens.end(); ++it){
		if(it == m_Screens.end()-1){
			(*it)->Update(deltaTime);
		}

		(*it)->Render();
	}
}

void  Kaotic_Alpha::GUIManager::Debug_PrintScreenStack()
{
	WriteLog << "Screens" << std::endl;
	WriteLog << "-------------------" << std::endl;
	for(std::vector<Kaotic_Alpha::GUIScreen*>::iterator it = m_Screens.begin(); it != m_Screens.end(); ++it){
		WriteLog << (*it)->GetName() << std::endl;
	}
	WriteLog << std::endl;
}