#ifndef _RGAPPLICATION_H_
#define _RGAPPLICATION_H_

#include "RGGraphic.h"
#include "RGInput.h"
#include "RGTime.h"
#include "RGAssetManager.h"
#include "RGScene.h"

namespace RGEngine
{
#define RGApp (RGEngine::Application::GetInstance())
#define RGGraphic (RGEngine::Application::GetInstance()->GetGraphic())
#define RGInput (RGEngine::Application::GetInstance()->GetInput())
#define RGTime (RGEngine::Application::GetInstance()->GetTime())
#define RGAsset (RGEngine::Application::GetInstance()->GetAsset())
#define RGAssetTexture (RGEngine::Application::GetInstance()->GetAsset()->GetTextureManager())
#define RGAssetSound ((RGEngine::Application::GetInstance()->GetAsset()->GetSoundManager()))


	class Application
	{
	private:
		Graphic *m_graphic;
		Input *m_input;
		Time *m_time;
		Scene *m_scene;
		Scene *m_nextScene;
		AssetManager *m_asset;

	private:
		Application(void);
		~Application();

	public:
		// 싱글톤(Singleton)
		static Application* GetInstance(void)
		{
			static Application instance;
			return &instance;
		}

		bool Initialize(const wchar_t *title, int width, int height, bool fullscreen);
		void Release(void);

		Graphic* GetGraphic(void) const { return m_graphic; }
		Input* GetInput(void) const { return m_input; }
		Time* GetTime(void) const { return m_time; }
		AssetManager* GetAsset(void) const { return m_asset; }

		void ChangeScene(Scene *scene);
		Scene* GetScene(void) const { return m_scene; }
		template<typename SceneType>
		SceneType* GetScene(void) const { return dynamic_cast<SceneType*>(m_scene); }

	public:
		// 프레임갱신, 화면에 출력, 앱종료
		void Update(void);
		void Render(void);
		void Exit(void);

	};
	inline double deltaTime(void)
	{
		return RGEngine::Application::GetInstance()->GetTime()->GetElapsedTime();
	}
}

#endif // _RGAPPLICATION_H_