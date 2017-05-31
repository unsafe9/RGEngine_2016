#include "RGApplication.h"

#include <cassert>

namespace RGEngine
{
	Application::Application(void) : m_time(NULL), m_graphic(NULL), m_input(NULL), m_scene(NULL) {}
	Application::~Application() { Release(); }

	bool Application::Initialize(const wchar_t *title, int width, int height, bool fullscreen)
	{
		m_graphic = new Graphic();
		if (!m_graphic->CreateFrame(title, width, height, fullscreen))
		{
			return false;
		}
		m_input = new Input(m_graphic->GetWindowHandle());
		m_time = new Time();
		m_asset = new AssetManager();
		if (!m_asset->Initialize())
		{
			return false;
		}
		return true;
	}


	void Application::Release(void)
	{
		if (m_scene)
		{
			m_scene->OnDestroy();
			delete m_scene;
			m_scene = NULL;
		}
		if (m_graphic)
		{
			delete m_graphic;
			m_graphic = NULL;
		}
		if (m_input)
		{
			delete m_input;
			m_input = NULL;
		}
		if (m_time)
		{
			delete m_time;
			m_time = NULL;
		}
		if (m_asset)
		{
			delete m_asset;
			m_asset = NULL;
		}
	}

	void Application::ChangeScene(Scene *scene)
	{
		if (m_scene)
		{
			m_scene->m_destroyed = true;
			m_nextScene = scene;
		}
		else
		{
			m_scene = scene;
			m_scene->OnCreate();
		}
	}

	void Application::Update(void)
	{
		m_time->Tick();
		m_input->Update();
		if (m_scene)
		{
			if (m_scene->GetDestroyed())
			{
				m_scene->OnDestroy();
				delete m_scene;
				m_scene = m_nextScene;
				m_nextScene = NULL;
				m_scene->OnCreate();
			}
			m_scene->Update();
		}
	}

	void Application::Render(void)
	{
		if (m_scene)
		{
			m_scene->Render();
		}
	}

	void Application::Exit(void)
	{
		Release();
		exit(0);
	}

}