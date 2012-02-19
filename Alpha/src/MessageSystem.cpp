#include "MessageSystem.h"
#include "MessageListener.h"
#include "GameLog.h"

Kaotic_Alpha::MessageSystem* Kaotic_Alpha::MessageSystem::p_Instance =  NULL;


Kaotic_Alpha::MessageSystem* Kaotic_Alpha::MessageSystem::GetSingleton()
{
	if(p_Instance == NULL){
		p_Instance = new MessageSystem();
	}
	return p_Instance;
}

void Kaotic_Alpha::MessageSystem::Shutdown()
{
	ClearMessages();
	ClearListeners();
	delete p_Instance;
	p_Instance = NULL;
}

void Kaotic_Alpha::MessageSystem::Update(float deltaTime)
{
	//read all messages back to front, so messages can be removed
	for(int i = static_cast<int>(m_MsgQueue.size()-1); i >= 0; --i)
	{
		GameMessage* msg = m_MsgQueue.at(i);
		if(msg != NULL && msg->TimeDelay <= 0)
		{
			//process message by sending a reference to all listeners
			for(std::vector<MessageListener*>::iterator listenerIt = m_Listeners.begin(); listenerIt != m_Listeners.end(); ++listenerIt)
			{
				GameMessage* returnMsg = (*listenerIt)->ProcessMessage(msg);
				break;
			}

			m_MsgQueue.erase(m_MsgQueue.begin() + i);
		}
		else if(msg != NULL){
			msg->TimeDelay -= deltaTime;
		}
	}
}

void Kaotic_Alpha::MessageSystem::RemoveListener(Kaotic_Alpha::MessageListener* msgListener)
{
	for(std::vector<MessageListener*>::iterator it = m_Listeners.begin(); it != m_Listeners.end(); ++it)
	{
		if((*it) == msgListener)
		{
			m_Listeners.erase(it);
			break;
		}
	}
}

void Kaotic_Alpha::MessageSystem::QueueMessage(Kaotic_Alpha::GameMessage* msg)
{ 
	m_MsgQueue.push_back(msg);
	std::cout << "queueing message" << std::endl;
}

void Kaotic_Alpha::MessageSystem::ClearMessages() 
{
	for(std::vector<GameMessage*>::iterator it = m_MsgQueue.begin(); it != m_MsgQueue.end(); ++it){
		delete *it;
	}
	m_MsgQueue.clear();
}