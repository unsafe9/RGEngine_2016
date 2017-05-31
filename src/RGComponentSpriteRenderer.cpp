#include "RGComponentSpriteRenderer.h"

#include "RGApplication.h"

namespace RGEngine
{
	namespace Components
	{
		SpriteRenderer::SpriteRenderer(GameObject *gameObject) : Renderer(gameObject)
		{
			Reset();
		}
		SpriteRenderer::~SpriteRenderer() {}
		Assets::Texture* SpriteRenderer::GetTexture(void) const
		{
			return m_texture;
		}
		void SpriteRenderer::SetTexture(std::string path)
		{
			if (RGAssetTexture->Get(path) == NULL)
			{
				RGAssetTexture->Load(path);
			}
			m_texture = RGAssetTexture->Get(path);
		}
		void SpriteRenderer::Reset(void)
		{
			m_texture = NULL;
		}
		void SpriteRenderer::OnRender(void)
		{
			if (m_texture)
			{
				m_texture->Blt();
			}
		}
	}
}