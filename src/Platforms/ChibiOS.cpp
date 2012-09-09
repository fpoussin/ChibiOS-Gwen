/*
	GWEN
	Copyright (c) 2012 Facepunch Studios
	See license in Gwen.h
*/

#include "Gwen/Macros.h"
#include "Gwen/Platform.h"

#include "ch.h"
#include "hal.h"
#include "gdisp_connector.h"



void Gwen::Platform::Sleep( unsigned int iMS )
{
	chThdSleepMilliseconds(iMS);
}

void Gwen::Platform::SetCursor( unsigned char iCursor )
{
	// No platform independent way to do this
}
#ifndef GWEN_NO_UNICODE
static Gwen::UnicodeString gs_ClipboardEmulator;

Gwen::UnicodeString Gwen::Platform::GetClipboardText()
{
	return gs_ClipboardEmulator;
}

bool Gwen::Platform::SetClipboardText( const Gwen::UnicodeString& str )
{
	gs_ClipboardEmulator = str;
	return true;
}
#else
static Gwen::String gs_ClipboardEmulator;

Gwen::String Gwen::Platform::GetClipboardText()
{
	return gs_ClipboardEmulator;
}

bool Gwen::Platform::SetClipboardText( const Gwen::String& str )
{
	gs_ClipboardEmulator = str;
	return true;
}
#endif

float Gwen::Platform::GetTimeInSeconds()
{
	return ((float)halGetCounterValue() / (float)halGetCounterFrequency());
}

bool Gwen::Platform::FileOpen( const String& Name, const String& StartPath, const String& Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback )
{
	// No platform independent way to do this.
	// Ideally you would open a system dialog here

	return false;
}

bool Gwen::Platform::FileSave( const String& Name, const String& StartPath, const String& Extension, Gwen::Event::Handler* pHandler, Gwen::Event::Handler::FunctionWithInformation fnCallback )
{
	// No platform independent way to do this.
	// Ideally you would open a system dialog here

	return false;
}

bool Gwen::Platform::FolderOpen( const String& Name, const String& StartPath, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback )
{
	return false;
}

void* Gwen::Platform::CreatePlatformWindow( int x, int y, int w, int h, const Gwen::String& strWindowTitle )
{
	
}

void Gwen::Platform::DestroyPlatformWindow( void* pPtr )
{
	
}

void Gwen::Platform::MessagePump( void* pWindow, Gwen::Controls::Canvas* ptarget )
{
	
}

void Gwen::Platform::SetBoundsPlatformWindow( void* pPtr, int x, int y, int w, int h )
{
	
}

void Gwen::Platform::SetWindowMaximized( void* pPtr, bool bMax, Gwen::Point& pNewPos, Gwen::Point& pNewSize )
{

}

void Gwen::Platform::SetWindowMinimized( void* pPtr, bool bMinimized )
{

}

bool Gwen::Platform::HasFocusPlatformWindow( void* pPtr )
{
	return true;
}

void Gwen::Platform::GetDesktopSize( int& w, int &h )
{
	w = gdispGetWidth();
	h = gdispGetHeight();
}

void Gwen::Platform::GetCursorPos( Gwen::Point &po )
{

}

