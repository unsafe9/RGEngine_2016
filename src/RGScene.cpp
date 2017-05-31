#include "RGScene.h"
#include "RGGameObject.h"

namespace RGEngine
{
	Scene::Scene(void) : m_destroyed(false)
	{
		m_camera = new GameObject();
	}

	Scene::~Scene()
	{
		for (auto &i : m_pGameObjects)
		{
			delete i;
		}
		m_pGameObjects.clear();

		for (auto &i : m_pAttachedGameObjects)
		{
			delete i;
		}
		m_pAttachedGameObjects.clear();

		delete m_camera;
	}

	GameObject* Scene::GetCamera(void) const
	{
		return m_camera;
	}

	GameObject** Scene::GetGameObjects(void) const
	{ 
		return (GameObject **)m_pGameObjects.data();
	}

	void Scene::PushBackGameObject(GameObject *object)
	{
		m_pAttachedGameObjects.push_back(object);
		object->parent = m_camera;
	}

	void Scene::Update(void)
	{
		for (auto &i : m_pAttachedGameObjects)
		{
			m_pGameObjects.push_back(i);
			i->OnCreate();
		}
		m_pAttachedGameObjects.clear();
		
		m_camera->Update();

		OnUpdate();

		for (auto &i : m_pGameObjects)
		{
			if (i->GetEnabled())
			{
				i->OnUpdate();
			}
		}

		for (auto &i : m_pGameObjects)
		{
			if (i->GetEnabled())
			{
				i->Update();
			}
		}

		for (auto &i : m_pGameObjects)
		{
			if (i->GetEnabled())
			{
				i->OnAfterUpdate();
			}
		}

		OnAfterUpdate();

		for (auto i = m_pGameObjects.begin(); i != m_pGameObjects.end(); ++i)
		{
			if ((*i)->GetDestroyed())
			{
				(*i)->OnDestroy();
				delete *i;
				i = m_pGameObjects.erase(i);
				if (i == m_pGameObjects.end())
				{
					break;
				}
			}
		}
	}

	void Scene::Render(void)
	{
		m_camera->Render();

		OnRender();

		for (auto &i : m_pGameObjects)
		{
			if (i->GetEnabled())
			{
				i->OnRender();
			}
		}

		for (auto &i : m_pGameObjects)
		{
			if (i->GetEnabled())
			{
				i->Render();
			}
		}

		for (auto &i : m_pGameObjects)
		{
			if (i->GetEnabled())
			{
				i->OnAfterRender();
			}
		}

		OnAfterRender();
	}
}