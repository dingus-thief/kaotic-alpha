#ifndef COMP_MOVABLE_H
#define COMP_MOVABLE_H

#include "Components/Component.h"
#include "Vector2.h"
#include "GameLog.h"

namespace Kaotic_Alpha
{
	class Comp_Movable
		: public Component
	{
	public:
		Comp_Movable()
			: m_DesiredVelocity(0,0), m_ActualVelocity(0,0), m_MovementSpeed(1.0f), 
			m_MovementSpeedMultipler(1.0f), m_CurrentPosition(0,0)
		{}

		void SetDesiredVelocity(Vector2 movementVector) {
			m_DesiredVelocity = movementVector; 
		}

		void SetDesiredVelocityX(float value) {
			m_DesiredVelocity.X = value;
		}

		void SetDesiredVelocityY(float value) {
			m_DesiredVelocity.Y = value;
		}
		
		void SetPositionX(float value){ m_CurrentPosition.X = value; }
		void SetPositionY(float value){ m_CurrentPosition.Y = value; }
		void SetPosition(Vector2 value) { m_CurrentPosition = value; }
		void SetActualVelocity(Vector2 value) { m_ActualVelocity = value; }
		void SetMovementSpeed(float value) { m_MovementSpeed = value; }
		void SetMovementSpeedMultiplier(float value) { m_MovementSpeedMultipler = value; }
		Vector2& GetDesiredVelocity() { return m_DesiredVelocity; }
		Vector2& GetActualVelocity() { return m_ActualVelocity; }
		Vector2 GetPosition() const { return m_CurrentPosition; }

		void Update(float deltaTime)
		{
			m_ActualVelocity.X = (m_DesiredVelocity.X * m_MovementSpeed * m_MovementSpeedMultipler * deltaTime);
			m_ActualVelocity.Y = (m_DesiredVelocity.Y * m_MovementSpeed * m_MovementSpeedMultipler * deltaTime); 
			m_CurrentPosition.X += m_ActualVelocity.X;
			m_CurrentPosition.Y += m_ActualVelocity.Y;
		}

	private:
		Vector2 m_CurrentPosition;
		Vector2 m_DesiredVelocity; //unit vector for intended movement
		Vector2 m_ActualVelocity; //vector for actual movement
		float m_MovementSpeed;
		float m_MovementSpeedMultipler;
	};
}

#endif
