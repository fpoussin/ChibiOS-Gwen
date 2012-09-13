/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#include "Gwen/ToolTip.h"
#include "Gwen/Utility.h"
#include <stdio.h>

using namespace Gwen;

const int& Gwen::Utility::Max( const int& x, const int& y )
{
  if ( y < x ) return x;
  return y;
}
const unsigned int& Gwen::Utility::Max( const unsigned int& x, const unsigned int& y )
{
  if ( y < x ) return x;
  return y;
}
const float& Gwen::Utility::Max( const float& x, const float& y )
{
  if ( y < x ) return x;
  return y;
}

const int& Gwen::Utility::Min( const int& x, const int& y )
{
  if ( y > x ) return x;
  return y;
}
const unsigned int& Gwen::Utility::Min( const unsigned int& x, const unsigned int& y )
{
  if ( y > x ) return x;
  return y;
}
const float& Gwen::Utility::Min( const float& x, const float& y )
{
  if ( y > x ) return x;
  return y;
}
#ifndef GWEN_NO_UNICODE
String Gwen::Utility::UnicodeToString( const UnicodeString& strIn )
{
    if ( !strIn.length() ) return "";

    String temp(strIn.length(), (char)0);
// TODO: Clean
   std::use_facet< std::ctype<wchar_t> >(std::locale()). \
      narrow(&strIn[0], &strIn[0]+strIn.length(), ' ', &temp[0]);
//
    return temp;
}

UnicodeString Gwen::Utility::StringToUnicode( const String& strIn )
{
    if ( !strIn.length() ) return L"";

    UnicodeString temp(strIn.length(), (wchar_t)0);
// TODO: Clean
    std::use_facet< std::ctype<wchar_t> >(std::locale()). \
        widen(&strIn[0], &strIn[0]+strIn.length(), &temp[0]);
//
    return temp;
}
#endif

template<typename T> void Gwen::Utility::Replace( T& str, const T& strFind, const T& strReplace )
{
    size_t pos = 0;
    while( (pos = str.find(strFind, pos) ) != T::npos )
    {
        str.replace( pos, strFind.length(), strReplace );
        pos += strReplace.length();
    }
}

Gwen::Rect Gwen::Utility::ClampRectToRect( Gwen::Rect inside, Gwen::Rect outside, bool clampSize )
{
    if ( inside.x < outside.x )
        inside.x = outside.x;

    if ( inside.y  < outside.y )
        inside.y = outside.y;

    if ( inside.x + inside.w > outside.x + outside.w )
    {
        if ( clampSize )
            inside.w = outside.w;
        else
            inside.x = outside.x + outside.w - inside.w;
    }
    if ( inside.y + inside.h > outside.y + outside.h )
    {
        if ( clampSize )
            inside.h = outside.h;
        else
            inside.y = outside.w + outside.h - inside.h;
    }

    return inside;
}

String Gwen::Utility::ToString( int num )
{
  char buf[11];
  snprintf(buf, sizeof(buf), "%d", num);
  return String(buf);
}

String Gwen::Utility::ToString( unsigned int num )
{
  char buf[11];
  snprintf(buf, sizeof(buf), "%u", num);
  return String(buf);
}

String Gwen::Utility::ToString( float num )
{
  char buf[13];
  snprintf(buf, sizeof(buf), "%10.2f", num);
  return String(buf);
}

#ifndef GWEN_NO_UNICODE
UnicodeString Gwen::Utility::Format( const wchar_t* fmt, ... )
{
	wchar_t strOut[ 4096 ];

	va_list s;
	va_start( s, fmt ); 
	vswprintf( strOut, sizeof(strOut), fmt, s );
	va_end(s);

	UnicodeString str = strOut;
	return str;
}
#else
String Gwen::Utility::Format( const char* fmt, ... )
{
	char strOut[ 4096 ];

	va_list s;
	va_start( s, fmt ); 
	vsprintf( strOut, fmt, s );
	va_end(s);

	String str = strOut;
	return str;
}
#endif

void Gwen::Utility::Strings::Split( const Gwen::String& str, const Gwen::String& seperator, Strings::List& outbits, bool bLeave )
{
	int iOffset = 0;
	int iLength = str.length();
	int iSepLen = seperator.length();

	size_t i = str.find( seperator, 0 );
	while ( i != std::string::npos )
	{
		outbits.push_back( str.substr( iOffset, i-iOffset ) );
		iOffset = i + iSepLen;

		i = str.find( seperator, iOffset );
		if ( bLeave ) iOffset -= iSepLen;
	}

	outbits.push_back( str.substr( iOffset, iLength-iOffset ) );
}
#ifndef GWEN_NO_UNICODE
void Gwen::Utility::Strings::Split( const Gwen::UnicodeString& str, const Gwen::UnicodeString& seperator, Strings::UnicodeList& outbits, bool bLeave )
{
	int iOffset = 0;
	int iLength = str.length();
	int iSepLen = seperator.length();

	size_t i = str.find( seperator, 0 );
	while ( i != std::wstring::npos )
	{
		outbits.push_back( str.substr( iOffset, i-iOffset ) );
		iOffset = i + iSepLen;

		i = str.find( seperator, iOffset );
		if ( bLeave ) iOffset -= iSepLen;
	}

	outbits.push_back( str.substr( iOffset, iLength-iOffset ) );
}
#endif
int Gwen::Utility::Strings::To::Int( const Gwen::String& str )
{
	if ( str == "" ) return 0;
	return atoi( str.c_str() );
}

