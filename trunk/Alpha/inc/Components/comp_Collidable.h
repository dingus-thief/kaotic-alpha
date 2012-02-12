#ifndef COMP_COLLIDABLE
#define COMP_COLLIDABLE

#include "Components/Component.h"
#include "Vector2.h"
#include "BoundingBox.h"

namespace Kaotic_Alpha
{
	class Comp_Collidable
		: public Component
	{
	public:
		void OnCollide(){}

	private:
		BoundingBox m_BoundingBox;
	};
}

#endif