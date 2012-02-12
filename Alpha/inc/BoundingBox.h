#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Vector2.h"

namespace Kaotic_Alpha
{
	class BoundingBox
	{
	public:
		BoundingBox()
			: m_Position(0,0)
		{}
		BoundingBox(float x, float y)
			: m_Position(x, y)
		{}
		BoundingBox(float x, float y, int width, int height)
			: m_Position(x, y), m_Width(width), m_Height(height)
		{}

		bool Intersects(BoundingBox other) 
		{ 
			Vector2 otherPos = other.GetPosition();

		    if((m_Position.Y + m_Height) < otherPos.Y) return(false);
			if (m_Position.Y > (otherPos.Y + other.GetHeight())) return(false);
			if ((m_Position.X + m_Width) < otherPos.X) return(false);
			if (m_Position.X > (otherPos.X + other.GetWidth())) return(false);

			return true; 
		}
		void SetWidth(unsigned int value) { m_Width = value; }
		void SetHeight(unsigned int value) { m_Height = value; }

		Vector2 GetPosition() const { return m_Position; }
		unsigned int GetHeight() const { return m_Height; }
		unsigned int GetWidth() const { return m_Width; }

	private:
		unsigned int m_Width;
		unsigned int m_Height;
		Vector2 m_Position;
	};
}

#endif