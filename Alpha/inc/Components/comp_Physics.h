#ifndef COMP_PHYSICS_H
#define COMP_PHSYICS_H

#include <Box2D/Box2d.h>
#include "Vector2.h"
#include "Components/Component.h"
#include "PhysicsWorld.h"

namespace Kaotic_Alpha
{
	class Comp_Physics
		: public Component
	{
	public:
		Comp_Physics()
		{ 
			//create physics body
			b2BodyDef bodyDef;
				bodyDef.type = b2_dynamicBody;
				bodyDef.position.Set(6.0f, 4.0f);//this will need to be modified
			m_Body = PhysicsWorld::GetSingleton()->GetPhysicsWorld()->CreateBody(&bodyDef);
				
			// Define another box shape for our dynamic body.
			b2PolygonShape dynamicBox;
				dynamicBox.SetAsBox(.55f, .8f);
			b2FixtureDef fixtureDef;
				fixtureDef.shape = &dynamicBox;
				fixtureDef.density = 0.5f;
				fixtureDef.friction = 0.1f;

			// Add the shape to the body.
			m_Body->CreateFixture(&fixtureDef);
		}
		void Update(float deltaTime)
		{}
		void Shutdown();
		b2Body* GetBody() const { return m_Body; }

	private:
		b2Body* m_Body;
	};
}
#endif