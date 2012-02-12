#ifndef COMP_ANIMATION_H
#define COMP_ANIMATION_H

#include <SFML/Graphics.hpp>
#include "Components/Component.h"
#include "Components/comp_renderable.h"
#include "AnimatedSprite.h"
#include <vector>

namespace Kaotic_Alpha
{
	class Comp_Animation
		: public Kaotic_Alpha::Component
	{
	public:
		Comp_Animation(Kaotic_Alpha::Comp_Renderable* renderable)
			: m_comp_RenderableRef(renderable)
		{}
		~Comp_Animation()
		{
			ClearAnimatedSprites();
		}

		//add sprite to sprite list
		void AddAnimatedSprite(Kaotic_Alpha::AnimatedSprite* sprite){
			m_Sprites.push_back(sprite);
		}
		
		//erase sprite from sprite list
		void RemoveAnimatedSprite(Kaotic_Alpha::AnimatedSprite* sprite)
		{
			for(std::vector<Kaotic_Alpha::AnimatedSprite*>::iterator it = m_Sprites.begin(); it != m_Sprites.end(); ++it)
			{
				if((*it) == sprite)
				{
					delete *it;
					m_Sprites.erase(it);
					break;
				}
			}
		}

		void ClearAnimatedSprites()
		{
			for(std::vector<Kaotic_Alpha::AnimatedSprite*>::iterator it = m_Sprites.begin(); it != m_Sprites.end(); ++it){
				delete *it;
			}
			m_Sprites.clear();
		}

		//Get an animated sprite based on the sprite's name, returns null if sprite is not found
		Kaotic_Alpha::AnimatedSprite* GetAnimatedSprite(std::string spritename)
		{
			//search for animated sprite
			for(std::vector<Kaotic_Alpha::AnimatedSprite*>::iterator it = m_Sprites.begin(); it != m_Sprites.end(); ++it){
				if( (*it)->m_Name == spritename){
					return *it;
				}
			}

			WriteLog << spritename << " not found. " << std::endl;
			return NULL;
		}

		//update all sprites, then queue them up to be rendered
		void Update()
		{
			for(std::vector<Kaotic_Alpha::AnimatedSprite*>::iterator it = m_Sprites.begin(); it != m_Sprites.end(); ++it){
				(*it)->Update();
				sf::Sprite sprite;
				if((*it)->GetSprite(sprite)){
					m_comp_RenderableRef->AddSprite(sprite);
				}		
			}
		}

	private:
		std::vector<Kaotic_Alpha::AnimatedSprite*> m_Sprites;
		Kaotic_Alpha::Comp_Renderable* m_comp_RenderableRef;
	};
}

#endif