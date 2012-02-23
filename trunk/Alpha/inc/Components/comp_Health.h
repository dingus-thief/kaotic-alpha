#ifndef COMP_HEALTH_H
#define COMP_HEALTH_H

#include "Components/Component.h"
#include "Game.h"
#include "MessageSystem.h"

namespace Kaotic_Alpha
{
	class Comp_Health
		: public Component
	{
	public:
		Comp_Health()
			: m_IsAlive(true), m_MaxHealth(1)
		{ 
			ResetHealth();
			m_NumLives = 5;
		}
		Comp_Health(int maxHealth)
			: m_IsAlive(true), m_MaxHealth(maxHealth)
		{
			ResetHealth();
		}
		Comp_Health(int maxHealth, int currentHealth)
			: m_IsAlive(true), m_MaxHealth(maxHealth), m_CurrentHealth(currentHealth)
		{}

		//add a positive or negative amount of health to player
		//clamp values to (0, maxHealth)
		void ModifyHealth(int value)
		{
			if((m_CurrentHealth + value) < 0)
				m_CurrentHealth = 0;
			else if((m_CurrentHealth + value) > m_MaxHealth)
				m_CurrentHealth = m_MaxHealth;
			else
				m_CurrentHealth += value;
		}
		void ResetHealth() { m_CurrentHealth = m_MaxHealth; }
		void CheckDeath() 
		{
			if(m_CurrentHealth <= 0 && m_IsAlive == true){ 
				m_IsAlive = false; --m_NumLives;
			} 
			else{ 
				m_IsAlive = true;
			} 
		}
		unsigned int GetCurrentLives() const { return m_NumLives; }
		unsigned int GetCurrentHealth() const { return m_CurrentHealth; }
		unsigned int GetMaxHealth() const { return m_MaxHealth; }
		void SetMaxHealth(int value) { m_MaxHealth = value; ResetHealth(); }

		void AddLife(){ ++m_NumLives; }
		void RemoveLife()
		{
			--m_NumLives; 
			if(m_NumLives <= 0){
				GameMessage* msg = new GameMessage(Kaotic_Alpha::GameMessage::STATECHANGE);
				msg->TargetState = QUITLEVEL;
				MessageSystem::GetSingleton()->QueueMessage(msg);
			}
		}

	private:
		bool m_IsAlive;
		unsigned int m_CurrentHealth;
		unsigned int m_MaxHealth;
		unsigned int m_NumLives;
	};
}

#endif