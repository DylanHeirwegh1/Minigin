#include "MiniginPCH.h"
#include "Subject.h"

void Subject::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
}

void Subject::RemoveObserver(Observer* observer)
{
	for (size_t i = 0; i < m_Observers.size(); i++)
	{
		if (observer == m_Observers[i])
		{
			m_Observers.erase(m_Observers.begin() + i);
		}
	}
}

void Subject::Notify(const dae::GameObject& actor, Event event)
{
	for (size_t i = 0; i < m_Observers.size(); i++)
	{
		m_Observers[i]->Notify(actor, event);
	}
}