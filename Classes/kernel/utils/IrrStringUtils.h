#ifndef _IRRSTRINGUTILS_H
#define _IRRSTRINGUTILS_H

#include "IrrMarcos.h"
#include "IrrTypeDef.h"

namespace irr_utils
{
	class IrrStringUtils
	{
	public:
		static int StringToInt( const IrrString& s );

		static unsigned int StringToUInt(const IrrString& s);

		static char StringToChar(const IrrString& s);

		static unsigned char StringToUChar(const IrrString& s);

		static long StringToLong(const IrrString& s);

		static float StringToFloat( const IrrString& s );

		static bool StringToBool( const IrrString& s );

		static double StringToDouble(const IrrString& s);

		static IrrString IntToString( int val );

		static IrrString UIntToString(unsigned int val);

		static IrrString CharToString(char val);

		static IrrString UCharToString(unsigned char val);

		static IrrString FloatToString( float val );

		static IrrString DoubleToString( double val);

		static IrrString LongToString(long val);

		static IrrString BoolToString( bool val );

		static IrrString ToUpper( const IrrString& s );

		static IrrString ToLower( const IrrString& s );

		static IrrStringVec SplitString( const IrrString& splitMe, const IrrString& splitChars, bool bRemoveEmptyEntries = true );

		static IrrStringVec SplitString( const IrrString& splitMe );

		static IrrString TrimString( const IrrString& trimMe, const IrrString& trimChars );

		static IrrString TrimString( const IrrString& trimMe );
	};
	
}

#endif	//_IRRSTRINGUTILS_H