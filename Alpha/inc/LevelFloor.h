#ifndef LEVEL_FLOOR
#define LEVEL_FLOOR

#include "GameObject.h"

namespace Kaotic_Alpha
{
	class LevelFloor
		: public Kaotic_Alpha::GameObject
	{
	public:
		LevelFloor(sf::RenderWindow* app, int uid)
			: Kaotic_Alpha::GameObject("Floor", uid)
		{
			m_AppRef = app;
		}

		void Startup()
		{    
			GameObject::Startup();
			m_MovableComp = new Comp_Movable();
			m_MovableComp->SetPosition(Vector2(0, 360));
			m_CollideComp = new Comp_Collidable(this, 10000, 20);
		}
		
		void Shutdown()
		{
			GameObject::Shutdown();
		}

	private:
	};
}

#endif