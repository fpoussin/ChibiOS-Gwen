/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/


#include "Gwen/Gwen.h"
#include "Gwen/BaseRender.h"
#include "Gwen/Utility.h"
#include "Gwen/Platform.h"

#include <math.h>

namespace Gwen
{
	namespace Renderer
	{

		Base::Base()
		{
			m_RenderOffset = Gwen::Point( 0, 0 );
			m_fScale = 1.0f;
		}

		Base::~Base()
		{
			if ( GetCTT() )
				GetCTT()->ShutDown();
		}

		void Base::RenderText( Gwen::Font* pFont, Gwen::Point pos, const Gwen::String& text ) const
		{

		}

		Gwen::Point Base::MeasureText( Gwen::Font* pFont, const Gwen::String& text ) const
		{
			Gwen::Point p;
			p.x = pFont->size * Scale() * (float)text.length() * 0.4;
			p.y = pFont->size * Scale();

			return p;
		}
				
        void Base::DrawLinedRect( Gwen::Rect const& rect ) const
		{
			DrawFilledRect( Gwen::Rect( rect.x, rect.y, rect.w, 1 ) );
			DrawFilledRect( Gwen::Rect( rect.x, rect.y + rect.h-1, rect.w, 1 ) );

			DrawFilledRect( Gwen::Rect( rect.x, rect.y, 1, rect.h ) );
			DrawFilledRect( Gwen::Rect( rect.x + rect.w-1, rect.y, 1, rect.h ) );
		};

        void Base::DrawPixel( int x, int y) const
		{
			DrawFilledRect( Gwen::Rect( x, y, 1, 1 ) );
		}

        void Base::DrawShavedCornerRect( Gwen::Rect rect, bool bSlight ) const
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

		void Base::Translate( int& x, int& y )
		{
			x += m_RenderOffset.x;
			y += m_RenderOffset.y;

			x = ceil( ((float) x ) * m_fScale );
			y = ceil( ((float) y ) * m_fScale );
		}

		void Base::Translate( Gwen::Rect& rect )
		{
			Translate( rect.x, rect.y );

			rect.w = ceil(((float) rect.w ) * m_fScale);
			rect.h = ceil(((float) rect.h ) * m_fScale);
		}

		void Gwen::Renderer::Base::SetClipRegion( Gwen::Rect const& rect )
		{ 
			m_rectClipRegion = rect; 
		}

		void Base::AddClipRegion( Gwen::Rect rect ) 
		{ 
			rect.x = m_RenderOffset.x;
			rect.y = m_RenderOffset.y;

			Gwen::Rect out = rect;
			if ( rect.x < m_rectClipRegion.x )
			{
				out.w -= ( m_rectClipRegion.x - out.x );
				out.x = m_rectClipRegion.x;
			}

			if ( rect.y < m_rectClipRegion.y )
			{
				out.h -= ( m_rectClipRegion.y - out.y );
				out.y = m_rectClipRegion.y;
			}

			if ( rect.x + rect.w > m_rectClipRegion.x + m_rectClipRegion.w )
			{
				out.w = (m_rectClipRegion.x + m_rectClipRegion.w) - out.x;
			}

			if ( rect.y + rect.h > m_rectClipRegion.y + m_rectClipRegion.h )
			{
				out.h = (m_rectClipRegion.y + m_rectClipRegion.h) - out.y;
			}

			m_rectClipRegion = out;
		}

		const Gwen::Rect& Base::ClipRegion() const
		{ 
			return m_rectClipRegion; 
		}

		bool Base::ClipRegionVisible()
		{
			if ( m_rectClipRegion.w <= 0 || m_rectClipRegion.h <= 0 )
				return false;
			
			return true;
		}

		void Base::DrawMissingImage( Gwen::Rect pTargetRect )
		{
			SetDrawColor( Colors::Red );
			DrawFilledRect( pTargetRect );
		}

		
		/*
			If they haven't defined these font functions in their renderer code
			we just draw some rects where the letters would be to give them an idea.
		*/
#ifndef GWEN_NO_UNICODE
		void Base::RenderText( Gwen::Font* pFont, Gwen::Point pos, const Gwen::UnicodeString& text ) const
		{

		}

		Gwen::Point Base::MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString& text ) const
		{
			Gwen::Point p;
			p.x = pFont->size * Scale() * (float)text.length() * 0.4;
			p.y = pFont->size * Scale();

			return p;
		}
#endif
	}
}

