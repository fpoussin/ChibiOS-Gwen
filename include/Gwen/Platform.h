/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#ifndef GWEN_PLATFORM_H
#define GWEN_PLATFORM_H

#include "Gwen/Structures.h"
#include "Gwen/Events.h"

namespace Gwen
{
	namespace Platform
	{
		//
		// Do nothing for this many milliseconds
		//
		 void Sleep( unsigned int iMS );

		//
		// Set the system cursor to iCursor
		// Cursors are defined in Structures.h
		//
		 void SetCursor( unsigned char iCursor );

		//
		//
		//
		 void GetCursorPos( Gwen::Point &p );
		 void GetDesktopSize( int& w, int &h );

		//
		// Used by copy/paste
		//
#ifndef GWEN_NO_UNICODE
		 UnicodeString GetClipboardText();
		 bool SetClipboardText( const UnicodeString& str );
#else
		String GetClipboardText();
		bool SetClipboardText( const String& str );
#endif
		//
		// Needed for things like double click
		//
		 float GetTimeInSeconds();

		//
		// System Dialogs ( Can return false if unhandled )
		//
		 bool FileOpen( const String& Name, const String& StartPath, const String& Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback );
		 bool FileSave( const String& Name, const String& StartPath, const String& Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback );
		 bool FolderOpen( const String& Name, const String& StartPath, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback );
		

		//
		// Window Creation
		//
		 void* CreatePlatformWindow( int x, int y, int w, int h, const Gwen::String& strWindowTitle );
		 void DestroyPlatformWindow( void* pPtr );
		 void SetBoundsPlatformWindow( void* pPtr, int x, int y, int w, int h );
		 void MessagePump( void* pWindow, Gwen::Controls::Canvas* ptarget );
		 bool HasFocusPlatformWindow( void* pPtr );
		 void SetWindowMaximized( void* pPtr, bool bMaximized, Gwen::Point& pNewPos, Gwen::Point& pNewSize );
		 void SetWindowMinimized( void* pPtr, bool bMinimized );
	}

}
#endif

