#include "RGAssetTexture.h"

namespace RGEngine
{
	namespace Assets
	{
		Texture::Texture(Graphic *graphic) :
			m_graphic(graphic), m_texture(NULL), m_flagColorKey(false),
			m_colorkey(),
			m_path(), m_width(0), m_height(0), sourceRect(), flagAutoRect(true), color(1.0f, 1.0f, 1.0f, 1.0f) { }
		Texture::~Texture() { Release(); }

		bool Texture::Load(std::string path)
		{
			m_path = path;
			m_flagColorKey = false;
			if (FAILED(D3DXCreateTextureFromFileExA(
				m_graphic->GetDevice(),
				path.c_str(),
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT_NONPOW2,
				1,
				0,
				D3DFMT_A8B8G8R8,
				D3DPOOL_MANAGED,
				D3DX_FILTER_NONE,
				D3DX_FILTER_NONE,
				NULL,
				NULL,
				NULL,
				&m_texture)))
			{
				return false;
			}

			D3DSURFACE_DESC desc; // texture의 크기를 구함
			m_texture->GetLevelDesc(0U, &desc);
			m_width = sourceRect.right = desc.Width;
			m_height = sourceRect.bottom = desc.Height;

			return true;
		}
		bool Texture::Load(std::string path, Math::Color colorkey)
		{
			m_path = path;
			m_flagColorKey = true;
			m_colorkey = colorkey;
			if (FAILED(D3DXCreateTextureFromFileExA(
				m_graphic->GetDevice(),
				path.c_str(),
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT_NONPOW2,
				1,
				0,
				D3DFMT_A8B8G8R8,
				D3DPOOL_MANAGED,
				D3DX_FILTER_NONE,
				D3DX_FILTER_NONE,
				(D3DCOLOR)colorkey,
				NULL,
				NULL,
				&m_texture)))
			{
				return false;
			}

			D3DSURFACE_DESC desc; // texture의 크기를 구함
			m_texture->GetLevelDesc(0U, &desc);
			m_width = sourceRect.right = desc.Width;
			m_height = sourceRect.bottom = desc.Height;

			return true;
		}
		void Texture::Release(void)
		{
			if (m_texture)
			{
				m_texture->Release();
				m_texture = NULL;
			}
		}

		std::string Texture::GetPath(void) const
		{
			return m_path;
		}
		Math::Color Texture::GetColorkey(void) const
		{
			return m_colorkey;
		}
		int Texture::GetWidth(void) const
		{
			return m_width;
		}
		int Texture::GetHeight(void) const
		{
			return m_height;
		}
		Types::Size Texture::GetSize(void) const
		{
			return Types::Size(m_width, m_height);
		}

		void Texture::Blt(void)
		{
			m_graphic->GetDevice()->SetTexture(0UL, m_texture);
			m_graphic->GetSprite()->Draw(m_texture, flagAutoRect ? NULL : (LPRECT)&sourceRect, NULL, NULL, (D3DCOLOR)color);
		}
	}
}