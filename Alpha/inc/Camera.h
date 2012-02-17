#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

namespace Kaotic_Alpha
{
	class Camera
		: public Kaotic_Alpha::GameObject
	{
	public:
		Camera(sf::RenderWindow* app)
			: m_AppRef(app), Kaotic_Alpha::GameObject("Camera")
		{}

		void Startup()
		{    
			GameObject::Startup();
			m_MovableComp = new Comp_Movable();

		}

		void Update(float deltaTime)
		{
		}

		void Shutdown()
		{
			GameObject::Shutdown();
		}
	private:
		sf::RenderWindow* m_AppRef;

	};
}

#endif