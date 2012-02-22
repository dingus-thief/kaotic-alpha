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

		void ConstructGround()
		{
			b2BodyDef groundBodyDef;
				groundBodyDef.position.Set(0.0f, 2.5f);
				m_Ground = PhysicsWorld::GetSingleton()->GetPhysicsWorld()->CreateBody(&groundBodyDef);	
			b2PolygonShape groundBox;	
				groundBox.SetAsBox(50.0f, 0.5f);
				m_Ground->CreateFixture(&groundBox, 0.0f);
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