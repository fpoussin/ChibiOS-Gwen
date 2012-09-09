/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_CONTROLS_TEXTBOX_H
#define GWEN_CONTROLS_TEXTOBX_H

#include "Gwen/BaseRender.h"
#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/ScrollControl.h"

namespace Gwen 
{
	namespace Controls
	{
		class  TextBox : public Label
		{
			GWEN_CONTROL( TextBox, Label );

				virtual void Render( Skin::Base* skin );
				virtual void RenderFocus( Gwen::Skin::Base* /*skin*/){};
				virtual void Layout( Skin::Base* skin );

				#ifndef GWEN_NO_ANIMATION
				virtual void UpdateCaretColor();
				#endif
#ifndef GWEN_NO_UNICODE
				virtual bool OnChar( Gwen::UnicodeChar c );
				virtual void InsertText( const Gwen::UnicodeString& str );
#else					
				virtual bool OnChar( char c );
				virtual void InsertText( const Gwen::String& str );
#endif					
				virtual void DeleteText( int iStartPos, int iLength );

				virtual void RefreshCursorBounds();

				virtual bool OnKeyReturn( bool bDown );
				virtual bool OnKeyBackspace( bool bDown );
				virtual bool OnKeyDelete( bool bDown );
				virtual bool OnKeyRight( bool bDown );
				virtual bool OnKeyLeft( bool bDown );
				virtual bool OnKeyHome( bool bDown );
				virtual bool OnKeyEnd( bool bDown );

				virtual bool AccelOnlyFocus() { return true; }

				virtual void OnPaste( Gwen::Controls::Base* pCtrl );
				virtual void OnCopy( Gwen::Controls::Base* pCtrl );
				virtual void OnCut( Gwen::Controls::Base* pCtrl );
				virtual void OnSelectAll( Gwen::Controls::Base* pCtrl );

				virtual void OnMouseDoubleClickLeft( int x, int y );

				virtual void EraseSelection();
				virtual bool HasSelection();
#ifndef GWEN_NO_UNICODE
				virtual UnicodeString GetSelection();
#else
				virtual String GetSelection();
#endif
				virtual void SetCursorPos( int i );
				virtual void SetCursorEnd( int i );

				virtual void OnMouseClickLeft( int x, int y, bool bDown );
				virtual void OnMouseMoved( int x, int y, int deltaX, int deltaY );

				virtual void SetSelectAllOnFocus( bool b ){ m_bSelectAll = b; if ( b ) OnSelectAll( this ); }

				virtual void MakeCaratVisible();

				virtual void OnEnter();

				virtual bool NeedsInputChars(){ return true; }

				virtual void MoveCaretToEnd();
				virtual void MoveCaretToStart();

				Event::Caller	onTextChanged;
				Event::Caller	onReturnPressed;

			protected:

				virtual void OnTextChanged();
#ifndef GWEN_NO_UNICODE
				virtual bool IsTextAllowed( const Gwen::UnicodeString& /*str*/, int /*iPos*/ ){ return true; }
#else
				virtual bool IsTextAllowed( const Gwen::String& /*str*/, int /*iPos*/ ){ return true; }
#endif
				bool m_bSelectAll;

				int m_iCursorPos;
				int m_iCursorEnd;
				int m_iCursorLine;
				
				Gwen::Rect m_rectSelectionBounds;
				Gwen::Rect m_rectCaretBounds;

				float m_fNextCaretColorChange;
				Gwen::Color	m_CaretColor;
		};

		class  TextBoxNumeric : public TextBox
		{
			public:

				GWEN_CONTROL( TextBoxNumeric, TextBox );

				virtual float GetFloatFromText();

			private:
#ifndef GWEN_NO_UNICODE
				virtual bool IsTextAllowed( const Gwen::UnicodeString& str, int iPos );
#else
				virtual bool IsTextAllowed( const Gwen::String& str, int iPos );
#endif		
		};

		class  TextBoxMultiline : public TextBox
		{
			public:

				GWEN_CONTROL( TextBoxMultiline, TextBox );

				virtual bool OnKeyReturn( bool bDown );
				virtual void MakeCaratVisible();

				virtual bool OnKeyHome( bool bDown );
				virtual bool OnKeyEnd( bool bDown );
				virtual bool OnKeyUp( bool bDown );
				virtual bool OnKeyDown( bool bDown );

				virtual int GetCurrentLine();

			protected:

		};
	}
}
#endif

