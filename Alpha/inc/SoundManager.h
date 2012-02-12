#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <string>

namespace Kaotic_Alpha
{
	class SoundManager
	{
	public:
		static Kaotic_Alpha::SoundManager* GetSingleton();
		void PlaySoundFX(std::string filename);
		void PlayMusic(std::string filename);
		void Shutdown();

	private:
		SoundManager(){}
		static Kaotic_Alpha::SoundManager* pInstance;
	};
}

#endif