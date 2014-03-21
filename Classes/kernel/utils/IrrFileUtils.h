#ifndef _IRRFILEUTILS_H_
#define _IRRFILEUTILS_H_

#include "IrrTypeDef.h"

namespace irr_utils
{
	class IrrFileUtils
	{
	public:
		static bool GetLinesFromFile(const IrrString& fileName, IrrStringVec& outList );

		static bool WriteLinesToFile( const IrrString& fileName, const IrrStringVec& strings );

		static bool AppendLineToFile( const IrrString& fileName, const IrrString& line );

		static bool MakeDirectories( const IrrString& path );
	};
}

#endif	//_IRRFILEUTILS_H_