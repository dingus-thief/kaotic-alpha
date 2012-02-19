#include "ObjectFactory.h"
#include "Player.h"
#include "GameLog.h"

Kaotic_Alpha::ObjectFactory* Kaotic_Alpha::ObjectFactory::p_Instance = NULL;
int Kaotic_Alpha::ObjectFactory::next_UID = 1;

Kaotic_Alpha::ObjectFactory* Kaotic_Alpha::ObjectFactory::GetSingleton()
{
  if(p_Instance == NULL){
    p_Instance = new ObjectFactory();
  }
  return p_Instance;
}

Kaotic_Alpha::ObjectFactory::ObjectFactory()
{}

Kaotic_Alpha::GameObject* Kaotic_Alpha::ObjectFactory::GetObject(int uid)
{
	Kaotic_Alpha::GameObject* obj = 0; 
	obj = m_ObjectMap.find(uid)->second;
	return obj;
}

Kaotic_Alpha::GameObject* Kaotic_Alpha::ObjectFactory::CreateObject(sf::RenderWindow* appRef, std::string objectName)
{
	int uid = GetUID();
	GameObject* gameObject;
	if(objectName == "Player"){
		gameObject = new Player(appRef, uid);
	}
	else{
		gameObject = new GameObject(objectName, uid);
	}

	WriteLog << "Creating Game Object(\"" << objectName.c_str() << "\", id: " << uid << ")" <<std::endl;
	m_ObjectMap.insert(std::pair<int, Kaotic_Alpha::GameObject*>(uid, gameObject));
	return gameObject;
}

void  Kaotic_Alpha::ObjectFactory::DestroyObject(GameObject* obj)
{
	std::map<int, GameObject*>::iterator it = m_ObjectMap.find(obj->GetUID());
	delete it->second;
	m_ObjectMap.erase(it);
}

void Kaotic_Alpha::ObjectFactory::Shutdown()
{
	m_ObjectMap.clear();
	delete p_Instance;
	p_Instance = NULL;
}