#ifndef _RGSCENE_H_
#define _RGSCENE_H_

#include <vector>
#include <list>
#include "RGGameObject.h"

namespace RGEngine
{
	class GameObject;

	class Scene
	{
	private:
		friend class Application;

		std::vector<GameObject *> m_pGameObjects;
		std::list<GameObject *> m_pAttachedGameObjects;
		GameObject *m_camera;
		bool m_destroyed;

	public:
		Scene(void);
		virtual ~Scene();

	public:
		GameObject* GetCamera(void) const;
		GameObject** GetGameObjects(void) const;
		int GetGameObjectSize(void) const { return m_pGameObjects.size(); }

		bool GetDestroyed(void) const { return m_destroyed; }

		void PushBackGameObject(GameObject *object); // 먼저 할수록 먼저 업데이트

		void Update(void);
		void Render(void); // 2d transformation

		virtual void OnCreate(void) {}
		virtual void OnDestroy(void) {}
		virtual void OnUpdate(void) {}
		virtual void OnAfterUpdate(void) {}
		virtual void OnRender(void) {}
		virtual void OnAfterRender(void) {}

	};
}

#endif // _RGSCENE_H_