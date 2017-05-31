#ifndef _RGCOMPONENTANIMATIONRENDERER_H_
#define _RGCOMPONENTANIMATIONRENDERER_H_

#include "RGComponentRenderer.h"
#include "RGAssetManager.h"

#include <vector>

namespace RGEngine
{
	namespace Components
	{
		class AnimationRenderer : public Renderer
		{
		private:
			std::vector<Assets::Texture *> m_textures;

		public:
			bool loop;
			bool pause;
			float speed;
			float nowFrame;

		public:
			AnimationRenderer(GameObject *gameObject);
			~AnimationRenderer() override;

			Assets::Texture* GetTexture(int index) const;
			const Assets::Texture** GetTextures(void) const;

			int GetSize(void) const;

			void PushBackFrame(std::string path);
			void ReplaceFrame(int index, std::string path);

			void Stop(void);

		public:
			void Reset(void) override;
			std::type_index GetID(void) override { return typeid(AnimationRenderer); }
			std::type_index GetFamilyID(void) override { return typeid(Renderer); }

			static std::type_index GetStaticID(void) { return typeid(AnimationRenderer); }
			static std::type_index GetStaticFamilyID(void) { return typeid(Renderer); }

		public:
			void OnUpdate(void) override;
			void OnRender(void) override;

		};
	}
}

#endif // _RGCOMPONENTANIMATIONRENDERER_H_