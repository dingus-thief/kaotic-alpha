#include "Components/comp_Collidable.h"
#include "GameObject.h"
#include "CollisionManager.h"

void Kaotic_Alpha::Comp_Collidable::CheckCollisions(GameObject* obj, Vector2 newPosition, float deltaTime)
{
	CollisionManager::GetSingleton()->CheckCollisions(obj, deltaTime);
}

Kaotic_Alpha::BoundingBox Kaotic_Alpha::Comp_Collidable::GetBounds()
{ 
	BoundingBox bounds;
	bounds.SetWidth(m_SizeX);
	bounds.SetHeight(m_SizeY);
	bounds.SetPosition(m_ParentRef->GetMovableComponent()->GetPosition());
	return bounds; 
}