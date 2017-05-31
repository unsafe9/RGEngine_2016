#include "RGComponentAnimationRenderer.h"
#include "RGApplication.h"
#include <cassert>

namespace RGEngine
{
	namespace Components
	{
		AnimationRenderer::AnimationRenderer(GameObject *gameObject) : Renderer(gameObject), loop(true), pause(false), nowFrame(0.0f), speed(1.0f) {}
		AnimationRenderer::~AnimationRenderer() {}
		Assets::Texture* AnimationRenderer::GetTexture(int index) const
		{
			return m_textures[index];
		}
		const Assets::Texture** AnimationRenderer::GetTextures(void) const
		{
			return (const Assets::Texture**)m_textures.data();
		}

		int AnimationRenderer::GetSize(void) const
		{
			return m_textures.size();
		}

		void AnimationRenderer::PushBackFrame(std::string path)
		{
			if (RGAssetTexture->Get(path) == NULL)
			{
				RGAssetTexture->Load(path);
			}
			m_textures.push_back(RGAssetTexture->Get(path));
		}

		void AnimationRenderer::ReplaceFrame(int index, std::string path)
		{
			assert((size_t)index < m_textures.size());
			if (RGAssetTexture->Get(path) == NULL)
			{
				RGAssetTexture->Load(path);
			}
			m_textures[index] = RGAssetTexture->Get(path);
		}

		void AnimationRenderer::Stop(void)
		{
			nowFrame = 0.0f;
			pause = true;
		}

		void AnimationRenderer::Reset(void)
		{
			m_textures.clear();
		}
		void AnimationRenderer::OnUpdate(void)
		{
			if (!pause)
			{
				nowFrame += speed * deltaTime();
				if (nowFrame >= m_textures.size())
				{
					nowFrame = 0.0f;
					if (!loop) pause = true;
				}
			}
		}
		void AnimationRenderer::OnRender(void)
		{
			if (!m_textures.empty())
			{
				m_textures[(int)nowFrame]->Blt();
			}
		}
	}
}