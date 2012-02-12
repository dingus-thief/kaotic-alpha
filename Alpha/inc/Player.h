#ifndef PLAYER_H
#define PLAYER_H

#include "ImageManager.h"
#include "GameObject.h"
#include "GameLog.h"
#include <SFML/Graphics.hpp>

namespace Kaotic_Alpha
{
	class Player
		: public Kaotic_Alpha::GameObject
	{
	public:
		Player(sf::RenderWindow* app)
			: m_AppRef(app), Kaotic_Alpha::GameObject("Player")
		{}

		void Startup()
		{    
			GameObject::Startup();
			m_RenderComp = new Comp_Renderable(m_AppRef);
			m_AnimationComp = new Comp_Animation(m_RenderComp);

			//create player sprite and add animations
			Kaotic_Alpha::AnimatedSprite* sprite = new Kaotic_Alpha::AnimatedSprite("Player");
			sprite->SetPosition(610.0f, 360.0f);
			sprite->SetScale(0.6f);
			sprite->AddAnimation("Running.png");
			sprite->AddAnimation("Idle.png");
			sprite->PlayAnimation("Idle.png");
			m_AnimationComp->AddAnimatedSprite(sprite);
		}

		void Update()
		{
			//Check input
			if(m_AppRef->GetInput().IsKeyDown(sf::Key::Right) || m_AppRef->GetInput().IsKeyDown(sf::Key::D))
			{
				m_AnimationComp->GetAnimatedSprite("Player")->FlipSprite(false);
				m_AnimationComp->GetAnimatedSprite("Player")->PlayAnimation("Running.png");
			}
			else if(m_AppRef->GetInput().IsKeyDown(sf::Key::Left) || m_AppRef->GetInput().IsKeyDown(sf::Key::A))
			{
				m_AnimationComp->GetAnimatedSprite("Player")->FlipSprite(true);
				m_AnimationComp->GetAnimatedSprite("Player")->PlayAnimation("Running.png");
			}
			else
			{
				m_AnimationComp->GetAnimatedSprite("Player")->PlayAnimation("Idle.png");
			}

			GameObject::Update();
		}

		void Shutdown()
		{
			GameObject::Shutdown();
		}
	private:
		sf::RenderWindow* m_AppRef;

	};
}

#endif