float Gwen::Utility::Strings::To::Float( const Gwen::String& str )
{
	if ( str == "" ) return 0.0f;
	return (float)atof( str.c_str() );
}
#ifndef GWEN_NO_UNICODE
float Gwen::Utility::Strings::To::Float( const Gwen::UnicodeString& str )
{
	return wcstod( str.c_str(), NULL);
}
#endif
bool Gwen::Utility::Strings::To::Bool( const Gwen::String& str )
{
	if ( str.size() == 0 ) return false;
	if ( str[0] == 'T' || str[0] == 't' || str[0] == 'y' || str[0] == 'Y' ) return true;
	if ( str[0] == 'F' || str[0] == 'f' || str[0] == 'n' || str[0] == 'N' ) return false;
	if ( str[0] == '0' ) return false;
	return true;
}

bool Gwen::Utility::Strings::To::Floats( const Gwen::String& str, float* f, size_t iCount )
{
	Strings::List lst;
	Strings::Split( str, " ", lst );
	if ( lst.size() != iCount ) return false;

	for ( size_t i=0; i<iCount; i++ )
	{
		f[i] = Strings::To::Float( lst[i] );
	}

	return true;
}

#ifndef GWEN_NO_UNICODE
bool Gwen::Utility::Strings::Wildcard( const TextObject& strWildcard, const TextObject& strHaystack )
{
	const UnicodeString& W = strWildcard.GetUnicode();
	const UnicodeString& H = strHaystack.GetUnicode();

	if ( strWildcard == "*" ) return true;

	unsigned int iPos = W.find( L"*", 0 );
	if ( iPos == UnicodeString::npos ) return strWildcard == strHaystack;

	// First half matches
	if ( iPos > 0 && W.substr( 0, iPos ) != H.substr( 0, iPos ) )
		return false;

	// Second half matches
	if ( iPos != W.length()-1 )
	{
		UnicodeString strEnd = W.substr( iPos+1, W.length() );

		if ( strEnd != H.substr( H.length() - strEnd.length(), H.length() ) )
			return false;
	}

	return true;
}

void Gwen::Utility::Strings::ToUpper( Gwen::UnicodeString& str )
{
	transform( str.begin(), str.end(), str.begin(), towupper );
}

void Gwen::Utility::Strings::Strip( Gwen::UnicodeString& str, const Gwen::UnicodeString& chars )
{
	Gwen::UnicodeString Source = str;
	str = L"";

	for ( unsigned int i =0; i<Source.length(); i++ )
	{
		if ( chars.find( Source[i] ) != Gwen::UnicodeString::npos )
			continue;

		str += Source[i];
	}
}
#else
bool Gwen::Utility::Strings::Wildcard( const TextObject& strWildcard, const TextObject& strHaystack )
{
	const String& W = strWildcard.Get();
	const String& H = strHaystack.Get();

	if ( strWildcard == "*" ) return true;

	unsigned int iPos = W.find( "*", 0 );
	if ( iPos == String::npos ) return strWildcard == strHaystack;

	// First half matches
	if ( iPos > 0 && W.substr( 0, iPos ) != H.substr( 0, iPos ) )
		return false;

	// Second half matches
	if ( iPos != W.length()-1 )
	{
		String strEnd = W.substr( iPos+1, W.length() );

		if ( strEnd != H.substr( H.length() - strEnd.length(), H.length() ) )
			return false;
	}

	return true;
}

void Gwen::Utility::Strings::ToUpper( Gwen::String& str )
{
	transform( str.begin(), str.end(), str.begin(), toupper );
}

void Gwen::Utility::Strings::Strip( Gwen::String& str, const Gwen::String& chars )
{
	Gwen::String Source = str;
	str = "";

	for ( unsigned int i =0; i<Source.length(); i++ )
	{
		if ( chars.find( Source[i] ) != Gwen::String::npos )
			continue;

		str += Source[i];
	}
}
#endif
template <typename T>
T Gwen::Utility::Strings::TrimLeft( const T& str, const T& strChars )
{
    T outstr = str;
    outstr.erase( 0, outstr.find_first_not_of( strChars ) );
    return outstr;
}



