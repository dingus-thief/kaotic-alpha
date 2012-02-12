#include "ObjectFactory.h"
#include "GameLog.h"

Kaotic_Alpha::ObjectFactory* Kaotic_Alpha::ObjectFactory::pInstance = NULL;
int Kaotic_Alpha::ObjectFactory::next_UID = 1;

Kaotic_Alpha::ObjectFactory* Kaotic_Alpha::ObjectFactory::GetSingleton()
{
  if(pInstance == NULL){
    pInstance = new ObjectFactory();
  }
  return pInstance;
}

Kaotic_Alpha::ObjectFactory::ObjectFactory()
{}

Kaotic_Alpha::GameObject* Kaotic_Alpha::ObjectFactory::GetObject(int uid)
{
	Kaotic_Alpha::GameObject* obj = 0;
	std::map<int, Kaotic_Alpha::GameObject*>::iterator it; 
	obj = objectMap.find(uid)->second;
	return obj;
}

Kaotic_Alpha::GameObject* Kaotic_Alpha::ObjectFactory::CreateObject(std::string objectName)
{
	Kaotic_Alpha::GameObject* gameObject = new Kaotic_Alpha::GameObject(objectName);
	int uid = GetUID();
	WriteLog << "Creating Game Object(\"" << objectName.c_str() << "\", id: " << uid << ")" <<std::endl;
	objectMap.insert(std::pair<int, Kaotic_Alpha::GameObject*>(uid, gameObject));
	return gameObject;
}

void Kaotic_Alpha::ObjectFactory::DestroyAllObjects()
{
	for(std::map<int,Kaotic_Alpha::GameObject*>::iterator it = objectMap.begin(); it != objectMap.end(); ++it){
		GameObject* obj = it->second;
		WriteLog << "Deleting Game Object(\"" << obj->GetName() << "\", id: " << it->first << ")" <<std::endl;
		delete it->second;
	}

	objectMap.clear();
}

void Kaotic_Alpha::ObjectFactory::Shutdown()
{
	DestroyAllObjects();
	delete pInstance;
	pInstance = NULL;
}