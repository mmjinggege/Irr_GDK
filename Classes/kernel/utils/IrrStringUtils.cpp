#include "IrrStringUtils.h"

#include <sstream>
#include <algorithm>
#include <cctype>

#ifdef WIN32
#define ci_strcmp _stricmp
#endif
#if defined(__APPLE__)
#define ci_strcmp strcasecmp
#endif

const char StringUtil_WhiteSpaceChars[] = " \t\n\r";

namespace irr_utils
{

	template <class T>
	bool from_string(T& t, const IrrString& s, std::ios_base& (*f)(std::ios_base&))
	{
		std::istringstream iss(s);
		return !(iss >> f >> t).fail();
	}

	template <class T>
	IrrString to_string(T& t, std::ios_base& (*f)(std::ios_base&))
	{
		std::stringstream ss;
		ss << f << t;
		return ss.str();
	}


	int IrrStringUtils::StringToInt( const IrrString& s )
	{
		int retVal = 0;
		from_string<int>( retVal, s, std::dec );
		return retVal;
	}


	unsigned int IrrStringUtils::StringToUInt( const IrrString& s )
	{
		unsigned int retVal = StringToInt(s);
		return retVal;
	}


	char IrrStringUtils::StringToChar( const IrrString& s )
	{
		char retVal = 0;
		from_string<char>( retVal, s, std::dec );
		return retVal;
	}


	unsigned char IrrStringUtils::StringToUChar( const IrrString& s )
	{
		unsigned char retVal = StringToChar(s);
		return retVal;
	}


	long IrrStringUtils::StringToLong( const IrrString& s )
	{
		long retVal = 0;
		from_string<long>( retVal,s,std::dec);
		return retVal;
	}


	float IrrStringUtils::StringToFloat( const IrrString& s )
	{
		float retVal = 0.0f;
		from_string<float>( retVal,s,std::dec);
		return retVal;
	}

	double IrrStringUtils::StringToDouble( const IrrString& s )
	{
		double retVal = 0;
		from_string<double>( retVal,s,std::dec);
		return retVal;
	}
	

	bool IrrStringUtils::StringToBool( const IrrString& s )
	{
		if( !ci_strcmp( s.c_str(), "true") )
			return true;
		else if( !ci_strcmp(s.c_str(), "false") )
			return false;
		return StringToInt(s) != 0;
	}


	IrrString IrrStringUtils::IntToString( int val )
	{
		return to_string( val, std::dec );
	}


	IrrString IrrStringUtils::UIntToString( unsigned int val )
	{
		return to_string( val, std::dec );
	}

	IrrString IrrStringUtils::CharToString( char val )
	{
		return to_string( val, std::dec );
	}

	IrrString IrrStringUtils::UCharToString( unsigned char val )
	{
		return to_string( val, std::dec );
	}


	IrrString IrrStringUtils::FloatToString( float val )
	{
		return to_string(val,std::dec);
	}


	IrrString IrrStringUtils::DoubleToString( double val )
	{
		return to_string(val,std::dec);
	}

	IrrString IrrStringUtils::LongToString( long val )
	{
		return to_string(val,std::dec);
	}
	
	IrrString IrrStringUtils::BoolToString( bool val )
	{
		return IntToString( val );
	}

	IrrString IrrStringUtils::ToUpper( const IrrString& s )
	{
		IrrString retVal = s;
		std::transform(retVal.begin(), retVal.end(), retVal.begin(),(int(*)(int)) std::toupper);
		return retVal;
	}

	IrrString IrrStringUtils::ToLower( const IrrString& s )
	{
		IrrString retVal = s;
		std::transform(retVal.begin(), retVal.end(), retVal.begin(),(int(*)(int)) std::tolower);
		return retVal;
	}

	IrrStringVec IrrStringUtils::SplitString( const IrrString& splitMe, const IrrString& splitChars, bool bRemoveEmptyEntries /*= true */ )
	{
		IrrStringVec retVal;
		IrrString buildString;
		for ( size_t i = 0; i < splitMe.length(); i++ )
		{
			char ch = splitMe[i];
			if( splitChars.find( ch ) != IrrString::npos)
			{
				if( !bRemoveEmptyEntries || buildString.length() > 0 )
					retVal.push_back( buildString );
				buildString.clear();
			}
			else
			{
				buildString += ch;
			}
		}
		if( buildString.length() > 0 )
			retVal.push_back( buildString );
		return retVal;
	}


	IrrStringVec IrrStringUtils::SplitString( const IrrString& splitMe )
	{
		return SplitString( splitMe, StringUtil_WhiteSpaceChars );
	}


	IrrString IrrStringUtils::TrimString( const IrrString& trimMe, const IrrString& trimChars )
	{
		IrrString retVal;

		if( trimChars.length() == 0 )
			return retVal;

		int trimStart = -1;
		for( size_t i = 0; i < trimMe.length(); i++ )
		{
			char ch = trimMe[i];
			if( trimChars.find(ch) == IrrString::npos)
			{
				trimStart = i;
				break;
			}
		}

		if( trimStart >= 0 && trimStart < ((int)trimMe.length()) )
		{
			for( int i = (int)trimMe.length()-1; i >= 0; i-- )
			{
				char ch = trimMe[i];
				if( trimChars.find(ch) == IrrString::npos )
				{
					retVal = trimMe.substr( trimStart, i - trimStart + 1);
					break;
				}
			}
		}

		return retVal;
	}


	IrrString IrrStringUtils::TrimString( const IrrString& trimMe )
	{
		return TrimString( trimMe, StringUtil_WhiteSpaceChars );
	}


}
