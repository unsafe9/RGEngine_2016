#include "RGComponent.h"

namespace RGEngine
{
	Component::Component(GameObject *gameObject) : m_pGameObject(gameObject), m_enabled(true) {}
	Component::~Component() {}

	void Component::SetEnabled(bool flag)
	{
		if (m_enabled != flag)
		{
			m_enabled = flag;
			m_enabled ? OnEnabled() : OnDisabled();
		}
	}

	bool Component::GetEnabled(void) const
	{
		return m_enabled;
	}

	GameObject* Component::GetGameObject(void) const
	{
		return m_pGameObject;
	}
}