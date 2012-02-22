#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include <Box2D/Box2D.h>

namespace Kaotic_Alpha
{
	class PhysicsWorld
	{
	public:
		static PhysicsWorld* GetSingleton();
		void Update(float deltaTime);

		void Startup();
		void Shutdown();

		b2World* GetPhysicsWorld() { return m_World; }

	private:	
		PhysicsWorld();

		b2World* m_World;
		static PhysicsWorld* p_Instance;
	};
}

#endif