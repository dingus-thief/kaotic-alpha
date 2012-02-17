#ifndef MESSAGE_SYSTEM_H
#define MESSAGE_SYSTEM_H

#include <vector>
#include "GameMessage.h"

namespace Kaotic_Alpha
{
	class MessageListener;

	class MessageSystem
	{
	public:
		static MessageSystem* GetSingleton();

		void AddListener(Kaotic_Alpha::MessageListener* msgListener){ m_Listeners.push_back(msgListener); }
		void RemoveListener(Kaotic_Alpha::MessageListener* msgListener);
		
		//do not handle cleanup of listeners, they must be shutdown where created
		void ClearListeners() { m_Listeners.clear(); }
		//handle cleanup of messages
		void ClearMessages();
		
		void QueueMessage(Kaotic_Alpha::GameMessage* msg);
		void Startup();
		void Update(float deltaTime);
		void Shutdown();

	private:
		MessageSystem(){}
		std::vector<GameMessage*> m_MsgQueue;
		std::vector<MessageListener*> m_Listeners;
		static Kaotic_Alpha::MessageSystem* p_Instance;
	};
}
#endif