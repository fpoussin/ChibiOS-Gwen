
#include "Gwen/Renderers/ChibiGFX.h"
#include "Gwen/Gwen.h"
#include "Gwen/Utility.h"
#include "Gwen/Platform.h"

#include <math.h>

namespace Gwen
{
    namespace Renderer
    {
        ChibiGFX::ChibiGFX()
        {
            m_fScale = 1.0f;
            gdispInit();
            gdispClear(RGB2COLOR(0,0,0));
        }

        ChibiGFX::~ChibiGFX()
        {
            if ( GetCTT() )
                GetCTT()->ShutDown();
        }
        
        void ChibiGFX::SetDrawColor( Gwen::Color const& color )
        {
          m_color.r = color.r;
          m_color.g = color.g;
          m_color.b = color.b;
          m_color.a = color.a;
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
          gdispFillArea(rect.x, rect.y, rect.w, rect.h, RGB2Color(this->m_color));
        }

        void ChibiGFX::DrawLine( int const& x, int const& y, int const& a, int const& b ) const
        {
          gdispDrawLine(x, y, a, b, RGB2Color(this->m_color));
        }

        void ChibiGFX::DrawLinedRect( Gwen::Rect const& rect ) const
        {
            DrawFilledRect( Gwen::Rect( rect.x, rect.y, rect.w, 1 ) );
            DrawFilledRect( Gwen::Rect( rect.x, rect.y + rect.h-1, rect.w, 1 ) );

            DrawFilledRect( Gwen::Rect( rect.x, rect.y, 1, rect.h ) );
            DrawFilledRect( Gwen::Rect( rect.x + rect.w-1, rect.y, 1, rect.h ) );
        }

        void ChibiGFX::DrawPixel( int const& x, int const& y ) const
        {
            DrawFilledRect( Gwen::Rect( x, y, 1, 1 ) );
        }

        void ChibiGFX::DrawShavedCornerRect( Gwen::Rect rect, bool bSlight ) const
        {
            // Draw INSIDE the w/h.
            rect.w -= 1;
            rect.h -= 1;

            if ( bSlight )
            {
                DrawFilledRect( Gwen::Rect( rect.x+1, rect.y, rect.w-1, 1 ) );
                DrawFilledRect( Gwen::Rect( rect.x+1, rect.y + rect.h, rect.w-1, 1 ) );

                DrawFilledRect( Gwen::Rect( rect.x, rect.y+1, 1, rect.h-1 ) );
                DrawFilledRect( Gwen::Rect( rect.x + rect.w, rect.y+1, 1, rect.h-1 ) );
                return;
            }

            DrawPixel( rect.x+1, rect.y+1 );
            DrawPixel( rect.x+rect.w-1, rect.y+1 );

            DrawPixel( rect.x+1, rect.y+rect.h-1 );
            DrawPixel( rect.x+rect.w-1, rect.y+rect.h-1 );

            DrawFilledRect( Gwen::Rect( rect.x+2, rect.y, rect.w-3, 1 ) );
            DrawFilledRect( Gwen::Rect( rect.x+2, rect.y + rect.h, rect.w-3, 1 ) );

            DrawFilledRect( Gwen::Rect( rect.x, rect.y+2, 1, rect.h-3 ) );
            DrawFilledRect( Gwen::Rect( rect.x + rect.w, rect.y+2, 1, rect.h-3 ) );
        }

        void ChibiGFX::DrawMissingImage( Gwen::Rect const& pTargetRect )
        {
            SetDrawColor( Gwen::Colors::Red );
            DrawFilledRect( pTargetRect );
        }

        /*
            If they haven't defined these font functions in their renderer code
            we just draw some rects where the letters would be to give them an idea.
        */

        void ChibiGFX::RenderText( Gwen::Font* pFont, Gwen::Point pos, const Gwen::UnicodeString& text )
        {
            float fSize = pFont->size * Scale();
            gdispDrawString(pos.x, pos.y, Gwen::Utility::UnicodeToString(text).c_str(), &fontUI2, RGB2Color(m_color));
        }

        Gwen::Point ChibiGFX::MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString& text )
        {
            Gwen::Point p;
            //p.x = pFont->size * Scale() * (float)text.length() * 0.4;
            //p.y = pFont->size * Scale();

            p.x = gdispGetStringWidth(Gwen::Utility::UnicodeToString(text).c_str(), &fontUI2);
            p.y = gdispGetFontMetric(&fontUI2, fontHeight);
            return p;
        }

        void ChibiGFX::LoadFont( Gwen::Font* font )
        {
            font->realsize = font->size * Scale();

            //font->data =  (void *)&OpenSans_ttf;
        }

        void ChibiGFX::FreeFont( Gwen::Font* pFont )
        {
            pFont->data = NULL;
        }

    }
}
