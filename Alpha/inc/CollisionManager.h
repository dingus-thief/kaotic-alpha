#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "BoundingBox.h"
#include "GameObject.h"
#include <vector>

namespace Kaotic_Alpha
{
	class CollisionManager
	{
	public:
		static CollisionManager* GetSingleton();
		void Update(float deltaTime);
		void CheckCollisions(GameObject* object, float deltaTime);
		void RegisterCollisionObject(GameObject* gameObj);
		void UnregisterCollisionObject(GameObject* gameObj);
		void Startup();
		void Shutdown();

	private:
		CollisionManager(){}
		std::vector<GameObject*> m_GameObjects;
		static CollisionManager* p_Instance;
	};
}

#endif