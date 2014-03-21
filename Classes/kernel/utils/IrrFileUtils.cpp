#include "IrrFileUtils.h"
#include "IrrStringUtils.h"

#if defined(WIN32)
#include <shlobj.h>
#elif defined(__APPLE__)
#include <sys/stat.h>
#endif
#include <fstream>

namespace irr_utils
{
	
	bool IrrFileUtils::GetLinesFromFile( const IrrString& fileName, IrrStringVec& outList )
	{
		std::ifstream inputFile( fileName.c_str() );
		if( inputFile.is_open() )
		{
			while (! inputFile.eof() )
			{
				IrrString line;
				getline (inputFile,line);
				outList.push_back( line );
			}
			inputFile.close();
			return true;
		}

		return false;
	}

	bool IrrFileUtils::WriteLinesToFile( const IrrString& fileName, const IrrStringVec& strings )
	{
		std::ofstream outputFile( fileName.c_str());
		if( outputFile.is_open() )
		{
			for( size_t i = 0; i < strings.size(); i++ )
			{
				outputFile << strings[i] << std::endl;
			}
			outputFile.close();
			return true;
		}
		return false;
	}


	bool IrrFileUtils::AppendLineToFile( const IrrString& fileName, const IrrString& line )
	{
		std::ofstream outputFile( fileName.c_str(), std::ios_base::app );
		if( outputFile.is_open() )
		{
			outputFile << line << std::endl;
			outputFile.close();
			return true;
		}
		return false;
	}

	bool IrrFileUtils::MakeDirectories( const IrrString& path )
	{
#if defined(WIN32)
		if (SHCreateDirectoryExA(NULL, path.c_str(), NULL) == ERROR_SUCCESS)
		{
			return true;
		}
		else
		{
			return false;
		}
#else
		char currentDir[PATH_MAX];
		getcwd(currentDir, PATH_MAX);
		chdir("/");
		bool retVal = true;

		IrrStringList elements = irr_utils::SplitString(path, "/");
		struct stat statInfo;
		IrrStringList::iterator it = elements.begin();
		IrrString pathAccum;
		while (it != elements.end())
		{
			pathAccum += *it;
			if (stat(pathAccum.c_str(), &statInfo) < 0)
			{
				//path doesn't exist
				if (mkdir(pathAccum.c_str(), S_IRWXU) != 0)
				{
					//couldn't be made
					retVal = false;
					break;
				}
			}
			if (!S_ISDIR(statInfo.st_mode))
			{
				//exists, but it's not a directory
				retVal = false;
				break;
			}

			pathAccum += "/";
			it++;
		}

		chdir(currentDir);
		return retVal;
#endif
	}

}