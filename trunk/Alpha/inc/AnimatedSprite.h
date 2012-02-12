#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ImageManager.h"
#include "SpriteAnimation.h"
#include "GameLog.h"
#include "Timer.h"

const float ANIMATION_FPS = 20.0f;

namespace Kaotic_Alpha
{
	class AnimatedSprite
	{
	public:
		AnimatedSprite(std::string spritename)
			: m_Name(spritename)
		{
			timer.Start();
			currentAnimation = -1;
			frame = 0;
			frameCounter = 0;
			prevAnimTime = timer.GetElapsedTime();
			flipSprite = false;
			posX = 0;
			posY = 0;
			scaleX = 1;
			scaleY = 1;
		}
		~AnimatedSprite()
		{
			ClearAllAnimations();
		}

		void AddAnimation(std::string animationName)
		{
			Kaotic_Alpha::SpriteAnimation* animation = new Kaotic_Alpha::SpriteAnimation(animationName);
			m_SpriteAnimations.push_back(animation);
		}
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
		void ClearAllAnimations()
		{
			for(std::vector<Kaotic_Alpha::SpriteAnimation*>::iterator it = m_SpriteAnimations.begin(); it != m_SpriteAnimations.end(); ++it){
				delete *it;
			}
			m_SpriteAnimations.clear();
		}
		//attempt to play animation
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

		void Update()
		{
			if(currentAnimation != -1)
			{
				//throttle animation frame rate so that program can run as fast as possible and sprites won't run any faster
				float deltaTime = timer.GetElapsedTime() - prevAnimTime;	
				prevAnimTime = timer.GetElapsedTime();
				frameCounter += (deltaTime * ANIMATION_FPS)/1000;
				frame = static_cast<int>(frameCounter) % m_SpriteAnimations[currentAnimation]->GetNumFrames();
			}
		}
		bool GetSprite(sf::Sprite& sprite) const { 
			if(currentAnimation == -1)
				return false;
			else{
				sprite = m_SpriteAnimations[currentAnimation]->GetSprite(frame);
				sprite.SetPosition(posX, posY);
				sprite.SetScale(scaleX, scaleY);
				sprite.FlipX(flipSprite);
			}
			return true;
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
		float prevAnimTime;
		bool flipSprite;
		Kaotic_Alpha::Timer timer;
	};
}

#endif