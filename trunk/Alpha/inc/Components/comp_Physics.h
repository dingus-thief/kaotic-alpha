#ifndef COMP_PHYSICS_H
#define COMP_PHSYICS_H

#include "Vector2.h"
#include "Components/Component.h"

const float maxPull = 1.0f;
const float gravity = 0.01f; 

namespace Kaotic_Alpha
{
	class Comp_Physics
		: public Component
	{
	public:
		void Startup();
		void Update(Kaotic_Alpha::Vector2& desiredVelocity, float deltaTime)
		{
			if(desiredVelocity.Y < maxPull){
				desiredVelocity.Y += gravity;
			}
		}
		void Shutdown();

	private:
	};
}
#endif