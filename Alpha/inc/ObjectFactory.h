#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "GameObject.h"
#include <map>

namespace Kaotic_Alpha
{
	class ObjectFactory
	{
	public:
		static ObjectFactory* GetSingleton();
		Kaotic_Alpha::GameObject* CreateObject(std::string objectName);
		void DestroyAllObjects();
		void Shutdown();
		GameObject* GetObject(int uid);

	private:
		int GetUID() const { return next_UID++; }

		std::map<int, Kaotic_Alpha::GameObject*> m_ObjectMap;
		static ObjectFactory* p_Instance;
		ObjectFactory();
		static int next_UID;
	};
}

#endif