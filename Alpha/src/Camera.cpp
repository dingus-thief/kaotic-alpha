#include "Camera.h"
#include "GameObject.h"

void Kaotic_Alpha::Camera::Update(float deltaTime)
{

	//temp
	int levelBounds_MINx = 0;
	int levelBounds_MAXx = 2500;
	int levelBounds_MINy = 0;
	int levelBounds_MAXy = 2500;

	if(m_Tracking && m_FollowTarget != NULL)
	{
		Vector2 pos = m_FollowTarget->GetMovableComponent()->GetPosition();
		Vector2 cameraPos;
		
		//clamp camera to max X
		if((pos.X - m_CameraBounds.GetWidth()/2) >= levelBounds_MAXx){
			cameraPos.X = levelBounds_MAXx;
		}
		//clamp camera to min X
		else if((pos.X - m_CameraBounds.GetWidth()/2) <= levelBounds_MINx){		
			cameraPos.X = levelBounds_MINx;
		}
		//don't clamp camera X
		else{			
			cameraPos.X = pos.X - m_CameraBounds.GetWidth()/2;
		}
		//clamp camera to max Y
		if((pos.Y - m_CameraBounds.GetHeight()/2) >= levelBounds_MAXy){
			cameraPos.Y = levelBounds_MAXy;
		}
		//clamp camera to min y
		else if((pos.Y - m_CameraBounds.GetHeight()/2) <= levelBounds_MINy){
			cameraPos.Y = levelBounds_MINy;
		}
		//don't clamp camera Y
		else{
			cameraPos.Y = pos.Y - m_CameraBounds.GetHeight()/2;
		}

		m_CameraBounds.SetPosition(cameraPos);
	}
}