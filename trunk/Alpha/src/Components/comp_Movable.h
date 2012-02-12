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
			: m_DesiredVelocity(0,0), m_ActualVelocity(0,0), m_MovementSpeed(1.0f), m_MovementSpeedMultipler(1.0f)
		{}

		void SetDesiredVelocity(Vector2 value) { m_DesiredVelocity = value; }
		void SetActualVelocity(Vector2 value) { m_ActualVelocity = value; }
		void SetMovementSpeed(float value) { m_MovementSpeed = value; }
		void SetMovementSpeedMultiplier(float value) { m_MovementSpeedMultipler = value; }
		Vector2 GetDesiredVelocity() const { return m_DesiredVelocity; }
		Vector2 GetActualVelocity() const { return m_ActualVelocity; }

		void UpdateMovement(Vector2 &currentPosition)
		{
			currentPosition.X += (m_ActualVelocity.X) * m_MovementSpeed * m_MovementSpeedMultipler;
			currentPosition.Y += (m_ActualVelocity.Y) * m_MovementSpeed * m_MovementSpeedMultipler; 
		}

	private:
		Vector2 m_DesiredVelocity; //unit vector for intended movement
		Vector2 m_ActualVelocity; //unit vector for actual movement
		float m_MovementSpeed;
		float m_MovementSpeedMultipler;
	};
}

#endif
