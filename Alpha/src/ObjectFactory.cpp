#include "ObjectFactory.h"
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
	std::map<int, Kaotic_Alpha::GameObject*>::iterator it; 
	obj = m_ObjectMap.find(uid)->second;
	return obj;
}

Kaotic_Alpha::GameObject* Kaotic_Alpha::ObjectFactory::CreateObject(std::string objectName)
{
	int uid = GetUID();
	Kaotic_Alpha::GameObject* gameObject = new Kaotic_Alpha::GameObject(objectName, uid);
	WriteLog << "Creating Game Object(\"" << objectName.c_str() << "\", id: " << uid << ")" <<std::endl;
	m_ObjectMap.insert(std::pair<int, Kaotic_Alpha::GameObject*>(uid, gameObject));
	return gameObject;
}

void Kaotic_Alpha::ObjectFactory::DestroyAllObjects()
{
	for(std::map<int,Kaotic_Alpha::GameObject*>::iterator it = m_ObjectMap.begin(); it != m_ObjectMap.end(); ++it){
		GameObject* obj = it->second;
		WriteLog << "Deleting Game Object(\"" << obj->GetName() << "\", id: " << it->first << ")" <<std::endl;
		delete it->second;
	}

	m_ObjectMap.clear();
}

void Kaotic_Alpha::ObjectFactory::Shutdown()
{
	DestroyAllObjects();
	delete p_Instance;
	p_Instance = NULL;
}