#include "RGAssetTextureManager.h"

namespace RGEngine
{
	namespace Assets
	{
		TextureManager::TextureManager(Graphic *graphic) : m_graphic(graphic) {}
		TextureManager::~TextureManager()
		{
			ReleaseAll();
		}
		bool TextureManager::Load(std::string path)
		{
			if (m_textures[path] != NULL)
			{
				return true;
			}
			Texture *t = new Texture(m_graphic);
			bool res = t->Load(path);
			m_textures[path] = t;
			return std::move(res);
		}
		bool TextureManager::Load(std::string path, Math::Color colorkey)
		{
			if (m_textures[path] != NULL)
			{
				return true;
			}
			Texture *t = new Texture(m_graphic);
			bool res = t->Load(path, colorkey);
			m_textures[path] = t;
			return std::move(res);
		}
		void TextureManager::Release(std::string path)
		{
			m_textures[path]->Release();
			m_textures.erase(path);
		}
		void TextureManager::ReleaseAll(void)
		{
			for (auto &i : m_textures)
			{
				(i.second)->Release();
			}
			m_textures.clear();
		}
		Texture* TextureManager::Get(std::string path)
		{
			return m_textures[path];
		}
	}
}