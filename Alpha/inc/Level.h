#ifndef LEVEL_H
#define LEVEL_H

#include "SoundManager.h"
#include "GameObject.h"
#include "Camera.h"
#include "Player.h"
#include <vector>

namespace Kaotic_Alpha
{
	class Level
	{
	public:
		Level(int levelNum, sf::RenderWindow* appRef)
			: m_LevelNum(levelNum), m_AppRef(appRef)
		{}

		//Todo: Implement all of this via xml or some sort of data format
		void ConstructGround()
		{
			b2BodyDef groundBodyDef;
			groundBodyDef.type = b2_staticBody;
			groundBodyDef.position.Set(600.0f, 250.0f); //creates ground centered at player
	
			//ground1
			b2Body* ground = PhysicsWorld::GetSingleton()->GetPhysicsWorld()->CreateBody(&groundBodyDef);	
			b2PolygonShape groundBox;		
			groundBox.SetAsBox(700.0f, 50.0f); //sets size to 200, 50			
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &groundBox;
			fixtureDef.density = 10.0f;
			fixtureDef.restitution = 0.0f;
			fixtureDef.friction = 1.0f;
			ground->CreateFixture(&fixtureDef);
			
			/*
			//ground2				
			groundBodyDef.position.Set(13.0f, 2.5f);
			b2Body* ground2 = PhysicsWorld::GetSingleton()->GetPhysicsWorld()->CreateBody(&groundBodyDef);	

			b2Vec2 vertices[3];
				vertices[0].Set(0.0f, -2.0f);
				vertices[1].Set(5.0f, -2.0f);
				vertices[2].Set(0.0f, 0.0f);  			
				
			int32 count = 3;
			b2PolygonShape triangle;
			triangle.Set(vertices, count);
			b2FixtureDef myFixtureDef;
			myFixtureDef.shape = &triangle;
			myFixtureDef.density = 1; 

			ground2->CreateFixture(&myFixtureDef);
			*/

			//ground3
			groundBodyDef.position.Set(2200.0f, 28.0f);
			b2Body* ground3 = PhysicsWorld::GetSingleton()->GetPhysicsWorld()->CreateBody(&groundBodyDef);	
			b2PolygonShape groundBox2;	
			groundBox2.SetAsBox(500.0f, 50.0f); //sets size to 200, 50
			fixtureDef.shape = &groundBox2;
			ground3->CreateFixture(&fixtureDef);
				
		}

		void Startup()
		{
			SoundManager::GetSingleton()->StopMusic();
			ConstructGround();

			//attempt to find level in the level xml file
			bool levelFound = false;
			XMLParser parser("../../media/Levels.xml");
			TiXmlElement* levelNode = parser.SearchForElement(parser.getXmlRootNode(), "level");
			while(levelNode != 0){	
				int levelID = atoi(levelNode->Attribute("id"));
				//level is found
				if(levelID == m_LevelNum)
				{
					//load level specific attributes
					SoundManager::GetSingleton()->PlayMusic(levelNode->Attribute("bgMusic"));
					m_BGSprite.SetImage(ImageManager::GetSingleton()->GetImage(levelNode->Attribute("bgImage")));
					levelFound = true;
					break;
				}
				levelNode = levelNode->NextSiblingElement();
			}
			if(!levelFound){
				WriteLog << "Level " << m_LevelNum << " not found in Levels.xml" << std::endl;
			}
		}
		void Update(float deltaTime, Camera* camera, GameObject* player)
		{
			Vector2 newBGpos = camera->TranslateWorldCoordsToLocal(Vector2(0, 720));
			m_BGSprite.SetPosition(newBGpos.X, newBGpos.Y);
			m_AppRef->Draw(m_BGSprite);

			//update objects logic
			for(std::vector<GameObject*>::iterator it = m_Objects.begin(); it != m_Objects.end(); ++it){
				(*it)->Update(deltaTime);
			}	
			player->Update(deltaTime);
			
			//update objects movement
			for(std::vector<GameObject*>::iterator it = m_Objects.begin(); it != m_Objects.end(); ++it){
				(*it)->UpdateMovement(deltaTime);
			}	
			player->UpdateMovement(deltaTime);

			//render objects
			for(std::vector<GameObject*>::iterator it = m_Objects.begin(); it != m_Objects.end(); ++it){
				(*it)->Render(deltaTime, camera);
			}
			player->Render(deltaTime, camera);
		}

		void Shutdown()
		{
			SoundManager::GetSingleton()->StopMusic();
			for(std::vector<GameObject*>::iterator it = m_Objects.begin(); it != m_Objects.end(); ++it){
				delete *it;
			}
			m_Objects.clear();
		}

	private:
		b2Body*						m_Ground;
		sf::RenderWindow*			m_AppRef;
		sf::Sprite					m_BGSprite;
		int							m_LevelNum;
		std::vector<GameObject*>	m_Objects; 
		Player*						m_PlayerRef;
	};
}

#endif