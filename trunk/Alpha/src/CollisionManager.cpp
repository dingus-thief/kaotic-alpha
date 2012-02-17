#include "CollisionManager.h"
#include "MessageSystem.h"

Kaotic_Alpha::CollisionManager* Kaotic_Alpha::CollisionManager::p_Instance = NULL;

void Kaotic_Alpha::CollisionManager::CheckCollisions(GameObject* object, float deltaTime)
{
	for(std::vector<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
	{
		if( object->GetUID() != (*it)->GetUID())
		{
			//if objects intersect
			if((*it)->GetBoundingBox().Intersects(object->GetBoundingBox()))
			{
				//send out a collision message
				//Kaotic_Alpha::GameMessage* msg = new Kaotic_Alpha::GameMessage(GameMessage::MSG_TYPE::COLLISION);
				//msg->SourceID = object->GetUID();
				//msg->TargetID = (*it)->GetUID();
				//Kaotic_Alpha::MessageSystem::GetSingleton()->QueueMessage(msg);
				//std::cout << "Collision(" << msg->SourceID << "," << msg->TargetID << ")" << std::endl;

				//resolve collision				
				bool horizColl = false;
				bool vertColl = false;
				Comp_Movable* comp_move = object->GetMovableComponent();
				Vector2 velocity = comp_move->GetActualVelocity();
				Vector2 initialPosition = comp_move->GetPosition() - comp_move->GetActualVelocity();

				//check X
				comp_move->SetPosition(initialPosition + Vector2(velocity.X, 0));
				if((*it)->GetBoundingBox().Intersects(object->GetBoundingBox())){
					horizColl = true;
				}
				//check Y
				comp_move->SetPosition(initialPosition + Vector2(0, velocity.Y));
				if((*it)->GetBoundingBox().Intersects(object->GetBoundingBox())){
					vertColl = true;
				}

				//move based on collisions
				if(vertColl && !horizColl){
					comp_move->SetDesiredVelocityY(0);
					comp_move->SetPosition(initialPosition + Vector2(velocity.X, 0));
				}
				else if(horizColl && !vertColl){
					comp_move->SetDesiredVelocityX(0);
					comp_move->SetPosition(initialPosition + Vector2(0, velocity.Y));
				}
				else{
					comp_move->SetDesiredVelocity(Vector2(0, 0));
					comp_move->SetPosition(initialPosition);
				}
			}
		}
	}
}

void Kaotic_Alpha::CollisionManager::RegisterCollisionObject(GameObject* gameObj)
{
	m_GameObjects.push_back(gameObj); 
}

void Kaotic_Alpha::CollisionManager::UnregisterCollisionObject(GameObject* gameObj)
{
	for(std::vector<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
	{
		if(gameObj == *it)
		{
			m_GameObjects.erase(it);
			return;
		}
	}
}

Kaotic_Alpha::CollisionManager* Kaotic_Alpha::CollisionManager::GetSingleton()
{
	if(p_Instance == NULL){
		p_Instance = new CollisionManager();
	}
	return p_Instance;
}

void Kaotic_Alpha::CollisionManager::Update(float deltaTime)
{
	//need access to camera info here
	//check all objects on screen against each other
	//if collision, create a message

}

void Kaotic_Alpha::CollisionManager::Startup()
{
}

void Kaotic_Alpha::CollisionManager::Shutdown()
{
	if(p_Instance != NULL)
	{
		delete p_Instance;
		p_Instance = NULL;
	}
	if(!m_GameObjects.empty()){
		m_GameObjects.clear();
	}
}
