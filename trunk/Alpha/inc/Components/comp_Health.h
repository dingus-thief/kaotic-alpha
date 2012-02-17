#ifndef COMP_HEALTH_H
#define COMP_HEALTH_H

#include "Components/Component.h"

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
		void CheckDeath() { if(m_CurrentHealth == 0){ m_IsAlive = false;} else{ m_IsAlive = true;} }
		unsigned int GetCurrentHealth() const { return m_CurrentHealth; }
		unsigned int GetMaxHealth() const { return m_MaxHealth; }
		unsigned int SetMaxHealth(int value) { m_MaxHealth = value; ResetHealth(); }

	private:
		bool m_IsAlive;
		unsigned int m_CurrentHealth;
		unsigned int m_MaxHealth;
		//unsigned int m_TempHealthBonus (powerup)
	};
}

#endif