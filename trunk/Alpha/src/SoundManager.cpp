#include "SoundManager.h"
#include "GameLog.h"

Kaotic_Alpha::SoundManager* Kaotic_Alpha::SoundManager::p_Instance = NULL;

Kaotic_Alpha::SoundManager* Kaotic_Alpha::SoundManager::GetSingleton()
{
  if(p_Instance == NULL){
    p_Instance = new SoundManager();
  }
  return p_Instance;
}

void Kaotic_Alpha::SoundManager::PlaySoundFX(std::string filename)
{
	unsigned int SampleRate = m_Buffer.GetSampleRate();
	unsigned int Channels   = m_Buffer.GetChannelsCount();

	if(!m_Buffer.LoadFromFile(filename))
	{
		WriteLog << "Could not play Sound Effect(\"" << filename << "\")" << std::endl;
		return;
	}

	m_Sound.SetBuffer(m_Buffer); 
	m_Sound.Play();
}

//stop current music
void Kaotic_Alpha::SoundManager::StopMusic()
{
	m_Music.Stop();
}

//do not start new music unless previous music has been stopped
void Kaotic_Alpha::SoundManager::PlayMusic(std::string filename)
{
	if(m_Music.GetStatus() != sf::Music::Playing)
	{
		std::string filepath = "../../media/music/" + filename;
		if (!m_Music.OpenFromFile(filepath))
		{
			WriteLog << "Could not play Music(\"" << filename << "\")" << std::endl;
			return;
		}

		m_Music.OpenFromFile(filepath);
		m_Music.Play();
	}
}

void Kaotic_Alpha::SoundManager::Shutdown()
{
	delete p_Instance;
	p_Instance = NULL;
}

void Kaotic_Alpha::SoundManager::Startup()
{

}