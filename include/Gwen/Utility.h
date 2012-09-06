/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_UTILITY_H
#define GWEN_UTILITY_H

#include <sstream>
#include <string>
#include "hacks.h"
#include <vector>
#include "Gwen/Structures.h"

namespace Gwen
{
	class TextObject;

	namespace Utility
	{
		template <typename T>
        const T& Max( const T& x, const T& y );
        template <typename T>
        const T& Min( const T& x, const T& y );

        String UnicodeToString( const UnicodeString& strIn );
        UnicodeString StringToUnicode( const String& strIn );
        template<typename T> void Replace( T& str, const T& strFind, const T& strReplace );
        template <class T> String ToString( const T& object );

        Gwen::Rect ClampRectToRect( Gwen::Rect inside, Gwen::Rect outside, bool clampSize = false );

		GWEN_EXPORT UnicodeString Format( const wchar_t* fmt, ... );

		namespace Strings
		{
			typedef std::vector<Gwen::String> List;
			typedef std::vector<Gwen::UnicodeString> UnicodeList;

			GWEN_EXPORT void Split( const Gwen::String& str, const Gwen::String& seperator, Strings::List& outbits, bool bLeaveSeperators = false );
			GWEN_EXPORT void Split( const Gwen::UnicodeString& str, const Gwen::UnicodeString& seperator, Strings::UnicodeList& outbits, bool bLeaveSeperators = false );
			GWEN_EXPORT bool Wildcard( const Gwen::TextObject& strWildcard, const Gwen::TextObject& strHaystack );

			GWEN_EXPORT void ToUpper( Gwen::UnicodeString& str );
			GWEN_EXPORT void Strip( Gwen::UnicodeString& str, const Gwen::UnicodeString& chars );

			template <typename T>
            T TrimLeft( const T& str, const T& strChars );

			namespace To
			{
				GWEN_EXPORT bool Bool( const Gwen::String& str );
				GWEN_EXPORT int Int( const Gwen::String& str );
				GWEN_EXPORT float Float( const Gwen::String& str );
				GWEN_EXPORT float Float( const Gwen::UnicodeString& str );
				GWEN_EXPORT bool Floats( const Gwen::String& str, float* f, size_t iCount );
			}
		}
	}



}
#endif

