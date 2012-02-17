#ifndef GAME_MESSAGE_H
#define GAME_MESSAGE_H

namespace Kaotic_Alpha
{
	class GameMessage
	{
	public:
		// currently using enum for message type
		enum MSG_TYPE
		{
			COLLISION = 0,
			INTERACTION
		};

		GameMessage(MSG_TYPE msgType)
			: TimeDelay(0), MsgType(msgType)
		{}

		float TimeDelay; //in seconds		
		int TargetID,SourceID;
		MSG_TYPE MsgType;
	};
}

#endif