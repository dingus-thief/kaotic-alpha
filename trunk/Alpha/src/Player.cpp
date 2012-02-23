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
	m_CurrentSpeed = 200.0f;  
	m_NumFootContacts = 0;		
}

void Kaotic_Alpha::Player::Update(float deltaTime)
{
	//Check input
	if(m_AppRef->GetInput().IsKeyDown(sf::Key::Right) || m_AppRef->GetInput().IsKeyDown(sf::Key::D))
	{
		b2Vec2 currentDirection = m_PhysicsComp->GetBody()->GetLinearVelocity();
		currentDirection.x = m_CurrentSpeed;
		m_PhysicsComp->GetBody()->SetLinearVelocity(currentDirection);
		m_AnimationComp->GetAnimatedSprite()->FlipSprite(false);
		m_AnimationComp->GetAnimatedSprite()->PlayAnimation("Running.png");
		m_AnimationComp->GetAnimatedSprite()->SetAnimationFPS(45.0f);
	}
	else if(m_AppRef->GetInput().IsKeyDown(sf::Key::Left) || m_AppRef->GetInput().IsKeyDown(sf::Key::A))
	{
		b2Vec2 currentDirection = m_PhysicsComp->GetBody()->GetLinearVelocity();
		currentDirection.x = -m_CurrentSpeed;
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

	//check if player is currently in the air
	if(m_NumFootContacts >= 1){
		m_Jumping = false;
	}
	else
		m_Jumping = true;

	//check if player can jump
	b2Vec2 currentVelocity = m_PhysicsComp->GetBody()->GetLinearVelocity();
	if((m_AppRef->GetInput().IsKeyDown(sf::Key::Space) || m_AppRef->GetInput().IsKeyDown(sf::Key::Up) || m_AppRef->GetInput().IsKeyDown(sf::Key::W))){
		if(!m_Jumping){
			b2Body* body = m_PhysicsComp->GetBody();
			float impulse = body->GetMass() * 5.0f;
			body->ApplyLinearImpulse( b2Vec2(0,impulse), body->GetWorldCenter() );
		}
	}

	//check if player sprinting
	if(m_AppRef->GetInput().IsKeyDown(sf::Key::LShift) || m_AppRef->GetInput().IsKeyDown(sf::Key::RShift)){
		//do not change speed if player is jumping
		if(!m_Jumping){
			m_CurrentSpeed = 400.0f;
		}
	}
	else{
		m_CurrentSpeed = 200.0f;
	}

	//check death
	if(m_MovableComp->GetPosition().Y < -200){
		m_HealthComp->RemoveLife();
		m_PhysicsComp->ResetPosition();
	}

	GameObject::Update(deltaTime);
}

Kaotic_Alpha::GameMessage* Kaotic_Alpha::Player::ProcessMessage(GameMessage* msg)
{
	//recieve message
	if(msg->MsgType == GameMessage::PLAYER_FOOTCONTACT)
	{
		if(msg->TargetID == 1){
			m_NumFootContacts++;
		}
		else{
			m_NumFootContacts--;
		}
	}

	return NULL; 
}

void Kaotic_Alpha::Player::Shutdown()
{
	GameObject::Shutdown();
}
