#ifndef _IRRTYPEDEF_H_
#define _IRRTYPEDEF_H_

#include <string>
#include <set>	
#include <map>  
#include <vector>
#include <list>

typedef int						IrrInt;
typedef unsigned int			IrrUint;
typedef short					IrrShort;
typedef unsigned short			IrrUShort;
typedef unsigned char			IrrUChar;
typedef float					IrrFloat;
typedef double					IrrDouble;
typedef long					IrrLong;
typedef std::string				IrrString;
typedef bool					IrrBool;
typedef const char*				*IrrConstChar;

typedef std::vector<IrrString>	IrrStringVec;
typedef std::list<IrrString>	IrrStringList;
typedef std::set<IrrString>		IrrStringSet;

#define INVALIDATE -1



#endif	//_IRRTYPEDEF_H_