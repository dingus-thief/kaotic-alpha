#ifndef GAME_MESSAGE_H
#define GAME_MESSAGE_H

namespace Kaotic_Alpha
{
	enum GAMESTATE;

	class GameMessage
	{
	public:

		// currently using enum for message type
		enum MSG_TYPE
		{
			COLLISION = 0,
			INTERACTION,
			STATECHANGE
		};

		GameMessage(MSG_TYPE msgType)
			: TimeDelay(0), MsgType(msgType)
		{}

		float TimeDelay; //in seconds		
		int TargetID,SourceID;
		GAMESTATE TargetState;
		MSG_TYPE MsgType;
	};
}

#endif