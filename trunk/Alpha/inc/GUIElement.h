#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <SFML/Graphics.hpp>
#include "GameLog.h"

class GUIElement
{
public:
	GUIElement(sf::RenderWindow* appRef)
		: m_AppRef(appRef)
	{}

	virtual void Startup(){}
	virtual void Update(float deltaTime){}
	virtual void Shutdown(){}
	virtual void Render(){}

protected:
	sf::RenderWindow*	m_AppRef;
};

#endif