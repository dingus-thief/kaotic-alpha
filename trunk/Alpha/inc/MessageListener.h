#ifndef MESSAGELISTENER_H
#define MESSAGELISTENER_H

namespace Kaotic_Alpha
{
	class GameMessage;

	class MessageListener
	{
	public:
		virtual GameMessage* ProcessMessage(GameMessage* msg){ return NULL; }
	};
}

#endif