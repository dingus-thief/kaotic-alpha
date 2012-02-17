#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "GameLog.h"

namespace Kaotic_Alpha
{
	class ImageManager
	{
	public:
		sf::Image& GetImage(std::string filename);
		static Kaotic_Alpha::ImageManager* GetSingleton();
		void Shutdown();
		void DestroyAllImages();
		void DestroyImage(std::string filename);

	private:
		ImageManager(){}
		std::map<std::string, sf::Image*> m_ImageMap;
		static Kaotic_Alpha::ImageManager* p_Instance;
	};
}

#endif