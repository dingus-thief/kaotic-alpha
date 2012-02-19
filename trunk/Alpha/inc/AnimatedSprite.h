#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "ImageManager.h"
#include "SpriteAnimation.h"
#include "GameLog.h"

namespace Kaotic_Alpha
{
	class AnimatedSprite
	{
	public:
		AnimatedSprite(std::string spritename)
			: m_Name(spritename)
		{
			currentAnimation = -1;
			frame = 0;
			frameCounter = 0;
			flipSprite = false;
			posX = 0;
			posY = 0;
			scaleX = 1;
			scaleY = 1;
			animationFPS = 60;
		}
		~AnimatedSprite()
		{
			ClearAllAnimations();
		}

		//add a specific animation to the animated sprite
		void AddAnimation(std::string animationName)
		{
			Kaotic_Alpha::SpriteAnimation* animation = new Kaotic_Alpha::SpriteAnimation(animationName);
			m_SpriteAnimations.push_back(animation);
		}
		
		//remove a specific animation from the animated sprite
		void RemoveAnimation(std::string animationName)
		{
			for(std::vector<Kaotic_Alpha::SpriteAnimation*>::iterator it = m_SpriteAnimations.begin(); it != m_SpriteAnimations.end(); ++it){
				if((*it)->m_Name == animationName)
				{
					delete *it;
					m_SpriteAnimations.erase(it);
					break;
				}
			}
		}
		
		//clear all animations from the animated sprite
		void ClearAllAnimations()
		{
			for(std::vector<Kaotic_Alpha::SpriteAnimation*>::iterator it = m_SpriteAnimations.begin(); it != m_SpriteAnimations.end(); ++it){
				delete *it;
			}
			m_SpriteAnimations.clear();
		}

		//set a specific animation as the current animation to play
		void PlayAnimation(std::string animationName)
		{
			currentAnimation = -1;
			for(int i=0; i<static_cast<int>(m_SpriteAnimations.size()); ++i){
				if(m_SpriteAnimations.at(i)->m_Name == animationName){
					currentAnimation = i;
				}
			}
			if(currentAnimation == -1)
				WriteLog << "Animation (\"" << animationName << "\") could not be fould." << std::endl;
		}

		//if there is an active animation, update it 
		void Update(float deltaTime)
		{
			if(currentAnimation != -1)
			{
				//throttle animation frame rate so that program can run as fast as possible and sprites won't run any faster
				frameCounter += (deltaTime * animationFPS);
				frame = static_cast<int>(frameCounter) % m_SpriteAnimations[currentAnimation]->GetNumFrames();
			}
		}

		Vector2 GetSpriteSize() 
		{
			sf::Sprite* temp = GetSprite();
			if(temp != NULL)
				return Vector2(temp->GetSize().x, temp->GetSize().y);
			else
				return Vector2(0,0);
		}

		//get the specific sprite that should be drawn to screen, based on the animation currently playing
		sf::Sprite* GetSprite() const { 
			sf::Sprite* sprite;
			if(currentAnimation == -1)
				return NULL;
			else{
				sprite = m_SpriteAnimations[currentAnimation]->GetSprite(frame);
				sprite->SetPosition(posX, posY);
				sprite->SetScale(scaleX, scaleY);
				sprite->FlipX(flipSprite);
				return sprite;
			}
		}
		void SetAnimationFPS(float val)
		{
			animationFPS = val;
		}
		void SetPosition(float x, float y)
		{
			posX = x;
			posY = y;
		}
		void SetScale(float x, float y)
		{
			scaleX = x;
			scaleY = y;
		}
		void SetScale(float scale)
		{
			scaleX = scale;
			scaleY = scale;
		}
		void FlipSprite(bool flip)
		{
			flipSprite = flip;
		}
		
		std::string m_Name;

	private:
		std::vector<Kaotic_Alpha::SpriteAnimation*> m_SpriteAnimations;
		float frameCounter;
		int frame;
		int currentAnimation;
		float posX, posY;
		float scaleX, scaleY;
		bool flipSprite;
		float animationFPS;
	};
}

#endif