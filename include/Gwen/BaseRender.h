/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_BASERENDER_H
#define GWEN_BASERENDER_H

#include "Gwen/Structures.h"

namespace Gwen 
{
	struct Font;
	struct Texture;
	class WindowProvider;
	
	namespace Renderer
	{
		class Base;

		class ICacheToTexture
		{
			public:

				virtual ~ICacheToTexture() {}
				virtual void Initialize() = 0;
				virtual void ShutDown() = 0;
				virtual void SetupCacheTexture( Gwen::Controls::Base* control ) = 0;
				virtual void FinishCacheTexture( Gwen::Controls::Base* control ) = 0;
				virtual void DrawCachedControlTexture( Gwen::Controls::Base* control ) = 0;
				virtual void CreateControlCacheTexture( Gwen::Controls::Base* control ) = 0;
				virtual void UpdateControlCacheTexture( Gwen::Controls::Base* control ) = 0;
				virtual void SetRenderer( Gwen::Renderer::Base* renderer ) = 0;

		};

		class  Base
		{
			public:

				Base();
				virtual ~Base();

				virtual void Init(){};

				virtual void Begin(){};
				virtual void End(){};

         virtual void SetDrawColor( Color const& color ){};

        virtual void DrawFilledRect( Gwen::Rect const& rect ) const{};
        virtual void DrawLine(Gwen::Point const&  pos1, Gwen::Point const&  pos2) const{};

				virtual void StartClip(){};
				virtual void EndClip(){};

				virtual void LoadTexture( Gwen::Texture* pTexture ){ (void*) pTexture; };
				virtual void FreeTexture( Gwen::Texture* pTexture ){ (void*) pTexture; };
				virtual void DrawTexturedRect( Gwen::Texture* pTexture, Gwen::Rect pTargetRect, float u1=0.0f, float v1=0.0f, float u2=1.0f, float v2=1.0f ){ (void*) pTexture; };
				virtual void DrawMissingImage( Gwen::Rect pTargetRect );
        virtual void DrawBlackImage( Gwen::Rect const&  rect, const unsigned char* image ) {};
				virtual Gwen::Color PixelColour( Gwen::Texture* pTexture, unsigned int x, unsigned int y, const Gwen::Color& col_default = Gwen::Color( 255, 255, 255, 255 ) ){ return col_default; }

				virtual ICacheToTexture* GetCTT() { return NULL; }

				virtual void LoadFont( Gwen::Font* pFont ){ (void*) pFont; };
				virtual void FreeFont( Gwen::Font* pFont ){ (void*) pFont; };
#ifndef GWEN_NO_UNICODE
				virtual void RenderText( Gwen::Font* pFont, Gwen::Point const& pos, const Gwen::UnicodeString& text ) const;
				virtual Gwen::Point MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString& text ) const;
#endif
				//
				// No need to implement these functions in your derived class, but if 
				// you can do them faster than the default implementation it's a good idea to.
				//
        virtual void DrawLinedRect( Gwen::Rect const& rect ) const;
        virtual void DrawPixel( int x, int y) const;
        virtual void DrawShavedCornerRect( Gwen::Rect rect, bool bSlight = false ) const;
				virtual Gwen::Point MeasureText( Gwen::Font* pFont, const Gwen::String& text ) const;
				virtual void RenderText( Gwen::Font* pFont, Gwen::Point const& pos, const Gwen::String& text ) const;

			public:

				//
				// Translate a panel's local drawing coordinate
				//  into view space, taking Offset's into account.
				//
				void Translate( int& x, int& y );
				void Translate( Gwen::Rect& rect );

				//
				// Set the rendering offset. You shouldn't have to 
				// touch these, ever.
				//
				void SetRenderOffset( const Gwen::Point& offset ){ m_RenderOffset = offset; }
				void AddRenderOffset( const Gwen::Rect& offset ){ m_RenderOffset.x += offset.x; m_RenderOffset.y += offset.y; }
				const Gwen::Point& GetRenderOffset() const { return m_RenderOffset; }

			private:

				Gwen::Point m_RenderOffset;

			public:

				void SetClipRegion( Gwen::Rect const& rect );
				void AddClipRegion( Gwen::Rect rect );
				bool ClipRegionVisible();
				const Gwen::Rect& ClipRegion() const;

			private:

				Gwen::Rect m_rectClipRegion;
				ICacheToTexture* m_RTT;

			public:
				
        void SetScale( float const&  fScale ){ m_fScale = fScale; }
				float Scale() const { return m_fScale; }

				float m_fScale;


			public:

				//
				// Self Initialization, shutdown
				//

				virtual bool InitializeContext( Gwen::WindowProvider* pWindow ){ return false; }
				virtual bool ShutdownContext( Gwen::WindowProvider* pWindow ){ return false; }
				virtual bool ResizedContext( Gwen::WindowProvider* pWindow, int w, int h ){ return false; }

				virtual bool BeginContext( Gwen::WindowProvider* pWindow){ return false; }
				virtual bool EndContext( Gwen::WindowProvider* pWindow ){ return false; }
				virtual bool PresentContext( Gwen::WindowProvider* pWindow ){ return false; }



		};
	}
}
#endif

