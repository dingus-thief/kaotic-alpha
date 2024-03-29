#include "PhysicsWorld.h"
#include "MessageSystem.h"
#include "GameLog.h"

Kaotic_Alpha::PhysicsWorld* Kaotic_Alpha::PhysicsWorld::p_Instance = NULL;

Kaotic_Alpha::PhysicsWorld::PhysicsWorld()
{
	std::cout << "creating world" << std::endl;
	b2Vec2 gravity(0.0f, -1000.0f);
	m_World = new b2World(gravity);
	m_ContactListener = new MyContactListener();
	m_World->SetContactListener(m_ContactListener);
}

Kaotic_Alpha::PhysicsWorld* Kaotic_Alpha::PhysicsWorld::GetSingleton()
{
	if(p_Instance == NULL){
		p_Instance = new PhysicsWorld();
	}
	return p_Instance;
}

void Kaotic_Alpha::PhysicsWorld::Update(float deltaTime)
{

}

void Kaotic_Alpha::PhysicsWorld::Startup()
{
}

void Kaotic_Alpha::PhysicsWorld::Shutdown()
{
	std::cout << "Shutdown" << std::endl;
	if(p_Instance != NULL){
		delete m_ContactListener;
		delete p_Instance;
		p_Instance = NULL;
	}
}
