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
        template<typename T> 
        const T& Max( const T& x, const T& y ) {  
          if ( y < x ) return x;
          return y;
        };
        
        template<typename T> 
        const T& Min( const T& x, const T& y ) {
          if ( y > x ) return x;
          return y;
        };

#ifndef GWEN_NO_UNICODE
        String UnicodeToString( const UnicodeString& strIn );
        UnicodeString StringToUnicode( const String& strIn );
#endif
        template<typename T> 
        void Replace( T& str, const T& strFind, const T& strReplace )
        {
    size_t pos = 0;
    while( (pos = str.find(strFind, pos) ) != T::npos )
    {
        str.replace( pos, strFind.length(), strReplace );
        pos += strReplace.length();
    }
};
    
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
			T TrimLeft( const T& str, const T& strChars )
      {
          T outstr = str;
          outstr.erase( 0, outstr.find_first_not_of( strChars ) );
          return outstr;
      };

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

