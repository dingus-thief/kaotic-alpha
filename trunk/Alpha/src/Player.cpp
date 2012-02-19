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
	m_MovableComp = new Comp_Movable();
	//m_PhysicsComp = new Comp_Physics(); 

	//set player default movement speed (can load from file, etc.)
	m_MovableComp->SetMovementSpeed(150.0f);

	//create player sprite and add animations
	Kaotic_Alpha::AnimatedSprite* sprite = new Kaotic_Alpha::AnimatedSprite("Player");
	sprite->SetScale(0.6f);
	sprite->AddAnimation("Running.png");
	sprite->AddAnimation("Idle.png");
	sprite->PlayAnimation("Idle.png");
	m_MovableComp->SetPosition(Vector2(610.0f, 340.0f));
	m_AnimationComp->SetAnimatedSprite(sprite);
			
	m_Jumping = false;
			
	//need sprite info before creating collidable component
	m_CollideComp = new Comp_Collidable(this, 55, 80);
}

void Kaotic_Alpha::Player::Update(float deltaTime)
{
	//Check input
	if(m_AppRef->GetInput().IsKeyDown(sf::Key::Right) || m_AppRef->GetInput().IsKeyDown(sf::Key::D))
	{
		m_MovableComp->SetDesiredVelocityX(1.0f);
		m_AnimationComp->GetAnimatedSprite()->FlipSprite(false);
		m_AnimationComp->GetAnimatedSprite()->PlayAnimation("Running.png");
		m_AnimationComp->GetAnimatedSprite()->SetAnimationFPS(45.0f);
	}
	else if(m_AppRef->GetInput().IsKeyDown(sf::Key::Left) || m_AppRef->GetInput().IsKeyDown(sf::Key::A))
	{
		m_MovableComp->SetDesiredVelocityX(-1.0f);
		m_AnimationComp->GetAnimatedSprite()->FlipSprite(true);
		m_AnimationComp->GetAnimatedSprite()->PlayAnimation("Running.png");
		m_AnimationComp->GetAnimatedSprite()->SetAnimationFPS(45.0f);
	}
	else
	{
		m_MovableComp->SetDesiredVelocityX(0.0f);
		m_AnimationComp->GetAnimatedSprite()->PlayAnimation("Idle.png");
		m_AnimationComp->GetAnimatedSprite()->SetAnimationFPS(10.0f);
	}
	if(m_MovableComp->GetDesiredVelocity().Y == 0.0f && (m_AppRef->GetInput().IsKeyDown(sf::Key::Space) || m_AppRef->GetInput().IsKeyDown(sf::Key::Up)))
	{
		m_Jumping = true;
	}

	//reset jumping flag if velocity < 0
	if(m_Jumping)
	{
		m_MovableComp->SetDesiredVelocityY(m_MovableComp->GetDesiredVelocity().Y + 2.5f);
		if(m_MovableComp->GetDesiredVelocity().Y >= 15.0f){
			m_Jumping = false;
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
			m_MovableComp->SetDesiredVelocity(Vector2(0,0));
		}
	}

	return NULL; 
}

void Kaotic_Alpha::Player::Shutdown()
{
	GameObject::Shutdown();
}
