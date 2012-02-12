#ifndef VECTOR2_H
#define VECTOR2_H

namespace Kaotic_Alpha
{
	struct Vector2
	{
		Vector2(float x, float y)
			: X(x), Y(y)
		{}
		Vector2()
			:X(0), Y(0)
		{}

		float X;
		float Y;
	};
}

#endif