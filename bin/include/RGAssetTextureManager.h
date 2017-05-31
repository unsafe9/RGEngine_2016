#ifndef _RGASSETTEXTUREMANAGER_H_
#define _RGASSETTEXTUREMANAGER_H_

#include "RGGraphic.h"
#include "RGAssetTexture.h"
#include <map>

namespace RGEngine
{
	namespace Assets
	{
		class TextureManager
		{
		private:
			std::map<std::string, Texture*> m_textures;
			Graphic *m_graphic;

		public:
			TextureManager(Graphic *graphic);
			~TextureManager();

			bool Load(std::string path);
			bool Load(std::string path, Math::Color colorkey);

			void Release(std::string path);
			void ReleaseAll(void);

			Texture* Get(std::string path);

		};
	}
}

#endif // _RGASSETTEXTUREMANAGER_H_