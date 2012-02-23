#ifndef COMP_PHYSICS_H
#define COMP_PHSYICS_H

#include <Box2D/Box2d.h>
#include <SFML/Graphics.hpp>

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

			//Create physics body
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(610.0f, 400.0f);
			m_Body = PhysicsWorld::GetSingleton()->GetPhysicsWorld()->CreateBody(&bodyDef);
				
			//Define a box shape for our dynamic body.
			b2PolygonShape boxShape;
			boxShape.SetAsBox(55.0f, 80.0f); 

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &boxShape;
			fixtureDef.density = 10.0f;
			fixtureDef.restitution = 0.0f;

			//Add the shape to the body.
			m_Body->CreateFixture(&fixtureDef);
			 
			//Add foot sensor fixture
			boxShape.SetAsBox(30.0f, 10.0f, b2Vec2(0,-80.0f), 0);
			fixtureDef.isSensor = true;
			b2Fixture* footSensorFixture = m_Body->CreateFixture(&fixtureDef);
			footSensorFixture->SetUserData( (void*)3 );
		}

		void ResetPosition() { m_Body->SetTransform(b2Vec2(610.0f, 400.0f), 0.0f); }
		void Update(float deltaTime)
		{

		}
		void Shutdown()
		{
			 PhysicsWorld::GetSingleton()->GetPhysicsWorld()->DestroyBody(m_Body);
		}
		b2Body* GetBody() const { return m_Body; }

	private:
		sf::FloatRect* rect;

		b2Body* m_Body;  
		int numFootContacts;
	};
}
#endif