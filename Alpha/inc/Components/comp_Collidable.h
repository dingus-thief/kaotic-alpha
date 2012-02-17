#ifndef COMP_COLLIDABLE
#define COMP_COLLIDABLE

#include "Components/Component.h"
#include "Vector2.h"
#include "BoundingBox.h"

namespace Kaotic_Alpha
{
	class GameObject;

	class Comp_Collidable
		: public Component
	{
	public:
		Comp_Collidable(GameObject* parentRef, float sizeX, float sizeY)
			: m_SizeX(sizeX), m_SizeY(sizeY), m_ParentRef(parentRef)
		{
		}
		Comp_Collidable(GameObject* m_ParentRef, Vector2 size)
			: m_SizeX(size.X), m_SizeY(size.Y)
		{
		}

		void CheckCollisions(GameObject* obj, Vector2 newPosition, float deltaTime);

		BoundingBox GetBounds();

	private:
		Comp_Collidable(){}
		float m_SizeX, m_SizeY;
		GameObject* m_ParentRef;
	};
}

#endif