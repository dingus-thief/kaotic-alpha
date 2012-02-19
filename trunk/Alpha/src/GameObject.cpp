#include "GameObject.h"
#include "MessageSystem.h"
#include "CollisionManager.h"

Kaotic_Alpha::GameObject::GameObject(std::string name, int uid){
	m_Name = name;
	m_UID = uid;
	Kaotic_Alpha::MessageSystem::GetSingleton()->AddListener(this);

}
Kaotic_Alpha::GameObject::~GameObject(){
	Kaotic_Alpha::MessageSystem::GetSingleton()->RemoveListener(this);
}

void Kaotic_Alpha::GameObject::Startup()
{
	m_AnimationComp = 0;
	m_CollideComp = 0;
	m_HealthComp = 0;
	m_MovableComp = 0;
	m_PhysicsComp = 0;
	m_RenderComp = 0;

	CollisionManager::GetSingleton()->RegisterCollisionObject(this);
}

void Kaotic_Alpha::GameObject::Shutdown()
{
	//animation component must be shut down before render component, as it contains a reference to render component
	if(m_AnimationComp)
		delete m_AnimationComp;
	if(m_RenderComp)
		delete m_RenderComp;
	if(m_CollideComp)
		delete m_CollideComp;
	if(m_HealthComp)
		delete m_HealthComp;
	if(m_MovableComp)
		delete m_MovableComp;
	
	m_AnimationComp = 0;
	m_CollideComp = 0;
	m_HealthComp = 0;
	m_MovableComp = 0;
	m_PhysicsComp = 0;
	m_RenderComp = 0;

	CollisionManager::GetSingleton()->UnregisterCollisionObject(this);
}

void Kaotic_Alpha::GameObject::Update(float deltaTime)
{
	if(m_PhysicsComp){
		m_PhysicsComp->Update(m_MovableComp->GetDesiredVelocity(), deltaTime);
	}
	if(m_HealthComp){
		m_HealthComp->CheckDeath();
	}
}

void Kaotic_Alpha::GameObject::UpdateMovement(float deltaTime)
{
	if(m_MovableComp){
		m_MovableComp->Update(deltaTime);
	}
	if(m_CollideComp){
		m_CollideComp->CheckCollisions(this, m_MovableComp->GetPosition(), deltaTime);
	}
	if(m_AnimationComp){
		m_AnimationComp->Update(deltaTime, m_MovableComp->GetPosition().X, m_MovableComp->GetPosition().Y);
	}
}

void Kaotic_Alpha::GameObject::Render(float deltaTime, Camera* camera)
{
	if(m_RenderComp){
		m_RenderComp->Render(camera);
	}
}
