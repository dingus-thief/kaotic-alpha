#ifndef CAMERA_H
#define CAMERA_H

#include "BoundingBox.h"
class GameObject;

namespace Kaotic_Alpha
{
	//temporarily a singleton to ease access

	class Camera
	{
	public:
		Camera()
		{
			m_CameraBounds.SetPosition(Vector2(0,0));
			m_Tracking = false;
		}

		Vector2 TranslateWorldCoordsToLocal(Vector2 worldCoords)
		{
			return Vector2(worldCoords.X - m_CameraBounds.GetPosition().X, m_CameraBounds.GetHeight() - worldCoords.Y + m_CameraBounds.GetPosition().Y);
		}

		void SetSize(float width, float height){
			m_CameraBounds.SetWidth(width);
			m_CameraBounds.SetHeight(height);
		}
		
		void Update(float deltaTime);

		void FollowTarget(GameObject* obj)
		{
			m_Tracking = true;
			m_FollowTarget = obj;
		}

	private:
		BoundingBox	m_CameraBounds;
		GameObject*	m_FollowTarget;
		bool m_Tracking;

	};
}

#endif