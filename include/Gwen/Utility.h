/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#ifndef GWEN_UTILITY_H
#define GWEN_UTILITY_H

#include <sstream>
#include <string>
#include <vector>
#include "Gwen/Structures.h"

namespace Gwen
{
	class TextObject;

	namespace Utility
	{
        const int& Max( const int& x, const int& y );
	const unsigned int& Max( const unsigned int& x, const unsigned int& y );
	const float& Max( const float& x, const float& y );
		
        const int& Min( const int& x, const int& y );
	const unsigned int& Min( const unsigned int& x, const unsigned int& y );
	const float& Min( const float& x, const float& y );

#ifndef GWEN_NO_UNICODE
        String UnicodeToString( const UnicodeString& strIn );
        UnicodeString StringToUnicode( const String& strIn );
#endif
        template<typename T> 
        void Replace( T& str, const T& strFind, const T& strReplace );
    
        String ToString( int num );
        String ToString( unsigned int num );
        String ToString( float num );

        Gwen::Rect ClampRectToRect( Gwen::Rect inside, Gwen::Rect outside, bool clampSize = false );
#ifndef GWEN_NO_UNICODE	
		UnicodeString Format( const wchar_t* fmt, ... );
#endif
		String Format( const char* fmt, ... );

		namespace Strings
		{
#ifndef GWEN_NO_UNICODE	
			typedef std::vector<Gwen::UnicodeString> UnicodeList;
			void Split( const Gwen::UnicodeString& str, const Gwen::UnicodeString& seperator, Strings::UnicodeList& outbits, bool bLeaveSeperators = false );
			void ToUpper( Gwen::UnicodeString& str );
			void Strip( Gwen::UnicodeString& str, const Gwen::UnicodeString& chars );
#endif
			typedef std::vector<Gwen::String> List;
			void Split( const Gwen::String& str, const Gwen::String& seperator, Strings::List& outbits, bool bLeaveSeperators = false );
			void ToUpper( Gwen::String& str );
			void Strip( Gwen::String& str, const Gwen::String& chars );
			
			bool Wildcard( const Gwen::TextObject& strWildcard, const Gwen::TextObject& strHaystack );


			template <typename T>
			T TrimLeft( const T& str, const T& strChars );

			namespace To
			{
				bool Bool( const Gwen::String& str );
				int Int( const Gwen::String& str );
				float Float( const Gwen::String& str );
#ifndef GWEN_NO_UNICODE	
				float Float( const Gwen::UnicodeString& str );
#endif		
				bool Floats( const Gwen::String& str, float* f, size_t iCount );
			}
		}
	}



}
#endif

