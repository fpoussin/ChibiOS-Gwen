
#include "Gwen/Renderers/ChibiGFX.h"
#include "Gwen/Gwen.h"
#include "Gwen/Utility.h"
#include "Gwen/Platform.h"

#include <math.h>

//#define DEBUG_RENDERER

#ifdef DEBUG_RENDERER
extern "C" {
	#include "ch.h"
	#include "hal.h"
	#include "chprintf.h"
	#include <string>
}
#endif

namespace Gwen
{
    namespace Renderer
    {
        ChibiGFX::ChibiGFX()
        {
		m_fScale = 1.0f;
		gdispInit();
		gdispClear(0);
		m_font = gdispOpenFont("UI2 Double");
        }

        ChibiGFX::~ChibiGFX()
        {
		if ( GetCTT() )
			GetCTT()->ShutDown();
        }
        
        void ChibiGFX::SetDrawColor( Gwen::Color const& color )
        {
		m_color = RGB2COLOR(color.r, color.g, color.b);
        }

        inline Gwen::Color ChibiGFX::BlendColor(Gwen::Color const& c1, Gwen::Color const& c2) const
        {
		Gwen::Color result;
		float a1 = c1.a / 255.0;
		float a2 = c2.a / 255.0;

		result.r = (int) (a1 * c1.r + a2 * (1 - a1) * c2.r);
		result.g = (int) (a1 * c1.g + a2 * (1 - a1) * c2.g);
		result.b = (int) (a1 * c1.b + a2 * (1 - a1) * c2.b);
		result.a = (int) (255 * (a1 + a2 * (1 - a1)));
		return result;
        }

        inline color_t ChibiGFX::RGB2Color(Gwen::Color const& color) const
        {
		return RGB2COLOR(color.r, color.g, color.b);
        }

        void ChibiGFX::DrawFilledRect( Gwen::Rect const& rect ) const
        {
		int x = GetRenderOffset().x + rect.x;
		int y = GetRenderOffset().y + rect.y;
		gdispFillArea(x, y, rect.w, rect.h, m_color);
#ifdef DEBUG_RENDERER
		std::string tmp("DrawFilledRect [X:"+Gwen::Utility::ToString(x)+" Y:"+Gwen::Utility::ToString(y)+ \
		" W:"+Gwen::Utility::ToString(rect.w)+" H:"+Gwen::Utility::ToString(rect.h)+"]\r\n");
		chprintf((BaseSequentialStream *)&SD2, tmp.c_str());	
#endif
        }

        void ChibiGFX::DrawLine(Gwen::Point const&  pos1, Gwen::Point const&  pos2) const
        {
		Gwen::Point offset = GetRenderOffset();
		const int x1 = offset.x + pos1.x;
		const int y1 = offset.y + pos1.y;
		const int x2 = offset.x + pos2.x;
		const int y2 = offset.y + pos2.y;
		gdispDrawLine(x1, y1, x2, y2, m_color);
        }

        void ChibiGFX::DrawLinedRect( Gwen::Rect const& rect ) const
        {
		const int x = GetRenderOffset().x + rect.x;
		const int y = GetRenderOffset().y + rect.y;
		gdispFillArea(x, y, rect.w, 1, m_color);
		gdispFillArea(x, y + rect.h-1, rect.w, 1, m_color);

		gdispFillArea(x, y, 1, rect.h, m_color);
		gdispFillArea(x + rect.w-1, y, 1, rect.h, m_color);
#ifdef DEBUG_RENDERER
		std::string tmp("DrawLinedRect [X:"+Gwen::Utility::ToString(x)+" Y:"+Gwen::Utility::ToString(y)+ \
		" W:"+Gwen::Utility::ToString(rect.w)+" H:"+Gwen::Utility::ToString(rect.h)+"]\r\n");
		chprintf((BaseSequentialStream *)&SD2, tmp.c_str());	
#endif
        }

        void ChibiGFX::DrawPixel( int x, int y) const
        {
		x += GetRenderOffset().x;
		y += GetRenderOffset().y;
		gdispFillArea(x, y, 1, 1, m_color);
#ifdef DEBUG_RENDERER
std::string tmp("DrawPixel [X:"+Gwen::Utility::ToString(x)+" Y:"+Gwen::Utility::ToString(y)+"]\r\n");
chprintf((BaseSequentialStream *)&SD2, tmp.c_str());	
#endif
        }

