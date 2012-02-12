#include "GameObject.h"

void Kaotic_Alpha::GameObject::Startup()
{
	m_RenderComp = 0;
	m_MovableComp = 0;
	m_CollideComp = 0;
	m_HealthComp = 0;
	m_AnimationComp = 0;
}

void Kaotic_Alpha::GameObject::Shutdown()
{
	if(m_RenderComp)
		delete m_RenderComp;
	if(m_CollideComp)
		delete m_CollideComp;
	if(m_HealthComp)
		delete m_HealthComp;
	if(m_MovableComp)
		delete m_MovableComp;
	if(m_AnimationComp)
		delete m_AnimationComp;

	m_RenderComp = 0;
	m_CollideComp = 0;
	m_HealthComp = 0;
	m_MovableComp = 0;
	m_AnimationComp = 0;
}

void Kaotic_Alpha::GameObject::Update()
{
	if(m_CollideComp){
	}
	if(m_HealthComp){
		m_HealthComp->CheckDeath();
	}
	if(m_MovableComp){
		//m_MovableComp->UpdateMovement();
	}
	if(m_AnimationComp){
		m_AnimationComp->Update();
	}
	if(m_RenderComp){
		m_RenderComp->Render();
	}
}