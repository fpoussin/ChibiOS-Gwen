/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/


#include "Gwen/Gwen.h"
#include "Gwen/Controls/TextBox.h"
#include "Gwen/Skin.h"
#include "Gwen/Utility.h"
#include "Gwen/Platform.h"


using namespace Gwen;
using namespace Gwen::Controls;

#ifndef GWEN_NO_UNICODE
GWEN_CONTROL_CONSTRUCTOR( TextBoxNumeric )
{
	SetText( L"0" );
}

bool TextBoxNumeric::IsTextAllowed( const Gwen::UnicodeString& str, int iPos )
{
	const UnicodeString& strString = GetText().GetUnicode();

	if ( str.length() == 0 )
		return true;

	for (size_t i=0; i<str.length(); i++)
	{
		if ( str[i] == L'-' )
		{
			// Has to be at the start
			if ( i != 0 || iPos != 0 )
				return false;

			// Can only be one
			if ( std::count( strString.begin(), strString.end(), L'-' ) > 0 )
				return false;

			continue;
		}

		if ( str[i] == L'0' ) continue;
		if ( str[i] == L'1' ) continue;
		if ( str[i] == L'2' ) continue;
		if ( str[i] == L'3' ) continue;
		if ( str[i] == L'4' ) continue;
		if ( str[i] == L'5' ) continue;
		if ( str[i] == L'6' ) continue;
		if ( str[i] == L'7' ) continue;
		if ( str[i] == L'8' ) continue;
		if ( str[i] == L'9' ) continue;

		if ( str[i] == L'.' )
		{
			// Already a fullstop
			if ( std::count( strString.begin(), strString.end(), L'.' ) > 0 )
				return false;

			continue;
		}

		return false;
	}

	return true;
}

float TextBoxNumeric::GetFloatFromText()
{
	return Gwen::Utility::Strings::To::Float( GetText().GetUnicode() );
}
#else
GWEN_CONTROL_CONSTRUCTOR( TextBoxNumeric )
{
	SetText( "0" );
}

bool TextBoxNumeric::IsTextAllowed( const Gwen::String& str, int iPos )
{
	const String& strString = GetText().Get();

	if ( str.length() == 0 )
		return true;

	for (size_t i=0; i<str.length(); i++)
	{
		if ( str[i] == '-' )
		{
			// Has to be at the start
			if ( i != 0 || iPos != 0 )
				return false;

			// Can only be one
			if ( std::count( strString.begin(), strString.end(), '-' ) > 0 )
				return false;

			continue;
		}

		if ( str[i] == '0' ) continue;
		if ( str[i] == '1' ) continue;
		if ( str[i] == '2' ) continue;
		if ( str[i] == '3' ) continue;
		if ( str[i] == '4' ) continue;
		if ( str[i] == '5' ) continue;
		if ( str[i] == '6' ) continue;
		if ( str[i] == '7' ) continue;
		if ( str[i] == '8' ) continue;
		if ( str[i] == '9' ) continue;

		if ( str[i] == '.' )
		{
			// Already a fullstop
			if ( std::count( strString.begin(), strString.end(), '.' ) > 0 )
				return false;

			continue;
		}

		return false;
	}

	return true;
}

float TextBoxNumeric::GetFloatFromText()
{
	return Gwen::Utility::Strings::To::Float( GetText().Get() );
}	
#endif
