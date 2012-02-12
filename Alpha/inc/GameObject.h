#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Components/comp_Collidable.h"
#include "Components/comp_Renderable.h"
#include "Components/comp_Health.h"
#include "Components/comp_Movable.h"
#include "Components/comp_Animation.h"
#include <string>

namespace Kaotic_Alpha
{
	class GameObject
	{
	public:
		GameObject(std::string name){
			m_Name = name;
		}
		virtual ~GameObject(){}
		virtual void Startup();
		virtual void Update();
		virtual void Shutdown();
		std::string GetName() const { return m_Name; }

	protected:
		int m_UID;
		std::string m_Name;
		
		//components
		Comp_Renderable*	m_RenderComp;
		Comp_Collidable*	m_CollideComp;
		Comp_Health*		m_HealthComp;
		Comp_Movable*		m_MovableComp;
		Comp_Animation*		m_AnimationComp;
	};
}

#endif
