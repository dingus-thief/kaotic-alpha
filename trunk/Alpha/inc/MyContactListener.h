#ifndef MYCONTACTLISTENER
#define MYCONTACTLISTENER

#include "GameLog.h"
#include <Box2D/Box2D.h>
#include "MessageSystem.h"

class MyContactListener : public b2ContactListener
{
	void SendContactMsg(bool contact)
	{	
		Kaotic_Alpha::GameMessage* msg = new Kaotic_Alpha::GameMessage(Kaotic_Alpha::GameMessage::PLAYER_FOOTCONTACT);
		if(contact)
			msg->TargetID = 1;
		else
			msg->TargetID = -1;
		Kaotic_Alpha::MessageSystem::GetSingleton()->QueueMessage(msg);
	}

	void BeginContact(b2Contact* contact)
	{
		//check if fixture A was the foot sensor
		void* fixtureUserData = contact->GetFixtureA()->GetUserData();
		if ( (int)fixtureUserData == 3 )
			SendContactMsg(true);

		//check if fixture B was the foot sensor
		fixtureUserData = contact->GetFixtureB()->GetUserData();
		if ( (int)fixtureUserData == 3 )
			SendContactMsg(true);
	}

	void EndContact(b2Contact* contact)
	{
		//check if fixture A was the foot sensor
		void* fixtureUserData = contact->GetFixtureA()->GetUserData();
		if ( (int)fixtureUserData == 3 )
			SendContactMsg(false);

		//check if fixture B was the foot sensor
		fixtureUserData = contact->GetFixtureB()->GetUserData();
		if ( (int)fixtureUserData == 3 )
			SendContactMsg(false);
	}
};

#endif