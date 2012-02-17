#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <string>
#include <SFML/Audio.hpp>

namespace Kaotic_Alpha
{
	class SoundManager
	{
	public:
		static Kaotic_Alpha::SoundManager* GetSingleton();
		void PlaySoundFX(std::string filename);
		void PlayMusic(std::string filename);
		void StopMusic();
		void Startup();
		void Shutdown();

	private:
		sf::Sound		m_Sound;
		sf::SoundBuffer m_Buffer;
		sf::Music		m_Music;  

		SoundManager(){}
		static Kaotic_Alpha::SoundManager* p_Instance;
	};
}

#endif