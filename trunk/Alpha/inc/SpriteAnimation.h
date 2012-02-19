#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "XMLParser.h"

namespace Kaotic_Alpha
{
	//Animation that an animated sprite can use
	class SpriteAnimation
	{
	public:
		SpriteAnimation(std::string animName)
			: m_Name(animName)
		{
			LoadAnimation();
		}

		//load the animation in the form of a sprite sheet and create the clips for it
		void LoadAnimation()
		{
			m_Sprite = new sf::Sprite(ImageManager::GetSingleton()->GetImage(m_Name));
			SetClips();
			m_NumFrames = m_Clips.size();
		}

		//load the clips from an XML file, this file is the same as the image name, but remove the extension and an xml extension
		void SetClips(){
			std::string truncname;
			truncname = m_Name.substr(0, m_Name.find_last_of("."));
			truncname = "../../media/" + truncname + ".xml";
			XMLParser parser(truncname.c_str());
			
			TiXmlElement* spriteNode = parser.SearchForElement(parser.getXmlRootNode(), "sprite");
			while(spriteNode != 0){	
				int x1 = atoi(spriteNode->Attribute("x"));
				int x2 = x1 + atoi(spriteNode->Attribute("w"));
				int y1 = atoi(spriteNode->Attribute("y"));
				int y2 = y1 + atoi(spriteNode->Attribute("h"));
				m_Clips.push_back(sf::IntRect(x1, y1, x2, y2));
				spriteNode = spriteNode->NextSiblingElement();
			}
		}		

		//based on the frame of the animation, return a sprite with just that clip
		sf::Sprite* GetSprite(int frame)  
		{ 
			m_Sprite->SetSubRect(m_Clips[frame]);
			return m_Sprite;
		}

		int GetNumFrames() const { return m_NumFrames; }

		std::string m_Name;

	private:
		int m_NumFrames;
		std::vector<sf::IntRect> m_Clips;
		sf::Sprite* m_Sprite;
	};
}
#endif