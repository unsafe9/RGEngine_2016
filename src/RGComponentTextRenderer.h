#ifndef _RGCOMPONENTTEXTRENDERER_H_
#define _RGCOMPONENTTEXTRENDERER_H_

#include "RGComponentRenderer.h"
#include "RGAssetManager.h"

namespace RGEngine
{
	namespace Components
	{
		class TextRenderer : public Renderer, virtual public ResetableComponentInterface
		{
		private:
			LPD3DXFONT m_font;
			std::string m_name;
			unsigned int m_size;
			unsigned int m_weight;
			bool m_italic;

		public:
			std::string text;
			Types::Rect sourceRect;
			bool flagAutoRect; // default true
			DWORD format; // DT_LEFT | DT_TOP | DT_NOCLIP
			Math::Color color;

		public:
			TextRenderer(GameObject *gameObject);
			~TextRenderer() override;

			bool SetFont(std::string name, unsigned int size, unsigned int weight = FW_NORMAL, bool italic = false);
			void ReleaseFont(void);

			void OnLostDevice(void) override;
			void OnResetDevice(void) override;

			LPD3DXFONT GetDXFont(void) const;
			std::string GetFontName(void) const;
			unsigned int GetFontSize(void) const;
			unsigned int GetFontWeight(void) const;
			bool GetFontItalic(void) const;

		public:
			void Reset(void) override;
			std::type_index GetID(void) override { return typeid(TextRenderer); }
			std::type_index GetFamilyID(void) override { return typeid(Renderer); }

			static std::type_index GetStaticID(void) { return typeid(TextRenderer); }
			static std::type_index GetStaticFamilyID(void) { return typeid(Renderer); }

		public:
			void OnRender(void) override;

		};
	}
}

#endif // _RGCOMPONENTTEXTRENDERER_H_