#include "RGComponentTextRenderer.h"
#include "RGApplication.h"

namespace RGEngine
{
	namespace Components
	{
		TextRenderer::TextRenderer(GameObject *gameObject) : Renderer(gameObject), m_font(NULL), text(""), sourceRect(), format(DT_LEFT | DT_TOP | DT_NOCLIP), color(0.0f, 0.0f, 0.0f, 1.0f), flagAutoRect(true) {}
		TextRenderer::~TextRenderer() { ReleaseFont(); }

		bool TextRenderer::SetFont(std::string name, unsigned int size, unsigned int weight, bool italic)
		{
			m_name = name;
			m_size = size;
			m_weight = weight;
			m_italic = italic;

			return SUCCEEDED(D3DXCreateFontA(
				RGGraphic->GetDevice(),
				m_size,						// Font height
				0U,							// Font width
				m_weight,					// Font Weight
				D3DX_DEFAULT,				// MipLevels
				m_italic,					// Italic
				DEFAULT_CHARSET,			// CharSet
				OUT_DEFAULT_PRECIS,			// OutputPrecision
				ANTIALIASED_QUALITY,		// Quality 
				DEFAULT_PITCH | FF_DONTCARE,// PitchAndFamily
				m_name.c_str(),				// pFacename
				&m_font));					// ppFont

			RGGraphic->PushResetableComponent(this);
		}
		void TextRenderer::ReleaseFont(void)
		{
			if (m_font)
			{
				RGGraphic->PopResetableComponent(this);
				m_font->Release();
				m_font = NULL;
			}
		}

		void TextRenderer::OnLostDevice(void)
		{
			if (m_font)
			{
				m_font->OnLostDevice();
			}
		}

		void TextRenderer::OnResetDevice(void)
		{
			if (m_font)
			{
				m_font->OnResetDevice();
			}
		}

		LPD3DXFONT TextRenderer::GetDXFont(void) const
		{
			return m_font;
		}

		std::string TextRenderer::GetFontName(void) const
		{
			return m_name;
		}
		unsigned int TextRenderer::GetFontSize(void) const
		{
			return m_size;
		}
		unsigned int TextRenderer::GetFontWeight(void) const
		{
			return m_weight;
		}
		bool TextRenderer::GetFontItalic(void) const
		{
			return m_italic;
		}

		void TextRenderer::Reset(void)
		{
			ReleaseFont();
		}
		void TextRenderer::OnRender(void)
		{
			if (m_font)
			{
				m_font->DrawTextA(
					RGGraphic->GetSprite(),
					text.c_str(),
					-1,
					flagAutoRect ? NULL : (LPRECT)&sourceRect,
					format,
					color);
			}
		}
	}
}