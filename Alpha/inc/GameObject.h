#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Components/comp_Renderable.h"
#include "Components/comp_Health.h"
#include "Components/comp_Movable.h"
#include "Components/comp_Animation.h"
#include "Components/comp_Physics.h"

#include "MessageListener.h"

namespace Kaotic_Alpha
{
	class Camera;

	class GameObject
		: public MessageListener
	{
	public:
		GameObject(std::string name, int uid);
		virtual ~GameObject();

		virtual void Startup();
		
		virtual void Update(float deltaTime); //update logic
		virtual void UpdateMovement(float deltaTime);
		virtual void Render(float deltaTime, Camera* camera);

		virtual void Shutdown();
		virtual GameMessage* ProcessMessage(GameMessage* msg){ return NULL; }

		int GetUID() const { return m_UID; }
		std::string GetName() const { return m_Name; }
	
		Comp_Health* GetHealthComponent() const { return m_HealthComp; }
		Comp_Movable* GetMovableComponent() const { return m_MovableComp; }

	protected:
		int m_UID;
		std::string m_Name;
		
		//components
		Comp_Renderable*	m_RenderComp;
		Comp_Health*		m_HealthComp;
		Comp_Movable*		m_MovableComp;
		Comp_Animation*		m_AnimationComp;
		Comp_Physics*		m_PhysicsComp;
		sf::RenderWindow*	m_AppRef;
	};
}

#endif
