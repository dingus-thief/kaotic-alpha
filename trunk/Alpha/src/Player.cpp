#include "Player.h"

#include "ImageManager.h"
#include "GameMessage.h"
#include "GameLog.h"
#include <SFML/Graphics.hpp>

Kaotic_Alpha::Player::Player(sf::RenderWindow* app, int uid)
	: Kaotic_Alpha::GameObject("Player", uid)
{
	m_AppRef = app;
}

void Kaotic_Alpha::Player::Startup()
{    
	GameObject::Startup();
	m_RenderComp = new Comp_Renderable(m_AppRef);
	m_AnimationComp = new Comp_Animation(m_RenderComp);
	m_HealthComp = new Comp_Health();
	m_MovableComp = new Comp_Movable();
	m_PhysicsComp = new Comp_Physics(); 

	//create player sprite and add animations
	Kaotic_Alpha::AnimatedSprite* sprite = new Kaotic_Alpha::AnimatedSprite("Player");
	sprite->SetScale(0.6f);
	sprite->AddAnimation("Running.png");
	sprite->AddAnimation("Idle.png");
	sprite->PlayAnimation("Idle.png");
	m_AnimationComp->SetAnimatedSprite(sprite);
			
	m_Jumping = false;
		
}

void Kaotic_Alpha::Player::Update(float deltaTime)
{
	//Check input
	if(m_AppRef->GetInput().IsKeyDown(sf::Key::Right) || m_AppRef->GetInput().IsKeyDown(sf::Key::D))
	{
		b2Vec2 currentDirection = m_PhysicsComp->GetBody()->GetLinearVelocity();
		currentDirection.x = 2.0f;
		m_PhysicsComp->GetBody()->SetLinearVelocity(currentDirection);
		m_AnimationComp->GetAnimatedSprite()->FlipSprite(false);
		m_AnimationComp->GetAnimatedSprite()->PlayAnimation("Running.png");
		m_AnimationComp->GetAnimatedSprite()->SetAnimationFPS(45.0f);
	}
	else if(m_AppRef->GetInput().IsKeyDown(sf::Key::Left) || m_AppRef->GetInput().IsKeyDown(sf::Key::A))
	{
		b2Vec2 currentDirection = m_PhysicsComp->GetBody()->GetLinearVelocity();
		currentDirection.x = -2.0f;
		m_PhysicsComp->GetBody()->SetLinearVelocity(currentDirection);
		m_AnimationComp->GetAnimatedSprite()->FlipSprite(true);
		m_AnimationComp->GetAnimatedSprite()->PlayAnimation("Running.png");
		m_AnimationComp->GetAnimatedSprite()->SetAnimationFPS(45.0f);
	}
	else
	{
		b2Vec2 currentDirection = m_PhysicsComp->GetBody()->GetLinearVelocity();
		currentDirection.x = 0.0f;
		m_PhysicsComp->GetBody()->SetLinearVelocity(currentDirection);
		m_AnimationComp->GetAnimatedSprite()->PlayAnimation("Idle.png");
		m_AnimationComp->GetAnimatedSprite()->SetAnimationFPS(10.0f);
	}

	//check if player can jump
	b2Vec2 currentVelocity = m_PhysicsComp->GetBody()->GetLinearVelocity();
	if((m_AppRef->GetInput().IsKeyDown(sf::Key::Space) || m_AppRef->GetInput().IsKeyDown(sf::Key::Up) || m_AppRef->GetInput().IsKeyDown(sf::Key::W))){
		if(!m_Jumping && currentVelocity.y < 0.01 && currentVelocity.y > -0.01){
			m_Jumping = true;
		}
	}

	//reset jumping flag if velocity < 0
	if(m_Jumping)
	{
		float maxJump = 3.0f;
		if(currentVelocity.y >= maxJump )	{
			m_Jumping = false;
		}
		else{
			currentVelocity.y += 1.0f;
			m_PhysicsComp->GetBody()->SetLinearVelocity(currentVelocity);
		}
	}

	GameObject::Update(deltaTime);
}

Kaotic_Alpha::GameMessage* Kaotic_Alpha::Player::ProcessMessage(GameMessage* msg)
{
	//recieve message
	if(msg->MsgType == GameMessage::MSG_TYPE::COLLISION)
	{
		if(msg->TargetID == m_UID){
		}
	}

	return NULL; 
}

void Kaotic_Alpha::Player::Shutdown()
{
	GameObject::Shutdown();
}
