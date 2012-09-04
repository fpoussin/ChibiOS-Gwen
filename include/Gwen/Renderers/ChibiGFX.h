/*
	GWEN
	Copyright (c) 2011 Facepunch Studios
	See license in Gwen.h
*/

#ifndef GWEN_RENDERERS_ChibiGFX_H
#define GWEN_RENDERERS_ChibiGFX_H

#include "Gwen/Gwen.h"
#include "Gwen/BaseRender.h"


namespace Gwen 
{
	namespace Renderer 
        {

        class ChibiGFX : public Gwen::Renderer::Base
		{
            public:

                ChibiGFX();
                ~ChibiGFX();

                //The following functions are empty in Gwen::Renderer::Base and must be implemented by your custom class:
                virtual void Begin(){}
                virtual void End(){}
                virtual void SetDrawColor( Color color ){ m_color = color; }
                virtual void DrawPixel( int x, int y);
                virtual void DrawLine( int x, int y, int a, int b );
                virtual void DrawFilledRect( Rect rect );
                virtual void DrawLinedRect( Rect rect );
                virtual void DrawShavedCornerRect( Gwen::Rect rect, bool bSlight );
                virtual void StartClip(){}
                virtual void EndClip(){}

                //You can ignore these if you just want to use the simple skin (rectangle based) and don't want to draw images on the GUI
                virtual void LoadTexture( Gwen::Texture* pTexture ){}
                virtual void FreeTexture( Gwen::Texture* pTexture ){}
                virtual void DrawTexturedRect( Gwen::Texture* pTexture, Gwen::Rect pTargetRect, float u1=0.0f, float v1=0.0f, float u2=1.0f, float v2=1.0f ){}
                virtual void DrawMissingImage( Gwen::Rect pTargetRect );

                //You can also ignore these if you don't care about having text on your GUI. That would be silly though
                virtual void LoadFont( Gwen::Font* pFont ){}
                virtual void FreeFont( Gwen::Font* pFont ){}
                virtual void RenderText( Gwen::Font* pFont, Gwen::Point pos, const Gwen::UnicodeString& text );
                virtual Gwen::Point MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString& text );

             private:
                Gwen::Color m_color;
                float m_fScale;

		};

	}
}
#endif

