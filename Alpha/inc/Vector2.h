#ifndef VECTOR2_H
#define VECTOR2_H

namespace Kaotic_Alpha
{
	class Vector2
	{
	public:
		Vector2(float x, float y)
			: X(x), Y(y)
		{}
		Vector2()
			:X(0), Y(0)
		{}

		float X,Y;
		Vector2 operator+(const Vector2& vec)
		{
			Vector2 newVector;
			newVector.X = X + vec.X;
			newVector.Y = Y + vec.Y;
			return newVector;
		}
		Vector2 operator-(const Vector2& vec)
		{
			Vector2 newVector;
			newVector.X = X - vec.X;
			newVector.Y = Y - vec.Y;
			return newVector;
		}
	};
}

#endif