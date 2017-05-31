#ifndef _RGCOMPONENT_H_
#define _RGCOMPONENT_H_

#include <typeindex>

namespace RGEngine
{
	// reference
	class GameObject;

	class Component
	{
	private:
		GameObject *m_pGameObject;
		bool m_enabled;

	public:
		Component(GameObject *gameObject);
		virtual ~Component();

	public:
		void SetEnabled(bool flag);
		bool GetEnabled(void) const;

		GameObject* GetGameObject(void) const;

	public:
		virtual void Reset(void) = 0 {}
		virtual std::type_index GetID(void) = 0 { return typeid(Component); }
		virtual std::type_index GetFamilyID(void) = 0 { return typeid(Component); }

		static std::type_index GetStaticID(void) { return typeid(Component); }
		static std::type_index GetStaticFamilyID(void) { return typeid(Component); }

	public:
		virtual void OnCreate(void) {}
		virtual void OnDestroy(void) {}
		virtual void OnEnabled(void) {}
		virtual void OnDisabled(void) {}
		virtual void OnUpdate(void) {}
		virtual void OnRender(void) {}


	};
}

#endif // _RGCOMPONENT_H_