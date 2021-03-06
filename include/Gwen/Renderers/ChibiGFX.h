/*
	GWEN
	Copyright (c) 2011 Facepunch Studios
	See license in Gwen.h
*/

#ifndef GWEN_RENDERERS_ChibiGFX_H
#define GWEN_RENDERERS_ChibiGFX_H

#include "Gwen/Gwen.h"
#include "Gwen/BaseRender.h"

extern "C" {
    #include "ch.h"
    #include "hal.h"
    #include "gdisp_connector.h"
}

namespace Gwen 
{
	namespace Renderer 
        {

        class ChibiGFX : public Gwen::Renderer::Base
		{
            public:

                ChibiGFX();
                ~ChibiGFX();

                inline Gwen::Color BlendColor(Gwen::Color const& c1, Gwen::Color const& c2) const;
                inline color_t RGB2Color(Gwen::Color const& color) const;
                uint16_t getHeight() const { return gdispGetHeight(); }
                uint16_t getWidth() const { return gdispGetWidth(); }

                //The following functions are empty in Gwen::Renderer::Base and must be implemented by your custom class:
                virtual void Begin(){}
                virtual void End(){}
                virtual void SetDrawColor( Gwen::Color const& color );
                virtual void DrawPixel( int x, int y) const;
                virtual void DrawLine(Gwen::Point const&  pos1, Gwen::Point const&  pos2) const;
                virtual void DrawFilledRect( Gwen::Rect const& rect ) const;
                virtual void DrawLinedRect( Gwen::Rect const& rect ) const;
                virtual void DrawShavedCornerRect( Gwen::Rect rect, bool bSlight = false ) const;
                virtual void StartClip(){}
                virtual void EndClip(){}

                //You can ignore these if you just want to use the simple skin (rectangle based) and don't want to draw images on the GUI
                virtual void LoadTexture( Gwen::Texture* pTexture ){ (void)pTexture; }
                virtual void FreeTexture( Gwen::Texture* pTexture ){ (void)pTexture; }
                virtual void DrawTexturedRect( Gwen::Texture* pTexture, Gwen::Rect const&  pTargetRect, float u1=0.0f, float v1=0.0f, float u2=1.0f, float v2=1.0f ){
			(void)pTexture; (void)pTargetRect; (void)u1; (void)v1; (void)u2; (void)v2;}
                virtual void DrawMissingImage( Gwen::Rect const& pTargetRect );
                virtual void DrawShape( Gwen::Rect const&  rect, const unsigned char* image ) ;

                //You can also ignore these if you don't care about having text on your GUI. That would be silly though
                virtual void LoadFont( Gwen::Font* pFont );
                virtual void FreeFont( Gwen::Font* pFont );
#ifndef GWEN_NO_UNICODE
                virtual void RenderText( Gwen::Font* pFont, Gwen::Point const&  pos, const Gwen::UnicodeString& text ) const;
                virtual Gwen::Point MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString& text ) const;
#endif
                virtual void RenderText( Gwen::Font* pFont, Gwen::Point const&  pos, const Gwen::String& text ) const;
                virtual Gwen::Point MeasureText( Gwen::Font* pFont, const Gwen::String& text ) const;

            private:
                color_t m_color;
                float m_fScale;
		font_t m_font;
		};

	}
}
#endif