        void ChibiGFX::DrawShavedCornerRect( Gwen::Rect rect, bool bSlight ) const
        {
		// Draw INSIDE the w/h.
		rect.w -= 1;
		rect.h -= 1;
		const int x = GetRenderOffset().x + rect.x;
		const int y = GetRenderOffset().y + rect.y;
		if ( bSlight ) {
			DrawFilledRect( Gwen::Rect( x+1, y, rect.w-1, 1 ) );
			DrawFilledRect( Gwen::Rect( x+1, y + rect.h, rect.w-1, 1 ) );

			DrawFilledRect( Gwen::Rect( x, y+1, 1, rect.h-1 ) );
			DrawFilledRect( Gwen::Rect( x + rect.w, y+1, 1, rect.h-1 ) );
			return;
		}

		DrawPixel( x+1, y+1 );
		DrawPixel( x+rect.w-1, y+1 );

		DrawPixel( x+1, y+rect.h-1 );
		DrawPixel( x+rect.w-1, y+rect.h-1 );

		DrawFilledRect( Gwen::Rect( x+2, y, rect.w-3, 1 ) );
		DrawFilledRect( Gwen::Rect( x+2, y + rect.h, rect.w-3, 1 ) );

		DrawFilledRect( Gwen::Rect( x, y+2, 1, rect.h-3 ) );
		DrawFilledRect( Gwen::Rect( x + rect.w, y+2, 1, rect.h-3 ) );
        }

        void ChibiGFX::DrawMissingImage( Gwen::Rect const& pTargetRect )
		{
		SetDrawColor( Gwen::Colors::Red );
		DrawFilledRect( pTargetRect );
        }
#ifndef GWEN_NO_UNICODE
        void ChibiGFX::RenderText( Gwen::Font* pFont, Gwen::Point const&  pos, const Gwen::UnicodeString& text ) const
        {
		const int x = GetRenderOffset().x + pos.x;
		const int y = GetRenderOffset().y + pos.y;
		float fSize = pFont->size * Scale();
		gdispDrawString(x, y, Gwen::Utility::UnicodeToString(text).c_str(), m_font, m_color);
#ifdef DEBUG_RENDERER
		std::string tmp("RenderText [X:"+Gwen::Utility::ToString(x)+" Y:"+Gwen::Utility::ToString(y)+"]\r\n");
		chprintf((BaseSequentialStream *)&SD2, tmp.c_str());	
#endif
        }
	
        Gwen::Point ChibiGFX::MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString& text ) const
        {
		(void)pFont;
		Gwen::Point p;
		//p.x = pFont->size * Scale() * (float)text.length() * 0.4;
		//p.y = pFont->size * Scale();

		p.x = gdispGetStringWidth(Gwen::Utility::UnicodeToString(text).c_str(), m_font);
		p.y = gdispGetFontMetric(&fontUI2, fontHeight);
		return p;
        }
#endif
        void ChibiGFX::RenderText( Gwen::Font* pFont, Gwen::Point const&  pos, const Gwen::String& text ) const
        {
		(void)pFont;
		const int x = GetRenderOffset().x + pos.x;
		const int y = GetRenderOffset().y + pos.y;
		//float fSize = pFont->size * Scale();
		gdispDrawString(x, y, text.c_str(), m_font, m_color);
#ifdef DEBUG_RENDERER
		std::string tmp("RenderText [X:"+Gwen::Utility::ToString(x)+" Y:"+Gwen::Utility::ToString(y)+" Text: "+text+ "]\r\n");
		chprintf((BaseSequentialStream *)&SD2, tmp.c_str());	
#endif
        }

        Gwen::Point ChibiGFX::MeasureText( Gwen::Font* pFont, const Gwen::String& text ) const
        {
		(void)pFont;
		Gwen::Point p;
		//p.x = pFont->size * Scale() * (float)text.length() * 0.4;
		//p.y = pFont->size * Scale();

		p.x = gdispGetStringWidth(text.c_str(), m_font);
		p.y = gdispGetFontMetric(m_font, fontHeight);

#ifdef DEBUG_RENDERER
		std::string tmp("MeasureText [X:"+Gwen::Utility::ToString(p.x)+" Y:"+Gwen::Utility::ToString(p.y)+" Text: "+text+ "]\r\n");
		chprintf((BaseSequentialStream *)&SD2, tmp.c_str());	
#endif
		return p;
        }

        void ChibiGFX::LoadFont( Gwen::Font* font )
        {
		font->realsize = font->size * Scale();
	}

        void ChibiGFX::FreeFont( Gwen::Font* pFont )
        {
		pFont->data = NULL;
        }
        
        void ChibiGFX::DrawShape( Gwen::Rect const&  rect, const unsigned char* image ) 
        {
		for (int j=0;j<rect.h;j++) {
			for (int i=0;i<8;i++) {
				if (!(image[j] & (1 << i)))  DrawPixel( j+rect.x, i+rect.y );
			}
		}
        }
        
    }
}
