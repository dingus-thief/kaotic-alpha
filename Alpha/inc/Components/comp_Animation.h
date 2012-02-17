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
		: public Component
	{
	public:
		Comp_Animation(Kaotic_Alpha::Comp_Renderable* renderable)
			: m_comp_RenderableRef(renderable)
		{}
		~Comp_Animation()
		{
			if(m_AnimatedSprite != NULL)
			{
				delete m_AnimatedSprite;
				m_AnimatedSprite = NULL;
			}
		}

		//set the current animated sprite
		void SetAnimatedSprite(Kaotic_Alpha::AnimatedSprite* sprite){
			m_AnimatedSprite = sprite;
		}

		//get the current animated sprite
		Kaotic_Alpha::AnimatedSprite* GetAnimatedSprite()
		{
			if(m_AnimatedSprite != NULL){
				return m_AnimatedSprite;
			}

			WriteLog << "No Animated Sprite found. " << std::endl;
			return NULL;
		}

		//update the current animated sprite, then add it to the renderering queue
		void Update(float deltaTime, float posX, float posY)
		{
			m_AnimatedSprite->Update(deltaTime);
			sf::Sprite sprite;
			if(m_AnimatedSprite->GetSprite(sprite)){
				sprite.SetPosition(posX, posY);
				m_comp_RenderableRef->AddSprite(sprite);
			}	
		}

	private:
		Kaotic_Alpha::AnimatedSprite* 	m_AnimatedSprite;
		Kaotic_Alpha::Comp_Renderable*	m_comp_RenderableRef;
	};
}

#endif