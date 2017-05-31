#ifndef _RGASSETSPRITE_H_
#define _RGASSETSPRITE_H_

#include "RGGraphic.h"
#include "RGMath.h"

namespace RGEngine
{
	namespace Assets
	{
		class Texture
		{
		private:
			Graphic *m_graphic;
			LPDIRECT3DTEXTURE9 m_texture;
			bool m_flagColorKey;
			Math::Color m_colorkey;
			std::string m_path;

			int m_width;
			int m_height;

		public:
			Types::Rect sourceRect;
			Math::Color color;
			bool flagAutoRect;

		public:
			Texture(Graphic *graphic);
			~Texture();

			bool Load(std::string path);
			bool Load(std::string path, Math::Color colorkey);
			void Release(void);

			std::string GetPath(void) const;
			Math::Color GetColorkey(void) const;
			int GetWidth(void) const;
			int GetHeight(void) const;
			Types::Size GetSize(void) const;

			void Blt(void);

		};
	}
}

#endif // _RGASSETSPRITE_H_