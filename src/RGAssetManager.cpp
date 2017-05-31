#include "RGAssetManager.h"

#include "RGApplication.h"

namespace RGEngine
{
	AssetManager::AssetManager(void) : m_texture(NULL), m_sound(NULL) {}
	AssetManager::~AssetManager() { Release(); }

	bool AssetManager::Initialize(void)
	{
		m_texture = new Assets::TextureManager(RGGraphic);
		m_sound = new Assets::SoundManager();

		return true;
	}
	void AssetManager::Release(void)
	{
		if (m_texture)
		{
			delete m_texture;
			m_texture = NULL;
		}
		if (m_sound)
		{
			delete m_sound;
			m_sound = NULL;
		}
	}

}