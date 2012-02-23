#ifndef COMP_MOVABLE_H
#define COMP_MOVABLE_H

#include "Components/Component.h"
#include <Box2D/Box2d.h>
#include "Vector2.h"
#include "GameLog.h"

namespace Kaotic_Alpha
{
	class Comp_Movable
		: public Component
	{
	public:
		Comp_Movable()
			: m_MovementSpeed(1.0f), m_MovementSpeedMultipler(1.0f), m_CurrentPosition(0,0)
		{}

		Vector2 GetPosition() const { return m_CurrentPosition; }

		void Update(float deltaTime, b2Body* body)
		{ 
			if(body != NULL){
				m_CurrentPosition.X = body->GetPosition().x;
				m_CurrentPosition.Y = body->GetPosition().y;
			}
		}

	private:
		Vector2 m_CurrentPosition;
		float m_MovementSpeed;
		float m_MovementSpeedMultipler;
	};
}

#endif
