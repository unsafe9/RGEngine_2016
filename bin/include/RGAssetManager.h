#ifndef _RGASSETMANAGER_H_
#define _RGASSETMANAGER_H_

#include "RGAssetTextureManager.h"
#include "RGAssetSoundManager.h"

namespace RGEngine
{
	class AssetManager
	{
	private:
		Assets::TextureManager *m_texture;
		Assets::SoundManager *m_sound;

	public:
		AssetManager(void);
		~AssetManager();

		bool Initialize(void);
		void Release(void);

		Assets::TextureManager* GetTextureManager(void) const { return m_texture; }
		Assets::SoundManager* GetSoundManager(void) const { return m_sound; }

	};
}

#endif // _RGASSETMANAGER_H_