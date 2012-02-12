#include "SoundManager.h"
#include "GameLog.h"

Kaotic_Alpha::SoundManager* Kaotic_Alpha::SoundManager::pInstance = NULL;

Kaotic_Alpha::SoundManager* Kaotic_Alpha::SoundManager::GetSingleton()
{
  if(pInstance == NULL){
    pInstance = new SoundManager();
  }
  return pInstance;
}

void Kaotic_Alpha::SoundManager::PlaySoundFX(std::string filename)
{
	try{}
	catch(...)
	{
		WriteLog << "Could not play Sound Effect(\"" << filename << "\")" << std::endl;
	}
}

void Kaotic_Alpha::SoundManager::PlayMusic(std::string filename)
{
	try{}
	catch(...)
	{
		WriteLog << "Could not play Music(\"" << filename << "\")" << std::endl;
	}
}

void Kaotic_Alpha::SoundManager::Shutdown()
{
	delete pInstance;
	pInstance = NULL;
}
